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

class JenSlider : public Slider{
public:
    
    JenSlider (Colour knobColour);
    
    JenSlider();
    
    void setNumberPoint(int);
    
    void setLabelStrings(Array<String>);
    
    void setLabels();
    
    virtual void setLabelPositions();
    
    void paint (Graphics& g) override;
    
    void paintMarkers (Graphics& g);
    
    virtual void paintMarkerLabels (int index, float alpha);
    
    void paintKnobCentre (Graphics& g);
    
    void resized() override;
    
    void setJenRotaryParameters (float startAngleRadians, float endAngleRadians, bool stopAtEnd);
    
protected:
    bool continuous;
    float jenRotaryStart, jenRotaryEnd;
    const float innerMarkerRadius = 25;
    const float outerMarkerRadius = 32;
    const float labelRadius = 40;
    float angelBetweenMarkersRadians;
    int numPoints;
    
    OwnedArray<Line<float>> marks;
    
    float pointOnCircumfranceX (float originX, float radius, float angle);
    
    float pointOnCircumfranceY (float originY, float radius, float angle);
    
private:
    Font labelFont;
    OwnedArray<Label> labels;
    Array<String> labelStrings;
    
    void calculateAngleBetweenMarks();
};

class JenKnobOctave : public JenSlider{
public:
    JenKnobOctave(Colour knobColor): JenSlider{knobColor} {
        setJenRotaryParameters(0.86364 * double_Pi * 2, 1.13636 * double_Pi * 2, true);
        setRange(0, 1, 0.3334);
        setNumberPoint(4);
        setLabelStrings({"32'", "16'", "8'", "4'"});
        continuous = false;
    }
    
};

class JenKnobWaveform : public JenSlider{
    
    class WaveIcon : public Component{
    public:
        WaveIcon(){};
        
        void setIconColour(Colour c){
            colour = c;
        }
        
        void paint (Graphics& g) {
            g.setColour(colour);
            g.strokePath (icon, PathStrokeType (2.0f));
        }
        
    protected:
        Path icon;
        Colour colour;
    };
    
    class SquareWaveIcon : public WaveIcon{
    public:
        SquareWaveIcon(){
            setSize(10,10);
            icon.startNewSubPath (1.0f, 5.0f);
            icon.lineTo(1.0f, 9.0f);
            icon.lineTo(5.0f, 9.0f);
            icon.lineTo(5.0f, 1.0f);
            icon.lineTo(9.0f, 1.0f);
            icon.lineTo(9.0f, 5.0f);
        }
    };
    
    class PulseWaveIcon : public WaveIcon{
    public:
        PulseWaveIcon(){
            setSize(12,10);
            icon.startNewSubPath (1.0f, 5.0f);
            icon.lineTo(1.0f, 9.0f);
            icon.lineTo(4.0f, 9.0f);
            icon.lineTo(4.0f, 1.0f);
            icon.lineTo(11.0f, 1.0f);
            icon.lineTo(11.0f, 5.0f);
        }
    };
    
    class TriangleWaveIcon : public WaveIcon{
    public:
        TriangleWaveIcon(){
            setSize(14,8);
            icon.startNewSubPath (1.0f, 7.0f);
            icon.lineTo(13.0f, 1.0f);
            icon.lineTo(13.0f, 7.0f);
        }
    };
    
public:
    JenKnobWaveform(Colour knobColor): JenSlider{knobColor} {
        setLabelStrings({});
        setRange(0, 1, 0.5);
        setJenRotaryParameters(0.9 * double_Pi * 2, 1.1 * double_Pi * 2, true);
        setNumberPoint(3);
        continuous = false;
        
        icons.add(new TriangleWaveIcon);
        icons.add(new SquareWaveIcon);
        icons.add(new PulseWaveIcon);
        
        for(int i = 0; i < icons.size(); ++i){
            addAndMakeVisible(icons[i]);
        }
        
        setLabelPositions();
        
    }
    
    void paintMarkerLabels(int index, float alpha){
        icons[index]->setIconColour((Colours::white).withAlpha(alpha));
    }
    
    void setLabelPositions() override{
        for(int i = 0; i < icons.size() && i < numPoints; ++i){
            float angle = jenRotaryStart + (i * angelBetweenMarkersRadians);
            icons[i]->setCentrePosition(pointOnCircumfranceX(53, labelRadius, angle), pointOnCircumfranceY(60, labelRadius, angle));
            
        }
    }
    
    OwnedArray<WaveIcon> icons;
};


class JenKnobPulseWidth : public JenSlider{
public:
    JenKnobPulseWidth(Colour knobColor): JenSlider{knobColor} {
        setNumberPoint(10);
        setLabelStrings({"5%", "10", "15", "20", "25", "30", "35", "40", "45", "50%"});
        setJenRotaryParameters(00.590909 * double_Pi * 2, 1.40909 * double_Pi * 2, true);
    }
};

class JenKnobNoise : public JenSlider{
public:
    JenKnobNoise(Colour knobColor): JenSlider{knobColor} {
        setJenRotaryParameters(0.9 * double_Pi * 2, 1.1 * double_Pi * 2, true);
        setRange(0, 1, 0.5);
        setNumberPoint(3);
        setLabelStrings({"off", "white", "pink"});
        continuous = false;
    }
};

class JenKnobTune : public JenSlider{
public:
    JenKnobTune(Colour knobColor): JenSlider{knobColor} {
        setLabelStrings({"-5", "4", "3", "2", "1", "0", "1", "2", "3", "4", "+5"});
    }
    
    void paint(Graphics& g) override{
        
        double currentValue = getValue();
        double segmentValue = getMaximum()/(numPoints - 1);
        double zeroValue = getMaximum()/2;
        double zeroPointIndex = 5; //TODO: don't hard code this
        
        for(int i = 0; i < numPoints; ++i){
            
            float alpha = 0.5;
            
            if (i < zeroPointIndex){
                if (currentValue <= (segmentValue * i)){
                    alpha = 1.0;
                }
            } else if (i > zeroPointIndex){
                if (currentValue >= (segmentValue * i)){
                    alpha = 1.0;
                }
            } else {
                if (currentValue != zeroValue){
                    alpha = 1.0;
                }
            }
            
            g.setColour((Colours::white).withAlpha(alpha));
            
            g.drawLine(*marks[i], 2);
            
            paintMarkerLabels(i, alpha);
        }

        paintKnobCentre(g);
        
    }
};


#endif