/*
  ==============================================================================

    OscMain.cpp
    Created: 6 Sep 2015 4:28:15pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "FreqControl.h"
#include "JenConstants.h"

FreqControl::FreqControl() : mTuning(0), mCurrentOctave(EIGHT), mTargetNote(72), mCurrentNote(0.0), mGlide{JenConstants::GlideMaxTime} {};

void FreqControl::setTuning (float semitones)
{
    mTuning = semitones;
}
    
void FreqControl::setNote (int midiNote)
{
    mOriginalMidiNote = midiNote;
    mTargetNote = midiNote + mCurrentOctave;
    mGlide.setGlide(mCurrentNote, mTargetNote);
}
    
double FreqControl::getNextFrequency()
{
    mCurrentNote = mTargetNote + mTuning + mVibrato.getNextVibratoIncrement() - mGlide.getNextGlideIncrement();
    return FreqControl::getMidiNoteInHertz(mCurrentNote);
}
    
void FreqControl::setOctave (Octave oct)
{
    mCurrentOctave = oct;
    setNote(mOriginalMidiNote);
}

void FreqControl::setGlideValue (double value)
{
    mGlide.setGlideValue(value);
}

void FreqControl::setSampleRate (double sampleRate)
{
    mGlide.setSampleRate(sampleRate);
}

void FreqControl::setNextVibratoOscSample (float sample)
{
    mVibrato.setNextVibratoOscSample(sample);
}

void FreqControl::setVibratoValue (float value)
{
    mVibrato.setVibratoAmount(value);
}

 double FreqControl::getMidiNoteInHertz (float noteNumber, const double frequencyOfA)
{
    return (frequencyOfA * pow (2.0, ((noteNumber - 69) / 12.0)));
}

