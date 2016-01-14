/*
  ==============================================================================

    VCF.cpp
    Created: 14 Jan 2016 8:38:13am
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "EqControl.h"

EqControl::EqControl() {
    filter.setFilterMode(Filter::FILTER_MODE_LOWPASS);
}

EqControl::~EqControl() {
}

void EqControl::setCutoff(float level){
    minCutoff = level;
    DBG("New Filter Cut Off: " + (String)masterCutoff);
}

void EqControl::setResonance(float level){
    resonance = level;
    filter.setResonance(level);
}

void EqControl::setLFOAmount(float level){
    LFOAmount = level;
}

void EqControl::setEnvLevel(float level){
    envLevel = level;
}

void EqControl::setAttackTime(double level){
    envelope.setAttackTime(level);
}

void EqControl::setDecayTime(double level){
    envelope.setDecayTime(level);
}

void EqControl::setSustainAmplitude(float level){
    envelope.setSustainAmplitude(level);
}

void EqControl::setReleaseTime(double level){
    envelope.setReleaseTime(level);
}

double EqControl::processNextSample(double sample){
    filter.setCutoff(((0.9999 - minCutoff) * envLevel * envelope.getNextSample() + minCutoff) * LFOSample);
    return filter.process(sample);
}

void EqControl::begin(){
    envelope.begin();
}

void EqControl::release(){
    envelope.release();
}

void EqControl::setNextLFOSample(double sample){
    LFOSample = (1 - (((sample + 1) / 2) * LFOAmount));
}
