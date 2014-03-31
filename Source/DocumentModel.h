#ifndef __DOCUMENTMODEL_H__
#define __DOCUMENTMODEL_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "ScriptFunctionMetadata.h"

class ScriptUIObject;

class DocumentModel
{
public:
    DocumentModel(void);

public:
    void AppendElement(ScriptUIObject *object);
    ScriptUIObject* GetElementByID(const juce::String &id);

    juce::Array<ScriptFunctionMetadata*> GetFunctionMetadata(void);

private:
    juce::Array<ScriptFunctionMetadata*> functionMetadata;
    juce::HashMap<juce::String, ScriptUIObject*> documentModelByID;
};

#endif //__DOCUMENTMODEL_H__