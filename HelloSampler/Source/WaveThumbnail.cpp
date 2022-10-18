/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 17 Oct 2022 6:53:21pm
    Author:  maxbu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"

//==============================================================================
WaveThumbnail::WaveThumbnail(HelloSamplerAudioProcessor& p) : audioProcessor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveThumbnail::~WaveThumbnail()
{
}

void WaveThumbnail::paint (juce::Graphics& g)
{

    g.fillAll(juce::Colours::cadetblue.darker());

    auto waveform = audioProcessor.getWaveForm();

    if(waveform.getNumSamples() > 0)
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

        g.setColour(juce::Colours::red);

        p.startNewSubPath(0, getHeight() / 2);

        //scale audio (y)
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0);
            p.lineTo(sample, point);
        }

        g.strokePath(p, juce::PathStrokeType(2));

        g.setColour(juce::Colours::white);
        g.setFont(15.0f);

        auto textBounds = getLocalBounds().reduced(10, 10);

        g.drawFittedText(mFileName, textBounds, juce::Justification::topRight, 1);

        auto playHeadPosition = juce::jmap<int>(audioProcessor.SampleCount(), 0, audioProcessor.getWaveForm().getNumSamples(), 0, getWidth());

        g.setColour(juce::Colours::white);
        g.drawLine(playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);

        g.setColour(juce::Colours::black.withAlpha(0.2f));
        g.fillRect(0, 0, playHeadPosition, getHeight());

    }
    else
    {
        g.setColour(juce::Colours::white);
        g.setFont(40.0f);

        g.drawFittedText("Drop and Audio File to Load", getLocalBounds(), juce::Justification::centred, 1);

    }

}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

bool WaveThumbnail::isInterestedInFileDrag(const juce::StringArray& files) //calls IIFile Drag (is it a valid file?)
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


void WaveThumbnail::filesDropped(const juce::StringArray& files, int x, int y) //calls when file is dropped
{
    for (auto file : files) //traverse through string array 'files'
    {
        if (isInterestedInFileDrag(file))
        {

            auto myFile = std::make_unique<juce::File>(file);
            mFileName = myFile->getFileNameWithoutExtension();

            audioProcessor.loadFile(file);
        }
    }

    repaint();

}
