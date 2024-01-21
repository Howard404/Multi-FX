/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainComponent.h"

//==============================================================================
/**
*/
class MultiFXAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MultiFXAudioProcessorEditor (MultiFXAudioProcessor&);
    ~MultiFXAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultiFXAudioProcessor& audioProcessor;
    MainComponent audioWindow;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiFXAudioProcessorEditor)
};
