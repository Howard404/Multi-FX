#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.

*/

class ListBoxComponent : public juce::Component, public juce::ListBoxModel

{
public:

    int getNumRows() override;


    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;




private:

    juce::Font font{ 10.0f };
    juce::ListBox list{ {}, this };
    int numRows = 0;
    int currentID;

};

class MainComponent : public juce::Component,
    public juce::Button::Listener

{
public:
    //==============================================================================
    MainComponent();

    ~MainComponent();

    //==============================================================================
    void paint(juce::Graphics&);
    void resized() override;
    void buttonClicked(juce::TextButton* button);








private:
    //==============================================================================
    // Your private member variables go here..

    ListBoxComponent active;
    ListBoxComponent library;

    juce::ListBox activeEffects;
    juce::ListBox effectLibrary;



    juce::TextButton add;
    juce::TextButton remove;
    juce::TextButton save;
    juce::TextButton load;





    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

class ListComponent : public juce::Component, juce::MouseListener
{
public:
    ListComponent(juce::String);

private:
    juce::String id;
    bool muted;
};




