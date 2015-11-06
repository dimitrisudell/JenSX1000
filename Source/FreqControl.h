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

class Vibrato{
public:
    float getNextVibratoIncrement(){
        float vibratoIncrement = nextVibOscSample * vibratoAmount;
        return vibratoIncrement;
    }
    
    void setNextVibratoOscSample(float oscSample){
        nextVibOscSample = oscSample;
    }
    
    /* set max number of semitones vibrato will ocilate by */
    void setVibratoAmount(float semitones){
        vibratoAmount = semitones;
    }
private:
    float vibratoAmount;
    float nextVibOscSample;
};

class Glide{
public:
    Glide(): targetNote(72), currentNote(0.0), firstGlide(true), glideEngaged(false), glideTime(1), totalGlideDistance(0.0), glideDistanceLeft(0.0){};
    
    void setGlide() {
        DBG("current note : " + (String)currentNote);
        if (firstGlide == false) {totalGlideDistance = targetNote - currentNote;;};
        glideDistanceLeft = totalGlideDistance;
        DBG("glide distance left : " + (String)glideDistanceLeft);
        DBG("total glide distance : " + (String)totalGlideDistance);
        updateGlideIncrement();
        firstGlide = false;
    }
    
    void setGlideTime(double samples) {
        glideTime = samples + 1; //extra logic would be needed if glideTime becomes 0, so instead I make 1 the minimum value
        updateGlideIncrement();
    }
    
    float getNextGlideIncrement() {
        if (totalGlideDistance < 0){
            if (glideDistanceLeft < 0) {glideDistanceLeft -= glideIncrement;};
            return glideDistanceLeft;
        }
        else {
            if (glideDistanceLeft > 0) {glideDistanceLeft -= glideIncrement;};
            return glideDistanceLeft;
        };
        
    }
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
    void updateGlideIncrement() {
        glideIncrement = totalGlideDistance / glideTime;
    };
    
};

class FreqControl: public Vibrato, public Glide{
public:
    enum Octave{
        THIRTY_TWO = -28, SIXTEEN = -14, EIGHT = 0, FOUR = 14
    };
    FreqControl(): tuning(0), currentOctave(EIGHT){};
    ~FreqControl() {};
    
    /* frequency can be tuned in semitones e.g. -1.5 will decrease all output by 1.5 semitones */
    void setTuning(float semitones) {tuning = semitones;};
    
    /* takes a midi note number */
    void setNote(float midiNote) {
        targetNote = midiNote;
        setGlide();
    };
    
    double getNextFrequency() {
        currentNote = targetNote + tuning + getNextVibratoIncrement() + currentOctave - getNextGlideIncrement();
        return getMidiNoteInHertz(currentNote);
    };
    
    void setOctave(Octave oct){
        currentOctave = oct;
    }
    
private:
    float tuning;
    Octave currentOctave;
    
    double getMidiNoteInHertz (float noteNumber, const double frequencyOfA = 440)
    {
        return frequencyOfA * pow (2.0, (noteNumber - 69) / 12.0);
    }
};

#endif  // FREQCONTROL_H_INCLUDED
