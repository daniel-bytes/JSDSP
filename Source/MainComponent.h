#ifndef __MAINCOMPONENT_H__
#define __MAINCOMPONENT_H__

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;

class DspCallback;
class AppWindow;
class ParameterControl;
class ScriptProcessor;
class ScriptObjectMetadata;

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
    void init(const String &filePath);

private:
    ScopedPointer<Label> projectFileLabel;
    ScopedPointer<Button> projectFileSelectButton;

    ScopedPointer<AppWindow> appWindow;
	ScopedPointer<AudioDeviceManager> audioDeviceManager;
    ScopedPointer<AudioDeviceSelectorComponent> audioDeviceSelector;
    ScopedPointer<DspCallback> dspCallback;

    ScopedPointer<ScriptProcessor> uiScriptProcessor;
    OwnedArray<ScriptObjectMetadata> uiScriptMetadata;

    OwnedArray<Component> allComponents;
    Array<ParameterControl*> allParameterControls;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif //__MAINCOMPONENT_H__