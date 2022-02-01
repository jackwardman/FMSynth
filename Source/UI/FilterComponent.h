/*
  ==============================================================================

    FilterComponent.h
    Created: 26 Jan 2022 3:41:14am
    Author:  Jack Wardman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(AudioProcessorValueTreeState &apvts, juce::String filterSelectId, juce::String filterCutoffId, juce::String filterResId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setComboBoxParams(ComboBox &combobox, Label &label);
    void setSliderParams(Slider &slider, Label &label);
    
    ComboBox filterSelectBox;
    Label filterSelectLabel{"Filter Type", "Filter Type" };
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterSelectAttachment;
    
    Slider filterCutoffSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
    Slider filterResSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterResAttachment;
    
    Label filterCutoffLabel{ "Filter Cutoff", "Filter Cutoff" };
    Label filterResLabel{ "Filter Resonance", "Filter Resonance" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
