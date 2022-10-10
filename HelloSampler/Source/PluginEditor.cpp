/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessorEditor::HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p) //construction (same name as class)
{

    //attack
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); //initialising sliders for GUI
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20 );
    mAttackSlider.setRange(0.0, 5.0, 0.01);
    mAttackSlider.addListener(this);
    addAndMakeVisible(mAttackSlider);

        mAttackLabel.setFont(10.f);
        mAttackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
        mAttackLabel.setJustificationType(juce::Justification::centredTop);
        mAttackLabel.attachToComponent(&mAttackSlider, false); //pointer to AttackSlider [attatched label to component

    //decay
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); //initialising sliders for GUI
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setRange(0.0, 5.0, 0.01);
    mDecaySlider.addListener(this);
    addAndMakeVisible(mDecaySlider);

        mDecayLabel.setFont(10.f);
        mDecayLabel.setText("Decay", juce::NotificationType::dontSendNotification);
        mDecayLabel.setJustificationType(juce::Justification::centredTop);
        mDecayLabel.attachToComponent(&mDecaySlider, false); //pointer to AttackSlider [attatched label to component


    //sustain
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); //initialising sliders for GUI
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setRange(0.0, 1.0, 0.01);
    mSustainSlider.addListener(this);
    addAndMakeVisible(mSustainSlider);

        mSustainLabel.setFont(10.f);
        mSustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
        mSustainLabel.setJustificationType(juce::Justification::centredTop);
        mSustainLabel.attachToComponent(&mSustainSlider, false); //pointer to AttackSlider [attatched label to component

    
    //release 
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); //initialising sliders for GUI
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mReleaseSlider.setRange(0.0, 5.0, 0.01);
    mReleaseSlider.addListener(this);
    addAndMakeVisible(mReleaseSlider);

        mReleaseLabel.setFont(10.f);
        mReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
        mReleaseLabel.setJustificationType(juce::Justification::centredTop);
        mReleaseLabel.attachToComponent(&mReleaseSlider, false); //pointer to AttackSlider [attatched label to component


    setSize (600, 200);
}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{

}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    if (mShouldBePainting)
    {
        juce::Path p;
        mAudioPoints.clear();

        auto waveform = audioProcessor.getWaveForm();
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);

        //scale audio (x)
        for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }

        p.startNewSubPath(0, getHeight() / 2);

        //scale audio (y)
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, 200, 0);
            p.lineTo(sample, point);
        }

        g.strokePath(p, juce::PathStrokeType(2));

        mShouldBePainting = false;
    }

}

void HelloSamplerAudioProcessorEditor::resized()
{
    const auto startX = 0.6f; //useful if I need to change values in all dials
    const auto startY = 0.6f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.4f;

    mAttackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative(startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative(startX + (dialWidth * 2), startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative(startX + (dialWidth * 3), startY, dialWidth, dialHeight);

}

bool HelloSamplerAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files) //calls IIFile Drag (is it a valid file?)
{
    for (auto file : files)//traverse through string array 'files'
    {
        if (file.contains("wav") || file.contains("mp3") || file.contains("aif")) //checks file extentions
        {
            return true;
        }
    }

    return false;
}

void HelloSamplerAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y) //calls when file is dropped
{
    for (auto file : files) //traverse through string array 'files'
    {
        if (isInterestedInFileDrag(file))
        {
            mShouldBePainting = true;
            audioProcessor.loadFile(file);
        }
    }

    repaint();
}

void HelloSamplerAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &mAttackSlider)
    {
        audioProcessor.attack = mAttackSlider.getValue();
    }
    else if (slider == &mDecaySlider)
    {
        audioProcessor.decay = mDecaySlider.getValue();
    }
    else if(slider == &mSustainSlider)
    {
        audioProcessor.sustain = mSustainSlider.getValue();
    }
    else if (slider == &mReleaseSlider)
    {
        audioProcessor.release = mReleaseSlider.getValue();
    }
}
