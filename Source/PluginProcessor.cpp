/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ChorusProcessor.h"
#include "ReverbProcessor.h"

// Global Index for nodeID array
int globalIndex = 0;

//==============================================================================
MultiFXAudioProcessor::MultiFXAudioProcessor()
     : AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
//                processorSlot1 (new juce::AudioParameterChoice(juce::ParameterID {"slot1", 1}, "Slot 1", processorChoices, 0)),
//                processorSlot2(new juce::AudioParameterChoice(juce::ParameterID {"slot2", 1}, "Slot 2", processorChoices, 0)),
                mainProcessor (new juce::AudioProcessorGraph())
{
//    addParameter(processorSlot1);
//    addParameter(processorSlot2);
}


MultiFXAudioProcessor::~MultiFXAudioProcessor()
{
}

//==============================================================================

MultiFXAudioProcessor::Node::Ptr MultiFXAudioProcessor::getChorus()
{
    MultiFXAudioProcessor::Node::Ptr chorusNode = mainProcessor->addNode (std::make_unique<ChorusProcessor>());
    return chorusNode;
}

const juce::String MultiFXAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultiFXAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultiFXAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultiFXAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultiFXAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultiFXAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultiFXAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultiFXAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MultiFXAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultiFXAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MultiFXAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(),
                                        getMainBusNumOutputChannels(),
                                        sampleRate, samplesPerBlock);
    mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);
    
    initialiseGraph();
}

void MultiFXAudioProcessor::initialiseGraph() {
    mainProcessor->clear();
    
    audioInputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioInputNode));
    
    audioOutputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioOutputNode));
    
    connectAudioNodes();
}

void MultiFXAudioProcessor::connectAudioNodes() {
    for(int channel = 0; channel < 2; ++channel){
        mainProcessor->addConnection({ {audioInputNode->nodeID, channel},
                                       {audioOutputNode->nodeID, channel} });
    }
}

void MultiFXAudioProcessor::releaseResources()
{
    mainProcessor->releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultiFXAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet()  == juce::AudioChannelSet::disabled()
     || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}
#endif

void MultiFXAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for(int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
//    updateGraph();
    
    mainProcessor->processBlock(buffer, midiMessages);
}

// UPDATE GRPAH FOR BUTTONS

MultiFXAudioProcessor::Node::Ptr MultiFXAudioProcessor::updateGraph(int slotIndex, const juce::String& effect)
{
    if(globalIndex == 2)
        return nullptr;
    
    globalIndex = slotIndex;
    
    bool hasChanged = false;
    Node::Ptr newNode = nullptr;
    
    juce::ReferenceCountedArray<Node> slots;
    slots.add(slot1Node);
    slots.add(slot2Node);
    
//    if(false)
//    {
//        //
//        auto slot = slots.getUnchecked(0);
//        if(slot != nullptr)
//        {
//            mainProcessor->removeNode(slot.get());
//            slots.set(0, nullptr);
//            hasChanged = true;
//        } // End if
//    } // End if
    if(effect == "CHORUS")
    {
        auto slot = slots.getUnchecked(slotIndex);
        
        if(slot != nullptr)
        {
            if(slot->getProcessor()->getName() == "Chorus")
            {
                return nullptr;
            } // End if
            
            mainProcessor->removeNode(slot.get());
        } // End if
        
        newNode = MultiFXAudioProcessor::getChorus();
        
        slots.set(slotIndex, newNode);
        
        slot = slots.getUnchecked(slotIndex);
        
        MultiFXAudioProcessor::nodeID_Array[slotIndex] = newNode;
        
        DBG("Processor: " << slot->getProcessor()->getName());
        DBG("Chorus Created");
        
        hasChanged = true;
    } // End else if
    
    
    // CONNECT NODES TO GRAPH
    if (hasChanged)
    {
        for (auto connection : mainProcessor->getConnections())
            mainProcessor->removeConnection (connection);

        juce::ReferenceCountedArray<Node> activeSlots;

        for (auto slot : slots)
        {
            if (slot != nullptr)
            {
                activeSlots.add (slot);

                slot->getProcessor()->setPlayConfigDetails (getMainBusNumInputChannels(),
                                                            getMainBusNumOutputChannels(),
                                                            getSampleRate(), getBlockSize());
            } // End if
        } // End for loop

        if (activeSlots.isEmpty())
        {
            DBG("NO ACTIVE SLOTS");
            connectAudioNodes();
        } // End if
        else
        {
            DBG("ACTIVE SLOTS CONNECTING");
            for (int i = 0; i < activeSlots.size() - 1; ++i)
            {
                for (int channel = 0; channel < 2; ++channel)
                    mainProcessor->addConnection ({ { activeSlots.getUnchecked (i)->nodeID,      channel },
                                                    { activeSlots.getUnchecked (i + 1)->nodeID,  channel } });
            } // End for loop

            for (int channel = 0; channel < 2; ++channel)
            {
                mainProcessor->addConnection ({ { audioInputNode->nodeID,         channel },
                                                { activeSlots.getFirst()->nodeID, channel } });
                mainProcessor->addConnection ({ { activeSlots.getLast()->nodeID,  channel },
                                                { audioOutputNode->nodeID,        channel } });
            } // End for loop
        } // End else

        for (auto node : mainProcessor->getNodes())
            node->getProcessor()->enableAllBuses();
        
        DBG("ACTIVE SLOTS CONNECTION COMPLETED");
    } // End if
    
    // Iterate and print NodeID_Array
    for(int i = 0; i < nodeID_Array.size(); i++)
    {
        if(nodeID_Array[i] != nullptr)
            DBG("Effect in index: " << i);
    }
    
     return newNode;
}

