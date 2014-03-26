#include "ScriptProcessor.h"
#include "ScriptObject.h"
#include <sstream>
#include <exception>
#include "Debugging.h"


// Allocator for ArrayBuffer type using standard Malloc.
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
  virtual void Free(void* data, size_t length) { (void)length; free(data); }
} mallocArrayBufferAllocator;



/*
template<typename T>
T* UnwrapObject(v8::Isolate *isolate, v8::Handle<v8::FunctionTemplate> objectTemplate, void *objectToWrap)
{
    auto isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    auto self = info.Holder();
    auto unwrappedField = v8::Local<v8::External>::Cast(self->GetInternalField(0));
    auto obj = static_cast<T*>(unwrappedField->Value());

    return obj;
}
*/
void ConstructObject(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scope(isolate);

    auto external = info.Data().As<v8::External>();
    auto externalValue = external->Value();
    auto metadata = static_cast<ScriptObjectMetadata*>(externalValue);

    auto instance = metadata->ConstructObject(info);
    auto wrappedInstance = instance->Persist(isolate);

    info.Holder()->SetInternalField(0, wrappedInstance);
}

void ConfigureObject(v8::Isolate *isolate, ScriptObjectMetadata *metadata, v8::Handle<v8::Object> global)
{
    v8::HandleScope scope(isolate);
    
    auto metadataExternal = metadata->Persist(isolate);
    auto ctorTemplate = v8::FunctionTemplate::New();

    ctorTemplate->InstanceTemplate()->SetInternalFieldCount(1);

    ctorTemplate->SetCallHandler(ConstructObject, metadataExternal);

    global->Set(v8::String::New(metadata->GetConstructorName()), ctorTemplate->GetFunction());
}

ScriptProcessor::ScriptProcessor(void)
{
}


ScriptProcessor::~ScriptProcessor(void)
{
}

v8::Handle<v8::Function> ScriptProcessor::GetProcessFunction(void)
{
    v8::HandleScope scope(isolate.value);

    auto funcPtr = v8::Local<v8::Function>::New(isolate.value, processFunction);
    return scope.Close(funcPtr);
}

v8::Isolate* ScriptProcessor::EnterIsolate(void)
{
    isolate.value->Enter();
    return isolate.value;
}

v8::Handle<v8::Context> ScriptProcessor::GetContext(void)
{
    return v8::Local<v8::Context>::New(isolate.value, context);
}

void ScriptProcessor::Execute(juce::String &script, juce::Array<ScriptObjectMetadata*> metadataObjects)
{
    v8::HandleScope handle_scope(isolate.value);

    auto tempContext = v8::Context::New(isolate.value, nullptr, v8::ObjectTemplate::New());

    context.Reset(isolate.value, tempContext);

    v8::Context::Scope contextScope(tempContext);

    auto _isolate = EnterIsolate();

    for (auto metadataObject : metadataObjects) {
        registeredMetadata.add(metadataObject);
        ConfigureObject(_isolate, metadataObject, tempContext->Global());
    }

    // Create a string containing the JavaScript source code.
    v8::Handle<v8::String> source = v8::String::NewFromUtf8(isolate.value, script.toUTF8());
  
    // Compile the source code.
    compiledScript = v8::Script::Compile(source);
  
    // Run the script to get the result.
    v8::TryCatch tryCatch;
    v8::Handle<v8::Value> result = compiledScript->Run();

    if (result.IsEmpty()) {
        auto msg = handleError(tryCatch);
        throw new std::runtime_error(msg.toUTF8());
    }
    else {
        juce::String funcName ="audioCallback";
        auto func = GetFunction(tempContext, funcName);
        processFunction.Reset(isolate.value, func);

    #if DEBUG
        PrintError("Script compiled and ran successfully.  Result: ");
        v8::String::Utf8Value utf8(result);
        PrintErrorLine(*utf8);
    #endif
    }
    _isolate->Exit();
}

v8::Handle<v8::Function> ScriptProcessor::GetFunction(v8::Handle<v8::Context> context, juce::String &name)
{
	auto globalObject = context->Global();
    auto functionNameString = name.toUTF8();

    auto functionName = v8::String::NewFromUtf8(isolate.value, functionNameString);
    auto functionObj = globalObject->Get(functionName);

    if (functionObj->IsUndefined()) {
        PrintError("Function is not defined: ");
        PrintErrorLine(name.toUTF8());
    }

	auto function = v8::Handle<v8::Function>::Cast(functionObj);
    return function;
}

juce::String ScriptProcessor::handleError(const v8::TryCatch &tryCatch)
{
    if (tryCatch.HasCaught()) {
        v8::HandleScope scope(isolate.value);
        auto exception = tryCatch.Exception();
        auto stackTrace = tryCatch.StackTrace();

        v8::String::AsciiValue exceptionMessage(exception);
        const char *exceptionString = *exceptionMessage;

        v8::String::AsciiValue stackTraceMessage(stackTrace);
        const char *stackTraceString = *stackTraceMessage;

        std::ostringstream errorStream;

        errorStream << "Exception caught: " << exceptionString << "\r\n" << "- Stack Trace: " << stackTraceString;

        const std::string errorString = errorStream.str();

        PrintError(errorString.c_str());

        return juce::String(errorString);
    }

    return "";
}