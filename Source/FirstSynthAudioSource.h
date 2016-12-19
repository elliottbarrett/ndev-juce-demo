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
#include "FirstSynthesiser.h"

struct FirstSynthAudioSource : public AudioSource
{
public:
    FirstSynthAudioSource(FirstSynthesiser *s);
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
	void releaseResources() override;
    
	FirstSynthesiser *synth;
	MidiMessageCollector midiCollector;
    
private:
    MidiInput *midiInput;
    bool hasMidiInput;
};

#endif
