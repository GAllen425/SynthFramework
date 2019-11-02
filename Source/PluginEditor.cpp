/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGUI (p), envGUI(p), filterGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 200);

	addAndMakeVisible(&oscGUI);
	addAndMakeVisible(&envGUI);
	addAndMakeVisible(&filterGUI);

}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}



//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

}

void SynthFrameworkAudioProcessorEditor::resized()
{
	const int componentWidth = 200;
	const int componentHeight = 200;

	juce::Rectangle<int> area = getLocalBounds();
	juce::Rectangle<int> oscArea = area.removeFromLeft(componentWidth).removeFromTop(componentHeight);
	juce::Rectangle<int> envArea = area.removeFromLeft(componentWidth).removeFromTop(componentHeight);
	juce::Rectangle<int> filterArea = area.removeFromLeft(2*componentWidth).removeFromTop(componentHeight);

	oscGUI.setBounds(oscArea);
	envGUI.setBounds(envArea);
	filterGUI.setBounds(filterArea);



}

