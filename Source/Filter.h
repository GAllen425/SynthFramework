/*
  ==============================================================================

    Filter.h
    Created: 29 Sep 2019 12:18:37pm
    Author:  Gareth

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(SynthFrameworkAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
	juce::Rectangle<int> filterArea;

	SynthFrameworkAudioProcessor& processor;

	ComboBox filterTypeComboBox;
	Slider filterCutoffSlider;
	Slider filterResSlider;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterSelection;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffVal;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> resVal;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
