#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include <functional>

class Parameters
{
    typedef juce::HashMap<juce::String, juce::var, juce::DefaultHashFunctions, juce::CriticalSection> HashMapType;

public:
    void SetParameter(juce::String name, juce::var value) {
        parameters.set(name, value);
    }

    juce::var GetParameter(juce::String name) {
        return parameters[name];
    }

    void ForEachParameter(std::function<void(juce::String, juce::var)> callback) {
        juce::ScopedLock lock(parameters.getLock());

        for (HashMapType::Iterator it(parameters); it.next();) {
            callback(it.getKey(), it.getValue());
        }
    }

private:
    HashMapType parameters;
};

#endif //__PARAMETERS_H__