#include "ScriptableSlider.h"
#include "ScriptUtility.h"

ScriptableSlider::ScriptableSlider(void)
{
}

ScriptableSlider::~ScriptableSlider(void)
{
}

void ScriptableSlider::init(const ScriptableSliderCreateParams &params)
{
    this->SetID(params.id);
    this->setComponentID(params.id);
    this->parameterName = params.parametername;

    setBounds(params.x, params.y, params.width, params.height);
    setSliderStyle(params.style);

    setRange(params.min, params.max, params.interval);
    setDoubleClickReturnValue(true, params.defaultvalue);
    setValue(params.defaultvalue);

    this->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, params.width, 20);
    
    label = new juce::Label("label", params.text);
    label->attachToComponent(this, false);
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

ScriptableSlider::Metadata::Metadata(ScriptableSlider *instance)
    : ScriptSingletonMetadata(instance)
{
}

const char* ScriptableSlider::Metadata::GetName(void)
{
    auto slider = (ScriptableSlider*)this->scriptObjectInstance;
    return slider->getComponentID().toUTF8();
}

void ScriptableSlider::Metadata::Configure(v8::Isolate *isolate)
{
    SetProperty(isolate, "parameter",
        [] (v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
            v8::HandleScope scope(info.GetIsolate());
            auto instance = UnwrapInternalObject<ScriptableSlider>(info.GetIsolate(), info.Holder());
            info.GetReturnValue().Set(instance->getValue());
        },
        [] (v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info) {
            v8::HandleScope scope(info.GetIsolate());
            auto instance = UnwrapInternalObject<ScriptableSlider>(info.GetIsolate(), info.Holder());
            if (value->IsNumber()) {
                auto number = value->NumberValue();
                instance->setValue(number);
            }
        });
}