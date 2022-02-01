/*
  ==============================================================================

    FilterComponent.cpp
    Created: 26 Jan 2022 3:41:14am
    Author:  Jack Wardman

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(AudioProcessorValueTreeState &apvts, juce::String filterSelectId, juce::String filterCutoffId, juce::String filterResId)
{
    filterSelectAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterSelectId, filterSelectBox);
    filterCutoffAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, filterCutoffId, filterCutoffSlider);
    filterResAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, filterResId, filterResSlider);
    
    setComboBoxParams(filterSelectBox, filterSelectLabel);
    setSliderParams(filterCutoffSlider, filterCutoffLabel);
    setSliderParams(filterResSlider, filterResLabel);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace, Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{
    const auto sliderWidth = 80;
    const auto sliderHeight = 70;
    const auto labelYOffset = 60;
    const auto labelHeight = 15;
    const auto startY = 60;
    
    
    filterSelectBox.setBounds(10, startY, 90, 20);
    filterCutoffSlider.setBounds(10, 90, sliderWidth, sliderHeight);
    filterResSlider.setBounds(90, 90, sliderWidth, sliderHeight);
    
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() + labelYOffset, sliderWidth, labelHeight);
    filterResLabel.setBounds(filterResSlider.getX(), filterResSlider.getY() + labelYOffset, sliderWidth, labelHeight);
    filterSelectLabel.setBounds(filterSelectBox.getX(), filterSelectBox.getY() - 20, 90, 20);

}

void FilterComponent::setComboBoxParams(ComboBox &combobox, Label &label)
{
    StringArray choices{"Lowpass", "Bandpass", "Highpass"};
    combobox.addItemList(choices, 1);
    addAndMakeVisible(combobox);
    
    label.setColour(Label::ColourIds::textColourId, Colours::white);
    label.setFont(13.0f);
    label.setJustificationType(Justification::centred);
    addAndMakeVisible(label);
}

void FilterComponent::setSliderParams(Slider &slider, Label &label)
{
    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(slider);

    label.setColour(Label::ColourIds::textColourId, Colours::white);
    label.setFont(13.0f);
    label.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(label);
}
