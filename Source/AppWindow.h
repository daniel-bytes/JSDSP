#ifndef __APPWINDOW_H__
#define __APPWINDOW_H__

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;


class AppWindow  
	: public DocumentWindow
{
public:
    //==============================================================================
    AppWindow();
    ~AppWindow();

    //==============================================================================
	void closeButtonPressed();

    void paint (Graphics& g);
    void resized();



private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppWindow)
};


#endif   // __APPWINDOW_H__
