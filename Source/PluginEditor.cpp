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

    reverb.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    chorus.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    muteChorus.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    muteReverb.setColour(juce::TextButton::buttonColourId, getLookAndFeel().findColour(juce::TextButton::buttonColourId));
    reverb.setButtonText("Reverb");
    chorus.setButtonText("Chorus");
    muteReverb.setButtonText("muted");
    muteChorus.setButtonText("muted");
    //muteChorus.setImages(false,true,true,unmuted,1.0,juce::Colours::white,unmuted,1.0, juce::Colours::white,muted,1.0, juce::Colours::white,0);
    //muteReverb.setImages(false, true, true, unmuted, 1.0, juce::Colours::white, unmuted, 1.0, juce::Colours::white, muted, 1.0, juce::Colours::white, 0);
    addAndMakeVisible(reverb);
    addAndMakeVisible(chorus);
    addAndMakeVisible(muteChorus);
    addAndMakeVisible(muteReverb);


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
    addAndMakeVisible(effectLibrary);

    
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




    auto sideButtonArea = activeArea.removeFromLeft(activeArea.getWidth() / 1.5);
    auto muteButtonArea = activeArea.removeFromLeft(activeArea.getWidth() / 1.2);
    reverb.setBounds(sideButtonArea.removeFromBottom(sideItemHeight).reduced(sideItemMargin));
    muteReverb.setBounds(muteButtonArea.removeFromBottom(sideItemHeight).reduced(sideItemMargin));
    chorus.setBounds(sideButtonArea.removeFromBottom(sideItemHeight).reduced(sideItemMargin));
    muteChorus.setBounds(muteButtonArea.removeFromBottom(sideItemHeight).reduced(sideItemMargin));


    auto effectArea = area.removeFromTop(getHeight() - footerHeight).removeFromLeft(getWidth() / 2);
    auto footerArea = area.removeFromBottom(getHeight() - footerHeight);


    save.setBounds(footerArea.removeFromLeft(getWidth() / 10).reduced(sideItemMargin));
    load.setBounds(footerArea.removeFromLeft(getWidth() / 10).reduced(sideItemMargin));
}




