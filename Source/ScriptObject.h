#ifndef __SCRIPTOBJECT_H__
#define __SCRIPTOBJECT_H__

#include "../V8/v8.h"

class ScriptObject
{
public:
	virtual void Register(v8::Handle<v8::ObjectTemplate> global) = 0;
};

#endif //__SCRIPTOBJECT_H__
