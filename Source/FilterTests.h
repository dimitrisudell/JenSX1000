/*
  ==============================================================================

    FilterTests.h
    Created: 15 Jan 2016 3:25:09pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef FILTERTESTS_H_INCLUDED
#define FILTERTESTS_H_INCLUDED

#include "Filter.h"
#include "../JuceLibraryCode/JuceHeader.h"

class FilterTests  : public UnitTest, public Filter {
    
public:
    FilterTests()  : UnitTest ("Filter Tests"){}
    
    
    
    void runTest() override {

    
    
    }
};



#endif  // FILTERTESTS_H_INCLUDED
