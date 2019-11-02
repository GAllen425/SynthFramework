/*
  ==============================================================================

    Envelope.cpp
    Created: 28 Sep 2019 4:10:41pm
    Author:  Gareth

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SynthFrameworkAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	adsrArea = getLocalBounds();

	attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attackSlider.setRange(0.1f,5000.0f);
	attackSlider.setValue(1.0f);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&attackSlider);

	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setRange(0.1f,2000.0f);
	decaySlider.setValue(1.0f);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&decaySlider);

	sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustainSlider.setRange(0.0f,1.0f);
	sustainSlider.setValue(1.0f);
	sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&sustainSlider);

	releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	releaseSlider.setRange(0.1f,5000.0f);
	releaseSlider.setValue(1.0f);
	releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(&releaseSlider);

	attackValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "attack", attackSlider);
	decayValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "decay", decaySlider);
	sustainValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "sustain", sustainSlider);
	releaseValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
		processor.tree, "release", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(10, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("ADSR", titleArea, Justification::centredTop);

	juce::Rectangle<float> area = getLocalBounds().reduced(30).toFloat();
	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20, 2);
}

void Envelope::resized()
{

	auto adsrArea = getLocalBounds().reduced(40);
	int numberEnvelopeSliders = 4;
	auto adsrSplitArea = adsrArea.withWidth (adsrArea.getWidth() / 
											 numberEnvelopeSliders);


	Array<Component*> sliderArray;
	sliderArray.add(&attackSlider, &decaySlider, &sustainSlider, &releaseSlider);

	for (auto slider : sliderArray)
	{
		slider->setBounds(adsrSplitArea);
		adsrSplitArea.translate(adsrSplitArea.getWidth(), 0.0f);
	}
}
