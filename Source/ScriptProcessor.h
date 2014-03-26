#ifndef __SCRIPTPROCESSOR_H__
#define __SCRIPTPROCESSOR_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../V8/v8.h"

class ScriptObjectMetadata;

// Executes a script in a new isolated v8 process.
// This script should only be accessed from a single thread.
class ScriptProcessor
{
public:
	ScriptProcessor(void);
	~ScriptProcessor(void);

private:

public:
	void Execute(juce::String &script, juce::Array<ScriptObjectMetadata*> metadataObjects);

    v8::Isolate* EnterIsolate(void);
    v8::Handle<v8::Context> GetContext(void);

    juce::String handleError(const v8::TryCatch &tryCatch);

    
    v8::Handle<v8::Function> GetProcessFunction(void);

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
    v8::Handle<v8::Function> GetFunction(v8::Handle<v8::Context> context, juce::String &name);

private:
    v8::Persistent<v8::Context> context;
    v8::Persistent<v8::Function> processFunction;
    v8::Handle<v8::Script> compiledScript;
    juce::Array<ScriptObjectMetadata*> registeredMetadata;
};

#endif //__SCRIPTPROCESSOR_H__

