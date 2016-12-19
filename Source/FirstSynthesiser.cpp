/*
  ==============================================================================

	FirstSynthesizer.cpp
	Created: 3 Nov 2016 2:01:46am
	Author:  Elliott Barrett

  ==============================================================================
*/
// #include "../JuceLibraryCode/JuceHeader.h"
// #include "FirstVoice.h"
// #include "FirstFMVoice.h"
// #include "ADSRVoice.h"
// #include "FirstSound.h"
// #include "Enums.h"

#include "FirstSynthesiser.h"
#include "FirstSound.h"
#include "FirstVoice.h"
#include "FirstFMVoice.h"
#include "ADSRVoice.h"

	// Constructor
FirstSynthesiser::FirstSynthesiser()
{
	SynthesiserSound *sound = new FirstSound();
	addSound(sound);
    setSynthType(ST_ADSR);
}

// Methods
void FirstSynthesiser::handleController (int midiChannel, int controllerNumber, int controllerValue)
{
    for (int i=0; i < getNumVoices(); i++)
    {
        this->getVoice(i)->controllerMoved(controllerNumber, controllerValue);
    }
}

void FirstSynthesiser::setSynthType(SynthType t)
{
    clearVoices();
    for (int i=0; i < NUM_VOICES; i++)
    {
        switch (t)
        {
            case ST_SQUARE_SINE:
                addVoice(new FirstVoice());
                break;
            case ST_FM:
                addVoice(new FirstFMVoice());
                break;
            case ST_ADSR:
                addVoice(new ADSRVoice());
                break;
            default:
                break;
        }
    }
}