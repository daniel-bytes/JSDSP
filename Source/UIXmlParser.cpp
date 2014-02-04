#include "UIXmlParser.h"
#include "AppWindow.h"

using namespace juce;

void LoadAppWindowCreateParams(AppWindowCreateParams &params, XmlElement *element);

ScopedPointer<DocumentWindow> ParseUIXml(String filePath)
{
    ScopedPointer<DocumentWindow> window = nullptr;
    File file(filePath);
    
    if (file.exists()) {
        XmlDocument xmlDocument(file);
        auto element = xmlDocument.getDocumentElement();

        if (element != nullptr) {
            if (element->getTagName() == "interface") {
                auto firstWindow = element->getChildByName("window");

                if (firstWindow != nullptr) {
                    AppWindowCreateParams params;
                    LoadAppWindowCreateParams(params, firstWindow);

                    window = new AppWindow(params);

                    // TODO
                }
            }

            delete element;
        }
        else {
            auto err = xmlDocument.getLastParseError();
        }
    }

    return window;
}


void LoadAppWindowCreateParams(AppWindowCreateParams &params, XmlElement *element)
{
    params.id = element->getStringAttribute("id", "window");
    params.text = element->getStringAttribute("text", "");
    params.width = element->getIntAttribute("width", 1000);
    params.height = element->getIntAttribute("height", 800);
}