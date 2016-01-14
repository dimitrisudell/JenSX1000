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
    
    //Set Envelope times in seconds
    //sampleRate - number samples per second
    Envelope(double maxAttackTime, double maxDecayTime, double maxReleaseTime, double sampleRate = 44000.00);
    
    void begin();
    
    void release();
    
    //Double between 0 and 1
    void setAttackValue(double);
    
    //Double between 0 and 1
    void setReleaseValue(double);
    
    //Double between 0 and 1
    void setDecayValue(double);
    
    //Double between 0 and 1
    void setSustainAmplitude(double);
    
    //Sample rate must be over 0
    void setSampleRate(double);
    
    float getNextSample();
    
private:
    
    State state;
    void updateState(State);
    
    const float maxAmplitude = 1;
    const float minAmplitude = 0;
    
    double mSampleRate;
    
    float mCurrentAmplitude;
    float mSustainAmplitude;
    
    double mMaxAttackTime;
    double mCurrentAttackValue;
    float mAttackIncrement;
    
    double mMaxDecayTime;
    double mCurrentDecayValue;
    float mDecayIncrement;
    
    double mMaxReleaseTime;
    double mCurrentReleaseValue;
    float mReleaseIncrement;
    
};

#endif  // ENVELOPE_H_INCLUDED
