#include "DspCallback.h"
#include "ScriptProcessor.h"

DspCallback::DspCallback(juce::String &script)
    : script(script),
      currentSampleRate(0)
{
}

DspCallback::~DspCallback(void)
{
}

void DspCallback::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
    currentSampleRate = device->getCurrentSampleRate();

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
    auto sampleRate = v8::Number::New(currentSampleRate);

    // setup input data
	for (int channel = 0; channel < numInputChannels; channel++) {
		auto inputBuffer = *(inputChannelData + channel);
		auto buffer = v8::ArrayBuffer::New(numSamples);

        for (int i = 0; i < numSamples; i++) {
            buffer->Set(i, v8::Number::New(inputBuffer[i]));
        }

		inputs->Set(channel, buffer);
	}

    // setup output data
	for (int channel = 0; channel < numOutputChannels; channel++) {
		auto outputBuffer = *(outputChannelData + channel);
		auto buffer = v8::ArrayBuffer::New(numSamples);

		outputs->Set(channel, buffer);
	}

    // call JS function and copy results to JUCE output buffer
	v8::Handle<v8::Value> values[] = { inputs, outputs, samples, sampleRate };
    function->Call(scriptProcessor->GetGlobalObject(), 4, values);

	for (int channel = 0; channel < numOutputChannels; channel++) {
        auto buffer = v8::Handle<v8::ArrayBuffer>::Cast(outputs->Get(channel));

        for (int i = 0; i < numSamples; i++) {
            float value = (float)buffer->Get(i)->NumberValue();
            outputChannelData[channel][i] = value;
        }
    }

    isolate->Exit();
}

