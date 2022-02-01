/*
  ==============================================================================

    SynthVoice.cpp
    Created: 24 Jan 2022 3:16:52pm
    Author:  Jack Wardman

  ==============================================================================
*/

#include "SynthVoice.h"
bool SynthVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modadsr.noteOn();
    gain.setGainLinear(0.3f * velocity);
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modadsr.noteOff();
    if (!allowTailOff || !adsr.isActive() )
        clearCurrentNote();
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}
    
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepareToPlay(spec);
    
    adsr.setSampleRate(sampleRate);
    
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    
    modadsr.setSampleRate(sampleRate);
    
    gain.prepare(spec);
    gain.setGainLinear(0.3f);
    
    isPrepared = true;
}

void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateModADSR(const float attack, const float decay, const float sustain, const float release)
{
    modadsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    if (! isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), outputBuffer.getNumSamples(), false, false, true);
    // Apply modulation adsr to empty buffer just to activate it!
    modadsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    synthBuffer.clear();
    dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.getNextAudioBlock(audioBlock);
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    filter.process(synthBuffer);
    gain.process(dsp::ProcessContextReplacing<float> (audioBlock));
    
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (! adsr.isActive())
            clearCurrentNote();
    }
}

void SynthVoice::updateFilterParams(const int filterType, const float frequency, const float resonance)
{
    float modulator = modadsr.getNextSample();
    filter.updateParameters(filterType, frequency, resonance, modulator);
    
}
