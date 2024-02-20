/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//#include "MainComponent.h"

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

    //MainComponent* audioWindow;

    juce::ListBox activeEffects;
    juce::ListBox effectLibrary;



    juce::TextButton reverb;
    juce::TextButton chorus;
    juce::TextButton muteChorus;
    juce::TextButton muteReverb;
    //juce::ImageButton muteChorus; 
    //juce::ImageButton muteReverb;
    juce::File mutedPic = juce::File::getCurrentWorkingDirectory().getChildFile("Muted.png");
    juce::File unMutedPic = juce::File::getCurrentWorkingDirectory().getChildFile("Unmuted.png");
    juce::Image muted = juce::ImageFileFormat::loadFrom(mutedPic);
    juce::Image unmuted = juce::ImageFileFormat::loadFrom(unMutedPic);
    //juce::Drawable *mutedSVG{ juce::DrawableImage::createFromImageFile(mutedPic) };
    juce::TextButton save;
    juce::TextButton load;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiFXAudioProcessorEditor)
};




