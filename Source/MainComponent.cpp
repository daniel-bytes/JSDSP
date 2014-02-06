#include "MainComponent.h"
#include "DspCallback.h"
#include "ScriptProcessor.h"
#include "JSFile.h"
#include "Parameters.h"
#include "XmlParser.h"

MainComponent::MainComponent(void)
{
    parameters = new Parameters();
    parameters->SetParameter("frequency", 100.0);
    
    ApplicationSettings settings;
    
    ParseXml(settings, "C:\\Users\\Daniel\\Documents\\GitHub\\JSDSP\\Source\\app.jsdsp");
    appWindow = settings.window;

    dspCallback = new DspCallback(parameters);
    dspCallback->SetAudioScript(settings.dspScript);

	audioDeviceManager = new AudioDeviceManager();
	audioDeviceManager->initialise(2, 2, nullptr, false);

    audioDeviceSelector = new AudioDeviceSelectorComponent(*audioDeviceManager, 0, 10, 2, 10, true, true, true, false);
    addAndMakeVisible(audioDeviceSelector);
    audioDeviceSelector->setBounds(5, 5, 600, 400);

    audioDeviceManager->addAudioCallback(dspCallback);

}

MainComponent::~MainComponent(void)
{
    //audioDeviceManager->removeAudioCallback(dspCallback);

    appWindow = nullptr;
	audioDeviceSelector = nullptr;
	audioDeviceManager = nullptr;
    dspCallback = nullptr;
    parameters = nullptr;
}

void MainComponent::buttonClicked(Button *buttonThatWasClicked)
{

}

void MainComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    
}