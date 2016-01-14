/*
  ==============================================================================

    polyBlepOscillator.cpp
    Created: 7 Jan 2016 4:50:12pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "PolyBlepOscillator.h"
#include "JuceHeader.h"


PolyBlepOscillator::PolyBlepOscillator() : lastOutput(0.0) {
    currentWave = SINE;
    currentPhase = 0; updatePhaseIncrement(); updateFrequency(440);};

float PolyBlepOscillator::getNextSample(){
    jassert(currentSampleRate > 0);
    jassert(currentFrequency > 0);
    
    double t = currentPhase / twoPI;
    
    float value;
    switch (currentWave){
        case SINE:
            value = naiveWaveformForMode(SINE);
            break;
        case SAW:
            value = naiveWaveformForMode(SAW);
            value -= poly_blep(t);
            break;
        case PULSE:
            value = naiveWaveformForMode(PULSE);
            value += poly_blep(t);
            value -= poly_blep(fmod(t + (1 - pulseWidthFaction), 1.0));
            break;
        default:
            value = naiveWaveformForMode(SQUARE);
            value += poly_blep(t);
            value -= poly_blep(fmod(t + 0.5, 1.0));
            if (currentWave == TRIANGLE) {
                // Leaky integrator: y[n] = A * x[n] + (1 - A) * y[n-1]
                value = phaseIncrement * value + (1 - phaseIncrement) * lastOutput;
                lastOutput = value;
            }
    }
    
    
    currentPhase += phaseIncrement;
    while (currentPhase >= twoPI) {
        currentPhase -= twoPI;
    }
    return value;
}

double PolyBlepOscillator::poly_blep(double t){
    double dt = phaseIncrement / twoPI;
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
