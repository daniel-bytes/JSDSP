#include "ScriptObjectMetadata.h"
#include "ScriptObject.h"
#include "ScriptUtility.h"

void ScriptObjectMetadata::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObjectMetadata>& data)
{
    auto isolate = data.GetIsolate();
    auto value = data.GetParameter();

    value->instanceWrapper.Dispose(isolate);
    value->functionTemplateWrapper.Dispose(isolate);
}

v8::Handle<v8::External> ScriptObjectMetadata::Persist(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);

    auto global = isolate->GetCurrentContext()->Global();
    auto external = v8::External::New((void*)this);
    this->instanceWrapper.Reset(isolate, external);
    this->instanceWrapper.SetWeak(this, WeakRefCallback);

    auto ctorTemplate = v8::FunctionTemplate::New();
    ctorTemplate->InstanceTemplate()->SetInternalFieldCount(1);
    
    ctorTemplate->SetCallHandler([] (const v8::FunctionCallbackInfo<v8::Value>& info) {
        auto metadata = UnwrapInternalDataObject<ScriptObjectMetadata>(info.GetIsolate(), info.Data());
        auto instance = metadata->ConstructObject(info.GetIsolate());
        auto instanceExternal = instance->Persist(info.GetIsolate());
        info.Holder()->SetInternalField(0, instanceExternal);
    }, external);
    
    this->functionTemplateWrapper.Reset(isolate, ctorTemplate);

    global->Set(v8::String::New(this->GetName()), ctorTemplate->GetFunction());

    return scope.Close(external);
}

v8::Handle<v8::FunctionTemplate> ScriptObjectMetadata::GetFunctionTemplate(v8::Isolate *isolate)
{
    if (functionTemplateWrapper.IsEmpty()) {
        throw std::runtime_error("Must call Persist() before accessing function template.");
    }

    v8::HandleScope scope(isolate);
    auto templateHandle = v8::Handle<v8::FunctionTemplate>::New(isolate, functionTemplateWrapper);
    
    return scope.Close(templateHandle);
}

void ScriptObjectMetadata::SetMethod(v8::Isolate *isolate, 
                                     const char *name, 
                                     v8::FunctionCallback callback)
{
    v8::HandleScope scope(isolate);

    auto functionTemplate = GetFunctionTemplate(isolate);
    auto function = v8::Function::New(isolate, callback);
    functionTemplate->InstanceTemplate()->Set(name, function);
    //functionTemplate->PrototypeTemplate()->Set(name, function);
}

void ScriptObjectMetadata::SetProperty(v8::Isolate *isolate, 
                                       const char *name, 
                                       v8::AccessorGetterCallback getter,  
                                       v8::AccessorSetterCallback setter)
{
    v8::HandleScope scope(isolate);

    auto functionTemplateObj = GetFunctionTemplate(isolate);
    functionTemplateObj->InstanceTemplate()->SetAccessor(v8::String::New(name), getter, setter);
}