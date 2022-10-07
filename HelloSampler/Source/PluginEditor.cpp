/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessorEditor::HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //mLoadButton.onClick = [&]() { audioProcessor.loadFile(); }; //Load Button Constructor
    //addAndMakeVisible(mLoadButton);

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
        p.clear();

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


    //g.setColour(juce::Colours::white);
    //g.setFont(15.0f);

    //if (audioProcessor.getNumSamplerSounds() > 0)
    //{
    //    g.fillAll(juce::Colours::blueviolet);
    //    g.drawText("Sound Loaded", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, juce::Justification::centred);
    //}
    //else
    //{
    //    g.drawText("Load a sound", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, juce::Justification::centred);
    //}
}

void HelloSamplerAudioProcessorEditor::resized()
{

    //mLoadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);

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