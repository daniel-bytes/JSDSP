#include "MainComponent.h"
#include "DspCallback.h"
#include "ScriptProcessor.h"
#include "JSFile.h"
#include "Parameters.h"

MainComponent::MainComponent(void)
{
    parameters = new Parameters();
    parameters->SetParameter("frequency", 100.0);

    auto script = parseFolder("C:\\Users\\Daniel\\Documents\\GitHub\\JSDSP\\Source");

    dspCallback = new DspCallback(parameters);
    dspCallback->SetAudioScript(script);

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