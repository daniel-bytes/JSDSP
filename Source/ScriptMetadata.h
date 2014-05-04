#ifndef __SCRIPTMETADATA_H__
#define __SCRIPTMETADATA_H__

#include "../V8/v8.h"
#include <map>

class ScriptMetadata
{
public:
    virtual const char* GetName(void) = 0;
    virtual void Configure(v8::Isolate *isolate) = 0;
    virtual v8::Handle<v8::External> Persist(v8::Isolate *isolate) = 0;
};

#endif //__SCRIPTMETADATA_H__