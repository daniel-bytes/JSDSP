#ifndef __SCRIPTDSPCALLBACK_H__
#define __SCRIPTDSPCALLBACK_H__

#include "ScriptObject.h"
#include "../JuceLibraryCode/JuceHeader.h"

class DspCallback;

class ScriptDspCallback
	: public juce::AudioIODeviceCallback,
	  public ScriptObject
{
public:
    ScriptDspCallback();
	virtual ~ScriptDspCallback(void);
	
public:
	virtual void Register(v8::Handle<v8::ObjectTemplate> global);

	virtual void BeginAudio();

	virtual void audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples);

	virtual void audioDeviceAboutToStart (juce::AudioIODevice* device);

	virtual void audioDeviceStopped();

private:
	juce::AudioDeviceManager audio;
};

#endif //__SCRIPTDSPCALLBACK_H__
