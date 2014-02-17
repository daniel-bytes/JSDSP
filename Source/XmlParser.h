#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterControl.h"

class AppWindow;

struct ApplicationSettings
{
    juce::ScopedPointer<AppWindow> window;
    juce::Array<juce::Component*> allComponents;
    juce::Array<ParameterControl*> allParameterControls;
    juce::String xmlfile;
    juce::String dspScript;
    juce::String uiScript;
    juce::String error;
};

bool ParseXml(ApplicationSettings &settings, juce::String filePath);

#endif //__XMLPARSER_H__