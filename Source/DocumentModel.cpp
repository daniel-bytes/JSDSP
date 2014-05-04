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
        auto scriptObject = iter->second;
        return scriptObject;
    }

    return nullptr;
}

DocumentModel::Metadata::Metadata(DocumentModel *instance)
    : ScriptSingletonMetadata(instance, true)
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
            if (info.Length() == 0) {
                return;
            }

            auto isolate = info.GetIsolate();
            v8::HandleScope scope(isolate);

            auto self = info.Holder();
            auto obj = UnwrapEmbeddedInstance<DocumentModel>(isolate, self);

            auto id = ToJuceString(info[0]);
            auto element = obj->GetElementByID(id);

            if (element != nullptr) {
                auto metadata = element->GetMetadata();
                auto obj = metadata->GetObjectWrapper(isolate);

                //auto obj = element->Wrap(info.GetIsolate());
                info.GetReturnValue().Set(obj);
            }
        });
}