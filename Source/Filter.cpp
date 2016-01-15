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
    jassert(newCutoff >= 0);
    jassert(newCutoff <= 1);
    //cut off cannot be 1 because it will cause a 0 in feedbackAmount calculation
    cutoff = newCutoff * 0.999;
    calculateFeedbackAmount();
}

void Filter::setResonance(double newResonance) {
    jassert(newResonance >= 0);
    jassert(newResonance <= 1);
    resonance = newResonance;
    calculateFeedbackAmount();
}

void Filter::setFilterMode(FilterMode newMode) {
    mode = newMode;
}