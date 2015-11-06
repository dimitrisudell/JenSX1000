/*
  ==============================================================================

    NoiseComponent.h
    Created: 5 Sep 2015 6:34:03pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef NOISECOMPONENT_H_INCLUDED
#define NOISECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "JenKnob.h"

//==============================================================================
/*
*/
class NoiseComponent    : public Component
{
public:
    NoiseComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        setSize(200, 100);
        
        addAndMakeVisible(noise);
        noise.slider.setRange(0, 1, 0.5);
        noise.slider.setRotaryParameters(1.5 * double_Pi, 2.5 * double_Pi, true);
        
        addAndMakeVisible(level);

    }

    ~NoiseComponent()
    {
    }

    void paint (Graphics& g)
    {
    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        noise.setTopLeftPosition(0, 0);
        level.setTopLeftPosition(106, 0);
    }
    
    JenKnob noise{"noise", Colours::yellow};
    JenKnob level{"level", Colours::yellow};

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseComponent)
};


#endif  // NOISECOMPONENT_H_INCLUDED
