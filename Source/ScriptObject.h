#ifndef __SCRIPTOBJECT_H__
#define __SCRIPTOBJECT_H__

#include "../V8/v8.h"
#include "../JuceLibraryCode/JuceHeader.h"


class ScriptObject
{
public:
    ScriptObject(void);

public:
    v8::Handle<v8::External> Persist(v8::Isolate *isolate);
    v8::Handle<v8::Object> Wrap(v8::Isolate *isolate);
    void DeleteOnGC(bool value);

private:
    static void WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObject>& data);
    v8::Persistent<v8::Value> instanceWrapper;
    bool deleteOnGC;
};


#endif //__SCRIPTOBJECT_H__
