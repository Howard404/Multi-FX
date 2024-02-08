/*
  ==============================================================================

    ReverbProcessor.cpp
    Created: 23 Jan 2024 5:53:37pm
    Author:  Grant Howard

  ==============================================================================
*/

#include "ReverbProcessor.h"
#include "PluginEditor.h"

// Constructor has bus layout stero-stero or mono-mono
ReverbProcessor::ReverbProcessor() : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo())
                                                     .withOutput ("Output", juce::AudioChannelSet::stereo()))
{
}

// Get name function
const juce::String ReverbProcessor::getName() const
{
    // Gets the name of the juce project... ignore
    return {};
}

// Accept midi function is always false (audio only)
bool ReverbProcessor::acceptsMidi() const
{
    return false;
}

bool ReverbProcessor::producesMidi() const 
{
    return false;
}

// Returns length of the processor tail (don't need)
double ReverbProcessor::getTailLengthSeconds() const
{
    return 0;
}

// We only have one host program, PluginProcessor, return 0
int ReverbProcessor::getNumPrograms()
{
    return 0;
}

// Returns the number of the currently active program. Used with AudioProcessorGraph
int ReverbProcessor::getCurrentProgram()
{
    return 0;
}

// Called by the host to change the current program. Used with AudioProcessorGraph
void ReverbProcessor::setCurrentProgram (int index)
{
}

// Must return the name of a given program. Used with AudioProcessorGraph
const juce::String ReverbProcessor::getProgramName (int index)
{
    return {};
}

// Called by the host to rename a program. Used with AudioProcessorGraph
void ReverbProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================

// Called before playback starts, to let the processor prepare itself.
void ReverbProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // PRE DSP LOGIC HERE
}


void ReverbProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // DSP LOGIC HERE
}

// Called after playback has stopped, to let the object free up any resources it no longer needs.
void ReverbProcessor::releaseResources()
{
}

// Determines if there will be an editor
bool ReverbProcessor::hasEditor() const
{
    return true;
}

// Creates generic editor window for effect
juce::AudioProcessorEditor* ReverbProcessor::createEditor()
{
//    return new MultiFXAudioProcessorEditor (*this);
//    return nullptr;
    return new juce::GenericAudioProcessorEditor(*this);
}


// Both methods below will save and load presets
void ReverbProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    
}

void ReverbProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
}
