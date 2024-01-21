#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
   
       
  

private:
    //==============================================================================
    // Your private member variables go here..
    juce::ListBox activeEffects;
    juce::ListBox effectLibrary;
 
    juce::TextButton add;
    juce::TextButton remove;
    juce::TextButton save;
    juce::TextButton load;
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

class ActiveEffectsComponent : public juce::Component
{
public:
    ActiveEffectsComponent()
    {
        
    }
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::grey);
    }
    void resized() override
    {
        /*auto area = getLocalBounds();

        auto headerFooterHeight = 36;
        
        auto sideBarArea = area.removeFromLeft(juce::jmax(80, area.getWidth() / 4));
        activeEffects.setBounds(sideBarArea); // [2]
        
        auto sideItemHeight = 40;
        auto sideItemMargin = 5;
        add.setBounds(sideBarArea.removeFromTop(sideItemHeight).reduced(sideItemMargin));
        remove.setBounds(sideBarArea.removeFromTop(sideItemHeight).reduced(sideItemMargin));*/
        
    }
    


private:

    
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ActiveEffectsComponent)
};

class EffectsLibraryComponent : public juce::Component
{
public:
    EffectsLibraryComponent()
    {

    }

private:


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsLibraryComponent)
};
