/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class HelloSamplerAudioProcessor  : public juce::AudioProcessor, public juce::ValueTree::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    HelloSamplerAudioProcessor();
    ~HelloSamplerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void loadFile(); //Load File Function
    void loadFile(const juce::String& path);

    int getNumSamplerSounds() { return mSampler.getNumSounds(); }
    juce::AudioBuffer<float>& getWaveForm() { return mWaveForm; }

    void updateADSR();

    juce::ADSR::Parameters& getADSRParams() { return mADSRParams; } //referencing private object mADSRParams 
                                                                    //so we are able to access the 'ADSR' member variables & attatch them
                                                                    //to the sliders

    juce::AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; } //using a getter to give access to the prvt APVTS class

    std::atomic<bool>& isNotePlayed() { return mIsNotePlayed; }
    std::atomic<int>& SampleCount() { return mSampleCount; }

private:
    juce::Synthesiser mSampler; //'m' as member variable, have to use juce:: as header is not found
    const int mNumVoices{ 3 }; //number of sampler voices
    juce::AudioBuffer<float> mWaveForm;

    juce::ADSR::Parameters mADSRParams; //holds Attack, Decay, Sustain and Release times (ACTUAL FUNCTION FOR IT)

    juce::AudioFormatManager mFormatManager; 
    juce::AudioFormatReader* mFormatReader { nullptr }; //pointer used if we re-select another file (just point somewhere else)

    juce::AudioProcessorValueTreeState mAPVTS;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property);

    std::atomic<bool> mShouldUpdate{ false };
    std::atomic<bool> mIsNotePlayed{ false };
    std::atomic<int> mSampleCount = {0};

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloSamplerAudioProcessor)
};
