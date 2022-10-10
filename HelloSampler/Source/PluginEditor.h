/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HelloSamplerAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::FileDragAndDropTarget, juce::Slider::Listener
{
public:
    HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor&);
    ~HelloSamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray& files); //override;
    void filesDropped(const juce::StringArray& files, int x, int y);

    void sliderValueChanged(juce::Slider* slider);
    //void juce::Slider::Listener::sliderValueChanged(Slider* slider);

private:
    std::vector<float> mAudioPoints;
    bool mShouldBePainting{ false };

    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider; //defining slider classes
    juce::Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel; //displays text string

    HelloSamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloSamplerAudioProcessorEditor)
};
