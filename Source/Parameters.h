#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include <functional>

class Parameters
{
public:
    void SetParameter(juce::String name, juce::var value) {
        parameters.set(name, value);
    }

    juce::var GetParameter(juce::String name) {
        return parameters[name];
    }

    void ForEachParameter(std::function<void(juce::String, juce::var)> callback) {
        for (juce::HashMap<juce::String, juce::var>::Iterator it(parameters); it.next();) {
            callback(it.getKey(), it.getValue());
        }
    }

private:
    juce::HashMap<juce::String, juce::var> parameters;
};

#endif //__PARAMETERS_H__