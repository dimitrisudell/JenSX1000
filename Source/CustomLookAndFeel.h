/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 27 Oct 2015 4:00:47pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef CUSTOMLOOKANDFEEL_H_INCLUDED
#define CUSTOMLOOKANDFEEL_H_INCLUDED

class CustomLookAndFeel : public LookAndFeel_V3{
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        const float radius = jmin (width / 2, height / 2) - 2.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
        
        const float coloredCentreEllipseRadius = radius * 0.6f;
        const float coloredCentreEllipseX = centreX - coloredCentreEllipseRadius;
        const float coloredCentreEllipseY = centreY - coloredCentreEllipseRadius;
        const float coloredCentreEllipseDiameter = coloredCentreEllipseRadius * 2.0f;
        
        g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        Path knobCentre;
        knobCentre.addEllipse (coloredCentreEllipseX, coloredCentreEllipseY, coloredCentreEllipseDiameter, coloredCentreEllipseDiameter);
        g.fillPath (knobCentre);
        
        g.setColour(Colours::white);
        
        const float movingElipsePathRadius = radius * 0.85f;
        const float movingElipseRadius = radius * 0.15f;
        const float movingElipseDiameter = movingElipseRadius * 2.0f;
        
        Path outerCircle;
        
        outerCircle.addEllipse( - movingElipseRadius, - movingElipsePathRadius - movingElipseRadius, movingElipseDiameter, movingElipseDiameter);
        
        g.fillPath (outerCircle, AffineTransform::rotation (angle).translated (centreX, centreY));
        /*
        if (radius > 12.0f)
        {
            if (slider.isEnabled())
                g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
            else
                g.setColour (Colour (0x80808080));
            
            const float thickness = 0.7f;
            
            //colored arc
            {
                Path filledArc;
                filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
                g.fillPath (filledArc);
            }
            
            //rotating part
            {
                const float innerRadius = radius * 0.2f;
                Path p;
                p.addTriangle (-innerRadius, 0.0f,
                               0.0f, -radius * thickness * 1.1f,
                               innerRadius, 0.0f);
                
                p.addEllipse (-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);
                
                g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
            }
            
            if (slider.isEnabled())
                g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
            else
                g.setColour (Colour (0x80808080));
            
            //arc outline
            Path outlineArc;
            outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
            outlineArc.closeSubPath();
            
            g.strokePath (outlineArc, PathStrokeType (slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
        }
        else
        {
            if (slider.isEnabled())
                g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
            else
                g.setColour (Colour (0x80808080));
            
            Path p;
            p.addEllipse (-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
            PathStrokeType (rw * 0.1f).createStrokedPath (p, p);
            
            p.addLineSegment (Line<float> (0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);
            
            g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
        }
         */
    }
};



#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
