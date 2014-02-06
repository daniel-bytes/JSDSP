#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include "../JuceLibraryCode/JuceHeader.h"

struct ApplicationSettings
{
    juce::ScopedPointer<juce::DocumentWindow> window;
    juce::String xmlfile;
    juce::String dspScript;
    juce::String uiScript;
    juce::String error;
};

bool ParseXml(ApplicationSettings &settings, juce::String filePath);

#endif //__XMLPARSER_H__