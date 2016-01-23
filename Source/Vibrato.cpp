/*
  ==============================================================================

    Vibrato.cpp
    Created: 7 Jan 2016 7:06:37pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Vibrato.h"

float Vibrato::getNextVibratoIncrement()
{
    float vibratoIncrement = mNextVibOscSample * mVibratoAmount;
    return vibratoIncrement;
}

void Vibrato::setNextVibratoOscSample (float oscSample)
{
    mNextVibOscSample = oscSample;
}

void Vibrato::setVibratoAmount (float semitones)
{
    mVibratoAmount = semitones;
}