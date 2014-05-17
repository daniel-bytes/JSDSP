#ifndef __SCRIPTSINGLETONMETADATA_H__
#define __SCRIPTSINGLETONMETADATA_H__

#include "../V8/v8.h"
#include "ScriptMetadata.h"

class ScriptObject;

class ScriptSingletonMetadata
    : public ScriptMetadata
{
public:
    ScriptSingletonMetadata(ScriptObject *instance, bool attachToGlobal);

    virtual const char* GetName(void) = 0;

    virtual void Configure(v8::Isolate *isolate);

    virtual v8::Handle<v8::External> Persist(v8::Isolate *isolate);

    v8::Handle<v8::Object> GetObjectWrapper(v8::Isolate *isolate);

public:
    v8::Isolate* GetConfiguredIsolate(void) const { return isolate; }

protected:
    void SetMethod(v8::Isolate *isolate, 
                   const char *name, 
                   v8::FunctionCallback callback);

    void SetProperty(v8::Isolate *isolate, 
                     const char *name, 
                     v8::AccessorGetterCallback getter,  
                     v8::AccessorSetterCallback setter = (v8::AccessorSetterCallback)nullptr);

private:
    static void WeakRefCallback(const v8::WeakCallbackData<v8::Object, ScriptSingletonMetadata>& data);

protected:
    ScriptObject *scriptObjectInstance;
    v8::Isolate *isolate;

private:
    bool attachToGlobal;
    v8::Persistent<v8::Object> objectWrapper;
};


#endif //__SCRIPTSINGLETONMETADATA_H__