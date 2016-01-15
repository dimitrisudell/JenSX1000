/*
  ==============================================================================

    Filter.h
    Created: 5 Sep 2015 8:07:43pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

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
    
    double cutoff;
    double resonance;
    FilterMode mode;
    float feedbackAmount;
    
    float buf0;
    float buf1;
    float buf2;
    float buf3;
    
    inline void calculateFeedbackAmount(){feedbackAmount = resonance + resonance/(1.0 - cutoff);};
};

#endif  // FILTER_H_INCLUDED
