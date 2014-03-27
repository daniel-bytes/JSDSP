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
    
    void test(void) {

    }

public:
    class Metadata
        : public ScriptObjectMetadata
    {
    public:
        virtual const char* GetConstructorName(void) { return "FileSystem"; }

        virtual void ConfigureMethods(v8::Isolate *isolate);

        virtual ScriptObject* ConstructObject(v8::Isolate *isolate);
    };

private:
    juce::String filePath;
};


#endif //__FILESYSTEM_H__