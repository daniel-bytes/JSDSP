#ifndef __SCRIPTFUNCTIONMETADATA_H__
#define __SCRIPTFUNCTIONMETADATA_H__

#include "../V8/v8.h"
#include "ScriptMetadata.h"

class ScriptFunctionMetadata
    : public ScriptMetadata
{
public:
    virtual const char* GetName(void) = 0;

    virtual void FunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info) = 0;

    virtual void Configure(v8::Isolate *isolate) {}

    v8::Handle<v8::External> Persist(v8::Isolate *isolate);

private:
    static void WeakRefCallback(const v8::WeakCallbackData<v8::Value, ScriptFunctionMetadata>& data);

private:
    v8::Persistent<v8::Value> instanceWrapper;
    v8::Persistent<v8::FunctionTemplate> functionTemplateWrapper;
};

#endif //__SCRIPTFUNCTIONMETADATA_H__