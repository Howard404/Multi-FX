/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MainComponent.h"

//==============================================================================
MultiFXAudioProcessorEditor::MultiFXAudioProcessorEditor (MultiFXAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1200, 800);
    addAndMakeVisible(audioWindow);
     

    
}

MultiFXAudioProcessorEditor::~MultiFXAudioProcessorEditor()
{
}

//==============================================================================
void MultiFXAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void MultiFXAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    audioWindow.resized();
}
