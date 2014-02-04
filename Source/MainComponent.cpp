#include "MainComponent.h"
#include "DspCallback.h"
#include "ScriptProcessor.h"
#include "JSFile.h"

MainComponent::MainComponent(void)
{
    auto script = parseFolder("C:\\Users\\Daniel\\Documents\\GitHub\\JSDSP\\Source");

    dspCallback = new DspCallback(script);
    audioSetupButton = new TextButton("Audio Setup", "Audio Setup");
    addAndMakeVisible(audioSetupButton);
    audioSetupButton->setBounds(10, 10, 100, 20);
    audioSetupButton->addListener(this);

    executeButton = new TextButton("Execute Script", "Execute Script");
    addAndMakeVisible(executeButton);
    executeButton->setBounds(200, 10, 150, 20);
    executeButton->addListener(this);

	audioDeviceManager = new AudioDeviceManager();
	audioDeviceManager->initialise(2, 2, nullptr, false);

    audioDeviceSelector = new AudioDeviceSelectorComponent(*audioDeviceManager, 0, 10, 2, 10, true, true, true, false);
    audioDeviceSelector->setBounds(5, 5, 600, 400);

    audioDeviceManager->addAudioCallback(dspCallback);
}

MainComponent::~MainComponent(void)
{
    //audioDeviceManager->removeAudioCallback(dspCallback);

    audioSetupButton = nullptr;
	audioDeviceSelector = nullptr;
	audioDeviceManager = nullptr;
    dspCallback = nullptr;
}

void MainComponent::buttonClicked(Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == audioSetupButton) {
        DialogWindow::LaunchOptions options;
        options.content = OptionalScopedPointer<Component>(audioDeviceSelector, false);
        options.dialogTitle = "Audio Device Setup";
        options.launchAsync();
    }
    else if (buttonThatWasClicked == executeButton) {

    }
}

void MainComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    
}