#include "JSFile.h"

juce::String downloadFile(const juce::String &url)
{
    juce::URL webreq(url);
    auto results = webreq.readEntireTextStream();
    return results;
}

juce::String parseFolder(const juce::String &folder)
{
    juce::File dir(folder);
    juce::String script;

    if (dir.isDirectory() && dir.exists()) {
        juce::Array<juce::File> jsfiles;

        dir.findChildFiles(jsfiles, juce::File::TypesOfFileToFind::findFiles, false, "*.js");

        for (auto jsfile : jsfiles) {
            script << parseFile(jsfile) << "\r\n";
        }
        
    }
    return script;

}

juce::String parseFile(const juce::File &jsfile)
{
    juce::String script;

    if (jsfile.existsAsFile()) {
        script << "// File: " << jsfile.getFileName() << "\r\n";
        juce::StringArray lines;
        jsfile.readLines(lines);

        for (auto str : lines) {
            script << str << "\r\n";
        }
    }

    return script;
}

juce::String parseFile(const juce::String &file)
{
    juce::File jsfile(file);

    return parseFile(jsfile);
}