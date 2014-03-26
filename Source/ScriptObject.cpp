#include "ScriptObject.h"


void ScriptObjectMetadata::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObjectMetadata>& data)
{
    auto value = data.GetParameter();
    value->wrapper.Dispose();
}

v8::Handle<v8::External> ScriptObjectMetadata::Persist(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);
    auto external = v8::External::New((void*)this);
    wrapper.Reset(isolate, external);
    wrapper.SetWeak(this, WeakRefCallback);

    return scope.Close(external);
}


void ScriptObject::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObject>& data)
{
    auto value = data.GetParameter();
    value->wrapper.Dispose();

    delete value;
}

v8::Handle<v8::External> ScriptObject::Persist(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);
    auto external = v8::External::New((void*)this);
    wrapper.Reset(isolate, external);
    wrapper.SetWeak(this, WeakRefCallback);

    return scope.Close(external);
}