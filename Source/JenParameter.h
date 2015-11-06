/*
  ==============================================================================

    jenParameter.h
    Created: 10 Sep 2015 1:40:11pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef JENPARAMETER_H_INCLUDED
#define JENPARAMETER_H_INCLUDED

#include <stdlib.h>

#include "JuceHeader.h"
#include "PluginProcessor.h"

class JenParameter: public AudioProcessorParameter{
public:
    
    JenParameter(JenSx1000AudioProcessor& p, String name, float defaultParamValue, int steps = AudioProcessor::getDefaultNumParameterSteps()) :
    parent(p),
    defaultValue(defaultParamValue),
    currentValue(defaultParamValue),
    paramName(name),
    paramLabel(""),
    numSteps(steps)
    {};
    
    float getValue() const override { return currentValue; };
    
    void setValue(float newValue) override { currentValue = newValue; parent.parameterChange(this, newValue);};
    
    float getDefaultValue() const override { return defaultValue; };
    
    String getName(int maximumStringLength) const override {return truncateString(paramName, maximumStringLength);};
    
    String getLabel() const override {return paramLabel; };
    
    float getValueForText (const String& text) const override { return text.getFloatValue(); };
    
    int getNumSteps() const override{
        return numSteps;
    }
    
private:
    JenSx1000AudioProcessor& parent;
    float defaultValue;
    float currentValue;
    String const paramName;
    String const paramLabel;
    int const numSteps;
    
    
    String truncateString(String str, int length, bool showElipse = true) const{
        if (str.length() > length){
            if (showElipse){
                return str.substring(0, length - 4) + "...";
            }
            else {
                return str.substring(0, length - 1);
            }
        }
        return str;
    }
};



#endif  // JENPARAMETER_H_INCLUDED
