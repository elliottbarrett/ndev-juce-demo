/*
  ==============================================================================

	FirstVoice.cpp
	Created: 3 Nov 2016 6:05:55pm
	Author:  Elliott Barrett

  ==============================================================================
*/
#include "FirstVoice.h"

FirstVoice::FirstVoice()
:   currentMidiNoteNumber(-1),
    angleDelta(0),
	currentAngle(0),
    volume(0.4),
	isTailingOff(false),
	tailOffFactor(1),
	tailOffDecay(0.99995),
    normalizedControllerPos(0.5)
{

}

// Methods
bool FirstVoice::canPlaySound(SynthesiserSound *sound) 
{
	return true;
}

void FirstVoice::startNote(int midiNoteNumber,
				float velocity,
				SynthesiserSound* sound,
				int currentPitchWheelPosition) 
{
	currentMidiNoteNumber = midiNoteNumber;
	double cyclesPerSecond = getNoteFrequency(midiNoteNumber, currentPitchWheelPosition);
	double cyclesPerSample = cyclesPerSecond / getSampleRate();
	angleDelta = cyclesPerSample * TAU;
	currentAngle = 0;
	currentMidiNoteNumber = midiNoteNumber;
	volume = 0.2 + 0.3 * velocity;
	tailOffFactor = 1.0;
	isTailingOff = false;
}

void FirstVoice::stopNote(float velocity, bool allowTailOff) 
{
	if (allowTailOff)
	{
		isTailingOff = true;
	}
	else
	{
		clearCurrentNote();
		angleDelta = 0.0;
	}
}

void FirstVoice::pitchWheelMoved(int newPitchWheelValue) 
{
	double hz = getNoteFrequency(currentMidiNoteNumber, newPitchWheelValue);
	double cyclesPerSample = hz / getSampleRate();
	angleDelta = cyclesPerSample * TAU;
}

void FirstVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{
    // Sine/square wave mixing function
    normalizedControllerPos = ((double)newControllerValue) / 127;
}

void FirstVoice::renderNextBlock (AudioBuffer<float>& outputBuffer,
					  int startSample,
					  int numSamples) 
{
	while (numSamples > 0)
	{
		float currentSampleSin = (float) (sin (currentAngle) * (volume * tailOffFactor));
        float currentSampleSquare = (currentSampleSin > 0 ? volume * tailOffFactor : -volume * tailOffFactor);
        float currentSample = (normalizedControllerPos * currentSampleSin) + ((1 - normalizedControllerPos) * currentSampleSquare);
		if (isTailingOff)
		{
			currentSample *= tailOffFactor;
			tailOffFactor *= tailOffDecay;
		}
		
		for (int i = outputBuffer.getNumChannels(); --i >= 0;)
        {
            outputBuffer.addSample (i, startSample, currentSample);
        }
        
		currentAngle += angleDelta;
		startSample++;
		numSamples--;
	}
	if (tailOffFactor < 0.0005 && isTailingOff)
	{
		stopNote(0, false);
	}
}

double FirstVoice::getNoteFrequency(int midiNoteNumber, int pitchWheelPosition)
{
	// Pitch wheel ranges from 0x0000 to 0x3fff, resting in the middle
	double pitchOffset = 2 * ((double)(pitchWheelPosition - (0x3fff / 2)) / 0x3fff);
	double pitchNow = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	double pitchAbove = MidiMessage::getMidiNoteInHertz(midiNoteNumber + 2);
	double pitchBelow = MidiMessage::getMidiNoteInHertz(midiNoteNumber - 2);

	if (pitchOffset < 0) {
		return (pitchNow * (1 + pitchOffset)) - (pitchBelow * pitchOffset);
	} else {
		return (pitchNow * (1 - pitchOffset)) + (pitchAbove * pitchOffset);
	}
}
