#include "XmlParser.h"
#include "AppWindow.h"
#include "DocumentModel.h"
#include "ScriptableSlider.h"
#include "JSFile.h"

using namespace juce;

int GetDoubleAttribute(XmlElement *element, const char *name, double defaultValue);
int GetIntAttribute(XmlElement *element, const char *name, int defaultValue);
juce::String GetStringAttribute(XmlElement *element, const char *name, const char *defaultValue);

bool ParseScriptsSection(ApplicationSettings &settings, XmlElement *element);
bool ParseInterfaceSection(ApplicationSettings &settings, XmlElement *element);
bool ParseWindowSection(ApplicationSettings &settings, XmlElement *element);
bool ParseSliderControl(ApplicationSettings &settings, XmlElement *element, Component *parentComponent, Slider::SliderStyle style);

// Implementations
int GetDoubleAttribute(XmlElement *element, const char *name, double defaultValue)
{
    return element->hasAttribute(name) ? element->getDoubleAttribute(name) : defaultValue;
}

int GetIntAttribute(XmlElement *element, const char *name, int defaultValue)
{
    return element->hasAttribute(name) ? element->getIntAttribute(name) : defaultValue;
}

juce::String GetStringAttribute(XmlElement *element, const char *name, const char *defaultValue)
{
    return element->hasAttribute(name) ? element->getStringAttribute(name) : defaultValue;
}

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
            auto type = GetStringAttribute(scriptElement, "type", "ui");
            auto pathtype = GetStringAttribute(scriptElement, "pathtype", "");
            auto path = GetStringAttribute(scriptElement, "path", "");
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
    windowParams.id = GetStringAttribute(element, "id", "window");
    windowParams.text = GetStringAttribute(element, "text", "");
    windowParams.width = GetIntAttribute(element, "width", 1000);
    windowParams.height = GetIntAttribute(element, "height", 800);

    auto window = new AppWindow(windowParams);

    for (int i = 0; i < element->getNumChildElements(); i++) {
        auto childElement = element->getChildElement(i);

        if (childElement->getTagName() == "knob") {
            ParseSliderControl(settings, childElement, window->getMainComponent(), Slider::SliderStyle::RotaryVerticalDrag);
        }
        else if (childElement->getTagName() == "slider") {
            auto direction = GetStringAttribute(childElement, "direction", "vertical");
            Slider::SliderStyle style = direction == "horizontal" ? Slider::SliderStyle::LinearHorizontal : Slider::SliderStyle::LinearBarVertical;
            ParseSliderControl(settings, childElement, window->getMainComponent(), style);
        }
    }

    settings.window = window;

    return true;
}

bool ParseSliderControl(ApplicationSettings &settings, XmlElement *element, Component *parentComponent, Slider::SliderStyle style)
{    
    ScriptableSliderCreateParams params;
    params.id = GetStringAttribute(element, "id", "");
    params.text = GetStringAttribute(element, "text", "");
    params.parametername = GetStringAttribute(element, "parameter", "");
    params.min = GetDoubleAttribute(element, "min", 0.0);
    params.max = GetDoubleAttribute(element, "max", 1.0);
    params.defaultvalue = GetDoubleAttribute(element, "default", (params.max - params.min) / 2.0);
    params.interval = GetDoubleAttribute(element, "interval", 0.0);
    params.x = GetIntAttribute(element, "left", 0);
    params.y = GetIntAttribute(element, "top", 0);
    params.width = GetIntAttribute(element, "width", 0);
    params.height = GetIntAttribute(element, "height", 0);
    params.style = style;

    auto slider = new ScriptableSlider();
    slider->init(params);
    slider->DeleteOnGC(false);
    parentComponent->addAndMakeVisible(slider);
    settings.allComponents.add(slider);
    settings.allParameterControls.add(slider);
    settings.documentModel->AppendElement(slider);
    settings.scriptMetadata.add(new ScriptableSlider::Metadata(slider));

    return true;
}