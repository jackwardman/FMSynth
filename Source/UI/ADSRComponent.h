/*
  ==============================================================================

    ADSRComponent.h
    Created: 24 Jan 2022 5:35:45pm
    Author:  Jack Wardman

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class ADSRComponent : public Component {
public:
    ADSRComponent(juce::String name, AudioProcessorValueTreeState &apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId);
    ~ADSRComponent() override;
    
    void paint(Graphics&) override;
    void resized() override;
    
private:
    void setSliderParams(Slider &slider, Label &label);

    using sliderAttachment = AudioProcessorValueTreeState::SliderAttachment;
    
    Slider attackSlider;
    Label attackLabel{ "Attack Label", "A" };
    Slider decaySlider;
    Label decayLabel{ "Decay Label", "D" };
    Slider sustainSlider;
    Label sustainLabel{ "Sustain Label", "S" };
    Slider releaseSlider;
    Label releaseLabel{ "Release Label", "R" };
    
    std::unique_ptr<sliderAttachment> attackSliderAttachment;
    std::unique_ptr<sliderAttachment> decayliderAttachment;
    std::unique_ptr<sliderAttachment> sustainSliderAttachment;
    std::unique_ptr<sliderAttachment> releaseSliderAttachment;
    
    juce::String componentName{""};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ADSRComponent)
};
