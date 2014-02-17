#ifndef __PARAMETERCONTROL_H__
#define __PARAMETERCONTROL_H__

#include "../JuceLibraryCode/JuceHeader.h"

class ParameterControl
{
public:
    virtual int getParameterCount(void) const = 0;
    virtual bool getParameter(int index, juce::String &name, juce::var &value) = 0;
};

#endif //__PARAMETERCONTROL_H__