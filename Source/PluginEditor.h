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
class ListBoxComponent : public juce::Component, public juce::ListBoxModel

{
public:

    //ListBoxComponent();
    //~ListBoxComponent();

    int getNumRows() override;


    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;

    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate) override;




private:

    juce::Font font{ 10.0f };
    juce::ListBox list{ {}, this };
    int numRows = 0;
    int currentID;

};

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

    ListBoxComponent library;

    juce::TextButton add;
    juce::TextButton remove;
    juce::TextButton save;
    juce::TextButton load;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiFXAudioProcessorEditor)
};

class ListComponent : public juce::Component
{
public:
    ListComponent(juce::String);

    //~ListComponent() override;
    void resized() override;

    

private:
    juce::String id;
    juce::TextButton mute;
    bool muted;
};


