/*
  ==============================================================================

    Oscillator.h
    Created: 14 Dec 2016 4:48:21pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#define TAU 6.2831853072

enum OscillatorType
{
    OT_NONE,
    OT_SINE,
    OT_SQUARE,
    OT_SAW,
    OT_TRIANGLE,
    OT_INVALID
};

class Oscillator
{
public:
    Oscillator();
    ~Oscillator();
    void setSampleRate(double hz);
    void setFrequency(float f);
    void setOscillatorType(OscillatorType t);
    float getNextValue();
    void reset();
private:
    OscillatorType type;
    float frequency;
    float angleDelta;
    float currentAngle;
    double sampleRate;
};



#endif  // OSCILLATOR_H_INCLUDED
