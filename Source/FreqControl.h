/*
  ==============================================================================

    OscMain.h
    Created: 6 Sep 2015 4:28:15pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef FREQCONTROL_H_INCLUDED
#define FREQCONTROL_H_INCLUDED

#include <math.h>
#include <iostream>
#include <JuceHeader.h>
#include "Glide.h"
#include "Vibrato.h"

class FreqControl: public Glide, public Vibrato{
    
public:
    
    enum Octave{
        THIRTY_TWO = -28, SIXTEEN = -14, EIGHT = 0, FOUR = 14
    };
    
    FreqControl();
    
    ~FreqControl() {};
    
    /* frequency can be tuned in semitones e.g. -1.5 will decrease all output by 1.5 semitones */
    void setTuning(float);
    
    /* takes a midi note number */
    void setNote(int);
    
    double getNextFrequency();
    
    void setOctave(Octave);
    
private:
    
    float tuning;
    Octave currentOctave;
    double getMidiNoteInHertz (float, const double frequencyOfA = 440);

};

#endif  // FREQCONTROL_H_INCLUDED
