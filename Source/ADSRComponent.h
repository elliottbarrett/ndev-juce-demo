/*
 ==============================================================================
 
 ADSRComponent.cpp
 Created: 13 Dec 2016 9:15:27pm
 Author:  Elliott Barrett
 
 ==============================================================================
 */

#ifndef ADSRCOMPONENT_H_INCLUDED
#define ADSRCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class ADSRComponent : public Component, Slider::Listener, ComboBox::Listener
{
public:
    ADSRComponent();
    ~ADSRComponent();
    void comboBoxChanged (ComboBox *changedComboBox) override;
    void sliderValueChanged(Slider *slider) override;
private:
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    Label attackLabel;
    Label decayLabel;
    Label sustainLabel;
    Label releaseLabel;
    Label waveSelectLabel;
    ComboBox waveTypeComboBox;
};

#endif
