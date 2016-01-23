/*
  ==============================================================================

    Envelope.cpp
    Created: 7 Jan 2016 3:57:37pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Envelope.h"
#include "../JuceLibraryCode/JuceHeader.h"

Envelope::Envelope (double maxAttackTime, double maxDecayTime, double maxReleaseTime, double sampleRate) :
mSampleRate(sampleRate),
mCurrentAmplitude(mMinAmplitude),
mMaxAttackTime(maxAttackTime),
mCurrentAttackValue(0.5),
mMaxDecayTime(maxDecayTime),
mCurrentDecayValue(0.5),
mMaxReleaseTime(maxReleaseTime),
mCurrentReleaseValue(0.5)
{
    jassert(maxAttackTime > 0);
    jassert(maxDecayTime > 0);
    jassert(maxReleaseTime > 0);
    jassert(sampleRate > 0);
    
    updateState(OFF);
    setSustainAmplitude(mMinAmplitude);
    setSampleRate(sampleRate);
}

void Envelope::begin()
{
    updateState(ATTACK);
    mCurrentAmplitude = mMinAmplitude;
}

void Envelope::release()
{
    DBG("release() called");
    setReleaseValue(mCurrentReleaseValue);
    updateState(RELEASE);
}

void Envelope::setAttackValue (double aValue)
{
    jassert(aValue >= 0);
    jassert(aValue <= 1);
    mCurrentAttackValue = aValue;
    calculateAttackIncrement();
}

void Envelope::calculateAttackIncrement()
{
    jassert(mCurrentAttackValue >= 0);
    jassert(mCurrentAttackValue <= 1);
    mAttackIncrement = mMaxAmplitude/((mCurrentAttackValue * 0.99999999 + 0.00000001) * mMaxAttackTime * mSampleRate); //returns nan if divide by 0
}

void Envelope::setReleaseValue (double rValue)
{
    jassert(rValue >= 0);
    jassert(rValue <= 1);
    jassert(mSustainAmplitude >= mMinAmplitude);
    mCurrentReleaseValue = rValue;
    calculateReleaseIncrement();
}

void Envelope::calculateReleaseIncrement()
{
    DBG("calculateReleaseIncrement called");
    jassert(mCurrentReleaseValue >= 0);
    jassert(mCurrentReleaseValue <= 1);
    jassert(mCurrentAmplitude >= 0);
    jassert(mCurrentAmplitude <= 1);
    mReleaseIncrement = mCurrentAmplitude/((mCurrentReleaseValue * 0.99999999 + 0.00000001) * mMaxReleaseTime * mSampleRate); //returns nan if divide by 0
}

void Envelope::setDecayValue (double dValue)
{
    jassert(dValue >= 0);
    jassert(dValue <= 1);
    jassert(mSustainAmplitude >= mMinAmplitude);
    mCurrentDecayValue = dValue;
    calculateDecayIncrement();
}

void Envelope::calculateDecayIncrement()
{
    jassert(mCurrentDecayValue >= 0);
    jassert(mCurrentDecayValue <= 1);
    mDecayIncrement = (mMaxAmplitude - mSustainAmplitude) / ((mCurrentDecayValue * 0.99999999 + 0.00000001) * mMaxDecayTime * mSampleRate); //returns nan if divide by 0
}

void Envelope::setSustainAmplitude (double sAmplitude)
{
    jassert(sAmplitude >= mMinAmplitude);
    jassert(sAmplitude <= mMaxAmplitude);
    mSustainAmplitude = sAmplitude;
    setReleaseValue(mCurrentReleaseValue);
    setDecayValue(mCurrentDecayValue);
}

void Envelope::setSampleRate (double sampleRate)
{
    jassert(sampleRate > 0);
    mSampleRate = sampleRate;
    setAttackValue(mCurrentAttackValue);
    setDecayValue(mCurrentDecayValue);
    setReleaseValue(mCurrentReleaseValue);
}

float Envelope::getNextSample()
{
    switch (mState){
        case ATTACK:
            mCurrentAmplitude += mAttackIncrement;
            if (mCurrentAmplitude >= mMaxAmplitude) {mCurrentAmplitude = mMaxAmplitude; updateState(DECAY);}
            break;
        case DECAY:
            mCurrentAmplitude -= mDecayIncrement;
            if (mCurrentAmplitude <= mSustainAmplitude) {mCurrentAmplitude = mSustainAmplitude; updateState(SUSTAIN);}
            break;
        case SUSTAIN:
            break;
        case RELEASE:
            mCurrentAmplitude -= mReleaseIncrement;
            if (mCurrentAmplitude <= mMinAmplitude) {mCurrentAmplitude = mMinAmplitude; updateState(OFF);}
        case OFF:
            break;
    }
    jassert(mCurrentAmplitude >= mMinAmplitude);
    jassert(mCurrentAmplitude <= mMaxAmplitude);
    return mCurrentAmplitude;
    
};

void Envelope::updateState(State s)
{
    mState = s;
}