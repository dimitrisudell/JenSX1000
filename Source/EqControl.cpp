/*
  ==============================================================================

    VCF.cpp
    Created: 14 Jan 2016 8:38:13am
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "EqControl.h"
#include "JenConstants.h"

EqControl::EqControl() : mEnvelope(JenConstants::FilterEnvMaxAttackTime, JenConstants::FilterEnvMaxDecayTime, JenConstants::FilterEnvMaxReleaseTime) {};

EqControl::~EqControl() {};

void EqControl::setCutoff (float level)
{
    jassert(level >= 0);
    jassert(level <= 1);
    
    mMinCutoff = (level * (JenConstants::FilterCutOffMax - JenConstants::FilterCutOffMin)) + JenConstants::FilterCutOffMin;
    DBG("New Filter Cut Off: " + (String)mMinCutoff);
}

void EqControl::setResonance (float level)
{
    jassert(level >= 0);
    jassert(level <= 1);
    
    mResonance = level;
    mFilter.setResonance(level);
}

void EqControl::setLFOAmount (float level)
{
    mLfoAmount = level;
}

void EqControl::setEnvLevel (float level)
{
    jassert(level >= 0);
    jassert(level <= 1);
    mEnvLevel = level;
}

void EqControl::setAttackValue (double level)
{
    mEnvelope.setAttackValue(level);
}

void EqControl::setDecayValue (double level)
{
    mEnvelope.setDecayValue(level);
}

void EqControl::setSustainAmplitude (float level)
{
    mEnvelope.setSustainAmplitude(level);
}

void EqControl::setReleaseValue (double level)
{
    mEnvelope.setReleaseValue(level);
}

void EqControl::setSampleRate (double sampleRate)
{
    mEnvelope.setSampleRate(sampleRate);
}

double EqControl::processNextSample (double sample)
{
    float nextEnvSample = mEnvelope.getNextSample();
    mFilter.setCutoff(((JenConstants::FilterCutOffMax - mMinCutoff) * mEnvLevel * nextEnvSample + mMinCutoff) * mLfoSample);
    float processedSample = mFilter.process(sample);
    return processedSample;
}

void EqControl::begin()
{
    mEnvelope.begin();
}

void EqControl::release()
{
    mEnvelope.release();
}

void EqControl::setNextLFOSample (double sample)
{
    mLfoSample = (1 - (((sample + 1) / 2) * mLfoAmount));
}
