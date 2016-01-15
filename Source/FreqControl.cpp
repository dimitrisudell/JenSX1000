/*
  ==============================================================================

    OscMain.cpp
    Created: 6 Sep 2015 4:28:15pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "FreqControl.h"
#include "JenConstants.h"


    FreqControl::FreqControl(): Glide(JenConstants::GlideMaxTime), tuning(0), currentOctave(EIGHT){};

    void FreqControl::setTuning(float semitones) {tuning = semitones;};
    
    void FreqControl::setNote(int midiNote) {
        targetNote = midiNote;
        setGlide();
    };
    
    double FreqControl::getNextFrequency() {
        currentNote = targetNote + tuning + getNextVibratoIncrement() + currentOctave - getNextGlideIncrement();
        return FreqControl::getMidiNoteInHertz(currentNote);
    };
    
    void FreqControl::setOctave(Octave oct){
        currentOctave = oct;
    }

double FreqControl::getMidiNoteInHertz (float noteNumber, const double frequencyOfA)
{
    return frequencyOfA * pow (2.0, (noteNumber - 69) / 12.0);
}

