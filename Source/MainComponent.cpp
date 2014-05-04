#include "MainComponent.h"
#include "ScriptConsoleComponent.h"
#include "DspCallback.h"
#include "ScriptProcessor.h"
#include "JSFile.h"
#include "XmlParser.h"
#include "AppWindow.h"
#include "ScriptProcessor.h"
#include "DocumentModel.h"
#include "FileSystem.h"

MainComponent::MainComponent(void)
{
    String text = "Project File: ";
    projectFileLabel = new Label("projectFileLabel", text);
    addAndMakeVisible(projectFileLabel);
    projectFileLabel->setBounds(5, 5, 400, 20);

    projectFileSelectButton = new TextButton("Select Project File", "Select Project File");
    addAndMakeVisible(projectFileSelectButton);
    projectFileSelectButton->setBounds(5, 30, 100, 25);
    projectFileSelectButton->addListener(this);

	audioDeviceManager = new AudioDeviceManager();
	audioDeviceManager->initialise(2, 2, nullptr, false);

    audioDeviceSelector = new AudioDeviceSelectorComponent(*audioDeviceManager, 0, 10, 2, 10, true, true, true, false);
    addAndMakeVisible(audioDeviceSelector);
    audioDeviceSelector->setBounds(5, 65, 600, 600);

    scriptConsole = new ScriptConsoleComponent();
    addAndMakeVisible(scriptConsole);
    scriptConsole->setBounds(610, 25, 560, 420);
    settings.scriptMetadata.add(scriptConsole);

    documentModel = new DocumentModel();
    settings.scriptMetadata.add(new DocumentModel::Metadata(documentModel));
    settings.documentModel = this->documentModel;

    settings.scriptMetadata.add(new FileSystem::Metadata());
    //appWindow->toFront(true);

    uiScriptProcessor = new ScriptProcessor();
}

MainComponent::~MainComponent(void)
{
    audioDeviceManager->removeAudioCallback(dspCallback);

    appWindow = nullptr;
	audioDeviceSelector = nullptr;
	audioDeviceManager = nullptr;
    dspCallback = nullptr;
    uiScriptProcessor = nullptr;
    documentModel = nullptr;
}

void MainComponent::init(const String &filePath)
{
    ParseXml(settings, filePath);
    appWindow = settings.window;
    allComponents.addArray(settings.allComponents);
    allParameterControls.addArray(settings.allParameterControls);

    String text = "Project File: ";
    text << filePath;
    projectFileLabel->setText(text, NotificationType::dontSendNotification);

    if (dspCallback != nullptr) {
        audioDeviceManager->removeAudioCallback(dspCallback);
        dspCallback = nullptr;
    }

    dspCallback = new DspCallback(allParameterControls);
    //dspCallback->SetAudioScript(settings.dspScript);
    //audioDeviceManager->addAudioCallback(dspCallback);

    auto result = uiScriptProcessor->Execute(settings.uiScript, settings.scriptMetadata.begin(), settings.scriptMetadata.end());

    if (!result.success) {
        scriptConsole->print(result.result);
    }
}

void MainComponent::buttonClicked(Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == projectFileSelectButton) {
        auto file = File::getSpecialLocation(File::SpecialLocationType::currentExecutableFile);
        juce::FileChooser f("Select a .jsdsp file", file.getParentDirectory(), "*.jsdsp", true);

        if (f.browseForFileToOpen()) {
            init(f.getResult().getFullPathName());
        }
    }
}

void MainComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    
}