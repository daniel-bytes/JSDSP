#ifndef __SCRIPTCONSOLECOMPONENT_H__
#define __SCRIPTCONSOLECOMPONENT_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Printable.h"
#include "ScriptFunctionMetadata.h"

class ScriptConsoleComponent
    : public juce::TextEditor,
      public Printable,
      public ScriptFunctionMetadata
{
public:
    ScriptConsoleComponent(void);
    virtual ~ScriptConsoleComponent(void);

public:
    virtual void print(const juce::String &text);
    virtual void FunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info);

    virtual const char* GetName(void) { return "log"; }
};

#endif //__SCRIPTCONSOLECOMPONENT_H__