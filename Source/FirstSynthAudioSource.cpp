/*
  ==============================================================================

	FirstSynthAudioSource.cpp
	Created: 3 Nov 2016 9:54:34pm
	Author:  Elliott Barrett

  ==============================================================================
*/
#include "FirstSynthAudioSource.h"
#include "FirstSound.h"

FirstSynthAudioSource::FirstSynthAudioSource(FirstSynthesiser *s) : synth(s)
{
	synth->clearSounds();
	synth->addSound(new FirstSound());
    
    auto devices = MidiInput::getDevices();
    if (devices.isEmpty())
    {
        hasMidiInput = false;
        return;
    }
    
    midiInput = MidiInput::openDevice(0, &midiCollector);
    midiInput->start();
}

void FirstSynthAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	midiCollector.reset(sampleRate);
	synth->setCurrentPlaybackSampleRate(sampleRate);
}

void FirstSynthAudioSource::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
	bufferToFill.clearActiveBufferRegion();
    
	// Fill a buffer with midi messages
	MidiBuffer incomingMidi;
	midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
	
	// Tell the synth to render those messages into the buffer
	synth->renderNextBlock(*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
}

void FirstSynthAudioSource::releaseResources()
{
    midiInput->stop();
    delete midiInput;
}
