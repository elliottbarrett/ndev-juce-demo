/*
  ==============================================================================

    Enums.h
    Created: 11 Nov 2016 12:09:43pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

enum SynthType
{
    ST_NONE,
    ST_SQUARE_SINE,
    ST_FM,
    ST_ADSR,
    ST_INVALID
};

enum EchoBufferState
{
    EBS_PREFILLING_A,
    EBS_READ_A_WRITE_B,
    EBS_READ_B_WRITE_A,
    EBS_INVALID
};

#endif  // ENUMS_H_INCLUDED
