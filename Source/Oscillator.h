/*
  ==============================================================================

    Oscillator.h
    Created: 5 Sep 2015 5:30:59pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED



class Oscillator{
public:
    enum Wave{
        SAW, SQUARE, PULSE, SINE, TRIANGLE
    };
    
    Oscillator();
    
    virtual ~Oscillator() {};
    
    void updateWave(Wave);
    
    void updateFrequency(double freq);
    
    virtual float getNextSample();
    
    void updateSampleRate(double sampleRate);
    
    void setPulseWidth(float);
    
    void calculteCurrentPulseWidth();
    
    void setNextPWMSample(double);
    
    void setPWMamount(float);
    
protected:
    
    virtual float naiveWaveformForMode(Wave);
    
    double currentFrequency, currentSampleRate, currentPhase, phaseIncrement;
    Wave currentWave;
    
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
