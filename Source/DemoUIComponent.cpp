/*
  ==============================================================================

	DemoUIComponent.cpp
	Created: 4 Nov 2016 2:16:25am
	Author:  Elliott Barrett

  ==============================================================================
*/
#include "DemoUIComponent.h"

DemoUIComponent::DemoUIComponent(FirstSynthAudioManager *am)
: synthManager(am), keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setOpaque(true);
    
    StringArray voiceSelectStrings;
    voiceSelectStrings.add("Square/Sine Synthesis");
    voiceSelectStrings.add("FM Synthesis");
    voiceSelectStrings.add("Audio Processing");
    voiceSelectStrings.add("ADSR Synth");
    voiceSelectComboBox.setTextWhenNothingSelected("Make a selection");
    voiceSelectComboBox.addItemList(voiceSelectStrings, 1);
    voiceSelectComboBox.addListener(this);

    addAndMakeVisible(voiceSelectComboBox);
    addAndMakeVisible(adsrComponent);
    addAndMakeVisible(voiceSelectComboBox);
    addAndMakeVisible(keyboardComponent);
}

DemoUIComponent::~DemoUIComponent()
{
    
}

void DemoUIComponent::comboBoxChanged (ComboBox *changedComboBox)
{
    switch (changedComboBox->getSelectedId())
    {
        case 1: // Square/Sine Synthesis
            synthManager->setSynthType(ST_SQUARE_SINE);
            break;
        case 2: // FM Synthesis
            synthManager->setSynthType(ST_FM);
            break;
        case 3: // Audio Processing
            synthManager->setSynthType(ST_NONE);
            break;
        case 4: // ADSR Synth
            synthManager->setSynthType(ST_ADSR);
            break;
            
    }
}

void DemoUIComponent::paint(Graphics& g)
{
    g.fillAll(Colours::aliceblue);
}

void DemoUIComponent::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    voiceSelectComboBox.setBounds(bounds.removeFromTop(30).reduced(5,5));
    keyboardComponent.setBounds(bounds.removeFromBottom(100));
    adsrComponent.setBounds(bounds);
}
