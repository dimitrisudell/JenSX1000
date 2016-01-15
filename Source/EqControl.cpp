/*
  ==============================================================================

    VCF.cpp
    Created: 14 Jan 2016 8:38:13am
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "EqControl.h"
#include "JenConstants.h"

EqControl::EqControl(): envelope(JenConstants::FilterEnvMaxAttackTime, JenConstants::FilterEnvMaxDecayTime, JenConstants::FilterEnvMaxReleaseTime) {
    filter.setFilterMode(Filter::FILTER_MODE_LOWPASS);
}

EqControl::~EqControl() {
}

void EqControl::setCutoff(float level){
    jassert(level >= 0);
    jassert(level <= 1);
    
    minCutoff = (level * (JenConstants::FilterCutOffMax - JenConstants::FilterCutOffMin)) + JenConstants::FilterCutOffMin;
    DBG("New Filter Cut Off: " + (String)masterCutoff);
}

void EqControl::setResonance(float level){
    jassert(level >= 0);
    jassert(level <= 1);
    
    resonance = level;
    filter.setResonance(level);
}

void EqControl::setLFOAmount(float level){
    LFOAmount = level;
}

void EqControl::setEnvLevel(float level){
    jassert(level >= 0);
    jassert(level <= 1);
    envLevel = level;
}

void EqControl::setAttackValue(double level){
    envelope.setAttackValue(level);
}

void EqControl::setDecayValue(double level){
    envelope.setDecayValue(level);
}

void EqControl::setSustainAmplitude(float level){
    envelope.setSustainAmplitude(level);
}

void EqControl::setReleaseValue(double level){
    envelope.setReleaseValue(level);
}

void EqControl::setSampleRate(double sampleRate){
    envelope.setSampleRate(sampleRate);
}

double EqControl::processNextSample(double sample){
    float nextEnvSample = envelope.getNextSample();
    filter.setCutoff(((JenConstants::FilterCutOffMax - minCutoff) * envLevel * nextEnvSample + minCutoff) * LFOSample);
    float processedSample = filter.process(sample);
    return processedSample;
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
