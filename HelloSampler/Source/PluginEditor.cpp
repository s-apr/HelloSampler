/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessorEditor::HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveThumbnail (p), mADSRComponent (p), audioProcessor(p) //construction (same name as class)
{
        addAndMakeVisible(mWaveThumbnail); //makes WaveThumbnail visible in the GUI
        addAndMakeVisible(mADSRComponent);
        
        juce::Timer::startTimerHz (30);
        
        setSize (600, 400);

}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{
    juce::Timer::stopTimer();
}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
}

void HelloSamplerAudioProcessorEditor::resized()
{
    mWaveThumbnail.setBoundsRelative(0.0f, 0.25f, 1.0f, 0.5f); //is called when the waveform changes or the window is resized
    mADSRComponent.setBoundsRelative(0.0f, 0.75f, 1.0f, 0.25f);
}

void HelloSamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}
