#include "AppWindow.h"
#include "AppComponent.h"

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

    mainComponent = new AppComponent("main");
    mainComponent->setSize(params.width, params.height);
    
    setContentNonOwned(mainComponent, true);
    mainComponent->setVisible(true);
}

AppWindow::~AppWindow()
{
    mainComponent = nullptr;
}

Component* AppWindow::getMainComponent(void)
{
    return mainComponent;
}

//==============================================================================
void AppWindow::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void AppWindow::resized()
{
}

void AppWindow::closeButtonPressed()
{
	JUCEApplicationBase::quit();
}
