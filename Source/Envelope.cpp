/*
  ==============================================================================

    Envelope.cpp
    Created: 7 Jan 2016 3:57:37pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Envelope.h"
#include "../JuceLibraryCode/JuceHeader.h"

Envelope::Envelope(double maxAttackTime, double maxDecayTime, double maxReleaseTime, double sampleRate):
mSampleRate(sampleRate),
mCurrentAmplitude(minAmplitude),
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
    setSustainAmplitude(minAmplitude);
    setSampleRate(sampleRate);
}

void Envelope::begin() {
    updateState(ATTACK);
    mCurrentAmplitude = minAmplitude;
}

void Envelope::release() {
    setReleaseValue(mCurrentReleaseValue);
    updateState(RELEASE);
}

void Envelope::setAttackValue(double aValue){
    jassert(aValue >= 0);
    jassert(aValue <= 1);
    //will cause errors if it is 0
    
    mAttackIncrement = maxAmplitude/(mCurrentAttackValue * mMaxAttackTime * mSampleRate); //returns nan if divide by 0
}

void Envelope::setReleaseValue(double rValue) {
    jassert(rValue >= 0);
    jassert(rValue <= 1);
    jassert(mSustainAmplitude >= minAmplitude);
    //will cause errors if it is 0
    mCurrentReleaseValue = rValue * 0.999 + 0.001;
    mReleaseIncrement = mCurrentAmplitude/(mCurrentReleaseValue * mMaxReleaseTime * mSampleRate); //returns nan if divide by 0
}

void Envelope::setDecayValue(double dValue) {
    jassert(dValue >= 0);
    jassert(dValue <= 1);
    jassert(mSustainAmplitude >= minAmplitude);
    //will cause errors if it is 0
    mCurrentDecayValue = dValue * 0.999 + 0.001;
    mDecayIncrement = (maxAmplitude - mSustainAmplitude) / (mCurrentDecayValue * mMaxDecayTime * mSampleRate); //returns nan if divide by 0
}

void Envelope::setSustainAmplitude(double sAmplitude){
    jassert(sAmplitude >= minAmplitude);
    jassert(sAmplitude <= maxAmplitude);
    mSustainAmplitude = sAmplitude;
    setReleaseValue(mCurrentReleaseValue);
    setDecayValue(mCurrentDecayValue);
}

void Envelope::setSampleRate(double sampleRate){
    jassert(sampleRate > 0);
    mSampleRate = sampleRate;
    setAttackValue(mCurrentAttackValue);
    setDecayValue(mCurrentDecayValue);
    setReleaseValue(mCurrentReleaseValue);
}

float Envelope::getNextSample(){
    switch (state){
        case ATTACK:
            mCurrentAmplitude += mAttackIncrement;
            if (mCurrentAmplitude >= maxAmplitude) {mCurrentAmplitude = maxAmplitude; updateState(DECAY);}
            break;
        case DECAY:
            mCurrentAmplitude -= mDecayIncrement;
            if (mCurrentAmplitude <= mSustainAmplitude) {mCurrentAmplitude = mSustainAmplitude; updateState(SUSTAIN);}
            break;
        case SUSTAIN:
            break;
        case RELEASE:
            mCurrentAmplitude -= mReleaseIncrement;
            if (mCurrentAmplitude <= minAmplitude) {mCurrentAmplitude = minAmplitude; updateState(OFF);}
        case OFF:
            break;
    }
    jassert(mCurrentAmplitude >= minAmplitude);
    jassert(mCurrentAmplitude <= maxAmplitude);
    return mCurrentAmplitude;
    
};

void Envelope::updateState(State s){
    state = s;
}