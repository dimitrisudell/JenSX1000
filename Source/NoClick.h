/*
  ==============================================================================

    NoClick.h
    Created: 18 Jan 2016 3:38:14pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef NOCLICK_H_INCLUDED
#define NOCLICK_H_INCLUDED

class NoClick{
public:
    
    void setSampleRate(double);
    
    bool fadingOut();
    
    bool fadingIn();
    
    void start();
    
    float getNextSample();
    
private:
    float mFadeIncrement = 0; //samples
    double mTotalFadeTime = 0.001; //no. seconds
    bool mFadeOut = false;
    bool mFadeIn = false;
    float mCurrentLevel;
};



#endif  // NOCLICK_H_INCLUDED
