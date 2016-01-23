/*
  ==============================================================================

    Filter.cpp
    Created: 7 Jan 2016 5:49:45pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "LowPassFilter.h"
#include "JuceHeader.h"

LowPassFilter::LowPassFilter() : mCutoff(0.2), mResonance(0.0)
{
    calculateFeedbackAmount();
}

float LowPassFilter::process (float inputValue)
{
    buf0 += mCutoff * (inputValue - buf0 + mFeedbackAmount * (buf0 - buf1));
    buf1 += mCutoff * (buf0 - buf1);
    buf2 += mCutoff * (buf1 - buf2);
    buf3 += mCutoff * (buf2 - buf3);
    return buf3;
}

void LowPassFilter::setCutoff (double newCutoff)
{
    jassert(newCutoff >= 0);
    jassert(newCutoff <= 1);
    //cut off cannot be 1 because it will cause a 0 in feedbackAmount calculation
    mCutoff = newCutoff * 0.999;
    calculateFeedbackAmount();
}

void LowPassFilter::setResonance (double newResonance)
{
    jassert(newResonance >= 0);
    jassert(newResonance <= 1);
    mResonance = newResonance;
    calculateFeedbackAmount();
}

void LowPassFilter::calculateFeedbackAmount()
{
    mFeedbackAmount = mResonance + mResonance/(1.0 - mCutoff);
}