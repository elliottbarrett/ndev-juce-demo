/*
  ==============================================================================

	FirstSound.cpp
	Created: 3 Nov 2016 6:05:36pm
	Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef FIRSTSOUND_H_INCLUDED
#define FIRSTSOUND_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class FirstSound : public SynthesiserSound
{
public:
	// Constructor
	FirstSound()
	{

	}

	// Destructor
	~FirstSound()
	{

	}

	// Methods
	bool appliesToNote (int midiNoteNumber)
	{
		return true;
	}

	bool appliesToChannel (int midiChannel)
	{
		return true;
	}

private:
	// Members

	// Methods
};

#endif