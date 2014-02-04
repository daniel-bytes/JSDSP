#ifndef __SCRIPTPROCESSOR_H__
#define __SCRIPTPROCESSOR_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../V8/v8.h"

class ScriptObject;

// Executes a script in a new isolated v8 process.
// This script should only be accessed from a single thread.
class ScriptProcessor
{
public:
	ScriptProcessor(void);
	~ScriptProcessor(void);

public:
	void Register(ScriptObject *scriptObject);
	juce::String Execute(juce::String &script);
    v8::Isolate* EnterIsolate(void);
    v8::Handle<v8::Object> GetGlobalObject(void);
    v8::Handle<v8::Function> GetFunction(juce::String &name);

private:
    // Wrapper around an Isolate so we can use proper RAII
    // and ensure the destructor is called after all other v8
    // objects are already disposed of.
    struct IsolateWrapper
    {
        IsolateWrapper(void)
            : value(nullptr)
        {
            value = v8::Isolate::New();
            value->Enter();
        }

        ~IsolateWrapper(void)
        {
            value->Exit();
            value->Dispose();
            value = nullptr;
        }

        v8::Isolate *value;
    } isolate;

private:
    //v8::Locker locker;
    v8::HandleScope handleScope;
    v8::Handle<v8::ObjectTemplate> global;
    v8::Handle<v8::Context> context;
    v8::Context::Scope contextScope;
    juce::Array<ScriptObject*> registeredObjects;
};

#endif //__SCRIPTPROCESSOR_H__

