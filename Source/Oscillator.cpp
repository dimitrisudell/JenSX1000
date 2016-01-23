/*
  ==============================================================================

    Oscillator.cpp
    Created: 6 Sep 2015 10:41:09am
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Oscillator.h"
#include "JuceHeader.h"

Oscillator::Oscillator() : mCurrentPhase(0), mCurrentWave(SINE)
{
    updatePhaseIncrement();
};

void Oscillator::updateWave(Wave w)
{
    mCurrentWave = w;
}

void Oscillator::updateFrequency (double freq)
{
    mCurrentFrequency = freq;
    jassert(mCurrentFrequency > 0);
    updatePhaseIncrement();
}

float Oscillator::getNextSample()
{
    jassert(mCurrentSampleRate > 0);
    jassert(mCurrentFrequency > 0);
    float value = naiveWaveformForMode(mCurrentWave);
    mCurrentPhase += mPhaseIncrement;
    while (mCurrentPhase >= twoPI) {
        mCurrentPhase -= twoPI;
    }
    return value;
}

float Oscillator::naiveWaveformForMode(Wave wave)
{
    float value;
    
    switch (wave) {
        case SINE:
            value = sin(mCurrentPhase);
            break;
        case SAW:
            value = (2.0 * mCurrentPhase / twoPI) - 1.0;
            break;
        case SQUARE:
            if (mCurrentPhase < PI) {
                value = 1.0;
            } else {
                value = -1.0;
            }
            break;
        case PULSE:
            calculteCurrentPulseWidth();
            if (mCurrentPhase < mPulseWidth) {
                value = 1.0;
            } else {
                value = -1.0;
            }
            break;
        case TRIANGLE:
            value = -1.0 + (2.0 * mCurrentPhase / twoPI);
            value = 2.0 * (fabs(value) - 0.5);
            break;
        default:
            break;
    }
    
    return value;
}

void Oscillator::updateSampleRate (double sampleRate)
{
    mCurrentSampleRate = sampleRate;
    updatePhaseIncrement();
}

void Oscillator::setPulseWidth (float percent)
{
    mMasterPulseWidthPercent = percent;
    calculteCurrentPulseWidth();
}

void Oscillator::calculteCurrentPulseWidth()
{
    mPulseWidthFaction = (mMasterPulseWidthPercent/100) + (mPwmLfoSample * mPwmAmount);
    if (mPulseWidthFaction < 0) { mPulseWidthFaction = 0;}
    mPulseWidth = twoPI * mPulseWidthFaction;
}

void Oscillator::setNextPWMSample (double sample)
{
    mPwmLfoSample = sample/4;
}

void Oscillator::setPWMamount (float amount)
{
    mPwmAmount = amount;
}

void Oscillator::updatePhaseIncrement()
{
    const double cyclesPerSample = mCurrentFrequency / mCurrentSampleRate;
    mPhaseIncrement = cyclesPerSample * twoPI;
}