#ifndef __JUCE_HEADER_1A7C0314FA0C68BA__
#define __JUCE_HEADER_1A7C0314FA0C68BA__

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;

class MainComponent;

class MainWindow  
	: public DocumentWindow
{
public:
    //==============================================================================
    MainWindow ();
    ~MainWindow();

    //==============================================================================
	void closeButtonPressed();

    void paint (Graphics& g);
    void resized();



private:
	ScopedPointer<MainComponent> mainComponent;

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1A7C0314FA0C68BA__
