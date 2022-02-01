/*
  ==============================================================================

    FilterData.cpp
    Created: 26 Jan 2022 2:16:24am
    Author:  Jack Wardman

  ==============================================================================
*/

#include "FilterData.h"
void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, const int numChannels)
{
    filter.reset();
    dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    filter.prepare(spec);
    
    isPrepared = true;
}

void FilterData::process(AudioBuffer<float> &buffer)
{
    jassert(isPrepared);
    dsp::AudioBlock<float> block {buffer};
    filter.process(dsp::ProcessContextReplacing<float> (block));
}

void FilterData::updateParameters(const int filterType, const float frequency, const float resonance, const float modulator)
{
    switch (filterType) {
        case 0:
            filter.setType(dsp::StateVariableTPTFilterType::lowpass);
            break;
        case 1:
            filter.setType(dsp::StateVariableTPTFilterType::bandpass);
        case 2:
            filter.setType(dsp::StateVariableTPTFilterType::highpass);
    }
    
    float modFreq = frequency * modulator;
    modFreq = std::fmin(std::fmax(modFreq, 20.0f), 20000.0f);
    
    filter.setCutoffFrequency(modFreq);
    filter.setResonance(resonance);
}

void FilterData::reset()
{
    filter.reset();
}
