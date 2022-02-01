/*
  ==============================================================================

    OscComponent.h
    Created: 24 Jan 2022 10:13:51pm
    Author:  Jack Wardman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(AudioProcessorValueTreeState &apvts, juce::String oscSelectorId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setComboBoxParams(ComboBox &combobox, Label &label);
    void setSliderParams(Slider &slider, Label &label);
    
    ComboBox oscSelectBox;
    Label oscSelectLabel{"Oscillator Type", "Oscillator Type" };
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectAttachment;
    
    ComboBox modOscSelectBox;
    Label modOscSelectLabel{" Mod Oscillator Type", "Mod Oscillator Type" };
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> modOscSelectAttachment;
    
    Slider fmFreqSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    Slider fmDepthSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;
    
    Label fmFreqLabel{ "FM Frequency", "FM Frequency" };
    Label fmDepthLabel{ "FM Depth", "FM Depth" };

    juce::String componentName{""};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
