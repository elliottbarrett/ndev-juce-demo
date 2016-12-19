/*
  ==============================================================================

    ADSRVoice.cpp
    Created: 11 Dec 2016 1:05:48pm
    Author:  Elliott Barrett

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "Globals.h"
#include "ADSRVoice.h"

ADSRVoice::ADSRVoice()
:   currentMidiNoteNumber(-1),
    volume(0.4),
    normalizedControllerPos(0.5),
    samplesElapsed(0)
{
    
}

bool ADSRVoice::canPlaySound(SynthesiserSound *sound)
{
    return true;
}

void ADSRVoice::startNote(int midiNoteNumber,
                float velocity,
                SynthesiserSound* sound,
                int currentPitchWheelPosition)
{
    // Setup pitch
    currentMidiNoteNumber = midiNoteNumber;
    volume = 0.2 + 0.3 * velocity;
    isTailingOff = false;
    oscillator.setSampleRate(getSampleRate());
    oscillator.setFrequency(getNoteFrequency(midiNoteNumber, currentPitchWheelPosition));
    oscillator.setOscillatorType(ADSR_Oscillator_Type);
    
    // ADSR
    samplesElapsed = 0;
    attackSamples = (int)(ADSR_Attack * getSampleRate());
    decaySamples = (int)(ADSR_Decay * getSampleRate());
    sustain = ADSR_Sustain;
    releaseSamples = (int)(ADSR_Release * getSampleRate());
}

void ADSRVoice::stopNote(float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        // TODO: Find something a little more elegant for this effect..
        //      What I'm doing is saying "you will release at a fixed rate, irrespective
        //      of whether you have reached that volume yet. If you're releasing, decay is ignored
        //      but perhaps it's more desirable to have the decay section play out regardless
        //      and flag the voice for "release requested"
        float currentEnvelopeValue = getEnvelopeValue();
        releaseSamples = (int)(releaseSamples * currentEnvelopeValue / sustain);
        sustain = currentEnvelopeValue;
        isTailingOff = true;
        samplesElapsed = 0;
    }
    else
    {
        clearCurrentNote();
        oscillator.setFrequency(0);
        oscillator.reset();
        samplesElapsed = 0;
    }
}

void ADSRVoice::pitchWheelMoved(int newPitchWheelValue)
{
    double hz = getNoteFrequency(currentMidiNoteNumber, newPitchWheelValue);
    oscillator.setFrequency(hz);
}

void ADSRVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    // Sine/square wave mixing function
    normalizedControllerPos = ((double)newControllerValue) / 127;
}
	
void ADSRVoice::renderNextBlock (AudioBuffer<float>& outputBuffer,
                      int startSample,
                      int numSamples)
{
    while (numSamples > 0)
    {
        float currentSample = getEnvelopeValue() * oscillator.getNextValue() * (volume);

        for (int i = outputBuffer.getNumChannels(); --i >= 0;)
        {
            outputBuffer.addSample (i, startSample, currentSample);
        }
        
        startSample++;
        samplesElapsed++;
        numSamples--;
    }
    
    if (isTailingOff && samplesElapsed >= releaseSamples)
    {
        stopNote(0, false);
    }
}

double ADSRVoice::getNoteFrequency(int midiNoteNumber, int pitchWheelPosition)
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

double ADSRVoice::getEnvelopeValue()
{
    if (isTailingOff)
    {
        float amount = ((float)samplesElapsed) / ((float)releaseSamples);
        amount = (amount > 1 ? 1 : amount);
        return lerp(amount, sustain, 0);
    }
    else if (samplesElapsed <= attackSamples)
    {
        return ((float)samplesElapsed) / ((float)attackSamples);
    }
    else if (samplesElapsed <= attackSamples + decaySamples)
    {
        float amount = ((double)(samplesElapsed - attackSamples)) / (double) decaySamples;
        return lerp(amount, 1, sustain);
    }
    else
    {
        return sustain;
    }
}

inline double ADSRVoice::lerp(double t, double a, double b)
{
    return ((1-t) * a) + (t * b);
}
