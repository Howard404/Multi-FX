/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "MainComponent.h"

//==============================================================================
MultiFXAudioProcessorEditor::MultiFXAudioProcessorEditor (MultiFXAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1200, 800);
    //addAndMakeVisible(audioWindow);
     //active effects window
    activeEffects.setColour(juce::ListBox::backgroundColourId, juce::Colour(36, 44, 50));
    activeEffects.setOutlineThickness(3);
    activeEffects.setColour(juce::ListBox::outlineColourId, juce::Colour(26, 30, 32));
    addAndMakeVisible(activeEffects);

    add.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    remove.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    add.setButtonText("Add");
    remove.setButtonText("Remove");
    addAndMakeVisible(add);
    addAndMakeVisible(remove);




    //footer buttons and list
    save.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    load.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    save.setButtonText("Save");
    load.setButtonText("Load");
    addAndMakeVisible(save);
    addAndMakeVisible(load);


    //effect window
    effectLibrary.setColour(juce::ListBox::backgroundColourId, juce::Colour(36, 44, 50));
    effectLibrary.setOutlineThickness(3);
    effectLibrary.setColour(juce::ListBox::outlineColourId, juce::Colour(26, 30, 32));
    effectLibrary.setModel(&library);
    //effectLibrary.addChildAndSetID(new ListComponent("Chorus") ,"Chorus");
    
     //effectLibrary.addChildAndSetID(new ListComponent("Reverb"), "Reverb");
     effectLibrary.updateContent();
    addAndMakeVisible(effectLibrary);

    
}

ListComponent::ListComponent(juce::String name)
{
    setSize(60, 20);
    this->id = name;
    this->muted = false;
    mute.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    mute.setButtonText("muted");
    addAndMakeVisible(mute);
}

void ListComponent::resized()
{
    auto area = getLocalBounds();
    mute.setBoundsRelative(0.1f,0.9f,0.9f,0.9f);
}

MultiFXAudioProcessorEditor::~MultiFXAudioProcessorEditor()
{
}

//==============================================================================
void MultiFXAudioProcessorEditor::paint (juce::Graphics& g)
{
    //audioWindow->paint(g);
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colour(26, 30, 32));
    g.fillRect(0, getHeight() - 40, getWidth(), 40);

}

void MultiFXAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    //audioWindow->resized();
    auto area = getLocalBounds();

    auto footerHeight = 36;
    auto sideItemHeight = 40;
    auto sideItemMargin = 5;

    auto sideBarArea = area.removeFromLeft(juce::jmax(80, area.getWidth() / 4));
    auto activeArea = sideBarArea.removeFromTop(area.getHeight() / 2);
    activeEffects.setBounds(activeArea);

    effectLibrary.setBounds(sideBarArea.removeFromBottom(activeArea.getHeight()).removeFromTop(activeArea.getHeight() - footerHeight - 4));




    auto sideButtonArea = activeArea.removeFromLeft(activeArea.getWidth() / 2);
    add.setBounds(sideButtonArea.removeFromBottom(sideItemHeight).reduced(sideItemMargin));
    remove.setBounds(activeArea.removeFromBottom(sideItemHeight).reduced(sideItemMargin));


    auto effectArea = area.removeFromTop(getHeight() - footerHeight).removeFromLeft(getWidth() / 2);
    auto footerArea = area.removeFromBottom(getHeight() - footerHeight);


    save.setBounds(footerArea.removeFromLeft(getWidth() / 10).reduced(sideItemMargin));
    load.setBounds(footerArea.removeFromLeft(getWidth() / 10).reduced(sideItemMargin));
}

int ListBoxComponent::getNumRows()
{
    return this->numRows;
}


void ListBoxComponent::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    g.fillAll(juce::Colours::red);

}

juce::Component* ListBoxComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
    return existingComponentToUpdate;
}


