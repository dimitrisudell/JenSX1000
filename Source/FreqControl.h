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

class FreqControl{
    
public:
    
    enum Octave{
        THIRTY_TWO = -24, SIXTEEN = -12, EIGHT = 0, FOUR = 12
    };
    
    FreqControl();
    
    ~FreqControl() {};
    
    /* frequency can be tuned in semitones e.g. -1.5 will decrease all output by 1.5 semitones */
    void setTuning(float);
    
    /* takes a midi note number */
    void setNote(int);
    
    double getNextFrequency();
    
    void setOctave(Octave);
    
    void setGlideValue(double);
    
    void setSampleRate(double);
    
    void setNextVibratoOscSample(float);
    
    void setVibratoValue(float);
    
    static double getMidiNoteInHertz (float, const double frequencyOfA = 440);
    
private:
    
    float mTuning;
    Octave mCurrentOctave;
    
    int mOriginalMidiNote = 0;
    float mTargetNote;
    float mCurrentNote;
    
    Glide mGlide;
    Vibrato mVibrato;
};

#endif  // FREQCONTROL_H_INCLUDED
