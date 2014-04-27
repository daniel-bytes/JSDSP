#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../V8/v8.h"
#include "ParameterControl.h"
#include "ScriptableSlider.h"

class AppWindow;
class DocumentModel;

struct ApplicationSettings
{
    DocumentModel* documentModel;
    juce::Array<ScriptMetadata*> scriptMetadata;

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