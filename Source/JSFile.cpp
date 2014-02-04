#include "JSFile.h"


juce::String parseFolder(const juce::String &folder)
{
    juce::File dir(folder);
    juce::String script;

    if (dir.isDirectory() && dir.exists()) {
        juce::Array<juce::File> jsfiles;

        dir.findChildFiles(jsfiles, juce::File::TypesOfFileToFind::findFiles, false, "*.js");

        for (auto jsfile : jsfiles) {
            juce::StringArray lines;
            jsfile.readLines(lines);

            for (auto str : lines) {
                script << str << "\r\n";
            }
        }
        
    }
    return script;

}