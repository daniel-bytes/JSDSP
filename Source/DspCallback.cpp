#include "DspCallback.h"
#include "ScriptProcessor.h"

DspCallback::DspCallback(juce::String &script)
    : script(script)
{
}

DspCallback::~DspCallback(void)
{
}

void DspCallback::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
    if (scriptProcessor == nullptr) {
        scriptProcessor = new ScriptProcessor();
        scriptProcessor->Execute(script);
    }
}

void DspCallback::audioDeviceStopped()
{
    scriptProcessor = nullptr;
}

void DspCallback::audioDeviceIOCallback (
	const float** inputChannelData,
    int numInputChannels,
    float** outputChannelData,
    int numOutputChannels,
    int numSamples)
{
    auto isolate = scriptProcessor->EnterIsolate();
    v8::HandleScope scope(isolate);
    //v8::Locker locker(isolate);

    juce::String functionName = "audioCallback";
    auto function = scriptProcessor->GetFunction(functionName);
	auto outputs = v8::Array::New(numOutputChannels);
	auto inputs = v8::Array::New(numInputChannels);
	auto samples = v8::Int32::New(numSamples);

	for (int channel = 0; channel < numOutputChannels; channel++) {
		auto outputBuffer = *(outputChannelData + channel);
		auto buffer = v8::ArrayBuffer::New(numSamples);
		//auto floatArray = v8::Float32Array::New(buffer, 0, numSamples);
		outputs->Set(channel, buffer);
	}

	for (int channel = 0; channel < numInputChannels; channel++) {
		auto *inputBuffer = const_cast<float*>(*(inputChannelData + channel));
		auto buffer = v8::ArrayBuffer::New(numSamples);
		//auto floatArray = v8::Float32Array::New(buffer, 0, numSamples);

		outputs->Set(channel, buffer);
	}

	v8::Handle<v8::Value> values[] = { inputs, outputs, samples };
    function->Call(scriptProcessor->GetGlobalObject(), 3, values);

	for (int channel = 0; channel < numOutputChannels; channel++) {
        auto buffer = v8::Handle<v8::ArrayBuffer>::Cast(outputs->Get(channel));

        for (int i = 0; i < numSamples; i++) {
            outputChannelData[channel][i] = (float)buffer->Get(i)->NumberValue();
        }
    }

    isolate->Exit();
}

