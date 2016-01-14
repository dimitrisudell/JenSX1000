/*
  ==============================================================================

    Glide.cpp
    Created: 7 Jan 2016 6:47:47pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "Glide.h"
#include "JuceHeader.h"

Glide::Glide(): targetNote(72), currentNote(0.0), firstGlide(true), glideEngaged(false), glideTime(1), totalGlideDistance(0.0), glideDistanceLeft(0.0) {};

void Glide::setGlide() {
    DBG("current note : " + (String)currentNote);
    if (firstGlide == false) {totalGlideDistance = targetNote - currentNote;;};
    glideDistanceLeft = totalGlideDistance;
    DBG("glide distance left : " + (String)glideDistanceLeft);
    DBG("total glide distance : " + (String)totalGlideDistance);
    updateGlideIncrement();
    firstGlide = false;
}

void Glide::setGlideTime(double samples) {
    glideTime = samples + 1; //extra logic would be needed if glideTime becomes 0, so instead I make 1 the minimum value
    updateGlideIncrement();
}

float Glide::getNextGlideIncrement() {
    if (totalGlideDistance < 0){
        if (glideDistanceLeft < 0) {glideDistanceLeft -= glideIncrement;};
        return glideDistanceLeft;
    }
    else {
        if (glideDistanceLeft > 0) {glideDistanceLeft -= glideIncrement;};
        return glideDistanceLeft;
    };
    
}

void Glide::updateGlideIncrement() {
    glideIncrement = totalGlideDistance / glideTime;
};
