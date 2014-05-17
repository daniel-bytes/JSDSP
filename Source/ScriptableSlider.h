#ifndef __SCRIPTABLESLIDER_H__
#define __SCRIPTABLESLIDER_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "AppComponent.h"

#include "ParameterControl.h"
#include "ScriptUIObject.h"
#include "ScriptSingletonMetadata.h"

class ScriptableSlider;

struct ScriptableSliderCreateParams
{
    int x;
    int y;
    int width;
    int height;
    double min;
    double max;
    double interval;
    float defaultvalue;
    juce::String id;
    juce::String text;
    juce::String parametername;
    juce::Slider::SliderStyle style;
    juce::Slider::TextEntryBoxPosition textposition;
};

class ScriptableSliderData
    : public ScriptObject
{
public:
    ScriptableSliderData(ScriptableSlider *parent);
    double getValue(void);
    void setValue(double value);

private:
    ScriptableSlider *parent;
    double value;
};

class ScriptableSliderMetadata
    : public ScriptSingletonMetadata
{
public:
    ScriptableSliderMetadata(ScriptableSlider *instance);
    virtual const char* GetName(void);
    virtual void Configure(v8::Isolate *isolate);
};

class ScriptableSlider
    : public juce::Slider,
      public ParameterControl,
      public ScriptUIObject
{
public:
    ScriptableSlider(void);
    ~ScriptableSlider(void);

    void init(const ScriptableSliderCreateParams &params);
    virtual v8::Handle<v8::External> Persist(v8::Isolate *isolate, bool makeWeak);

    virtual void valueChanged();
    virtual int getParameterCount(void) const;
    virtual bool getParameter(int index, juce::String &name, juce::var &value);

private:
    juce::ScopedPointer<juce::Label> label;
    juce::String parameterName;
    ScriptableSliderData data;
};

#endif //__SCRIPTABLESLIDER_H__
