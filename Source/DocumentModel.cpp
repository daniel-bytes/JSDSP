#include "DocumentModel.h"
#include "ScriptUIObject.h"
#include "ScriptUtility.h"

/*
 * Metadata Objects
 */

class GetElementByIDMetadata
    : public ScriptFunctionMetadata
{
public:
    GetElementByIDMetadata(DocumentModel *parent)
        : parent(parent) {}

public:
    virtual const char* GetName(void) { return "getElementById"; }

    virtual void FunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info);

private:
    DocumentModel *parent;
};

void GetElementByIDMetadata::FunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::HandleScope scope(info.GetIsolate());

    if (info.Length() == 0) {
        return;
    }

    auto id = ToJuceString(info[0]);
    auto element = parent->GetElementByID(id);

    if (element == nullptr) {
        //info.GetReturnValue().Set(
    }
}


/*
 * DocumentModel
 */
DocumentModel::DocumentModel(void)
{
    functionMetadata.add(new GetElementByIDMetadata(this));
}

void DocumentModel::AppendElement(ScriptUIObject *object)
{
    this->documentModelByID.set(object->GetID(), object);
}

ScriptUIObject* DocumentModel::GetElementByID(const juce::String &id)
{
    return this->documentModelByID[id];
}

juce::Array<ScriptFunctionMetadata*> DocumentModel::GetFunctionMetadata(void)
{
    juce::Array<ScriptFunctionMetadata*> arr(functionMetadata);

    return arr;
}