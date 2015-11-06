/*
  ==============================================================================

    JenOscillator.h
    Created: 17 Sep 2015 8:37:39pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef JENOSCILLATOR_H_INCLUDED
#define JENOSCILLATOR_H_INCLUDED
#include "Oscillator.h"


class JenOscillator : public Oscillator{
public:
    
    float naiveWaveformForMode(Wave wave) override{
        float value;
        switch (wave) {
            case SINE:
                value = sin(currentPhase);
                break;
            case SAW:
                value = (2.0 * currentPhase / twoPI) - 1.0;
                break;
            case SQUARE:
                if (currentPhase < PI) {
                    if (square_up) {
                        square_value = 1.0;
                        square_up = false;
                    }
                    square_value -= square_slope_increment;
                    value = square_value;
                }
                else {
                    if (!square_up) {
                        square_value = -1.0;
                        square_up = true;
                    }
                    square_value += square_slope_increment;
                    value = square_value;
                }
                break;
            case PULSE:
                if (currentPhase < pulseWidth) {
                    value = 1.0;
                } else {
                    value = -1.0;
                }
                break;
            case TRIANGLE:
                value = -1.0 + (2.0 * currentPhase / twoPI);
                value = 2.0 * (fabs(value) - 0.5);
                break;
            default:
                break;
        }
        return value;
    }
    
    void updatePhaseIncrement() override{
        const double cyclesPerSample = currentFrequency / currentSampleRate;
        phaseIncrement = cyclesPerSample * twoPI;
        
        square_slope_increment = 0.5/(currentSampleRate/(currentFrequency * 2));
    }
    
private:
    float square_slope_increment;
    float square_value;
    bool square_up = false;
    
};



#endif  // JENOSCILLATOR_H_INCLUDED
