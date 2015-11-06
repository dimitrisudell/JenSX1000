/*
  ==============================================================================

    Oscillator.h
    Created: 5 Sep 2015 5:30:59pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include <math.h>
#include <iostream>

class Oscillator{
public:
    enum Wave{
        SAW, SQUARE, PULSE, SINE, TRIANGLE
    };
    
    Oscillator(): currentPhase(0), currentWave(SINE) { updatePhaseIncrement();};
    virtual ~Oscillator() {};
    
    void updateWave(Wave w) { currentWave = w; };
    
    void updateFrequency(double freq);
    
    virtual float getNextSample();
    
    void updateSampleRate(double sampleRate);
    
    void setPulseWidth(float percent){
        masterPulseWidthPercent = percent;
        calculteCurrentPulseWidth();
    }
    
    void calculteCurrentPulseWidth(){
        pulseWidthFaction = (masterPulseWidthPercent/100) + (PWMLFOSample * PWMamount);
        if (pulseWidthFaction < 0) { pulseWidthFaction = 0;}
        pulseWidth = twoPI * pulseWidthFaction;
    }
    
    void setNextPWMSample(double sample){
        PWMLFOSample = sample/4;
    }
    
    void setPWMamount(float amount){
        PWMamount = amount;
    }
    
    
protected:
    virtual float naiveWaveformForMode(Wave wave);
    
    double currentSampleRate, currentPhase, phaseIncrement;
    Wave currentWave;
    double currentFrequency;
    
    virtual void updatePhaseIncrement();
    
    const double PI = 2*acos(0.0);
    const double twoPI = 2 * PI;
    
    float masterPulseWidthPercent;
    double pulseWidthFaction;
    double pulseWidth;
    double PWMLFOSample;
    float PWMamount;
    
    
};

#endif  // OSCILLATOR_H_INCLUDED
