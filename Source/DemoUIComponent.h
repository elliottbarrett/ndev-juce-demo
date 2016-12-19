/*
  ==============================================================================

	DemoUIComponent.h
	Created: 4 Nov 2016 2:16:25am
	Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef DEMOUICOMPONENT_H_INCLUDED
#define DEMOUICOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FirstSynthAudioManager.h"
#include "ADSRComponent.h"

class DemoUIComponent : public Component, public ComboBox::Listener
{
public:
    DemoUIComponent(FirstSynthAudioManager *am);
    ~DemoUIComponent();
    void comboBoxChanged (ComboBox *changedComboBox) override;
    void paint(Graphics& g) override;
    void resized() override;
    
private:
    FirstSynthAudioManager *synthManager;
    ComboBox voiceSelectComboBox;
    ADSRComponent adsrComponent;
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
};

#endif
