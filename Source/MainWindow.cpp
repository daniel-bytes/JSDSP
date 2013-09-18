/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainWindow.h"
#include "MainMenuBar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainWindow::MainWindow ()
    : DocumentWindow ("JSDSP",
                      Colours::azure,
                      DocumentWindow::allButtons,
                      true)
{

    //[UserPreSize]
    setResizable (true, false); // resizability is a property of ResizableWindow
    setResizeLimits (400, 300, 8192, 8192);
    //[/UserPreSize]

    setSize (1200, 800);


    //[Constructor] You can add your own custom stuff here..
	scriptRunner = new ScriptRunner();
	scriptRunner->setVisible(true);

	setUsingNativeTitleBar(true);
#if HIDE
	MainMenuBar *menuBar = new MainMenuBar();
    setContentOwned (menuBar, false);

    // this tells the DocumentWindow to automatically create and manage a MenuBarComponent
    // which uses our contentComp as its MenuBarModel
    setMenuBar (menuBar);
#endif
    //[/Constructor]
}

MainWindow::~MainWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	scriptRunner = nullptr;
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainWindow::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}


void MainWindow::closeButtonPressed()
{
	JUCEApplicationBase::quit();
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainWindow" componentName=""
                 parentClasses="public DocumentWindow" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1200" initialHeight="1000">
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
