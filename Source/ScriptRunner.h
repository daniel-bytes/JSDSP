#ifndef __JUCE_HEADER_C0B4F26B22E84BD6__
#define __JUCE_HEADER_C0B4F26B22E84BD6__

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;

class ScriptProcessor;
class ScriptDspCallback;

class ScriptRunner  : public Component,
                      public ButtonListener
{
public:
    //==============================================================================
    ScriptRunner ();
    ~ScriptRunner();

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //==============================================================================
    ScopedPointer<TextEditor> scriptEditor;
    ScopedPointer<TextEditor> scriptOutput;
    ScopedPointer<TextButton> executeButton;
	ScopedPointer<ScriptProcessor> scriptProcessor;
	ScopedPointer<ScriptDspCallback> dspCallback;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScriptRunner)
};

#endif   // __JUCE_HEADER_C0B4F26B22E84BD6__
