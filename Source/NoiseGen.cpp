/*
  ==============================================================================

    NoiseGen.cpp
    Created: 22 Jan 2016 1:11:45pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "NoiseGen.h"

NoiseGen::NoiseGen() : mState(OFF) {};

NoiseGen::~NoiseGen() {};

float NoiseGen::getNextSample()
{
    switch (mState){
        case OFF:
            return 0;
        case WHITE:
            return randamplitude();
        case PINK:
            float white = randamplitude();
            b0 = 0.99765 * b0 + white * 0.0990460;
            b1 = 0.96300 * b1 + white * 0.2965164;
            b2 = 0.57000 * b2 + white * 1.0526913;
            float tmp = (b0 + b1 + b2 + white * 0.1848)/3.5;
            return tmp;
    }
};

void NoiseGen::setState (States s)
{
    mState = s;
}

float NoiseGen::randamplitude()
{
    float randFloat = mRandom.nextFloat();
    return (randFloat * 2 - 1);
}