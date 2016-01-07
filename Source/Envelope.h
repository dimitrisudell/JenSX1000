/*
  ==============================================================================

    Envelope.h
    Created: 5 Sep 2015 8:07:37pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDED

class Envelope{
    
public:
    
    enum State{
        ATTACK, DECAY, SUSTAIN, RELEASE, OFF
    };
    
    Envelope();
    
    void begin();
    
    void release();
    
    void setAttackTime(double);
    
    void setReleaseTime(double);
    
    void setDecayTime(double);
    
    void setSustainAmplitude(double);
    
    float getNextSample();
    
private:
    
    State state;
    void updateState(State);
    
    const float maxAmplitude = 1;
    const float minAmplitude = 0;
    float currentAmplitude;
    
    double attackTime;
    float attackIncrement;
    
    double decayTime;
    float decayIncrement;
    
    float sustainAmplitude;
    
    double releaseTime;
    float releaseIncrement;
    
};

#endif  // ENVELOPE_H_INCLUDED
