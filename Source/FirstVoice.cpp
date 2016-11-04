/*
  ==============================================================================

    FirstVoice.cpp
    Created: 3 Nov 2016 6:05:55pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef FIRSTVOICE_H_INCLUDED
#define FIRSTVOICE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#define TAU 6.2831853072

struct FirstVoice : public SynthesiserVoice
{
public:
	// Constructor
	FirstVoice()
    :   angleDelta(0),
        volume(0.4),
        currentAngle(0),
        currentMidiNoteNumber(-1),
        isTailingOff(false),
        tailOffFactor(1),
        tailOffDecay(0.99999)
	{

	}

	// Destructor
	~FirstVoice()
	{

	}

	// Methods
	bool canPlaySound(SynthesiserSound *sound)
	{
		return true;
	}

    void startNote(int midiNoteNumber,
                    float velocity,
                    SynthesiserSound* sound,
                    int currentPitchWheelPosition)
	{
        // Need frequency of note wave!
        double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        // But we're populating a discrete array, so we need to know how far to step along the curve
        double cyclesPerSample = cyclesPerSecond / getSampleRate();
        angleDelta = cyclesPerSample * TAU;
        currentAngle = 0;
        currentMidiNoteNumber = midiNoteNumber;
        volume = 0.2 + 0.3*velocity;
        tailOffFactor = 1.0;
        isTailingOff = false;
	}

	void stopNote(float velocity, bool allowTailOff)
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

	void pitchWheelMoved(int newPitchWheelValue)
	{
        // Pitch wheel ranges from 0x0000 to 0x3fff, resting in the middle
        double pitchOffset = ((double)(newPitchWheelValue - (0x3fff / 2)) / 0x3fff);
        double pitchNow = MidiMessage::getMidiNoteInHertz(currentMidiNoteNumber);
        double pitchAbove = MidiMessage::getMidiNoteInHertz(currentMidiNoteNumber + 1);
        double pitchBelow = MidiMessage::getMidiNoteInHertz(currentMidiNoteNumber - 1);
        double hz;
        if (pitchOffset < 0) {
            hz = (pitchNow * (1 + pitchOffset)) - (pitchBelow * pitchOffset);
        } else {
            hz = (pitchNow * (1 - pitchOffset)) + (pitchAbove * pitchOffset);
        }
        double cyclesPerSample = hz / getSampleRate();
        angleDelta = cyclesPerSample * TAU;
	}

	void controllerMoved(int controllerNumber, int newControllerValue)
	{
	}

private:
	// Members
    int currentMidiNoteNumber;
    double angleDelta;
    double currentAngle;
    double volume;
    bool isTailingOff;
    double tailOffFactor;
    double tailOffDecay;
    
	// Methods
	void renderNextBlock (AudioBuffer<float>& outputBuffer,
                          int startSample,
                          int numSamples)
	{
        while (numSamples > 0)
        {
            float sinValue = sin(currentAngle);
            float currentSample = (float) (sin (currentAngle) * (volume * tailOffFactor));
            if (isTailingOff)
            {
                currentSample *= tailOffFactor;
                tailOffFactor *= tailOffDecay;
            }
            
            for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample (i, startSample, currentSample);
            
            currentAngle += angleDelta;
            startSample++;
            numSamples--;
        }
        if (tailOffFactor < 0.0005 && isTailingOff)
        {
            stopNote(0, false);
        }
	}
};

#endif
