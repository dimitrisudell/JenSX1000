/*
  ==============================================================================

    OscMain.cpp
    Created: 6 Sep 2015 4:28:15pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "FreqControl.h"
#include "JenConstants.h"

FreqControl::FreqControl(): tuning(0), currentOctave(EIGHT), targetNote(72), currentNote(0.0), glide{JenConstants::GlideMaxTime}{};

void FreqControl::setTuning(float semitones) {tuning = semitones;};
    
void FreqControl::setNote(int midiNote) {
    targetNote = midiNote + currentOctave;
    glide.setGlide(currentNote, targetNote);
};
    
double FreqControl::getNextFrequency() {
    currentNote = targetNote + tuning + vibrato.getNextVibratoIncrement() - glide.getNextGlideIncrement();
    return FreqControl::getMidiNoteInHertz(currentNote);
};
    
void FreqControl::setOctave(Octave oct){
    currentOctave = oct;
}

void FreqControl::setGlideValue(double value){
    glide.setGlideValue(value);
}

void FreqControl::setSampleRate(double sampleRate){
    glide.setSampleRate(sampleRate);
}

void FreqControl::setNextVibratoOscSample(float sample){
    vibrato.setNextVibratoOscSample(sample);
}

void FreqControl::setVibratoValue(float value){
    vibrato.setVibratoAmount(value);
}

double FreqControl::getMidiNoteInHertz (float noteNumber, const double frequencyOfA)
{
    return (frequencyOfA * pow (2.0, ((noteNumber - 69) / 12.0)));
}

