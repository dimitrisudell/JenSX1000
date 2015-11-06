/*
  ==============================================================================

    envelopeGUI.h
    Created: 5 Sep 2015 6:09:24pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef ENVELOPECOMPONENT_H_INCLUDED
#define ENVELOPECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "JenKnob.h"

//==============================================================================
/*
*/
class envelopeComponent    : public Component
{
public:
    envelopeComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        
        setSize(400, 100);
        
        addAndMakeVisible(attack);
        addAndMakeVisible(decay);
        addAndMakeVisible(sustain);
        addAndMakeVisible(release);

    }

    ~envelopeComponent()
    {
    }

    void paint (Graphics& g)
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */
    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        attack.setTopLeftPosition(0, 0);
        decay.setTopLeftPosition(100, 0);
        sustain.setTopLeftPosition(200, 0);
        release.setTopLeftPosition(300, 0);

    }
    
    JenKnob attack{"attack", Colours::blue};
    JenKnob decay{"decay", Colours::blue};
    JenKnob sustain{"sustain", Colours::blue};
    JenKnob release{"release", Colours::blue};

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (envelopeComponent)
};


#endif  // ENVELOPECOMPONENT_H_INCLUDED
