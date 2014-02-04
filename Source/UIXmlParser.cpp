#include "UIXmlParser.h"
#include "AppWindow.h"

juce::DocumentWindow* ParseUIXml(juce::String file)
{
    AppWindow *window = new AppWindow();
    window->centreWithSize (1200, 800);
    window->setVisible (true);

    return window;
}