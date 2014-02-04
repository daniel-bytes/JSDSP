#include "MainWindow.h"
#include "MainComponent.h"

//==============================================================================
MainWindow::MainWindow ()
    : DocumentWindow ("JSDSP",
      Colours::azure,
      DocumentWindow::allButtons,
      true)
{
    setResizable (true, true); // resizability is a property of ResizableWindow
    setResizeLimits (400, 300, 8192, 8192);

    setSize (1200, 800);

	//scriptRunner = new ScriptRunner();
	//setContentComponent(scriptRunner);
	//scriptRunner->setVisible(true);

	setUsingNativeTitleBar(true);
	mainComponent = new MainComponent();
	setContentNonOwned(mainComponent, false);
	mainComponent->setVisible(true);
	mainComponent->setSize(this->getWidth(), this->getHeight());

#if HIDE
	MainMenuBar *menuBar = new MainMenuBar();
    setContentOwned (menuBar, false);

    // this tells the DocumentWindow to automatically create and manage a MenuBarComponent
    // which uses our contentComp as its MenuBarModel
    setMenuBar (menuBar);
#endif
}

MainWindow::~MainWindow()
{
	mainComponent = nullptr;
}

//==============================================================================
void MainWindow::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void MainWindow::resized()
{
}

void MainWindow::closeButtonPressed()
{
	JUCEApplicationBase::quit();
}
