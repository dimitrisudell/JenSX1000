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
    
    Glide();
    
    void setGlide();
    
    void setGlideTime(double);
    
    float getNextGlideIncrement();
    
protected:
    
    float targetNote;
    float currentNote;
    
private:
    
    bool firstGlide;
    bool glideEngaged;
    double glideTime; //glide time is messured in samples
    float glideIncrement; //percent of note distance to increase each sample
    float totalGlideDistance;
    float glideDistanceLeft;
    void updateGlideIncrement();
    
};


#endif  // GLIDE_H_INCLUDED
