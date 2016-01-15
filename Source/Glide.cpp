/*
  ==============================================================================

    Glide.cpp
    Created: 7 Jan 2016 6:47:47pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Glide.h"
#include "JuceHeader.h"

Glide::Glide(double maxGlideTime, double sampleRate): mFirstGlide(true), mMaxGlideTime(maxGlideTime), mGlideValue(0.5), mTotalGlideDistance(0.0), mGlideDistanceLeft(0.0)
{
    setSampleRate(sampleRate);
}

void Glide::setGlide(double currentNote, double targetNote) {
    if (mFirstGlide == false) {mTotalGlideDistance = targetNote - currentNote;};
    mGlideDistanceLeft = mTotalGlideDistance;
    updateGlideIncrement();
    mFirstGlide = false;
}

void Glide::setGlideValue(double value) {
    jassert(value >= 0);
    jassert(value <= 1);
    //will cause errors if it is 0
    mGlideValue = value * 0.999 + 0.001;
    updateGlideIncrement();
}

void Glide::setSampleRate(double sampleRate){
    jassert(sampleRate > 0);
    mSampleRate = sampleRate;
    updateGlideIncrement();
}

float Glide::getNextGlideIncrement() {
    if (mTotalGlideDistance < 0){
        if (mGlideDistanceLeft < 0) {mGlideDistanceLeft -= mGlideIncrement;};
        return mGlideDistanceLeft;
    }
    else {
        if (mGlideDistanceLeft > 0) {mGlideDistanceLeft -= mGlideIncrement;};
        return mGlideDistanceLeft;
    };
    
}

void Glide::updateGlideIncrement() {
    mGlideIncrement = mTotalGlideDistance / (mGlideValue * mMaxGlideTime * mSampleRate);
};
