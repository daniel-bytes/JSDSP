#include "ScriptObject.h"



void ScriptObject::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObject>& data)
{
    auto value = data.GetParameter();
    value->instanceWrapper.Dispose(data.GetIsolate());

    delete value;
}

v8::Handle<v8::External> ScriptObject::Persist(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);
    auto external = v8::External::New((void*)this);
    instanceWrapper.Reset(isolate, external);
    instanceWrapper.SetWeak(this, WeakRefCallback);

    return scope.Close(external);
}