#include "ScriptableSlider.h"
#include "ScriptUtility.h"

ScriptableSlider::ScriptableSlider()
    : data(this)
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
    auto value = this->getValue();
    this->data.setValue(value);
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

v8::Handle<v8::External> ScriptableSlider::Persist(v8::Isolate *isolate, bool makeWeak)
{
    v8::HandleScope scope(isolate);
    auto external = this->data.Persist(isolate, makeWeak);
    return scope.Close(external); 
}

ScriptableSliderMetadata::ScriptableSliderMetadata(ScriptableSlider *instance)
    : ScriptSingletonMetadata(static_cast<ScriptObject*>(instance), false)
{
}

const char* ScriptableSliderMetadata::GetName(void)
{
    auto slider = (ScriptableSlider*)this->scriptObjectInstance;
    return slider->getComponentID().toUTF8();
}

void ScriptableSliderMetadata::Configure(v8::Isolate *isolate)
{
    SetProperty(isolate, "parameter",
        [] (v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
            auto isolate = info.GetIsolate();
            v8::HandleScope scope(isolate);

            auto self = info.Holder();
            auto instance = UnwrapEmbeddedInstance<ScriptableSliderData>(isolate, self);
            auto value = instance->getValue();
            info.GetReturnValue().Set(value);
        },
        [] (v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info) {
            auto isolate = info.GetIsolate();
            v8::HandleScope scope(isolate);

            auto self = info.Holder();
            auto instance = UnwrapEmbeddedInstance<ScriptableSliderData>(isolate, self);
            if (value->IsNumber()) {
                auto number = value->NumberValue();
                instance->setValue(number);
            }
        });
}


ScriptableSliderData::ScriptableSliderData(ScriptableSlider *parent) 
    : value(0), parent(parent) {}

double ScriptableSliderData::getValue(void) { return value; }
void ScriptableSliderData::setValue(double value) { this->value = value; parent->setValue(value, juce::NotificationType::dontSendNotification); }