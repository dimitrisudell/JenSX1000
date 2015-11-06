/*
  ==============================================================================

    FilterComponent.h
    Created: 5 Sep 2015 6:34:32pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef FILTERCOMPONENT_H_INCLUDED
#define FILTERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "JenKnob.h"
#include "EnvelopeComponent.h"

//==============================================================================
/*
*/
class FilterComponent    : public Component
{
public:
    FilterComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        
        setSize(424, 240);
        
        addAndMakeVisible(frequency);
        addAndMakeVisible(resonance);
        addAndMakeVisible(lfo);
        addAndMakeVisible(envLevel);
        
        addAndMakeVisible(envelope);

    }

    ~FilterComponent()
    {
    }

    void paint (Graphics& g)
    {

    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        frequency.setTopLeftPosition(0,0);
        resonance.setTopLeftPosition(100,0);
        lfo.setTopLeftPosition(200,0);
        envLevel.setTopLeftPosition(300,0);
        
        envelope.setTopLeftPosition(0,100);

    }
    
    JenKnob frequency{"frequency", Colours::white};
    JenKnob resonance{"resonance", Colours::white};
    JenKnob lfo{"L.F.O.", Colours::yellow};
    JenKnob envLevel{"env. level", Colours::blue};

    envelopeComponent envelope;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};


#endif  // FILTERCOMPONENT_H_INCLUDED
