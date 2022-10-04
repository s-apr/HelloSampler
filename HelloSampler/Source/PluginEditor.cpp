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
    mLoadButton.onClick = [&]() { audioProcessor.loadFile(); }; //Load Button Constructor
    addAndMakeVisible(mLoadButton);

    setSize (200, 200);
}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{
}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void HelloSamplerAudioProcessorEditor::resized()
{

    mLoadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);

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
            audioProcessor.loadFile(file);
        }
    }
}