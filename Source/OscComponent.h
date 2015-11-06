/*
  ==============================================================================

    VCOComponent.h
    Created: 5 Sep 2015 6:31:01pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef OSCCOMPONENT_H_INCLUDED
#define OSCCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "JenKnob.h"

//==============================================================================
/*
*/
class OscComponent    : public Component
{
public:
    OscComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        
        setSize(400,300);
                
        addAndMakeVisible(tune);
        
        addAndMakeVisible(octave);
        octave.slider.setRange(0, 1, 0.3333);
        octave.slider.setRotaryParameters(1.5 * double_Pi, 2.5 * double_Pi, true);
        
        addAndMakeVisible(vibrato);
        
        addAndMakeVisible(waveform);
        waveform.slider.setRange(0, 1, 0.5);
        waveform.slider.setRotaryParameters(1.5 * double_Pi, 2.5 * double_Pi, true);
        
        addAndMakeVisible(pulsewidth);
        
        addAndMakeVisible(pwm);
        addAndMakeVisible(level);
        
        addAndMakeVisible(glide);

    }

    ~OscComponent()
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
        
        tune.setTopLeftPosition(0, 0);
        octave.setTopLeftPosition(100, 0);
        vibrato.setTopLeftPosition(200, 0);
        
        waveform.setTopLeftPosition(0, 100);
        pulsewidth.setTopLeftPosition(100, 100);
        pwm.setTopLeftPosition(200, 100);
        level.setTopLeftPosition(300, 100);
        
        glide.setTopLeftPosition(0, 200);

    }
    
    JenKnob tune{"tune", Colours::red};
    JenKnob octave{"octave", Colours::red};
    JenKnob vibrato{"vibrato", Colours::yellow};
    
    JenKnob waveform{"waveform", Colours::red};
    JenKnob pulsewidth{"pulse width", Colours::red};
    JenKnob pwm{"P.W.M.", Colours::red};
    JenKnob level{"level", Colours::red};
    
    JenKnob glide{"glide", Colours::red};

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};


#endif  // OSCCOMPONENT_H_INCLUDED
