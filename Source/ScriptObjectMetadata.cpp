#include "ScriptObjectMetadata.h"
#include "ScriptObject.h"

void ScriptObjectMetadata::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObjectMetadata>& data)
{
    auto isolate = data.GetIsolate();
    auto value = data.GetParameter();

    value->wrapper.Dispose(isolate);
    value->functionTemplate.Dispose(isolate);
}

v8::Handle<v8::External> ScriptObjectMetadata::Persist(v8::Isolate *isolate, v8::Handle<v8::FunctionTemplate> functionTemplate)
{
    v8::HandleScope scope(isolate);
    auto external = v8::External::New((void*)this);
    this->wrapper.Reset(isolate, external);
    this->wrapper.SetWeak(this, WeakRefCallback);

    this->functionTemplate.Reset(isolate, functionTemplate);

    return scope.Close(external);
}

v8::Handle<v8::FunctionTemplate> ScriptObjectMetadata::GetFunctionTemplate(v8::Isolate *isolate)
{
    if (functionTemplate.IsEmpty()) {
        throw std::runtime_error("Must call Persist before accessing function template.");
    }

    v8::HandleScope scope(isolate);
    auto templateHandle = v8::Handle<v8::FunctionTemplate>::New(isolate, functionTemplate);
    
    return scope.Close(templateHandle);
}

void ScriptObjectMetadata::SetMethod(v8::Isolate *isolate, 
                                     const char *name, 
                                     v8::FunctionCallback callback)
{
    auto functionTemplateObj = GetFunctionTemplate(isolate);
    auto function = v8::Function::New(isolate, callback);
    functionTemplateObj->PrototypeTemplate()->Set(name, function);

}

void ScriptObjectMetadata::SetProperty(v8::Isolate *isolate, 
                                       const char *name, 
                                       v8::AccessorGetterCallback getter,  
                                       v8::AccessorSetterCallback setter)
{
    auto functionTemplateObj = GetFunctionTemplate(isolate);
    functionTemplateObj->InstanceTemplate()->SetAccessor(v8::String::New(name), getter, setter);
}