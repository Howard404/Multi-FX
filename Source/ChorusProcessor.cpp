/*
  ==============================================================================

    ChorusProcessor.cpp
    Created: 23 Jan 2024 5:53:25pm
    Author:  Grant Howard

  ==============================================================================
*/

#include "ChorusProcessor.h"
#include "PluginEditor.h"

ChorusProcessor::ChorusProcessor() : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo())
                                                     .withOutput ("Output", juce::AudioChannelSet::stereo()))
{
}

// Get name function
const juce::String ChorusProcessor::getName() const
{
    // Gets the name of the juce project... ignore
    return {};
}

// Accept midi function is always false (audio only)
bool ChorusProcessor::acceptsMidi() const
{
    return false;
}

bool ChorusProcessor::producesMidi() const
{
    return false;
}

// Returns length of the processor tail (don't need)
double ChorusProcessor::getTailLengthSeconds() const
{
    return 0;
}

// We only have one host program, PluginProcessor, return 0
int ChorusProcessor::getNumPrograms()
{
    return 0;
}

// Returns the number of the currently active program. Used with AudioProcessorGraph
int ChorusProcessor::getCurrentProgram()
{
    return 0;
}

// Called by the host to change the current program. Used with AudioProcessorGraph
void ChorusProcessor::setCurrentProgram (int index)
{
}

// Must return the name of a given program. Used with AudioProcessorGraph
const juce::String ChorusProcessor::getProgramName (int index)
{
    return {};
}

// Called by the host to rename a program. Used with AudioProcessorGraph
void ChorusProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================

// Called before playback starts, to let the processor prepare itself.
void ChorusProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // PRE DSP LOGIC HERE
}


void ChorusProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // DSP LOGIC HERE
}

// Called after playback has stopped, to let the object free up any resources it no longer needs.
void ChorusProcessor::releaseResources()
{
}

// Determines if there will be an editor
bool ChorusProcessor::hasEditor() const
{
    return false;
}

// Creates generic editor window for effect
juce::AudioProcessorEditor* ChorusProcessor::createEditor()
{
//    return new MultiFXAudioProcessorEditor (*this);
//    return nullptr;
    return new juce::GenericAudioProcessorEditor(*this);
}


// Both methods below will save and load presets
void ChorusProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    
}

void ChorusProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
}
