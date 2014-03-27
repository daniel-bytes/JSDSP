#include "FileSystem.h"

const juce::String& FileSystem::GetFilePath(void) const
{
    return this->filePath;
}

void FileSystem::SetFilePath(const juce::String &value)
{
    this->filePath = value;
}

void FileSystem::Metadata::ConfigureMethods(v8::Isolate *isolate)
{
    SetMethod(isolate, "test", [&] (const v8::FunctionCallbackInfo<v8::Value>& info) {
        auto obj = ScriptObject::Unwrap<FileSystem>(info.GetIsolate(), info.Holder());
        obj->test();
    });
}

ScriptObject* FileSystem::Metadata::ConstructObject(v8::Isolate *isolate)
{
    return new FileSystem();
}
