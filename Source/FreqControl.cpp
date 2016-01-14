/*
  ==============================================================================

    OscMain.cpp
    Created: 6 Sep 2015 4:28:15pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "FreqControl.h"
#include "juce_MidiMessage.h"


    FreqControl::FreqControl(): tuning(0), currentOctave(EIGHT){};

    void FreqControl::setTuning(float semitones) {tuning = semitones;};
    
    void FreqControl::setNote(int midiNote) {
        targetNote = midiNote;
        setGlide();
    };
    
    double FreqControl::getNextFrequency() {
        currentNote = targetNote + tuning + getNextVibratoIncrement() + currentOctave - getNextGlideIncrement();
        return MidiMessage::getMidiNoteInHertz(currentNote);
    };
    
    void FreqControl::setOctave(Octave oct){
        currentOctave = oct;
    }
