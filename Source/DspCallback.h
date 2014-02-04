#ifndef __DSPCALLBACK_H__
#define __DSPCALLBACK_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../V8/v8.h"

class Parameters;
class ScriptProcessor;

class DspCallback
	: public juce::AudioIODeviceCallback
{
public:
	DspCallback(Parameters *parameters);
	virtual ~DspCallback(void);

public:
    void SetAudioScript(juce::String script);

	virtual void audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples);

	virtual void audioDeviceAboutToStart(juce::AudioIODevice* device);

	virtual void audioDeviceStopped();

private:
    Parameters *parameters;
    double currentSampleRate;
    juce::String script;
    juce::ScopedPointer<ScriptProcessor> scriptProcessor;
};

#endif //__DSPCALLBACK_H__
