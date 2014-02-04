#ifndef __APPWINDOW_H__
#define __APPWINDOW_H__

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;


struct AppWindowCreateParams
{
    juce::String id;
    juce::String text;
    int width;
    int height;
};

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



private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppWindow)
};


#endif   // __APPWINDOW_H__
