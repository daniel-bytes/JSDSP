#ifndef __APPWINDOW_H__
#define __APPWINDOW_H__

#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce;

class AppComponent;

//
// Defines parameter values used to create a new AppWindow
struct AppWindowCreateParams
{
    juce::String id;
    juce::String text;
    int width;
    int height;
};

//
// Document Window created dynamically by parsing a .jsdsp XML file.
// This is the primary window used by the JSDSP application, as defined
// in the .jsdsp XML and accompanying Javascript files.
class AppWindow  
	: public DocumentWindow
{
public:
    //==============================================================================
    AppWindow(AppWindowCreateParams params);
    ~AppWindow();

    //==============================================================================
	void closeButtonPressed();

    void paint (Graphics& g);
    void resized();

    Component* getMainComponent(void);

private:
    ScopedPointer<AppComponent> mainComponent;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppWindow)
};


#endif   // __APPWINDOW_H__
