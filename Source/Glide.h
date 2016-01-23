/*
  ==============================================================================

    Glide.h
    Created: 7 Jan 2016 6:47:47pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef GLIDE_H_INCLUDED
#define GLIDE_H_INCLUDED


class Glide{
    
public:
    
    Glide (double maxGlideTime, double sampleRate = 44000.00);
    
    void setGlide (double currentNote, double targetNote);
    
    void setGlideValue(double);
    
    void setSampleRate (double sampleRate);
    
    float getNextGlideIncrement();

private:
    
    bool mFirstGlide;
    double mMaxGlideTime;
    double mGlideValue;
    float mGlideIncrement; //percent of note distance to increase each sample
    float mTotalGlideDistance;
    float mGlideDistanceLeft;
    double mSampleRate;
    
    void updateGlideIncrement();
    
};


#endif  // GLIDE_H_INCLUDED
