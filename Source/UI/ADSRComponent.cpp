/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 24 Jan 2022 5:35:45pm
    Author:  Jack Wardman

  ==============================================================================
*/

#include "ADSRComponent.h"

ADSRComponent::ADSRComponent(juce::String name, AudioProcessorValueTreeState &apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    
    componentName = name;
    
    attackSliderAttachment = std::make_unique<sliderAttachment>(apvts, attackId, attackSlider);
    setSliderParams(attackSlider, attackLabel);
    decayliderAttachment = std::make_unique<sliderAttachment>(apvts, decayId, decaySlider);
    setSliderParams(decaySlider, decayLabel);
    sustainSliderAttachment = std::make_unique<sliderAttachment>(apvts, sustainId, sustainSlider);
    setSliderParams(sustainSlider, sustainLabel);
    releaseSliderAttachment = std::make_unique<sliderAttachment>(apvts, releaseId, releaseSlider);
    setSliderParams(releaseSlider, releaseLabel);
}

ADSRComponent::~ADSRComponent()
{
    
}

void ADSRComponent::paint(Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.setFont(20.0f);
    g.drawText(componentName, labelSpace, Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
    
}

void ADSRComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() * 0.75;
    const auto startX = padding + 5;
    const auto startY = bounds.getHeight() / 2 - (sliderHeight / 3) - 10;
    const auto labelYOffset = 130;
    const auto labelHeight = 15;
    
    
    attackSlider.setBounds(startX, startY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, startY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, startY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, startY, sliderWidth, sliderHeight);
    
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() + labelYOffset, sliderWidth, labelHeight);
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getY() + labelYOffset, sliderWidth, labelHeight);
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getY() + labelYOffset, sliderWidth, labelHeight);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() + labelYOffset, sliderWidth, labelHeight);
}




void ADSRComponent::setSliderParams(Slider &slider, Label &label)
{
    slider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(slider);

    label.setColour(Label::ColourIds::textColourId, Colours::white);
    label.setFont(13.0f);
    label.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(label);
}
