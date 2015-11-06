/*
  ==============================================================================

    JenKnob.h
    Created: 5 Sep 2015 5:57:01pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef JENKNOB_H_INCLUDED
#define JENKNOB_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/

class MySlider : public Slider{
    
public:
    MySlider(SliderStyle style, TextEntryBoxPosition textBoxPosition) {Slider::Slider(style, Slider::NoTextBox);};
    
    void paint (Graphics& g) override{
        DBG("entered slider paint");
        
        g.setColour((Colours::blue).withAlpha(0.5f));
        Path rect;
        rect.addRectangle (getX(), getY(), getWidth(), getHeight());
        g.fillPath (rect);
        g.setColour (findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver() ? 1.0f : 0.7f));
        Path filledArc;
        filledArc.addEllipse (getX(), getY(), getWidth()/2, getHeight()/2);
        g.fillPath (filledArc);
    }
};


class JenKnob   : public Component{
public:
    JenKnob(String labelText, Colour knobColor):slider{Slider::RotaryVerticalDrag, Slider::NoTextBox}, label{labelText + "Label", labelText}
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        setSize(106, 120);
        
        addAndMakeVisible(slider);
        slider.setSize(50, 50);
        slider.setRange(0, 1, 0.01);
        slider.setColour(Slider::ColourIds::rotarySliderFillColourId, knobColor);
        
        addAndMakeVisible(label);
        label.setSize(70, 20);
        label.setJustificationType(Justification::horizontallyCentred);
        label.setJustificationType(Justification::verticallyCentred);
    }

    ~JenKnob()
    {
    }

    void paint (Graphics& g) {
    
        g.setColour(Colours::white);
        
        for(int i = 0; i < 100; i += 10){
            g.drawLine(i,0,i,10);
        }
        
    };

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
        slider.setTopLeftPosition(25, 25);
        label.setTopLeftPosition(15, 80);

    }
    
    Slider slider;
    Label label;
    int noPoints;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JenKnob)
};


#endif  // JENKNOB_H_INCLUDED
