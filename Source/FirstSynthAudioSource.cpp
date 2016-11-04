/*
  ==============================================================================

    FirstSynthAudioSource.cpp
    Created: 3 Nov 2016 9:54:34pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef FIRSTSYNTHAUDIOSOURCE_H_INCLUDED
#define FIRSTSYNTHAUDIOSOURCE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FirstSynthesiser.cpp"

struct FirstSynthAudioSource : public AudioSource
{
public:
    FirstSynthAudioSource()
    {
        synth.clearSounds();
        synth.addSound(new FirstSound());
    }
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        midiCollector.reset(sampleRate);
        synth.setCurrentPlaybackSampleRate(sampleRate);
    }
    
    void releaseResources()
    {
        
    }
    
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
    {
        // Is this needed?
        bufferToFill.clearActiveBufferRegion();
        
        // Fill a buffer with midi messages
        MidiBuffer incomingMidi;
        midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
        
        // Tell the synth to render those messages into the buffer
        synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    }

	FirstSynthesiser synth;
	FirstSynthMidiCallback midiCollector;
};

#endif
