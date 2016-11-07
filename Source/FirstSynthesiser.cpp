/*
  ==============================================================================

	FirstSynthesizer.cpp
	Created: 3 Nov 2016 2:01:46am
	Author:  Elliott Barrett

  ==============================================================================
*/
#ifndef FIRSTSYNTHESISER_H_INCLUDED
#define FIRSTSYNTHESISER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FirstVoice.cpp"
#include "FirstSound.cpp"
#include "FirstSynthMidiCallback.cpp"

class FirstSynthesiser : public Synthesiser
{
public:
	// Constructor
	FirstSynthesiser()
	{
		SynthesiserSound *sound = new FirstSound();
		addSound(sound);
		for (int i=0; i < 10; i++)
		{
			SynthesiserVoice *voice = new FirstVoice();
			addVoice(voice);
		}
	}
	// Destructor
	~FirstSynthesiser()
	{
		
	}

	// Methods
	void noteOn(const int midiChannel, const int midiNoteNumber, const float velocity) override
	{
		Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
	}

	void noteOff (int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) override
	{
		Synthesiser::noteOff(midiChannel, midiNoteNumber, velocity, allowTailOff);
    }
    
    void handleController (int midiChannel, int controllerNumber, int controllerValue) override
    {
        for (int i=0; i < getNumVoices(); i++)
        {
            this->getVoice(i)->controllerMoved(controllerNumber, controllerValue);
        }
    }
private:
	// Members
		
	// Methods
};
#endif
