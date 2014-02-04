#include "ScriptProcessor.h"
#include "ScriptObject.h"

#define GetIsolate v8::Isolate::GetCurrent

class MallocArrayBufferAllocator 
    : public v8::ArrayBuffer::Allocator 
{
public:
    MallocArrayBufferAllocator(void) {
        v8::V8::SetArrayBufferAllocator(this);
    }

public:
  virtual void* Allocate(size_t length) { return malloc(length); }
  virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
  virtual void Free(void* data, size_t length) { free(data); }
} mallocArrayBufferAllocator;



ScriptProcessor::ScriptProcessor(void)
    : //locker(isolate.value), 
      handleScope(isolate.value), 
      global(v8::ObjectTemplate::New()),
      context(v8::Context::New(isolate.value, nullptr, global)),
      contextScope(context)
{
}


ScriptProcessor::~ScriptProcessor(void)
{

}

v8::Isolate* ScriptProcessor::EnterIsolate(void)
{
    isolate.value->Enter();
    return isolate.value;
}

void ScriptProcessor::Execute(juce::String &script)
{
    for (auto registeredObject : registeredObjects) {
        registeredObject->Register(global);
    }

    // Create a string containing the JavaScript source code.
    v8::Handle<v8::String> source = v8::String::NewFromUtf8(isolate.value, script.toUTF8());
  
    // Compile the source code.
    v8::Handle<v8::Script> compiledScript = v8::Script::Compile(source);
  
    // Run the script to get the result.
    v8::Handle<v8::Value> result = compiledScript->Run();
  
    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(result);
    printf("%s\n", *utf8);
}

v8::Handle<v8::Object> ScriptProcessor::GetGlobalObject(void)
{
    return context->Global();
}

v8::Handle<v8::Function> ScriptProcessor::GetFunction(juce::String &name)
{
	auto globalObject = context->Global();

    auto functionName = v8::String::NewFromUtf8(isolate.value, name.toUTF8());
	auto function = v8::Handle<v8::Function>::Cast(globalObject->Get(functionName));
    return function;
}

void ScriptProcessor::Register(ScriptObject *scriptObject)
{
    registeredObjects.add(scriptObject);
}