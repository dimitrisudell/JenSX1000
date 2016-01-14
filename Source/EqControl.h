/*
  ==============================================================================

    VCF.h
    Created: 12 Sep 2015 12:50:18pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef EQCONTROL_H_INCLUDED
#define EQCONTROL_H_INCLUDED

#include "Envelope.h"
#include "Filter.h"
#include "JuceHeader.h"

class EqControl{
public:
    
    EqControl();
    
    ~EqControl();
    
    void setCutoff(float);
    
    void setResonance(float);
    
    void setLFOAmount(float);
    
    void setEnvLevel(float);
    
    void setAttackTime(double);
    
    void setDecayTime(double);
    
    void setSustainAmplitude(float);
    
    void setReleaseTime(double);
    
    double processNextSample(double);
    
    void begin();
    
    void release();
    
    void setNextLFOSample(double);
    
private:
    Envelope envelope;
    Filter filter;
    float masterCutoff;
    float minCutoff;
    float envCuttoff;
    float afterEnvCutoff;
    float resonance;
    float lfoAmount;
    float envLevel;
    double LFOSample;
    float LFOAmount;
};



#endif  // EQCONTROL_H_INCLUDED
