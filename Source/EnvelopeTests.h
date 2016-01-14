/*
  ==============================================================================

    EnvelopeTests.h
    Created: 6 Jan 2016 5:23:20pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef ENVELOPETESTS_H_INCLUDED
#define ENVELOPETESTS_H_INCLUDED

#include "Envelope.h"

class EnvelopeTests  : public UnitTest, public Envelope {
    
public:
    EnvelopeTests()  : UnitTest ("Envelope Tests") {}
    
    void runTest() override {

    }
};




#endif  // ENVELOPETESTS_H_INCLUDED
