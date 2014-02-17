#include "DspCallback.h"
#include "ScriptProcessor.h"
#include "Parameters.h"
#include "ParameterControl.h"

DspCallback::DspCallback(juce::Array<ParameterControl*> parameters)
      : currentSampleRate(0)
{
    this->parameters.addArray(parameters);
}

DspCallback::~DspCallback(void)
{
}

void DspCallback::SetAudioScript(juce::String script)
{
    this->script = script;
    this->scriptProcessor = nullptr;
}

void DspCallback::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
    currentSampleRate = device->getCurrentSampleRate();

    if (scriptProcessor == nullptr) {
        scriptProcessor = new ScriptProcessor();

        // TODO:
        // scriptProcessor->Register(someDspType);

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
    auto parametersObject = v8::Object::New();

    for (auto parameterControl : parameters) {
        int count = parameterControl->getParameterCount();

        for (int i = 0; i < count; i++) {
            juce::String name;
            juce::var value;

            if (parameterControl->getParameter(i, name, value)) {
                auto parameterName = v8::String::NewFromUtf8(isolate, name.toUTF8());

                if (value.isBool()) {
                    parametersObject->Set(parameterName, v8::Boolean::New((bool)value));
                }
                else if (value.isDouble()) {
                    parametersObject->Set(parameterName, v8::Number::New((double)value));
                }
                else if (value.isInt()) {
                    parametersObject->Set(parameterName, v8::Int32::New((int)value));
                }
                else if (value.isString()) {
                    parametersObject->Set(parameterName, v8::String::NewFromUtf8(isolate, ((juce::String)value).toUTF8()));
                }
            }
        }
    }

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
	v8::Handle<v8::Value> values[] = { inputs, outputs, samples, sampleRate, parametersObject };
    function->Call(scriptProcessor->GetGlobalObject(), 5, values);

	for (int channel = 0; channel < numOutputChannels; channel++) {
        auto buffer = v8::Handle<v8::ArrayBuffer>::Cast(outputs->Get(channel));

        for (int i = 0; i < numSamples; i++) {
            float value = (float)buffer->Get(i)->NumberValue();
            outputChannelData[channel][i] = value;
        }
    }

    isolate->Exit();
}

