/*
  ==============================================================================

    Vibrato.cpp
    Created: 7 Jan 2016 7:06:37pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Vibrato.h"

float Vibrato::getNextVibratoIncrement(){
    float vibratoIncrement = nextVibOscSample * vibratoAmount;
    return vibratoIncrement;
}

void Vibrato::setNextVibratoOscSample(float oscSample){
    nextVibOscSample = oscSample;
}

void Vibrato::setVibratoAmount(float semitones){
    vibratoAmount = semitones;
}