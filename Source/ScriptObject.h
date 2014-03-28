#ifndef __SCRIPTOBJECT_H__
#define __SCRIPTOBJECT_H__

#include "../V8/v8.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <map>

class ScriptObject
{
public:
    v8::Handle<v8::External> Persist(v8::Isolate *isolate);

    template<typename TScriptObject>
    static TScriptObject* Unwrap(v8::Isolate *isolate, v8::Handle<v8::Object> holder);

private:
    static void WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObject>& data);

private:
    v8::Persistent<v8::Value> wrapper;
};


class ScriptObjectMetadata
{
public:
    virtual const char* GetConstructorName(void) = 0;

    virtual ScriptObject* ConstructObject(v8::Isolate *isolate) = 0;

    virtual void Configure(v8::Isolate *isolate) = 0;

public:
    v8::Handle<v8::External> Persist(v8::Isolate *isolate, v8::Handle<v8::FunctionTemplate> functionTemplate);

protected:
    v8::Handle<v8::FunctionTemplate> GetFunctionTemplate(v8::Isolate *isolate);

    void SetMethod(v8::Isolate *isolate, 
                   const char *name, 
                   v8::FunctionCallback callback);

    void SetProperty(v8::Isolate *isolate, 
                     const char *name, 
                     v8::AccessorGetterCallback getter,  
                     v8::AccessorSetterCallback setter = (v8::AccessorSetterCallback)nullptr);

private:
    static void WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObjectMetadata>& data);

private:
    v8::Persistent<v8::Value> wrapper;
    v8::Persistent<v8::FunctionTemplate> functionTemplate;
};


template<typename TScriptObject>
TScriptObject* ScriptObject::Unwrap(v8::Isolate *isolate, v8::Handle<v8::Object> holder)
{
    v8::HandleScope scope(isolate);

    auto internalField = holder->GetInternalField(0);
    auto external = internalField.As<v8::External>();
    auto data = external->Value();

    return static_cast<TScriptObject*>(data);
}

#endif //__SCRIPTOBJECT_H__
