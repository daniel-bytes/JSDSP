#ifndef __SCRIPTOBJECT_H__
#define __SCRIPTOBJECT_H__

#include "../V8/v8.h"
#include "../JuceLibraryCode/JuceHeader.h"


class ScriptObject
{
public:
    v8::Handle<v8::External> Persist(v8::Isolate *isolate);

    template<typename TScriptObject>
    static TScriptObject* Unwrap(v8::Isolate *isolate, v8::Handle<v8::Object> holder);

private:
    static void WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptObject>& data);

private:
    v8::Persistent<v8::Value> wrapper;
};


template<typename TScriptObject>
TScriptObject* ScriptObject::Unwrap(v8::Isolate *isolate, v8::Handle<v8::Object> holder)
{
    v8::HandleScope scope(isolate);

    auto internalField = holder->GetInternalField(0);
    auto external = internalField.As<v8::External>();
    auto data = external->Value();

    return static_cast<TScriptObject*>(data);
}

#endif //__SCRIPTOBJECT_H__
