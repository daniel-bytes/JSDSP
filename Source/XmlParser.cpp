#include "XmlParser.h"
#include "AppWindow.h"
#include "JSFile.h"

using namespace juce;

bool ParseScriptsSection(ApplicationSettings &settings, XmlElement *element);
bool ParseInterfaceSection(ApplicationSettings &settings, XmlElement *element);
bool ParseWindowSection(ApplicationSettings &settings, XmlElement *element);


void LoadAppWindowCreateParams(AppWindowCreateParams &params, XmlElement *element);

bool ParseXml(ApplicationSettings &settings, String filePath)
{
    settings.xmlfile = filePath;
    File file(filePath);
    
    if (file.exists()) {
        XmlDocument xmlDocument(file);
        ScopedPointer<XmlElement> element = xmlDocument.getDocumentElement();

        if (element != nullptr) {
            if (element->getTagName() == "jsdsp") {
                auto scripts = element->getChildByName("scripts");
                if (scripts != nullptr) {
                    if (!ParseScriptsSection(settings, scripts)) {
                        return false;
                    }
                }
                else {
                    settings.error = "Missing 'scripts' section";
                    return false;
                }

                auto interface = element->getChildByName("interface");
                if (interface != nullptr) {
                    if (!ParseInterfaceSection(settings, interface)) {
                        return false;
                    }
                }
                else {
                    settings.error = "Missing 'interface' section";
                    return false;
                }
            }
            else {
                settings.error = "Invalid XML.  Top level element should be 'jsdsp'.";
                return false;
            }
        }
        else {
            settings.error = xmlDocument.getLastParseError();
            return false;
        }
    }

    return true;
}


bool ParseScriptsSection(ApplicationSettings &settings, XmlElement *element)
{
    settings.dspScript = "";
    settings.uiScript = "";

    for (int i = 0; i < element->getNumChildElements(); i++) {
        auto scriptElement = element->getChildElement(i);

        if (scriptElement->getTagName() == "script") {
            auto type = scriptElement->getStringAttribute("type");
            auto pathtype = scriptElement->getStringAttribute("pathtype");
            auto path = scriptElement->getStringAttribute("path");
            String script;

            if (pathtype == "file") {
                File file = File(settings.xmlfile).getParentDirectory().getChildFile(path);
                
                if (file.existsAsFile()) {
                    script = parseFile(file);
                }
            }
            else if (pathtype == "web") {
                script = downloadFile(path);
            }

            if (type == "dsp") {
                settings.dspScript << script << "\r\n";
            }
            else if (type == "ui") {
                settings.uiScript << script << "\r\n";
            }
        }
    }

    return true;
}

bool ParseInterfaceSection(ApplicationSettings &settings, XmlElement *element)
{
    auto scripts = element->getChildByName("window");

    if (scripts != nullptr) {
        if (!ParseWindowSection(settings, scripts)) {
            return false;
        }
    }
    else {
        settings.error = "Missing 'interface/window' section.";
        return false;
    }
}

bool ParseWindowSection(ApplicationSettings &settings, XmlElement *element)
{
    AppWindowCreateParams windowParams;
    windowParams.id = element->getStringAttribute("id", "window");
    windowParams.text = element->getStringAttribute("text", "");
    windowParams.width = element->getIntAttribute("width", 1000);
    windowParams.height = element->getIntAttribute("height", 800);

    settings.window = new AppWindow(windowParams);

    return true;
}