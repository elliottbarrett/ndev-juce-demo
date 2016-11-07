/*
  ==============================================================================

	DemoUIComponent.cpp
	Created: 4 Nov 2016 2:16:25am
	Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef DEMOUICOMPONENT_H_INCLUDED
#define DEMOUICOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FirstSynthAudioManager.cpp"

class DemoUIComponent : public Component, public ComboBox::Listener
{
public:
    DemoUIComponent(FirstSynthAudioManager *am) : synthManager(am)
    {
        setOpaque(true);
        
        StringArray voiceSelectStrings;
        voiceSelectStrings.add("Square/Sine");
        voiceSelectStrings.add("Triangle");
        voiceSelectStrings.add("Sawtooth");
        voiceSelectStrings.add("Sampled");
        voiceSelectComboBox.setTextWhenNothingSelected("Make a selection");
        voiceSelectComboBox.addItemList(voiceSelectStrings, 1);
        voiceSelectComboBox.addListener(this);

        addAndMakeVisible(voiceSelectComboBox);
    }
    
    ~DemoUIComponent()
    {
        
    }
    
    void comboBoxChanged (ComboBox *changedComboBox) override
    {

    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::aliceblue);
    }
    
    void resized() override
    {
        Rectangle<int> bounds = getLocalBounds();
        voiceSelectComboBox.setBounds(bounds.removeFromTop(30).removeFromRight(getWidth() - 20).reduced(8, 0));
    }
private:
    FirstSynthAudioManager *synthManager;
    ComboBox voiceSelectComboBox;
};

#endif
