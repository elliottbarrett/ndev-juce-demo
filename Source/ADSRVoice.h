/*
  ==============================================================================

    ADSRVoice.cpp
    Created: 11 Dec 2016 1:05:48pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef ADSRVOICE_H_INCLUDED
#define ADSRVOICE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

#define TAU 6.2831853072
#define NUM_VOICES 10


class ADSRVoice : public SynthesiserVoice
{
public:
	// Constructor
    ADSRVoice();
	// Methods
	bool canPlaySound(SynthesiserSound *sound) override;

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
private:
	// Members
	int currentMidiNoteNumber;
    Oscillator oscillator;
	double volume;
    double normalizedControllerPos;
    
    double sustain; // value between 0 and 1
    
    bool isTailingOff = false;
    
    int attackSamples;
    int decaySamples;
    int releaseSamples;
    int samplesElapsed;
	
	// Methods
	void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
	double getNoteFrequency(int midiNoteNumber, int pitchWheelPosition);
    double getEnvelopeValue();
    inline double lerp(double t, double a, double b);
};

#endif
