/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Jan 2022 3:16:52pm
    Author:  Jack Wardman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/OscData.h"
#include "Data/ADSRData.h"
#include "Data/FilterData.h"


class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    void updateFilterParams(const int filterType, const float frequency, const float resonance);
    void updateModADSR(const float attack, const float decay, const float sustain, const float release);
    OscData &getOscillator() { return osc; };
    ADSRData& getAdsr() { return adsr; }
    ADSRData& getModAdsr() { return modadsr; }
    FilterData& getFilter() { return filter; }
    
private:
    
    OscData osc;
    ADSRData adsr;
    FilterData filter;
    ADSRData modadsr;
    
    float velocity;
    
    AudioBuffer<float> synthBuffer;
    dsp::Gain<float> gain;
    bool isPrepared { false };
};
