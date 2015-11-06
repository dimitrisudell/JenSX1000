/*
  ==============================================================================

    Oscillator.cpp
    Created: 6 Sep 2015 10:41:09am
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Oscillator.h"
#include <iostream>
#include "JuceHeader.h"

void Oscillator::updateFrequency(double freq){
    currentFrequency = freq;
    jassert(currentFrequency > 0);
    updatePhaseIncrement();
}

float Oscillator::getNextSample(){
    jassert(currentSampleRate > 0);
    jassert(currentFrequency > 0);
    double value = naiveWaveformForMode(currentWave);
    currentPhase += phaseIncrement;
    while (currentPhase >= twoPI) {
        currentPhase -= twoPI;
    }
    return value;
}

float Oscillator::naiveWaveformForMode(Wave wave) {
    float value;
    switch (wave) {
        case SINE:
            value = sin(currentPhase);
            break;
        case SAW:
            value = (2.0 * currentPhase / twoPI) - 1.0;
            break;
        case SQUARE:
            if (currentPhase < PI) {
                value = 1.0;
            } else {
                value = -1.0;
            }
            break;
        case PULSE:
            calculteCurrentPulseWidth();
            if (currentPhase < pulseWidth) {
                value = 1.0;
            } else {
                value = -1.0;
            }
            break;
        case TRIANGLE:
            value = -1.0 + (2.0 * currentPhase / twoPI);
            value = 2.0 * (fabs(value) - 0.5);
            break;
        default:
            break;
    }
    return value;
}

void Oscillator::updateSampleRate(double sampleRate){
    currentSampleRate = sampleRate;
    updatePhaseIncrement();
}

void Oscillator::updatePhaseIncrement(){
    const double cyclesPerSample = currentFrequency / currentSampleRate;
    phaseIncrement = cyclesPerSample * twoPI;
}