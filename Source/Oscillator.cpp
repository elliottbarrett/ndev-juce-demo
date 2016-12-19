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
        case OT_INVALID:
        case OT_NONE:
            value = 0;
            break;
        case OT_SINE:
            value = sin(currentAngle);
            break;
        case OT_SQUARE:
            value = (sin(currentAngle) > 0 ? 1 : -1);
            break;
        case OT_SAW:
            value = (2 * currentAngle / TAU) - 1;
            break;
        case OT_TRIANGLE:
            float cur = currentAngle / TAU;
            if (cur <= 0.25) {
                value = cur / 0.25;
            } else if (cur <= 0.5) {
                value = 1.0 - ((cur - 0.25) / 0.25);
            } else if (cur <= 0.75) {
                value = 0.0 - ((cur - 0.5) / 0.25);
            } else {
                value = -1.0 + ((cur - 0.75) / 0.25);
            }
            break;
    }
    currentAngle = fmod(currentAngle + angleDelta, TAU);
    return value;
}

void Oscillator::reset()
{
    float cyclesPerSample = frequency / sampleRate;
    angleDelta = cyclesPerSample * TAU;
    currentAngle = 0;
}
