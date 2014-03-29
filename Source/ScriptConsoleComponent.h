#ifndef __SCRIPTCONSOLECOMPONENT_H__
#define __SCRIPTCONSOLECOMPONENT_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Printable.h"

class ScriptConsoleComponent
    : public juce::TextEditor,
      public Printable
{
public:
    ScriptConsoleComponent(void);
    virtual ~ScriptConsoleComponent(void);

public:
    virtual void print(const juce::String &text);
};

#endif //__SCRIPTCONSOLECOMPONENT_H__