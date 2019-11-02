/*
  ==============================================================================

    Oscillator.h
    Created: 28 Sep 2019 2:58:07pm
    Author:  Gareth

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator(SynthFrameworkAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

private:
	ComboBox waveShapeComboBox;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;


	SynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
