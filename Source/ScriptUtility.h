#ifndef __SCRIPTUTILITY_H__
#define __SCRIPTUTILITY_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../V8/v8.h"

inline juce::String ToJuceString(v8::Handle<v8::Value> &value)
{
    juce::String result;

    if (!value->IsNull() && !value->IsUndefined()) {
        v8::String::AsciiValue v(value->ToString());
        result << *v;
    }

    return result;
}


template<typename TScriptObject>
TScriptObject* UnwrapInternalDataObject(v8::Isolate *isolate, v8::Handle<v8::Value> data)
{
    v8::HandleScope scope(isolate);
    
    auto external = data.As<v8::External>();
    auto ptr = external->Value();

    return static_cast<TScriptObject*>(ptr);
}

template<typename TScriptObject>
TScriptObject* UnwrapInternalObject(v8::Isolate *isolate, v8::Handle<v8::Object> holder)
{
    v8::HandleScope scope(isolate);

    auto internalField = holder->GetInternalField(0);
    auto external = internalField.As<v8::External>();
    auto ptr = external->Value();

    return static_cast<TScriptObject*>(ptr);
}

#endif //__SCRIPTUTILITY_H__