#include "ScriptConsoleComponent.h"
#include "ScriptUtility.h"

ScriptConsoleComponent::ScriptConsoleComponent(void)
{
    this->setReadOnly(true);
    this->setMultiLine(true);
}

ScriptConsoleComponent::~ScriptConsoleComponent(void)
{
}

void ScriptConsoleComponent::FunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    juce::String str = this->getText();

    for (int i = 0; i < info.Length(); i++) {
        str << ToJuceString(info[i]) << " ";
    }
    str << "\r\n";

    this->setText(str);
}

void ScriptConsoleComponent::print(const juce::String &text)
{
    this->insertTextAtCaret(text);
}
