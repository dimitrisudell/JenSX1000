/*
  ==============================================================================

    VCAComponent.h
    Created: 5 Sep 2015 6:33:07pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef AMPCOMPONENT_H_INCLUDED
#define AMPCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "JenKnob.h"
#include "EnvelopeComponent.h"

//==============================================================================
/*
*/
class AmpComponent    : public Component
{
public:
    AmpComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        
        setSize(500, 100);
                
        addAndMakeVisible(outputVolume);
        
        addAndMakeVisible(envelope);

    }

    ~AmpComponent()
    {
    }

    void paint (Graphics& g)
    {

    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        outputVolume.setTopLeftPosition(0,0);
        envelope.setTopLeftPosition(100,0);

    }
    
    JenKnob outputVolume{"output volume", Colours::red};
    envelopeComponent envelope;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpComponent)
};


#endif  // AMPCOMPONENT_H_INCLUDED
