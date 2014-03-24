#ifndef __SCRIPTOBJECT_H__
#define __SCRIPTOBJECT_H__

#include "../V8/v8.h"

class ScriptObject;

class ScriptObjectMetadata
{
public:
    virtual const char* GetConstructorName(void) = 0;
    virtual ScriptObject* ConstructObject(const v8::FunctionCallbackInfo<v8::Value>& info) = 0;
};

class ScriptObject
{
public:
    virtual void InvokeMethod(const v8::FunctionCallbackInfo<v8::Value>& info) = 0;
    virtual void InvokeGetter(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info) = 0;
    virtual void InvokeSetter(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info) = 0;
};




#endif //__SCRIPTOBJECT_H__