void MultiFXAudioProcessor::removeNode(int index)
{
    if(nodeID_Array.size() <= index)
    {
        DBG("PARAM index OUT OF BOUNDS");
        return;
    }
    
    juce::ReferenceCountedArray<Node> slots;
    slots.add(slot1Node);
    slots.add(slot2Node);
    
    auto slot = slots.getUnchecked(index);
    if(slot.get() != nullptr)
    {
        mainProcessor->removeNode(slot.get());
        nodeID_Array[index] = nullptr;
    } else
    {
        DBG("SLOT REFERENCE NOT FOUND");
        return;
    }
    
    // CONNECT NODES
    
    for (auto connection : mainProcessor->getConnections())
        mainProcessor->removeConnection (connection);

    juce::ReferenceCountedArray<Node> activeSlots;

    for (auto slot : slots)
    {
        if (slot != nullptr)
        {
            activeSlots.add (slot);

            slot->getProcessor()->setPlayConfigDetails (getMainBusNumInputChannels(),
                                                        getMainBusNumOutputChannels(),
                                                        getSampleRate(), getBlockSize());
        } // End if
    } // End for loop

    if (activeSlots.isEmpty())
    {
        DBG("NO ACTIVE SLOTS");
        connectAudioNodes();
    } // End if
    else
    {
        DBG("ACTIVE SLOTS CONNECTING");
        for (int i = 0; i < activeSlots.size() - 1; ++i)
        {
            for (int channel = 0; channel < 2; ++channel)
                mainProcessor->addConnection ({ { activeSlots.getUnchecked (i)->nodeID,      channel },
                    { activeSlots.getUnchecked (i + 1)->nodeID,  channel } });
        } // End for loop
        
        for (int channel = 0; channel < 2; ++channel)
        {
            mainProcessor->addConnection ({ { audioInputNode->nodeID,         channel },
                { activeSlots.getFirst()->nodeID, channel } });
            mainProcessor->addConnection ({ { activeSlots.getLast()->nodeID,  channel },
                { audioOutputNode->nodeID,        channel } });
        }
    }// End for loop
}

//void MultiFXAudioProcessor::updateGraph() {
//    bool hasChanged = false;
//    
//    juce::Array<juce::AudioParameterChoice*> choices = {processorSlot1, processorSlot2};
//    
//    juce::ReferenceCountedArray<Node> slots;
//    slots.add(slot1Node);
//    slots.add(slot2Node);
//    
//    DBG("update graph is called");
//    
//    for (int i = 0; i < 2; ++i)
//           {
//               auto& choice = choices.getReference (i);
//               auto  slot   = slots  .getUnchecked (i);
//    
//               if (choice->getIndex() == 0)
//               {
//                   if (slot != nullptr)
//                   {
//                       mainProcessor->removeNode (slot.get());
//                       slots.set (i, nullptr);
//                       hasChanged = true;
//                   }
//               }
//               else if (choice->getIndex() == 1)
//               {
//                   if (slot != nullptr)
//                   {
//                       if (slot->getProcessor()->getName() == "Chorus")
//                           continue;
//    
//                       mainProcessor->removeNode (slot.get());
//                   }
//                   DBG("CHORUS PROCESSOR");
//                   slots.set (i, mainProcessor->addNode (std::make_unique<ChorusProcessor>()));
//                   hasChanged = true;
//               }
//               else if (choice->getIndex() == 2)
//               {
//                   if (slot != nullptr)
//                   {
//                       if (slot->getProcessor()->getName() == "Reverb")
//                           continue;
//    
//                       mainProcessor->removeNode (slot.get());
//                   }
//                   DBG("REVERB PROCESSOR");
//                   slots.set (i, mainProcessor->addNode (std::make_unique<ReverbProcessor>()));
//                   hasChanged = true;
//               }
//           }
//}

//==============================================================================
bool MultiFXAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* MultiFXAudioProcessor::createEditor()
{
    return new MultiFXAudioProcessorEditor (*this);
//    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void MultiFXAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MultiFXAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultiFXAudioProcessor();
}
