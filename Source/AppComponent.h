#ifndef __APPCOMPONENT_H__
#define __APPCOMPONENT_H__

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;

class AppComponent
     : public Component
{
public:
    AppComponent(juce::String name)
        : Component(name)
    {
    }

    virtual ~AppComponent()
    {
    }

    void paint(Graphics &g);
};

#endif //__APPCOMPONENT_H__