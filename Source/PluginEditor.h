/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"


//==============================================================================
/**
*/
class BasicSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BasicSynthAudioProcessorEditor (BasicSynthAudioProcessor&);
    ~BasicSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    
    BasicSynthAudioProcessor& audioProcessor;
    
    ADSRComponent adsr;
    OscComponent osc;
    FilterComponent filter;
    ADSRComponent modadsr;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSynthAudioProcessorEditor)
};
