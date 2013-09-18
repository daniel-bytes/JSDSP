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

#include "ScriptRunner.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ScriptRunner::ScriptRunner ()
{
    addAndMakeVisible (scriptEditor = new TextEditor ("scriptEditor"));
    scriptEditor->setMultiLine (true);
    scriptEditor->setReturnKeyStartsNewLine (true);
    scriptEditor->setReadOnly (false);
    scriptEditor->setScrollbarsShown (true);
    scriptEditor->setCaretVisible (true);
    scriptEditor->setPopupMenuEnabled (true);
    scriptEditor->setText (String::empty);

    addAndMakeVisible (scriptOutput = new TextEditor ("scriptOutput"));
    scriptOutput->setMultiLine (true);
    scriptOutput->setReturnKeyStartsNewLine (false);
    scriptOutput->setReadOnly (true);
    scriptOutput->setScrollbarsShown (true);
    scriptOutput->setCaretVisible (true);
    scriptOutput->setPopupMenuEnabled (true);
    scriptOutput->setText (String::empty);

    addAndMakeVisible (executeButton = new TextButton ("executeButton"));
    executeButton->setButtonText ("Execute Script");
    executeButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ScriptRunner::~ScriptRunner()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    scriptEditor = nullptr;
    scriptOutput = nullptr;
    executeButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ScriptRunner::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ScriptRunner::resized()
{
    scriptEditor->setBounds (8, 48, 1056, 456);
    scriptOutput->setBounds (8, 512, 1056, 240);
    executeButton->setBounds (912, 16, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ScriptRunner::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == executeButton)
    {
        //[UserButtonCode_executeButton] -- add your button handler code here..
        //[/UserButtonCode_executeButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ScriptRunner" componentName=""
                 parentClasses="public DocumentWindow" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="scriptEditor" id="27d32435f370ad22" memberName="scriptEditor"
              virtualName="" explicitFocusOrder="0" pos="8 48 1056 456" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="scriptOutput" id="b6e58cf8e3b5c6dc" memberName="scriptOutput"
              virtualName="" explicitFocusOrder="0" pos="8 512 1056 240" initialText=""
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="executeButton" id="97bc236ac0762085" memberName="executeButton"
              virtualName="" explicitFocusOrder="0" pos="912 16 150 24" buttonText="Execute Script"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
