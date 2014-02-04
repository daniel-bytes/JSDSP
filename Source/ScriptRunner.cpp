#include "ScriptRunner.h"
#include "ScriptProcessor.h"
#include "DspCallback.h"

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
    scriptOutput->setReturnKeyStartsNewLine (true);
    scriptOutput->setReadOnly (true);
    scriptOutput->setScrollbarsShown (true);
    scriptOutput->setCaretVisible (false);
    scriptOutput->setPopupMenuEnabled (true);
    scriptOutput->setText (String::empty);

    addAndMakeVisible (executeButton = new TextButton ("executeButton"));
    executeButton->setButtonText ("Execute Script");
    executeButton->addListener (this);

    setSize (1200, 800);

	scriptProcessor = new ScriptProcessor();
}

ScriptRunner::~ScriptRunner()
{
    scriptEditor = nullptr;
    scriptOutput = nullptr;
    executeButton = nullptr;
	scriptProcessor = nullptr;
	dspCallback = nullptr;
}

//==============================================================================
void ScriptRunner::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void ScriptRunner::resized()
{
	//auto bounds = this->getBounds();

    scriptEditor->setBounds (8, 48, 1056, 192);
    scriptOutput->setBounds (8, 248, 1056, 128);
    executeButton->setBounds (912, 16, 150, 24);
}

void ScriptRunner::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == executeButton)
    {
		juce::String script = scriptEditor->getText();
		juce::String result = scriptProcessor->Execute(script);
		this->scriptOutput->setText(result);
    }
}

