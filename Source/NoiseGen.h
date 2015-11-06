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
    
    NoiseGen(): state(PINK) {};
    ~NoiseGen() {};
    
    float getNextSample(){
        switch (state){
        case OFF:
            return 0;
        case WHITE:
            return randamplitude();
        case PINK:
                float white = randamplitude();
                b0 = 0.99765 * b0 + white * 0.0990460;
                b1 = 0.96300 * b1 + white * 0.2965164;
                b2 = 0.57000 * b2 + white * 1.0526913;
                float tmp = b0 + b1 + b2 + white * 0.1848;
                //if (tmp > 1) {tmp = 1;};
                //if (tmp > -1) {tmp = -1;};
            return tmp;
        }
    };
    
    void setState(States s) {state = s;};
    
    float randamplitude(){
        float randFloat = random.nextFloat();
        return (randFloat * 2 - 1);
    }
    
private:
    Random random;
    States state;
    float b0, b1, b2 = 0;
};



#endif  // NOISEGEN_H_INCLUDED
