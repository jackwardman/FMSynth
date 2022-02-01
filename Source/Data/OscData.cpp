/*
  ==============================================================================

    OscData.cpp
    Created: 24 Jan 2022 9:45:03pm
    Author:  Jack Wardman

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(dsp::ProcessSpec spec)
{
    fmOsc.prepare(spec);
    prepare(spec);

}

void OscData::getNextAudioBlock(dsp::AudioBlock<float> &block)
{
    for (int ch = 0; ch < block.getNumChannels(); ++ch) {
        for (int i = 0; i < block.getNumSamples(); i++) {
            fmMod = fmOsc.processSample(block.getSample(ch, i)) * fmDepth;
        }
    }
    process(dsp::ProcessContextReplacing<float> (block));
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(MidiMessage::getMidiNoteInHertz(midiNoteNumber) + lastMidiNote * fmMod);
    lastMidiNote = midiNoteNumber;
}

void OscData::setWaveType(const int choice)
{
    switch (choice) {
        case 0:
            //sine
            initialise([](float x){ return std::sin(x); });
            break;
        case 1:
            //saw
            initialise([](float x){ return x / M_PI; });
            break;
        case 2:
            //square
            initialise([](float x){ return x > 0.0f ? -1.0f : 1.0f; });
            break;
        default:
            jassertfalse;
            break;
    }
}

void OscData::setFMParams(const float depth, const float frequency, const int choice)
{
    switch (choice) {
        case 0:
            //sine
            fmOsc.initialise([](float x){ return std::sin(x); });
            break;
        case 1:
            //saw
            fmOsc.initialise([](float x){ return x / M_PI; });
            break;
        case 2:
            //square
            fmOsc.initialise([](float x){ return x > 0.0f ? -1.0f : 1.0f; });
            break;
        default:
            jassertfalse;
            break;
    }
    fmOsc.setFrequency(frequency);
    fmDepth = depth;
    setWaveFrequency(lastMidiNote);
}

