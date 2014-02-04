#ifndef __DSPCALLBACK_H__
#define __DSPCALLBACK_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../V8/v8.h"

class ScriptProcessor;

class DspCallback
	: public juce::AudioIODeviceCallback
{
public:
	DspCallback(juce::String &script);
	virtual ~DspCallback(void);

public:
	virtual void audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples);

	virtual void audioDeviceAboutToStart (juce::AudioIODevice* device);

	virtual void audioDeviceStopped();

private:
    juce::String script;
    juce::ScopedPointer<ScriptProcessor> scriptProcessor;
};

#endif //__DSPCALLBACK_H__
