#include "DocumentModel.h"
#include "ScriptUIObject.h"
#include "ScriptUtility.h"

DocumentModel::DocumentModel(void)
{
}

DocumentModel::~DocumentModel(void)
{
}

void DocumentModel::AppendElement(ScriptUIObject *object)
{
    auto hashCode = object->GetID().hashCode64();
    this->documentModelByID[hashCode] = object;
}

ScriptUIObject* DocumentModel::GetElementByID(const juce::String &id)
{
    auto hashCode = id.hashCode64();
    
    auto iter = this->documentModelByID.find(hashCode);

    if (iter != this->documentModelByID.end()) {
        return iter->second;
    }

    return nullptr;
}

DocumentModel::Metadata::Metadata(DocumentModel *instance)
    : ScriptSingletonMetadata(instance)
{

}

const char* DocumentModel::Metadata::GetName(void)
{
    return "document";
}

void DocumentModel::Metadata::Configure(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);

    SetMethod(isolate, "getElementById", 
        [] (const v8::FunctionCallbackInfo<v8::Value>& info) {
            auto obj = UnwrapSingletonFromThis<DocumentModel>(info.GetIsolate(), info.This());
            v8::HandleScope scope(info.GetIsolate());

            if (info.Length() == 0) {
                return;
            }

            auto id = ToJuceString(info[0]);
            auto element = obj->GetElementByID(id);

            if (element != nullptr) {
                auto value = element->Wrap(info.GetIsolate());
                info.GetReturnValue().Set(value);
            }
        });
}