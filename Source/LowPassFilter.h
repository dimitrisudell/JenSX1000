/*
  ==============================================================================

    Filter.h
    Created: 5 Sep 2015 8:07:43pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef LOWPASSFILTER_H_INCLUDED
#define LOWPASSFILTER_H_INCLUDED

class LowPassFilter {
    
public:

    LowPassFilter();
    
    float process(float);
    
    void setCutoff(double);
    
    void setResonance(double);

private:
    
    double mCutoff;
    double mResonance;
    float mFeedbackAmount;
    
    float buf0, buf1, buf2, buf3 = 0.0f;
    
    void calculateFeedbackAmount();
};

#endif  // FILTER_H_INCLUDED
