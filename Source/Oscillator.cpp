/*
  ==============================================================================

    Oscillator.cpp
    Created: 28 Sep 2019 2:58:07pm
    Author:  Gareth

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFrameworkAudioProcessor& p) : processor (p)
{
	setSize(200, 200);
	waveShapeComboBox.addItem("Sine", 1);
	waveShapeComboBox.addItem("Saw", 2);
	waveShapeComboBox.addItem("Square", 3);
	waveShapeComboBox.setJustificationType(Justification::centred);

	addAndMakeVisible(&waveShapeComboBox);


	waveSelection = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(
		processor.tree, "wavetype", waveShapeComboBox);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(10, 10, getWidth(), 20);

    g.fillAll (Colours::black); 
    g.setColour (Colours::white);
	g.drawText("Oscillator One", titleArea, Justification::centredTop);

	juce::Rectangle<float> area = getLocalBounds().reduced(30).toFloat();
	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20, 2);

}

void Oscillator::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40);
	waveShapeComboBox.setBounds(area.removeFromTop(20));

}
