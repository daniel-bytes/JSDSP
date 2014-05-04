#ifndef __SCRIPTUIOBJECT_H__
#define __SCRIPTUIOBJECT_H__

#include "../V8/v8.h"
#include "ScriptObject.h"
#include "ScriptSingletonMetadata.h"

class ScriptUIObject
    : public ScriptObject
{
public:
    ScriptUIObject(void)
    {
    }

public:
    juce::String GetID(void) const { return this->id; }
    void SetID(const juce::String &str) { this->id = str; }

    ScriptSingletonMetadata* GetMetadata(void) { return this->metadata; }
    void SetMetadata(ScriptSingletonMetadata *metadata) { this->metadata = metadata; }

private:
    ScriptSingletonMetadata *metadata;
    juce::String id;
};

#endif //__SCRIPTUIOBJECT_H__