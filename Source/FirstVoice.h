/*
  ==============================================================================

	FirstVoice.h
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
	FirstVoice();

	// Methods
	bool canPlaySound(SynthesiserSound *sound) override;
	void startNote(int midiNoteNumber,
					float velocity,
					SynthesiserSound* sound,
					int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;

private:
	// Members
	int currentMidiNoteNumber;
	double angleDelta;
	double currentAngle;
	double volume;
	bool isTailingOff;
	double tailOffFactor;
	double tailOffDecay;
    double normalizedControllerPos;
	
	// Methods
	void renderNextBlock (AudioBuffer<float>& outputBuffer,
						  int startSample,
						  int numSamples) override;

	double getNoteFrequency(int midiNoteNumber, int pitchWheelPosition);
};

#endif
