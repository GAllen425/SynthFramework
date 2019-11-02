/*
  ==============================================================================

    SynthSound.h
    Created: 25 Sep 2019 10:45:17pm
    Author:  Gareth

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
	bool appliesToNote (int /*midiNoteNumber*/) override
	{
		return true;
	}

	bool appliesToChannel (int /*midiChannel*/) override
	{
		return true;
	}
};