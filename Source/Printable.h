#ifndef __PRINTABLE_H__
#define __PRINTABLE_H__

#include "../JuceLibraryCode/JuceHeader.h"

class Printable
{
public:
    virtual void print(const juce::String &text) = 0;
};

#endif //__PRINTABLE_H__