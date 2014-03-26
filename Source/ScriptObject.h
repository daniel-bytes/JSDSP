#ifndef __SCRIPTOBJECT_H__
#define __SCRIPTOBJECT_H__

#include "../V8/v8.h"
#include "../JuceLibraryCode/JuceHeader.h"

class ScriptObject
{
public:
    virtual void InvokeMethod(const v8::FunctionCallbackInfo<v8::Value>& info) = 0;
    virtual void InvokeGetter(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info) = 0;
    virtual void InvokeSetter(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info) = 0;
    
public:
    v8::Handle<v8::External> Persist(v8::Isolate *isolate);
    static ScriptObject* Unwrap(v8::Isolate *isolate, v8::Handle<v8::Object> holder);

private:
    static void WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObject>& data);

private:
    v8::Persistent<v8::Value> wrapper;
};



class ScriptObjectMetadata
{
public:
    virtual juce::Array<juce::String> GetMethodNames(void) = 0;
    virtual const char* GetConstructorName(void) = 0;
    virtual ScriptObject* ConstructObject(const v8::FunctionCallbackInfo<v8::Value>& info) = 0;

public:
    v8::Handle<v8::External> Persist(v8::Isolate *isolate);

private:
    static void WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObjectMetadata>& data);

private:
    v8::Persistent<v8::Value> wrapper;
};







#endif //__SCRIPTOBJECT_H__
