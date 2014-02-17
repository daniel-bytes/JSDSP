#include "ScriptableSlider.h"

ScriptableSlider::ScriptableSlider(const ScriptableSliderCreateParams &params)
    : juce::Slider(params.id),
      parameterName(params.parametername)
{
    setBounds(params.x, params.y, params.width, params.height);
    setSliderStyle(params.style);

    setRange(params.min, params.max, params.interval);
    setDoubleClickReturnValue(true, params.defaultvalue);
    setValue(params.defaultvalue);

    this->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, params.width, 20);
    
    label = new juce::Label("label", params.text);
    label->attachToComponent(this, false);
}

ScriptableSlider::~ScriptableSlider(void)
{
}

void ScriptableSlider::valueChanged()
{
}


int ScriptableSlider::getParameterCount(void) const
{
    return 1;
}

bool ScriptableSlider::getParameter(int index, juce::String &name, juce::var &value)
{
    if (index != 0) {
        return false;
    }

    name = parameterName;
    value = getValue();

    return true;
}
