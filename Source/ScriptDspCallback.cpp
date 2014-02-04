#include "ScriptDspCallback.h"

ScriptDspCallback::ScriptDspCallback()
{
}

ScriptDspCallback::~ScriptDspCallback()
{
}

void ScriptDspCallback::Register(v8::Handle<v8::ObjectTemplate> global)
{
}

void ScriptDspCallback::BeginAudio()
{
	audio.initialise(0, 2, nullptr, true);
	audio.addAudioCallback(this);

	juce::AudioDeviceManager::AudioDeviceSetup setup;
	audio.getAudioDeviceSetup(setup);
}

void ScriptDspCallback::audioDeviceIOCallback (
	const float** inputChannelData,
    int numInputChannels,
    float** outputChannelData,
    int numOutputChannels,
    int numSamples)
{
	auto isolate = v8::Isolate::GetCurrent();
	v8::Locker locker(isolate);
	v8::Isolate::Scope isolateScope(isolate);
	auto context = isolate->GetCurrentContext();
	v8::HandleScope scope(isolate);
	auto globalObject = context->Global();

	auto callback = v8::Handle<v8::Function>::Cast(globalObject->Get(v8::String::New("audioCallback")));
	auto outputs = v8::Array::New(numOutputChannels);
	auto inputs = v8::Array::New(numInputChannels);
	auto samples = v8::Int32::New(numSamples);

	for (int i = 0; i < numOutputChannels; i++) {
		auto outputBuffer = *(outputChannelData + i);
		auto buffer = v8::ArrayBuffer::New(outputBuffer, numSamples);
		auto floatArray = v8::Float32Array::New(buffer, 0, numSamples);
		outputs->Set(i, floatArray);
	}

	for (int i = 0; i < numInputChannels; i++) {
		auto *inputBuffer = const_cast<float*>(*(inputChannelData + i));
		auto buffer = v8::ArrayBuffer::New(inputBuffer, numSamples);
		auto floatArray = v8::Float32Array::New(buffer, 0, numSamples);

		outputs->Set(i, floatArray);
	}

	v8::Handle<v8::Value> values[] = { inputs, outputs, samples };
	callback->Call(globalObject, 3, values);
}

void ScriptDspCallback::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
}

void ScriptDspCallback::audioDeviceStopped()
{
}
