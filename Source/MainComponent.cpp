#include "MainComponent.h"
#include "DspCallback.h"
#include "ScriptProcessor.h"
#include "JSFile.h"
#include "XmlParser.h"
#include "AppWindow.h"

MainComponent::MainComponent(void)
{
    projectFileLabel = new Label("Project File: ");
    addAndMakeVisible(projectFileLabel);
    projectFileLabel->setBounds(5, 5, 400, 20);

    projectFileSelectButton = new TextButton("projectFileSelectButton", "Select Project File");
    addAndMakeVisible(projectFileLabel);
    projectFileLabel->setBounds(5, 410, 100, 20);

    
    ApplicationSettings settings;
    ParseXml(settings, "C:\\Users\\Daniel\\Documents\\GitHub\\JSDSP\\Source\\app.jsdsp");
    appWindow = settings.window;
    allComponents.addArray(settings.allComponents);
    allParameterControls.addArray(settings.allParameterControls);

    dspCallback = new DspCallback(allParameterControls);
    dspCallback->SetAudioScript(settings.dspScript);

	audioDeviceManager = new AudioDeviceManager();
	audioDeviceManager->initialise(2, 2, nullptr, false);

    audioDeviceSelector = new AudioDeviceSelectorComponent(*audioDeviceManager, 0, 10, 2, 10, true, true, true, false);
    addAndMakeVisible(audioDeviceSelector);
    audioDeviceSelector->setBounds(5, 25, 600, 400);

    audioDeviceManager->addAudioCallback(dspCallback);
    
    appWindow->toFront(true);
}

MainComponent::~MainComponent(void)
{
    audioDeviceManager->removeAudioCallback(dspCallback);

    appWindow = nullptr;
	audioDeviceSelector = nullptr;
	audioDeviceManager = nullptr;
    dspCallback = nullptr;
}

void MainComponent::buttonClicked(Button *buttonThatWasClicked)
{

}

void MainComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    
}