/*
 ==============================================================================
 
	FirstFMVoice.cpp
	Created: 7 Nov 2016 10:29:49pm
	Author:  Elliott Barrett
 
 ==============================================================================
 */

#ifndef FIRSTFMVOICE_H_INCLUDED
#define FIRSTFMVOICE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#define TAU 6.2831853072
#define PHASE TAU/4

class FirstFMVoice : public SynthesiserVoice
{
public:
    FirstFMVoice();
    ~FirstFMVoice();

    bool canPlaySound(SynthesiserSound *sound) override;
    
    void startNote(int midiNoteNumber,
                   float velocity,
                   SynthesiserSound* sound,
                   int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;   
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    
private:
    int currentMidiNoteNumber;
    double angleDelta;
    double currentAngle;
    double modulatingAngle;
    double modulatingAngleDelta;
    double volume;
    double modulatingCoefficient;
    
    void renderNextBlock (AudioBuffer<float>& outputBuffer,
                          int startSample,
                          int numSamples) override;
    
    double getNoteFrequency(int midiNoteNumber, int pitchWheelPosition);
};
#endif