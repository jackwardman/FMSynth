/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthAudioProcessorEditor::BasicSynthAudioProcessorEditor (BasicSynthAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p), adsr("Envelope", audioProcessor.apvts, "attack", "decay", "sustain", "release"), osc(audioProcessor.apvts, "osctype", "fmfreq", "fmdepth"), filter(audioProcessor.apvts, "filtertype", "filtercutoff", "filterresonance"), modadsr("Filter Envelope", audioProcessor.apvts, "modattack", "moddecay", "modsustain", "modrelease")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setSize (500, 500);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(modadsr);
    
}

BasicSynthAudioProcessorEditor::~BasicSynthAudioProcessorEditor()
{
}

//==============================================================================
void BasicSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    g.setColour (juce::Colours::white);


}

void BasicSynthAudioProcessorEditor::resized()
{
    const auto padding = 10;
    
    adsr.setBounds(getWidth() / 2 + padding, 10, 220, 200);
    osc.setBounds(padding, padding, 220, 200);
    filter.setBounds(getWidth() / 2 + padding, adsr.getBottom(), 220, 200);
    modadsr.setBounds(padding, osc.getBottom(), 220, 200);

}

