/*
  ==============================================================================

    VCF.h
    Created: 12 Sep 2015 12:50:18pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef VCF_H_INCLUDED
#define VCF_H_INCLUDED

#include "Envelope.h"
#include "Filter.h"
#include "JuceHeader.h"

class VCF{
public:
    VCF() {filter.setFilterMode(Filter::FILTER_MODE_LOWPASS);};
    ~VCF() {};
    
    void setCutoff(float level){
        minCutoff = level;
        //setEnvLevel(envLevel);
        DBG("New Filter Cut Off: " + (String)masterCutoff);
    }
    
    void setResonance(float level){
        resonance = level;
        filter.setResonance(level);
    }
    
    void setLFOAmount(float level){
        LFOAmount = level;
    }
    
    void setEnvLevel(float level){
        envLevel = level;
        //envCuttoff = masterCutoff * level;
        //afterEnvCutoff = masterCutoff - envCuttoff;
    }
    
    void setAttackTime(double level){
        envelope.setAttackTime(level);
    }
    
    void setDecayTime(double level){
        envelope.setDecayTime(level);
    }
    
    void setSustainAmplitude(float level){
        envelope.setSustainAmplitude(level);
    }
    
    void setReleaseTime(double level){
        envelope.setReleaseTime(level);
    }
    
    double processNextSample(double sample){
        //filter.setCutoff(((envelope.getNextSample() * afterEnvCutoff) + envCuttoff) * LFOSample);
        filter.setCutoff(((0.9999 - minCutoff) * envLevel * envelope.getNextSample() + minCutoff) * LFOSample);
        return filter.process(sample);
    }
    
    void begin(){envelope.begin();};
    
    void release(){envelope.release();};
    
    void setNextLFOSample(double sample){
        //LFOSample = (((sample + 1) / 2) * LFOAmount)   + 1 - LFOAmount;
        LFOSample = (1 - (((sample + 1) / 2) * LFOAmount));
    }
    
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



#endif  // VCF_H_INCLUDED
