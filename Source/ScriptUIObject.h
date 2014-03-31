#ifndef __SCRIPTUIOBJECT_H__
#define __SCRIPTUIOBJECT_H__

#include "ScriptObject.h"

class ScriptUIObject
    : public ScriptObject
{
public:
    juce::String GetID(void) const { return this->id; }
    void SetID(const juce::String &str) { this->id = str; }
private:
    juce::String id;
};

#endif //__SCRIPTUIOBJECT_H__