#include "ScriptFunctionMetadata.h"
#include "ScriptUtility.h"
#include <exception>

void ScriptFunctionMetadata::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptFunctionMetadata>& data)
{
    auto isolate = data.GetIsolate();
    auto value = data.GetParameter();

    value->instanceWrapper.Dispose(isolate);
    value->functionTemplateWrapper.Dispose(isolate);
}

v8::Handle<v8::External> ScriptFunctionMetadata::Persist(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);
    auto global = isolate->GetCurrentContext()->Global();
    auto external = v8::External::New((void*)this);
    this->instanceWrapper.Reset(isolate, external);
    this->instanceWrapper.SetWeak(this, WeakRefCallback);

    auto functionTemplate = v8::FunctionTemplate::New();
    
    functionTemplate->SetCallHandler([] (const v8::FunctionCallbackInfo<v8::Value>& info) {
        auto metadata = UnwrapInternalDataObject<ScriptFunctionMetadata>(info.GetIsolate(), info.Data());
        metadata->FunctionCallback(info);
    }, external);
    
    this->functionTemplateWrapper.Reset(isolate, functionTemplate);

    global->Set(v8::String::New(this->GetName()), functionTemplate->GetFunction());

    return scope.Close(external);
}

