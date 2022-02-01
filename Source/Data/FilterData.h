/*
  ==============================================================================

    FilterData.h
    Created: 26 Jan 2022 2:16:24am
    Author:  Jack Wardman

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData {
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, const int numChannels);
    void process(AudioBuffer<float> &buffer);
    void updateParameters(const int filterType, const float frequency, const float resonance, const float modulator = 1.0f);
    void reset();
    
private:
    dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{false};
};
