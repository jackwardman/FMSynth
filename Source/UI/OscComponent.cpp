/*
  ==============================================================================

    OscComponent.cpp
    Created: 24 Jan 2022 10:13:51pm
    Author:  Jack Wardman

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(AudioProcessorValueTreeState &apvts, juce::String oscSelectorId, juce::String fmFreqId, juce::String fmDepthId)
{
    oscSelectAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscSelectorId, oscSelectBox);
    modOscSelectAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscSelectorId, oscSelectBox);
    
    fmFreqAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider);
    fmDepthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider);

    setComboBoxParams(oscSelectBox, oscSelectLabel);
    setComboBoxParams(modOscSelectBox, modOscSelectLabel);
    setSliderParams(fmFreqSlider, fmFreqLabel);
    setSliderParams(fmDepthSlider, fmDepthLabel);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.setFont(20.0f);
    g.drawText("Oscillator", labelSpace, Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);}

void OscComponent::resized()
{
    const auto sliderWidth = 80;
    const auto sliderHeight = 70;
    const auto labelYOffset = 60;
    const auto labelHeight = 15;
    const auto startY = 60;
    
    oscSelectBox.setBounds(10, startY, 90, 20);
    modOscSelectBox.setBounds(oscSelectBox.getRight() + 10, startY, 90, 20);
    fmFreqSlider.setBounds(10, 90, sliderWidth, sliderHeight);
    fmDepthSlider.setBounds(90, 90, sliderWidth, sliderHeight);
    
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() + labelYOffset, sliderWidth, labelHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() + labelYOffset, sliderWidth, labelHeight);
    oscSelectLabel.setBounds(oscSelectBox.getX(), oscSelectBox.getY() - 20, 90, 20);
    modOscSelectLabel.setBounds(modOscSelectBox.getX(), modOscSelectBox.getY() - 20, 90, 20);
}

void OscComponent::setComboBoxParams(ComboBox &combobox, Label &label)
{
    StringArray choices{"Sine", "Saw", "Square"};
    combobox.addItemList(choices, 1);
    addAndMakeVisible(combobox);
    
    label.setColour(Label::ColourIds::textColourId, Colours::white);
    label.setFont(13.0f);
    label.setJustificationType(Justification::centred);
    addAndMakeVisible(label);
}

void OscComponent::setSliderParams(Slider &slider, Label &label)
{
    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(slider);

    label.setColour(Label::ColourIds::textColourId, Colours::white);
    label.setFont(13.0f);
    label.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(label);
}
