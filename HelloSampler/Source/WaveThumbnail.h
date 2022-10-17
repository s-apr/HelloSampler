/*
  ==============================================================================

    WaveThumbnail.h
    Created: 17 Oct 2022 6:53:21pm
    Author:  maxbu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveThumbnail  : public juce::Component, public juce::FileDragAndDropTarget
{
public:
    WaveThumbnail(HelloSamplerAudioProcessor& p); //processor needs to be passed to the WaveThumbnail contructor
                                                  //initialisers (in JUCE) have to give a reference to a processor 
    ~WaveThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray& files); //override;
    void filesDropped(const juce::StringArray& files, int x, int y);

private:
    std::vector<float> mAudioPoints;
    bool mShouldBePainting{ false };

    juce::String mFileName{};

    HelloSamplerAudioProcessor& audioProcessor; //reference to audioProcesser (pluginprocessor)

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
