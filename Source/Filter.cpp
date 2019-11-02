/*
  ==============================================================================

    Filter.cpp
    Created: 29 Sep 2019 12:18:37pm
    Author:  Gareth

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(SynthFrameworkAudioProcessor& p) : processor(p)
{
	filterArea = getLocalBounds();
	filterTypeComboBox.addItem("Low Pass", 1);
	filterTypeComboBox.addItem("High Pass", 2);
	filterTypeComboBox.addItem("Band Pass", 3);
	filterTypeComboBox.setJustificationType(Justification::centred);
	addAndMakeVisible(&filterTypeComboBox);
	filterSelection = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(
		processor.tree, "filterType", filterTypeComboBox);

	filterCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterCutoffSlider.setRange(20.0f, 10000.0f);
	filterCutoffSlider.setValue(400.0);
	//filterCutoffSlider.setSkewFactorFromMidPoint(1000.0f);
	filterCutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterCutoffSlider);
	cutoffVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "filterCutoff", filterCutoffSlider);

	filterResSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterResSlider.setRange(1, 5);
	filterResSlider.setValue(1);
	filterResSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterResSlider);
	resVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "filterRes", filterResSlider);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(10, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Filter", titleArea, Justification::centredTop);

	juce::Rectangle<float> area = getLocalBounds().reduced(30).toFloat();
	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20, 2);
}

void Filter::resized()
{
	auto filterArea = getLocalBounds().reduced(40);
	int numberParameters = 3;

	auto filterSplitArea = filterArea.withWidth(filterArea.getWidth() /
		numberParameters);

	Array<Component*> componentArray;
	componentArray.add(&filterTypeComboBox, &filterCutoffSlider, &filterResSlider);

	for (auto component : componentArray)
	{
		component->setBounds(filterSplitArea);
		filterSplitArea.translate(filterSplitArea.getWidth(), 0.0f);
	}

}
