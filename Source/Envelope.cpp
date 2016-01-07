/*
  ==============================================================================

    Envelope.cpp
    Created: 7 Jan 2016 3:57:37pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Envelope.h"
#include "../JuceLibraryCode/JuceHeader.h"

Envelope::Envelope(): currentAmplitude(minAmplitude), sustainAmplitude(minAmplitude) { updateState(OFF);};

void Envelope::begin() {
    updateState(ATTACK);
    currentAmplitude = minAmplitude;
}

void Envelope::release() {
    setReleaseTime(releaseTime);
    updateState(RELEASE);
}

void Envelope::setAttackTime(double aTime){
    attackTime = aTime + 1;
    attackIncrement = maxAmplitude/(attackTime); //returns nan if divide by 0
}

void Envelope::setReleaseTime(double rTime) {
    jassert(sustainAmplitude >= minAmplitude);
    releaseTime = rTime + 1;
    releaseIncrement = currentAmplitude/(releaseTime); //returns nan if divide by 0
}

void Envelope::setDecayTime(double dTime) {
    jassert(sustainAmplitude >= minAmplitude);
    decayTime = dTime + 1;
    decayIncrement = (maxAmplitude - sustainAmplitude) / (decayTime); //returns nan if divide by 0
}

void Envelope::setSustainAmplitude(double sAmplitude){
    jassert((sAmplitude >= minAmplitude) && (sAmplitude <= maxAmplitude));
    sustainAmplitude = sAmplitude;
    setReleaseTime(releaseTime);
    setDecayTime(decayTime);
}

float Envelope::getNextSample(){
    switch (state){
        case ATTACK:
            currentAmplitude += attackIncrement;
            if (currentAmplitude >= maxAmplitude) {currentAmplitude = maxAmplitude; updateState(DECAY);}
            break;
        case DECAY:
            currentAmplitude -= decayIncrement;
            if (currentAmplitude <= sustainAmplitude) {currentAmplitude = sustainAmplitude; updateState(SUSTAIN);}
            break;
        case SUSTAIN:
            break;
        case RELEASE:
            currentAmplitude -= releaseIncrement;
            if (currentAmplitude <= minAmplitude) {currentAmplitude = minAmplitude; updateState(OFF);}
        case OFF:
            break;
    }
    jassert((currentAmplitude >= minAmplitude) && (currentAmplitude <= maxAmplitude));
    return currentAmplitude;
    
};

void Envelope::updateState(State s){
    state = s;
}