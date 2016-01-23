/*
  ==============================================================================

    JenKnob.cpp
    Created: 23 Jan 2016 2:08:49pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#include "JenKnob.h"
#include "JenColours.h"

JenSlider::JenSlider (Colour knobColour) : JenSlider()
{
    setColour(ColourIds::rotarySliderFillColourId, knobColour);
}

JenSlider::JenSlider(): Slider{RotaryVerticalDrag, Slider::NoTextBox}, labelFont{12, Font::bold}
{
    setNumberPoint(11);
    continuous = true;
    setJenRotaryParameters(static_cast<float>(0.5833 * 2 * double_Pi), static_cast<float>(1.4167 * 2 * double_Pi), true);
    setRange(0, 1, 0.01);
    setSize(106,120);
    setLabelStrings({{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"}});
}

void JenSlider::setNumberPoint (int num)
{
    numPoints = num;
    calculateAngleBetweenMarks();
    
    marks.clear();
    
    for(int i = 0; i < numPoints; ++i){
        
        float angle = jenRotaryStart + (angelBetweenMarkersRadians * i);
        
        marks.add(new Line<float>{pointOnCircumfranceX(getWidth()/2, innerMarkerRadius, angle), pointOnCircumfranceY(getHeight()/2, innerMarkerRadius, angle), pointOnCircumfranceX(getWidth()/2, outerMarkerRadius, angle), pointOnCircumfranceY(getHeight()/2, outerMarkerRadius, angle)});
        
    }
    
    setLabelPositions();
}

void JenSlider::setLabelStrings(Array<String> st)
{
    labelStrings.clear();
    
    for(int i = 0; i < st.size(); ++i){
        labelStrings.add(st[i]);
    }
    setLabels();
}

void JenSlider::setLabels()
{
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

 void JenSlider::setLabelPositions()
{
    for(int i = 0; i < labels.size() && i < numPoints; ++i){
        float angle = jenRotaryStart + (angelBetweenMarkersRadians * i);
        
        labels[i]->setCentrePosition(pointOnCircumfranceX(53, labelRadius, angle), pointOnCircumfranceY(60, labelRadius, angle));
        
    }
}

void JenSlider::paint (Graphics& g)
{
    paintMarkers(g);
    paintKnobCentre(g);
}

void JenSlider::paintMarkers (Graphics& g)
{
    float alpha;
    
    double currentValue = getValue();
    double segmentValue = getMaximum()/(numPoints - 1);
    
    for(int i = 0; i < numPoints; ++i){
        
        alpha = 0.5;
        
        if (continuous){
            if (currentValue > 0 && (currentValue >= segmentValue * i)) {alpha = 1;}
        }
        else if(!continuous){
            double currentSegmentValue = segmentValue * i;
            if (currentValue == currentSegmentValue || ((currentValue > (currentSegmentValue - (segmentValue * 0.5))) && (currentValue < (currentSegmentValue + (segmentValue * 0.5))))) {alpha = 1;}
        };
        
        g.setColour((JenColours::white).withAlpha(alpha));
        
        g.drawLine(*marks[i], 2);
        
        paintMarkerLabels(i, alpha);
    }
}

void JenSlider::paintMarkerLabels (int index, float alpha)
{
    labels[index]->setColour(Label::textColourId, (JenColours::white).withAlpha(alpha));
}

void JenSlider::paintKnobCentre (Graphics& g)
{
    const float radius = 23;
    const float centreX = getWidth() / 2;
    const float centreY = getHeight() / 2;
    const bool isMouseOver = isMouseOverOrDragging() && isEnabled();
    
    const float coloredCentreEllipseRadius = radius * 0.6f;
    const float coloredCentreEllipseX = centreX - coloredCentreEllipseRadius;
    const float coloredCentreEllipseY = centreY - coloredCentreEllipseRadius;
    const float coloredCentreEllipseDiameter = coloredCentreEllipseRadius * 2.0f;
    
    //TODO: revert or remove
    const float alpha = (isMouseOver ? 1.0f : 1.0f);
    
    g.setColour (findColour (Slider::rotarySliderFillColourId).withAlpha(alpha));
    
    Path knobCentre;
    knobCentre.addEllipse (coloredCentreEllipseX, coloredCentreEllipseY, coloredCentreEllipseDiameter, coloredCentreEllipseDiameter);
    g.fillPath (knobCentre);
    
    g.setColour((JenColours::white).withAlpha(alpha));
    
    const float movingElipsePathRadius = radius * 0.85f;
    const float movingElipseRadius = radius * 0.15f;
    const float movingElipseDiameter = movingElipseRadius * 2.0f;
    
    float currentAngle = jenRotaryStart + getValue() * (jenRotaryEnd - jenRotaryStart);
    
    Path outerCircle;
    
    outerCircle.addEllipse(pointOnCircumfranceX(centreX, movingElipsePathRadius, currentAngle) - movingElipseRadius, pointOnCircumfranceY(centreY, movingElipsePathRadius, currentAngle) - movingElipseRadius, movingElipseDiameter, movingElipseDiameter);
    
    g.fillPath (outerCircle);
};

void JenSlider::resized()
{
    Slider::resized();
    setNumberPoint(numPoints);
}

void JenSlider::setJenRotaryParameters (float startAngleRadians, float endAngleRadians, bool stopAtEnd)
{
    setRotaryParameters(startAngleRadians, endAngleRadians, stopAtEnd);
    jenRotaryStart = startAngleRadians;
    jenRotaryEnd = endAngleRadians;
    calculateAngleBetweenMarks();
    setNumberPoint(numPoints);
    setLabelPositions();
}

float JenSlider::pointOnCircumfranceX (float originX, float radius, float angle)
{
    float x = originX + (radius * sin(angle));
    return x;
}

float JenSlider::pointOnCircumfranceY (float originY, float radius, float angle)
{
    float y = originY - (radius * cos(angle));
    return y;
}

void JenSlider::calculateAngleBetweenMarks(){
    //TODO: number of points could be come negative... does it matter??
    angelBetweenMarkersRadians = (jenRotaryEnd - jenRotaryStart)/(numPoints - 1);
}