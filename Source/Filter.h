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
    Filter() :
    cutoff(0.2),
    resonance(0.0),
    mode(FILTER_MODE_LOWPASS),
    buf0(0.0),
    buf1(0.0),
    buf2(0.0),
    buf3(0.0)
    {
        calculateFeedbackAmount();
    };
    float process(float inputValue){
        buf0 += cutoff * (inputValue - buf0 + feedbackAmount * (buf0 - buf1));
        buf1 += cutoff * (buf0 - buf1);
        buf2 += cutoff * (buf1 - buf2);
        buf3 += cutoff * (buf2 - buf3);
        switch (mode) {
            case FILTER_MODE_LOWPASS:
                return buf3;
            case FILTER_MODE_HIGHPASS:
                return inputValue - buf0;
            case FILTER_MODE_BANDPASS:
                return buf0 - buf1;
            default:
                return 0.0;
        }
    };
    inline void setCutoff(double newCutoff) {
        //cut off cannot be 1 because it will cause a 0 in feedbackAmount calculation i.e. assert((newCutoff < 1) & (newCutoff >= 0))
        if (!(newCutoff < 1) || !(newCutoff >= 0)){
            DBG("Cut of value is not valid : " + (String)newCutoff);
            jassertfalse;
        }
        cutoff = newCutoff; calculateFeedbackAmount();
    }
    inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount();};
    inline void setFilterMode(FilterMode newMode) { mode = newMode; }
private:
    double cutoff;
    double resonance;
    FilterMode mode;
    float feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    float buf0;
    float buf1;
    float buf2;
    float buf3;
};

#endif  // FILTER_H_INCLUDED
