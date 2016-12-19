/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 13 Dec 2016 9:15:27pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Globals.h"
#include "ADSRComponent.h"

ADSRComponent::ADSRComponent() : attackSlider(Slider::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow),
        decaySlider(Slider::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow),
        sustainSlider(Slider::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow),
        releaseSlider(Slider::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow),
        attackLabel("attackLabel", "Attack"),
        decayLabel("decayLabel", "Decay"),
        sustainLabel("sustainLabel", "Sustain"),
        releaseLabel("releaseLabel", "Release"),
        waveSelectLabel("waveSelectLabel", "Waveform")
{
    attackSlider.setRange(0, 5, 0.01);
    decaySlider.setRange(0, 5, 0.01);
    sustainSlider.setRange(0, 1, 0.01);
    releaseSlider.setRange(0, 5, 0.01);
    
    attackSlider.setRotaryParameters(float_Pi * 1.2f, float_Pi * 2.8f, false);
    decaySlider.setRotaryParameters(float_Pi * 1.2f, float_Pi * 2.8f, false);
    sustainSlider.setRotaryParameters(float_Pi * 1.2f, float_Pi * 2.8f, false);
    releaseSlider.setRotaryParameters(float_Pi * 1.2f, float_Pi * 2.8f, false);
    
    attackSlider.addListener(this);
    decaySlider.addListener(this);
    sustainSlider.addListener(this);
    releaseSlider.addListener(this);
    
    attackLabel.setJustificationType(juce::Justification::centred);
    decayLabel.setJustificationType(juce::Justification::centred);
    sustainLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.setJustificationType(juce::Justification::centred);
    
    StringArray waveTypeStrings;
    waveTypeStrings.add("Sine");
    waveTypeStrings.add("Square");
    waveTypeStrings.add("Saw");
    waveTypeStrings.add("Triangle");
    waveTypeComboBox.setTextWhenNothingSelected("");
    waveTypeComboBox.addItemList(waveTypeStrings, 1);
    waveTypeComboBox.addListener(this);
    
    int sliderHeight = 100;
    int sliderWidth = 120;
    int labelHeight = 20;
    int waveSelectWidth = 120;
    int waveSelectHeight = 20;
    attackSlider.setBounds(0, 0, sliderWidth, sliderHeight);
    attackLabel.setBounds(0, sliderHeight, sliderWidth, labelHeight);
    decaySlider.setBounds(sliderWidth, 0, sliderWidth, sliderHeight);
    decayLabel.setBounds(sliderWidth, sliderHeight, sliderWidth, labelHeight);
    sustainSlider.setBounds(sliderWidth * 2, 0, sliderWidth, sliderHeight);
    sustainLabel.setBounds(sliderWidth * 2, sliderHeight, sliderWidth, labelHeight);
    releaseSlider.setBounds(sliderWidth * 3, 0, sliderWidth, sliderHeight);
    releaseLabel.setBounds(sliderWidth * 3, sliderHeight, sliderWidth, labelHeight);
    waveSelectLabel.setBounds(sliderWidth * 4, 0, waveSelectWidth, labelHeight);
    waveTypeComboBox.setBounds(sliderWidth * 4, labelHeight, waveSelectWidth, waveSelectHeight);
    
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(attackLabel);
    addAndMakeVisible(decayLabel);
    addAndMakeVisible(sustainLabel);
    addAndMakeVisible(releaseLabel);
    addAndMakeVisible(waveSelectLabel);
    addAndMakeVisible(waveTypeComboBox);
}
    
ADSRComponent::~ADSRComponent()
{
    
}
    
void ADSRComponent::sliderValueChanged(Slider *slider)
{
   ADSR_Attack = attackSlider.getValue();
   ADSR_Decay = decaySlider.getValue();
   ADSR_Sustain = sustainSlider.getValue();
   ADSR_Release = releaseSlider.getValue();
}

void ADSRComponent::comboBoxChanged(ComboBox *changedComboBox)
{
    switch (changedComboBox->getSelectedId())
    {
        case 1: // Sin
            ADSR_Oscillator_Type = OT_SINE;
            break;
        case 2: // Square
            ADSR_Oscillator_Type = OT_SQUARE;
            break;
        case 3: // Saw
            ADSR_Oscillator_Type = OT_SAW;
            break;
        case 4: // Triangle
            ADSR_Oscillator_Type = OT_TRIANGLE;
            break;
        default:
            break;
    }
}
