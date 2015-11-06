/*
  ==============================================================================

    LFOComponent.h
    Created: 5 Sep 2015 6:33:47pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef LFOCOMPONENT_H_INCLUDED
#define LFOCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "JenKnob.h"

//==============================================================================
/*
*/
class LFOComponent    : public Component
{
public:
    LFOComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        setSize(100, 100);
        
        addAndMakeVisible(speed);
    }

    ~LFOComponent()
    {
    }

    void paint (Graphics& g)
    {
    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        speed.setTopLeftPosition(0, 0);
    }
    
    JenKnob speed{"speed", Colours::yellow};

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};


#endif  // LFOCOMPONENT_H_INCLUDED
