#include "AppWindow.h"

//==============================================================================
AppWindow::AppWindow (AppWindowCreateParams params)
    : DocumentWindow (params.id,
      Colours::azure,
      DocumentWindow::allButtons,
      true)
{
    setResizable (true, true); // resizability is a property of ResizableWindow

	setUsingNativeTitleBar(true);

    
    centreWithSize (params.width, params.height);
    setVisible (true);
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
