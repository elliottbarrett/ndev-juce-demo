/*
  ==============================================================================

    FirstSynthMidiCallback.cpp
    Created: 3 Nov 2016 11:49:46pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef FIRSTSYNTHMIDICALLBACK_H_INCLUDED
#define FIRSTSYNTHMIDICALLBACK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class FirstSynthMidiCallback : public MidiMessageCollector
{
public:
	FirstSynthMidiCallback()
	{
		assignMidiInput();
	}

	~FirstSynthMidiCallback()
	{
		if (midiInput != nullptr)
		{
			midiInput->stop();
			delete midiInput;
		}
	}
private:
	// Members
	MidiInput *midiInput;

	// Methods
	void assignMidiInput()
	{
		midiInput = MidiInput::openDevice(0, this);
		midiInput->start();
	}

	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
	{
        MidiMessageCollector::handleIncomingMidiMessage(source, message);
	}
};

#endif
