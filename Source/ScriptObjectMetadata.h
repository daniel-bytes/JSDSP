#ifndef __SCRIPTOJECTMETADATA_H__
#define __SCRIPTOJECTMETADATA_H__

#include "../V8/v8.h"

class ScriptObject;

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

#endif //__SCRIPTOJECTMETADATA_H__