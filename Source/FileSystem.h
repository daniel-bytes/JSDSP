#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "ScriptObject.h"

class FileSystem
    : public ScriptObject
{
public:
    const juce::String& GetFilePath(void) const;
    void SetFilePath(const juce::String &value);
    
    virtual void InvokeMethod(const v8::FunctionCallbackInfo<v8::Value>& info);
    virtual void InvokeGetter(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
    virtual void InvokeSetter(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);

public:
    class Metadata
        : public ScriptObjectMetadata
    {
    public:
        virtual const char* GetConstructorName(void) { return "FileSystem"; }
        virtual ScriptObject* ConstructObject(const v8::FunctionCallbackInfo<v8::Value>& info);
    };

private:
    juce::String filePath;
};


#endif //__FILESYSTEM_H__