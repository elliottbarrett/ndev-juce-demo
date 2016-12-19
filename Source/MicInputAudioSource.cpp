/*
  ==============================================================================

    MicInputAudioSource.cpp
    Created: 12 Nov 2016 6:59:10pm
    Author:  Elliott Barrett

  ==============================================================================
*/

#include "MicInputAudioSource.h"

MicInputAudioSource::MicInputAudioSource(AudioDeviceManager *dm) :
    deviceManager(dm)
{
    // Want to echo a second later, so buffer 44,100 samples
    // Rather than deal with circular queue just swap between two buffers
    echoBufferA = new AudioSampleBuffer(2, 44100);
    echoBufferB = new AudioSampleBuffer(2, 44100);
    echoBufferSampleIndex = 0;
}

MicInputAudioSource::~MicInputAudioSource()
{
    delete echoBufferA;
    delete echoBufferB;
}

void MicInputAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate) 
{
}

void MicInputAudioSource::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) 
{
    AudioIODevice *device = deviceManager->getCurrentAudioDevice();
    const BigInteger activeInputChannels = device->getActiveInputChannels();
    const BigInteger activeOutputChannels = device->getActiveOutputChannels();
    const int maxInputChannels = activeInputChannels.getHighestBit() + 1;
    const int maxOutputChannels = activeOutputChannels.getHighestBit() + 1;
    
    int echoIndexStart = echoBufferSampleIndex;
    EchoBufferState echoStateStart = echoState;
    
    for (int channel = 0; channel < maxOutputChannels; channel++)
    {
        echoBufferSampleIndex = echoIndexStart;
        echoState = echoStateStart;
        if ((! activeOutputChannels[channel]) || maxInputChannels == 0)
        {
            bufferToFill.buffer->clear (channel, bufferToFill.startSample, bufferToFill.numSamples);
        }
        else
        {
            const int actualInputChannel = channel % maxInputChannels; // [1]
            
            if (! activeInputChannels[channel]) // [2]
            {
                bufferToFill.buffer->clear (channel, bufferToFill.startSample, bufferToFill.numSamples);
            }
            else // [3]
            {
                const float* inBuffer = bufferToFill.buffer->getReadPointer (actualInputChannel,
                                                                             bufferToFill.startSample);
                float* outBuffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
                
                for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
                {
                    switch (echoState)
                    {
                        case EBS_PREFILLING_A:
                            echoBufferA->setSample(channel, echoBufferSampleIndex, inBuffer[sample]);
                            outBuffer[sample] = inBuffer[sample];
                            updateEchoBufferState();
                            break;
                        case EBS_READ_A_WRITE_B:
                            echoBufferB->setSample(channel, echoBufferSampleIndex, inBuffer[sample]);
                            outBuffer[sample] = 0.5 * inBuffer[sample] + 0.5 * echoBufferA->getSample(channel, echoBufferSampleIndex);
                            updateEchoBufferState();
                            break;
                        case EBS_READ_B_WRITE_A:
                            echoBufferA->setSample(channel, echoBufferSampleIndex, inBuffer[sample]);
                            outBuffer[sample] = 0.5 * inBuffer[sample] + 0.5 * echoBufferB->getSample(channel, echoBufferSampleIndex);
                            updateEchoBufferState();
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void MicInputAudioSource::releaseResources()
{
    
}

void MicInputAudioSource::updateEchoBufferState()
{
    echoBufferSampleIndex++;
    if (echoBufferSampleIndex >= 44100)
    {
        echoBufferSampleIndex = 0;
        switch (echoState)
        {
            case EBS_PREFILLING_A:
                echoState = EBS_READ_A_WRITE_B;
                break;
            case EBS_READ_A_WRITE_B:
                echoState = EBS_READ_B_WRITE_A;
                break;
            case EBS_READ_B_WRITE_A:
                echoState = EBS_READ_A_WRITE_B;
                break;
            default:
                assert(false); 
        }
    }
}