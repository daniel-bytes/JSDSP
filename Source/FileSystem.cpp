#include "FileSystem.h"

const juce::String& FileSystem::GetFilePath(void) const
{
    return this->filePath;
}

void FileSystem::SetFilePath(const juce::String &value)
{
    this->filePath = value;
}


void FileSystem::InvokeMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
}

void FileSystem::InvokeGetter(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
}

void FileSystem::InvokeSetter(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
}

ScriptObject* FileSystem::Metadata::ConstructObject(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    return new FileSystem();
}