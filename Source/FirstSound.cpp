/*
  ==============================================================================

	FirstSound.cpp
	Created: 3 Nov 2016 6:05:36pm
	Author:  Elliott Barrett

  ==============================================================================
*/

#include "FirstSound.h"

bool FirstSound::appliesToNote (int midiNoteNumber)
{
	return true;
}

bool FirstSound::appliesToChannel (int midiChannel)
{
	return true;
}