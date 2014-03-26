#include "ScriptObject.h"


void ScriptObjectMetadata::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObjectMetadata>& data)
{
    auto value = data.GetParameter();
    value->wrapper.Dispose(data.GetIsolate());
}

v8::Handle<v8::External> ScriptObjectMetadata::Persist(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);
    auto external = v8::External::New((void*)this);
    wrapper.Reset(isolate, external);
    wrapper.SetWeak(this, WeakRefCallback);

    return scope.Close(external);
}


ScriptObject* ScriptObject::Unwrap(v8::Isolate *isolate, v8::Handle<v8::Object> holder)
{
    v8::HandleScope scope(isolate);

    auto internalField = holder->GetInternalField(0);
    auto external = internalField.As<v8::External>();
    auto data = external->Value();

    return static_cast<ScriptObject*>(data);
}

void ScriptObject::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObject>& data)
{
    auto value = data.GetParameter();
    value->wrapper.Dispose(data.GetIsolate());

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