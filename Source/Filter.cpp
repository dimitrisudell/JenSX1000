/*
  ==============================================================================

    Filter.cpp
    Created: 7 Jan 2016 5:49:45pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Filter.h"
#include "JuceHeader.h"

Filter::Filter() : cutoff(0.2), resonance(0.0), mode(FILTER_MODE_LOWPASS), buf0(0.0), buf1(0.0), buf2(0.0), buf3(0.0) {
    calculateFeedbackAmount();
};

float Filter::process(float inputValue) {
    buf0 += cutoff * (inputValue - buf0 + feedbackAmount * (buf0 - buf1));
    buf1 += cutoff * (buf0 - buf1);
    buf2 += cutoff * (buf1 - buf2);
    buf3 += cutoff * (buf2 - buf3);
    switch (mode) {
        case FILTER_MODE_LOWPASS:
            jassert(buf3 >= -1);
            jassert(buf3 <= 1);
            return buf3;
        case FILTER_MODE_HIGHPASS:
            return inputValue - buf0;
        case FILTER_MODE_BANDPASS:
            return buf0 - buf1;
        default:
            return 0.0;
    }
}

void Filter::setCutoff(double newCutoff) {
    //cut off cannot be 1 because it will cause a 0 in feedbackAmount calculation i.e. assert((newCutoff < 1) & (newCutoff >= 0))
    if (!(newCutoff < 1) || !(newCutoff >= 0)){
        DBG("Cut of value is not valid : " + (String)newCutoff);
        jassertfalse;
    }
    cutoff = newCutoff;
    calculateFeedbackAmount();
}

void Filter::setResonance(double newResonance) {
    resonance = newResonance;
    calculateFeedbackAmount();
}

void Filter::setFilterMode(FilterMode newMode) {
    mode = newMode;
}

void Filter::calculateFeedbackAmount() {
    feedbackAmount = resonance + resonance/(1.0 - cutoff);
}