/*
  ==============================================================================

    SynthVoice.h
    Created: 25 Sep 2019 10:45:24pm
    Author:  Gareth

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice {
public:
	// START base override functions
	bool canPlaySound(SynthesiserSound* sound) override
	{
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition) override
	{
		env1.trigger = 1;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		level = velocity * 0.15;

		//Logger::outputDebugString( "MIDI #:" + std::to_string(midiNoteNumber) + 
		//	                       "FREQ:"   + std::to_string(frequency) + "\n" );
	}

	void stopNote(float velocity, bool allowTailOff) override
	{
		env1.trigger = 0;
		allowTailOff = true;
		
		if (velocity == 0)
			clearCurrentNote();
	}

	void pitchWheelMoved(int newPitchWheelValue) override
	{

	}
	void controllerMoved(int controllerNumber, int newControllerValue) override
	{

	}

	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
	{

		for (int i = 0; i < numSamples; ++i)
		{

			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			{
				outputBuffer.addSample(channel, startSample, setFilterParams() * level);
			}

			++startSample;
		}

	}

	// END base override functions

	// ENVELOPE functions
	void getEnvParams(float* attack, float* decay, float* sustain, float*release)
	{
		env1.setAttack(*attack);
		env1.setDecay(*decay);
		env1.setSustain(*sustain);
		env1.setRelease(*release);
	}

	double setEnvelope()
	{
		return env1.adsr(setOscillatorType(), env1.trigger);
	}

	// Oscillator fucntions
	void getOscillatorType(float* selection)
	{
		if (selection != nullptr)
			waveShapeInt = *selection;
	}

	double setOscillatorType()
	{
		switch (waveShapeInt)
		{
		case 0:
			return osc1.sinewave(frequency);
			break;
		case 1:
			return osc1.saw(frequency);
			break;
		case 2:
			return osc1.square(frequency);
			break;
		default:
			return osc1.sinewave(frequency);
			break;
		}

	}

	// Filter functions
	void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
	{
		filterChoice = *filterType;
		cutoff = *filterCutoff;
		resonance = *filterRes;
	}

	double setFilterParams()
	{
		switch (filterChoice)
		{
		case 0:
			return filter1.lores(setEnvelope(), cutoff, resonance);
			break;
		case 1:
			return filter1.hires(setEnvelope() , cutoff, resonance);
			break;
		case 2:
			return filter1.bandpass(setEnvelope(), cutoff, resonance);
			break;
		default:
			return setEnvelope();
			break;
		}
	}

private:
	//Oscillator
	double frequency;
	double level;
	int waveShapeInt = 0;

	//Filter
	int filterChoice;
	float cutoff;
	float resonance;

	maxiOsc osc1;
	maxiOsc osc2;
	maxiEnv env1; 
	maxiFilter filter1;

};