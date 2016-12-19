/*
 ==============================================================================
 
	FirstFMVoice.cpp
	Created: 7 Nov 2016 10:29:49pm
	Author:  Elliott Barrett
 
 ==============================================================================
 */

#include "FirstFMVoice.h"

FirstFMVoice::FirstFMVoice()
:   currentMidiNoteNumber(-1),
    angleDelta(0),
    currentAngle(0),
    modulatingAngle(0),
    modulatingAngleDelta(0),
    volume(0.4),
    modulatingCoefficient(0)
{
    
}

FirstFMVoice::~FirstFMVoice()
{
    
}

// Methods
bool FirstFMVoice::canPlaySound(SynthesiserSound *sound)
{
    return true;
}

void FirstFMVoice::startNote(int midiNoteNumber,
               float velocity,
               SynthesiserSound* sound,
               int currentPitchWheelPosition)
{
    // Need frequency of note wave!
    currentMidiNoteNumber = midiNoteNumber;
    double cyclesPerSecond = getNoteFrequency(midiNoteNumber, currentPitchWheelPosition);
    // But we're populating a discrete array, so we need to know how far to step along the curve
    double cyclesPerSample = cyclesPerSecond / getSampleRate();
    angleDelta = cyclesPerSample * TAU;
    currentAngle = 0;
    currentMidiNoteNumber = midiNoteNumber;
    volume = 0.2 + 0.3*velocity;
    
    // Modulating
    double modulatingCyclesPerSecond = cyclesPerSecond * 1.5;
    double modulatingCyclesPerSample = modulatingCyclesPerSecond / getSampleRate();
    modulatingAngleDelta = modulatingCyclesPerSample * TAU;
    modulatingAngle = 0;
}

void FirstFMVoice::stopNote(float velocity, bool allowTailOff)
{
    clearCurrentNote();
    angleDelta = 0.0;
    modulatingAngleDelta = 0;
}

void FirstFMVoice::pitchWheelMoved(int newPitchWheelValue)
{
    double hz = getNoteFrequency(currentMidiNoteNumber, newPitchWheelValue);
    double cyclesPerSample = hz / getSampleRate();
    angleDelta = cyclesPerSample * TAU;
}

void FirstFMVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    // Sine/square wave mixing function
    modulatingCoefficient = ((double)newControllerValue) / 127;
}

void FirstFMVoice::renderNextBlock (AudioBuffer<float>& outputBuffer,
                      int startSample,
                      int numSamples)
{
    while (numSamples > 0)
    {
        float currentSample = (float) (volume * sin (currentAngle + (modulatingCoefficient * sin(modulatingAngle))));
        
        for (int i = outputBuffer.getNumChannels(); --i >= 0;)
        {
            outputBuffer.addSample (i, startSample, currentSample);
        }
        
        currentAngle += angleDelta;
        modulatingAngle += modulatingAngleDelta;
        startSample++;
        numSamples--;
    }
}

double FirstFMVoice::getNoteFrequency(int midiNoteNumber, int pitchWheelPosition)
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
