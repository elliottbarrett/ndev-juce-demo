/*
  ==============================================================================

    MicInputAudioSource.h
    Created: 12 Nov 2016 6:59:10pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#ifndef MICINPUTAUDIOSOURCE_H_INCLUDED
#define MICINPUTAUDIOSOURCE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Enums.h"

class MicInputAudioSource : public AudioSource
{
public:
    MicInputAudioSource(AudioDeviceManager *dm);
    ~MicInputAudioSource();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

private:
    AudioDeviceManager *deviceManager;
    int echoBufferSampleIndex;
    AudioSampleBuffer *echoBufferA;
    AudioSampleBuffer *echoBufferB;
    EchoBufferState echoState;
    
    void updateEchoBufferState();
};

#endif
