/*
  ==============================================================================

    NoClick.cpp
    Created: 18 Jan 2016 3:38:14pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "NoClick.h"

void NoClick::setSampleRate (double sampleRate)
{
    mFadeIncrement = 1 / (mTotalFadeTime * sampleRate);
}

bool NoClick::fadingOut()
{
    return mFadeOut;
}

bool NoClick::fadingIn()
{
    return mFadeIn;
}

void NoClick::start()
{
    mFadeOut = true;
    mFadeIn = false;
}

float NoClick::getNextSample()
{
    if (mFadeOut)
    {
        mCurrentLevel -= mFadeIncrement;
        if (mCurrentLevel <= 0){
            mCurrentLevel = 0;
            mFadeOut = false;
            mFadeIn = true;
        }
    }
    
    if (mFadeIn)
    {
        mCurrentLevel += mFadeIncrement;
        if (mCurrentLevel >= 1){
            mCurrentLevel = 1;
            mFadeOut = false;
            mFadeIn = false;
        }
    }
    
    return mCurrentLevel;
}