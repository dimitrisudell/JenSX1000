/*
  ==============================================================================

    polyBLEPOscillator.h
    Created: 9 Sep 2015 7:06:02pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef POLYBLEPOSCILLATOR_H_INCLUDED
#define POLYBLEPOSCILLATOR_H_INCLUDED

#include "Oscillator.h"

class PolyBlepOscillator: public Oscillator {
    
public:
    
    PolyBlepOscillator();
    
    ~PolyBlepOscillator() {};
    
    float getNextSample();
    
private:
    
    double polyBlep(double);
    
    double mLastOutput;
};

#endif  // POLYBLEPOSCILLATOR_H_INCLUDED
