/*
  ==============================================================================

    polyBlepOscillator.cpp
    Created: 7 Jan 2016 4:50:12pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "PolyBlepOscillator.h"
#include "JuceHeader.h"


PolyBlepOscillator::PolyBlepOscillator() : mLastOutput(0.0)
{
    mCurrentWave = SINE;
    mCurrentPhase = 0;
    updatePhaseIncrement();
    updateFrequency(440);
}

float PolyBlepOscillator::getNextSample()
{
    jassert(mCurrentSampleRate > 0);
    jassert(mCurrentFrequency > 0);
    
    double t = mCurrentPhase / twoPI;
    
    float value;
    switch (mCurrentWave){
        case SINE:
            value = naiveWaveformForMode(SINE);
            break;
        case SAW:
            value = naiveWaveformForMode(SAW);
            value -= polyBlep(t);
            break;
        case PULSE:
            value = naiveWaveformForMode(PULSE);
            value += polyBlep(t);
            value -= polyBlep(fmod(t + (1 - mPulseWidthFaction), 1.0));
            break;
        default:
            value = naiveWaveformForMode(SQUARE);
            value += polyBlep(t);
            value -= polyBlep(fmod(t + 0.5, 1.0));
            if (mCurrentWave == TRIANGLE) {
                // Leaky integrator: y[n] = A * x[n] + (1 - A) * y[n-1]
                value = mPhaseIncrement * value + (1 - mPhaseIncrement) * mLastOutput;
                mLastOutput = value;
            }
    }
    
    mCurrentPhase += mPhaseIncrement;
    
    while (mCurrentPhase >= twoPI) {
        mCurrentPhase -= twoPI;
    }
    
    return value;
}

double PolyBlepOscillator::polyBlep (double t)
{
    double dt = mPhaseIncrement / twoPI;
    // 0 <= t < 1
    if (t < dt) {
        t /= dt;
        return t+t - t*t - 1.0;
    }
    // -1 < t < 0
    else if (t > 1.0 - dt) {
        t = (t - 1.0) / dt;
        return t*t + t+t + 1.0;
    }
    // 0 otherwise
    else {return 0.0;};
}
