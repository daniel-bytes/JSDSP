#include "ScriptConsoleComponent.h"

ScriptConsoleComponent::ScriptConsoleComponent(void)
{
    this->setReadOnly(true);
}

ScriptConsoleComponent::~ScriptConsoleComponent(void)
{
}

void ScriptConsoleComponent::print(const juce::String &text)
{
    juce::String str = text;
    str << "\r\n";
    this->insertTextAtCaret(str);
}