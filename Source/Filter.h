/*
  ==============================================================================

    Filter.h
    Created: 5 Sep 2015 8:07:43pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Filter {
    
public:
    
    enum FilterMode {
        FILTER_MODE_LOWPASS = 0,
        FILTER_MODE_HIGHPASS,
        FILTER_MODE_BANDPASS,
        kNumFilterModes
    };
    
    Filter();
    
    float process(float);
    
    void setCutoff(double);
    
    void setResonance(double);
    
    void setFilterMode(FilterMode);

private:
    
    inline void calculateFeedbackAmount();
    
    double cutoff;
    double resonance;
    FilterMode mode;
    float feedbackAmount;
    
    float buf0;
    float buf1;
    float buf2;
    float buf3;
};

#endif  // FILTER_H_INCLUDED
