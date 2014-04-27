#include "ScriptObject.h"

ScriptObject::ScriptObject(void)
    : deleteOnGC(true)
{
}

void ScriptObject::DeleteOnGC(bool value)
{
    this->deleteOnGC = value;
}

void ScriptObject::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObject>& data)
{
    auto value = data.GetParameter();
    value->instanceWrapper.Dispose(data.GetIsolate());

    if (!value->deleteOnGC)
    {
        delete value;
    }
}

v8::Handle<v8::External> ScriptObject::Persist(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);
    
    auto external = v8::External::New((void*)this);

    if (instanceWrapper.IsEmpty()) {
        instanceWrapper.Reset(isolate, external);
        instanceWrapper.SetWeak(this, WeakRefCallback);
    }
        
    return scope.Close(external);
}

v8::Handle<v8::Object> ScriptObject::Wrap(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);

    auto external = Persist(isolate);
    auto obj = v8::Object::New();

    obj->Set(v8::String::New("__data"), external);

    return scope.Close(obj);
}