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
#include "LowPassFilter.h"
#include "JuceHeader.h"

class EqControl{
public:
    
    EqControl();
    
    ~EqControl();
    
    void setCutoff(float);
    
    void setResonance(float);
    
    void setLFOAmount(float);
    
    void setEnvLevel(float);
    
    void setAttackValue(double);
    
    void setDecayValue(double);
    
    void setSustainAmplitude(float);
    
    void setReleaseValue(double);
    
    void setSampleRate(double);
    
    double processNextSample(double);
    
    void begin();
    
    void release();
    
    void setNextLFOSample(double);
    
private:
    Envelope mEnvelope;
    LowPassFilter mFilter;
    float mMinCutoff;
    float mResonance;
    float mEnvLevel;
    double mLfoSample;
    float mLfoAmount;
};



#endif  // EQCONTROL_H_INCLUDED
