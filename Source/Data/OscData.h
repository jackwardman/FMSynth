/*
  ==============================================================================

    OscData.h
    Created: 24 Jan 2022 9:45:03pm
    Author:  Jack Wardman

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public dsp::Oscillator<float>
{
public:
    void prepareToPlay(dsp::ProcessSpec spec);
    void getNextAudioBlock(dsp::AudioBlock<float> &block);
    void setWaveFrequency(const int midiNoteNumber);
    void setWaveType(const int choice);
    void setFMParams(const float depth, const float frequency, const int choice);
    
private:
    dsp::Oscillator<float> fmOsc;
    float fmMod{0.f};
    float fmDepth;
    
    int lastMidiNote;

};
