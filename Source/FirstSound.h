/*
  ==============================================================================

	FirstSound.h
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
	bool appliesToNote (int midiNoteNumber) override;
	bool appliesToChannel (int midiChannel) override;
};

#endif
