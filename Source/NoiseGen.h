/*
  ==============================================================================

    NoiseGen.h
    Created: 9 Sep 2015 5:57:39pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef NOISEGEN_H_INCLUDED
#define NOISEGEN_H_INCLUDED

#include <JuceHeader.h>

class NoiseGen{
    
public:
    enum States{
        OFF, WHITE, PINK
    };
    
    NoiseGen();
    
    ~NoiseGen();
    
    float getNextSample();
    
    void setState(States);
    
    float randamplitude();
    
private:
    Random mRandom;
    States mState;
    float b0, b1, b2 = 0;
};



#endif  // NOISEGEN_H_INCLUDED
