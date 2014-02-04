#ifndef __MAINCOMPONENT_H__
#define __MAINCOMPONENT_H__

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;

class DspCallback;
class Parameters;

class MainComponent  
	: public Component,
      public Button::Listener,
      public ComboBox::Listener
{
public:
    MainComponent(void);
    ~MainComponent(void);

    virtual void buttonClicked(Button *buttonThatWasClicked);
    virtual void comboBoxChanged(ComboBox *comboBoxThatHasChanged);

private:
    ScopedPointer<DocumentWindow> appWindow;
    ScopedPointer<Parameters> parameters;
	ScopedPointer<AudioDeviceManager> audioDeviceManager;
    ScopedPointer<AudioDeviceSelectorComponent> audioDeviceSelector;
    ScopedPointer<DspCallback> dspCallback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif //__MAINCOMPONENT_H__