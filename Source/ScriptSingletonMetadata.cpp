#include "ScriptSingletonMetadata.h"
#include "ScriptObject.h"
#include "ScriptUtility.h"


ScriptSingletonMetadata::ScriptSingletonMetadata(ScriptObject *instance)
    : scriptObjectInstance(instance)
{
}

void ScriptSingletonMetadata::WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptSingletonMetadata>& data)
{
    auto isolate = data.GetIsolate();
    auto value = data.GetParameter();

    value->instanceWrapper.Dispose(isolate);
    value->objectWrapper.Dispose(isolate);
}

v8::Handle<v8::External> ScriptSingletonMetadata::Persist(v8::Isolate *isolate)
{
    v8::HandleScope scope(isolate);

    auto global = isolate->GetCurrentContext()->Global();
    auto instance = this->scriptObjectInstance;
    auto external = v8::External::New((void*)instance);
    auto obj = v8::Object::New();

    obj->Set(v8::String::New("__instance"), external);
    this->instanceWrapper.Reset(isolate, external);
    this->objectWrapper.Reset(isolate, obj);
    this->instanceWrapper.SetWeak(this, WeakRefCallback);

    global->Set(v8::String::New(this->GetName()), obj);
    
    return scope.Close(external);
}

v8::Handle<v8::Object> ScriptSingletonMetadata::GetObjectWrapper(v8::Isolate *isolate)
{
    if (objectWrapper.IsEmpty()) {
        throw std::runtime_error("Must call Persist() before accessing object wrapper.");
    }

    v8::HandleScope scope(isolate);
    auto objectHandle = v8::Handle<v8::Object>::New(isolate, objectWrapper);
    
    return scope.Close(objectHandle);
}

v8::Handle<v8::Value> ScriptSingletonMetadata::GetInstanceWrapper(v8::Isolate *isolate)
{
    if (instanceWrapper.IsEmpty()) {
        throw std::runtime_error("Must call Persist() before accessing instance wrapper.");
    }

    v8::HandleScope scope(isolate);
    auto instanceHandle = v8::Handle<v8::Value>::New(isolate, instanceWrapper);
    
    return scope.Close(instanceHandle);
}

void ScriptSingletonMetadata::Configure(v8::Isolate *isolate)
{
}

void ScriptSingletonMetadata::SetMethod(v8::Isolate *isolate, 
                                        const char *name, 
                                        v8::FunctionCallback callback)
{
    v8::HandleScope scope(isolate);

    auto objectWrapper = GetObjectWrapper(isolate);
   // auto instanceWrapper = GetInstanceWrapper(isolate);
    auto function = v8::Function::New(isolate, callback);
    objectWrapper->Set(v8::String::New(name), function);
}

void ScriptSingletonMetadata::SetProperty(v8::Isolate *isolate, 
                                       const char *name, 
                                       v8::AccessorGetterCallback getter,  
                                       v8::AccessorSetterCallback setter)
{
    v8::HandleScope scope(isolate);
    
    auto objectWrapper = GetObjectWrapper(isolate);
    objectWrapper->SetAccessor(v8::String::New(name), getter, setter);
}