/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 17 Oct 2022 7:54:51pm
    Author:  maxbu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(HelloSamplerAudioProcessor& p) : audioProcessor(p)
{
    //attack
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); //initialising sliders for GUI
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mAttackSlider.setRange(0.0, 5.0, 0.01);
    addAndMakeVisible(mAttackSlider);

    mAttackLabel.setFont(10.f);
    mAttackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    mAttackLabel.setJustificationType(juce::Justification::centredTop);
    mAttackLabel.attachToComponent(&mAttackSlider, false); //pointer to AttackSlider [attatched label to component

    mAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "ATTACK", mAttackSlider);

    //decay
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); //initialising sliders for GUI
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setRange(0.0, 5.0, 0.01);
    addAndMakeVisible(mDecaySlider);

    mDecayLabel.setFont(10.f);
    mDecayLabel.setText("Decay", juce::NotificationType::dontSendNotification);
    mDecayLabel.setJustificationType(juce::Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false); //pointer to AttackSlider [attatched label to component

    mDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DECAY", mDecaySlider);

    //sustain
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); //initialising sliders for GUI
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible(mSustainSlider);

    mSustainLabel.setFont(10.f);
    mSustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
    mSustainLabel.setJustificationType(juce::Justification::centredTop);
    mSustainLabel.attachToComponent(&mSustainSlider, false); //pointer to AttackSlider [attatched label to component

    mSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "SUSTAIN", mSustainSlider);

    //release 
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); //initialising sliders for GUI
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mReleaseSlider.setRange(0.0, 5.0, 0.01);
    addAndMakeVisible(mReleaseSlider);

    mReleaseLabel.setFont(10.f);
    mReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    mReleaseLabel.setJustificationType(juce::Justification::centredTop);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false); //pointer to AttackSlider [attatched label to component
    mReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "RELEASE", mReleaseSlider);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void ADSRComponent::resized()
{
    const auto startX = 0.6f; //useful if I need to change values in all dials
    const auto startY = 0.2f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.75f;

    mAttackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative(startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative(startX + (dialWidth * 2), startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative(startX + (dialWidth * 3), startY, dialWidth, dialHeight);
}
