/*
  ==============================================================================

    Oscillator.cpp
    Created: 14 Dec 2016 4:48:21pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#include "Oscillator.h"

Oscillator::Oscillator()
{
    
}

Oscillator::~Oscillator()
{
    
}

void Oscillator::setOscillatorType(OscillatorType t)
{
    type = t;
}

void Oscillator::setFrequency(float f)
{
    frequency = f;
    reset();
}

void Oscillator::setSampleRate(double hz)
{
    sampleRate = hz;
    reset();
}

float Oscillator::getNextValue()
{
    float value;
    if (angleDelta == 0)
    {
        return 0;
    }
    switch (type)
    {
        case OT_SINE:
            value = sin(currentAngle);
            break;
        case OT_SQUARE:
            value = (sin(currentAngle) > 0 ? 1 : -1);
            break;
        case OT_SAW:
            value = (2 * fmod(currentAngle, TAU) / TAU) - 1;
            break;
        case OT_TRIANGLE:
            value = 0; // TODO
            break;
        default:
            value = 0;
            break;
            
    }
    currentAngle += angleDelta;
    return value;
}

void Oscillator::reset()
{
    float cyclesPerSample = frequency / sampleRate;
    angleDelta = cyclesPerSample * TAU;
    currentAngle = 0;
}
