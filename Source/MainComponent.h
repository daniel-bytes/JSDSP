#ifndef __MAINCOMPONENT_H__
#define __MAINCOMPONENT_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "XmlParser.h"
using namespace juce;

class DspCallback;
class AppWindow;
class ParameterControl;
class ScriptConsoleComponent;
class ScriptProcessor;
class ScriptMetadata;
class DocumentModel;

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
    ScopedPointer<ScriptConsoleComponent> scriptConsole;
    ScopedPointer<DspCallback> dspCallback;
    ScopedPointer<DocumentModel> documentModel;

    ScopedPointer<ScriptProcessor> uiScriptProcessor;

    OwnedArray<Component> allComponents;
    Array<ParameterControl*> allParameterControls;

    ApplicationSettings settings;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif //__MAINCOMPONENT_H__