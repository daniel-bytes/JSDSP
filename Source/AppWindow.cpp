#include "AppWindow.h"


//==============================================================================
AppWindow::AppWindow ()
    : DocumentWindow ("JSDSP",
      Colours::azure,
      DocumentWindow::allButtons,
      true)
{
    setResizable (true, true); // resizability is a property of ResizableWindow

	setUsingNativeTitleBar(true);
}

AppWindow::~AppWindow()
{
}

//==============================================================================
void AppWindow::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void AppWindow::resized()
{
}

void AppWindow::closeButtonPressed()
{
	JUCEApplicationBase::quit();
}
