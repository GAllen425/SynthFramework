/*
  ==============================================================================

    Envelope.h
    Created: 28 Sep 2019 4:10:41pm
    Author:  Gareth

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(SynthFrameworkAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
	juce::Rectangle<int> adsrArea;

	SynthFrameworkAudioProcessor& processor;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseValue;

	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
