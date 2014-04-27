#ifndef __DOCUMENTMODEL_H__
#define __DOCUMENTMODEL_H__

#include <hash_map>
#include "../JuceLibraryCode/JuceHeader.h"
#include "ScriptObject.h"
#include "ScriptSingletonMetadata.h"

class ScriptUIObject;

class DocumentModel
    : public ScriptObject
{
public:
    DocumentModel(void);
    ~DocumentModel(void);

public:
    void AppendElement(ScriptUIObject *object);
    ScriptUIObject* GetElementByID(const juce::String &id);

    class Metadata
        : public ScriptSingletonMetadata
    {
    public:
        Metadata(DocumentModel *instance);
        virtual const char* GetName(void);
        virtual void Configure(v8::Isolate *isolate);
    };

private:
    std::hash_map<long, ScriptUIObject*> documentModelByID;
};

#endif //__DOCUMENTMODEL_H__