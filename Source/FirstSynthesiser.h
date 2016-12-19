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
#include "Enums.h"

#define NUM_VOICES 10
class FirstSynthesiser : public Synthesiser
{
public:
	// Constructor
	FirstSynthesiser();
	// Methods
    void handleController (int midiChannel, int controllerNumber, int controllerValue) override;
    void setSynthType(SynthType t);
private:
	// Members
		
	// Methods
};
#endif
