#include "FileSystem.h"
#include "ScriptUtility.h"

const juce::String& FileSystem::GetFilePath(void) const
{
    return this->filePath;
}

void FileSystem::SetFilePath(const juce::String &value)
{
    this->filePath = value;
}

void FileSystem::Metadata::Configure(v8::Isolate *isolate)
{/*
    SetMethod(isolate, "test", 
        [] (const v8::FunctionCallbackInfo<v8::Value>& info) {
            auto obj = UnwrapInternalObject<FileSystem>(info.GetIsolate(), info.Holder());
            obj->test();
        });
        */
    SetProperty(isolate, "filePath", 
        [] (v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
            auto obj = UnwrapInternalObject<FileSystem>(info.GetIsolate(), info.Holder());
            auto path = v8::String::New(obj->GetFilePath().toUTF8());
            info.GetReturnValue().Set(path);
        },
        [] (v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info) {
            auto obj = UnwrapInternalObject<FileSystem>(info.GetIsolate(), info.Holder());
            v8::String::AsciiValue str(value);
            obj->SetFilePath(*str);
        });
}

ScriptObject* FileSystem::Metadata::ConstructObject(v8::Isolate *isolate)
{
    return new FileSystem();
}
