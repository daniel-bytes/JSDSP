#ifndef __JSFILE_H__
#define __JSFILE_H__

#include "../JuceLibraryCode/JuceHeader.h"

juce::String parseFolder(const juce::String &folder);
juce::String parseFile(const juce::String &file);
juce::String parseFile(const juce::File &jsfile);
juce::String downloadFile(const juce::String &url);

#endif //__JSFILE_H__