/*
  ==============================================================================

    Vibrato.h
    Created: 7 Jan 2016 7:06:37pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef VIBRATO_H_INCLUDED
#define VIBRATO_H_INCLUDED


class Vibrato{
    
public:
    
    float getNextVibratoIncrement();
    
    void setNextVibratoOscSample(float);
    
    /* set max number of semitones vibrato will ocilate by */
    void setVibratoAmount(float);
    
private:
    
    float vibratoAmount;
    float nextVibOscSample;
    
};


#endif  // VIBRATO_H_INCLUDED
