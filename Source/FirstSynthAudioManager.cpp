/*
  ==============================================================================

	FirstSynthAudioManager.cpp
	Created: 4 Nov 2016 12:06:05am
	Author:  Elliott Barrett

  ==============================================================================
*/
#include "FirstSynthAudioManager.h"

FirstSynthAudioManager::FirstSynthAudioManager()
{
	deviceManager = new AudioDeviceManager();
	deviceManager->initialise(2, 2, 0, true, String::empty, 0);
	deviceManager->addAudioCallback(&synthAudioSourcePlayer);
    
	synthAudioSource = new FirstSynthAudioSource(&synth);
	synthAudioSourcePlayer.setSource(synthAudioSource);
	deviceManager->addMidiInputCallback(String::empty, &(synthAudioSource->midiCollector));
        
    return;
    inputAudioSource = new MicInputAudioSource(deviceManager);
    inputAudioSourcePlayer.setSource(inputAudioSource);
    deviceManager->addAudioCallback(&inputAudioSourcePlayer);
}

// Methods
void FirstSynthAudioManager::setSynthType(SynthType t)
{
    synth.setSynthType(t);
}
