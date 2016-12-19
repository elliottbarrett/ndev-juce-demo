/*
  ==============================================================================

	FirstSynthAudioManager.h
	Created: 4 Nov 2016 12:06:05am
	Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef FIRSTSYNTHAUDIOMANAGER_H_INCLUDED
#define FIRSTSYNTHAUDIOMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FirstSynthAudioSource.h"
#include "FirstSynthesiser.h"
#include "MicInputAudioSource.h"
#include "Enums.h"

class FirstSynthAudioManager
{
public:
	FirstSynthAudioManager();
    void setSynthType(SynthType t);
    
private:
	// Members
	ScopedPointer<AudioDeviceManager> deviceManager;
    AudioSourcePlayer synthAudioSourcePlayer;
    AudioSourcePlayer inputAudioSourcePlayer;
    FirstSynthesiser synth;
    ScopedPointer<FirstSynthAudioSource> synthAudioSource;
    ScopedPointer<MicInputAudioSource> inputAudioSource;

    // Methods
};

#endif
