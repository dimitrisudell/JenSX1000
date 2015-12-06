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
    
    JenSlider(Colour knobColour): JenSlider(){
        setColour(ColourIds::rotarySliderFillColourId, knobColour);
    }
    
    JenSlider(): Slider{RotaryVerticalDrag, Slider::NoTextBox}, labelFont{12, Font::bold} {
        setNumberPoint(11);
        continuous = true;
        setJenRotaryParameters(static_cast<float>(0.5833 * 2 * double_Pi), static_cast<float>(1.4167 * 2 * double_Pi), true);
        setRange(0, 1, 0.01);
        setSize(106,120);
        setLabelStrings({{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"}});
    }
    
    void setNumberPoint(int num){
        numPoints = num;
        calculateAngleBetweenMarks();
        
        marks.clear();
        
        for(int i = 0; i < numPoints; ++i){
            
            float angle = jenRotaryStart + (angelBetweenMarkersRadians * i);
            
            marks.add(new Line<float>{pointOnCircumfranceX(getWidth()/2, innerMarkerRadius, angle), pointOnCircumfranceY(getHeight()/2, innerMarkerRadius, angle), pointOnCircumfranceX(getWidth()/2, outerMarkerRadius, angle), pointOnCircumfranceY(getHeight()/2, outerMarkerRadius, angle)});
            
        }
        
        setLabelPositions();
    }
    
    void setLabelStrings(Array<String> st){
        labelStrings.clear();
        
        for(int i = 0; i < st.size(); ++i){
            labelStrings.add(st[i]);
        }
        setLabels();
    }
    
    void setLabels(){
        BorderSize<int> border;
        
        labels.clear();
        
        for (int i=0; i < labelStrings.size(); ++i){
            labels.add(new Label{labelStrings[i], labelStrings[i]});
            labels[i]->setSize(20,20);
            labels[i]->setBorderSize(border);
            labels[i]->setJustificationType(Justification::centred);
            labels[i]->setText(labelStrings[i], dontSendNotification);
            labels[i]->setFont(labelFont);
            addAndMakeVisible(labels[i]);
        }
        
        setLabelPositions();
    }
    
    virtual void setLabelPositions(){
        for(int i = 0; i < labels.size() && i < numPoints; ++i){
            float angle = jenRotaryStart + (angelBetweenMarkersRadians * i);
            
            labels[i]->setCentrePosition(pointOnCircumfranceX(53, labelRadius, angle), pointOnCircumfranceY(60, labelRadius, angle));
            
        }
    }
    
    void paint(Graphics& g) override{
        float alpha = 0.5;
        
        for(int i = 0; i < numPoints; ++i){
            
            double currentValue = getValue();
            double segmentValue = getMaximum()/(numPoints - 1);
            
            if (continuous){
                if (currentValue > 0 && (currentValue >= segmentValue * i)) {alpha = 1;}
                else {alpha = 0.5;};
            }
            else if(!continuous){
                double currentSegmentValue = segmentValue * i;
                if (currentValue == currentSegmentValue || ((currentValue > (currentSegmentValue - (segmentValue * 0.5))) && (currentValue < (currentSegmentValue + (segmentValue * 0.5))))) {alpha = 1;}
                else {alpha = 0.5;};
            };
            
            g.setColour((Colours::white).withAlpha(alpha));
            
            g.drawLine(*marks[i], 2);
            
            paintMarkerLabels(i, alpha);
            
            paintKnobCentre(g);

        }
    }
    
    virtual void paintMarkerLabels(int index, float alpha) {
        labels[index]->setColour(Label::textColourId, (Colours::white).withAlpha(alpha));
    }
    
    void paintKnobCentre(Graphics& g){
        const float radius = 23;
        const float centreX = getWidth() / 2;
        const float centreY = getHeight() / 2;
        const bool isMouseOver = isMouseOverOrDragging() && isEnabled();
        
        const float coloredCentreEllipseRadius = radius * 0.6f;
        const float coloredCentreEllipseX = centreX - coloredCentreEllipseRadius;
        const float coloredCentreEllipseY = centreY - coloredCentreEllipseRadius;
        const float coloredCentreEllipseDiameter = coloredCentreEllipseRadius * 2.0f;
        
        //revert or remove
        g.setColour (findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 1.0f));
        
        Path knobCentre;
        knobCentre.addEllipse (coloredCentreEllipseX, coloredCentreEllipseY, coloredCentreEllipseDiameter, coloredCentreEllipseDiameter);
        g.fillPath (knobCentre);
        
        g.setColour(Colours::white);
        
        const float movingElipsePathRadius = radius * 0.85f;
        const float movingElipseRadius = radius * 0.15f;
        const float movingElipseDiameter = movingElipseRadius * 2.0f;
        
        float currentAngle = jenRotaryStart + getValue() * (jenRotaryEnd - jenRotaryStart);
        
        Path outerCircle;
        
        outerCircle.addEllipse(pointOnCircumfranceX(centreX, movingElipsePathRadius, currentAngle) - movingElipseRadius, pointOnCircumfranceY(centreY, movingElipsePathRadius, currentAngle) - movingElipseRadius, movingElipseDiameter, movingElipseDiameter);
        
        g.fillPath (outerCircle);
    };
    
    void resized() override{
        Slider::resized();
        setNumberPoint(numPoints);
    }
    
    void setJenRotaryParameters(float startAngleRadians, float endAngleRadians, bool stopAtEnd){
        setRotaryParameters(startAngleRadians, endAngleRadians, stopAtEnd);
        jenRotaryStart = startAngleRadians;
        jenRotaryEnd = endAngleRadians;
        calculateAngleBetweenMarks();
        setNumberPoint(numPoints);
        setLabelPositions();
    }

    float angelBetweenMarkersRadians;
    int numPoints;
    
protected:
    bool continuous;
    float jenRotaryStart, jenRotaryEnd;
    const float innerMarkerRadius = 25;
    const float outerMarkerRadius = 32;
    const float labelRadius = 40;
    
    float pointOnCircumfranceX(float originX, float radius, float angle){
        float x = originX + (radius * sin(angle));
        return x;
    }
    
    float pointOnCircumfranceY(float originY, float radius, float angle){
        float y = originY - (radius * cos(angle));
        return y;
    }
    
private:
    OwnedArray<Line<float>> marks;
    Font labelFont;
    OwnedArray<Label> labels;
    Array<String> labelStrings;
    
    void calculateAngleBetweenMarks(){
        //number of points could be come negative... does it matter??
        angelBetweenMarkersRadians = (jenRotaryEnd - jenRotaryStart)/(numPoints - 1);
    }
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
};


#endif