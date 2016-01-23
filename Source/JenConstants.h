/*
  ==============================================================================

    Constants.h
    Created: 14 Jan 2016 3:01:35pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef JENCONSTANTS_H_INCLUDED
#define JENCONSTANTS_H_INCLUDED

namespace JenConstants{
    
    static double const AmpEnvMaxAttackTime = 3.66;
    static double const AmpEnvMaxDecayTime = 9.6;
    static double const AmpEnvMaxReleaseTime = 9.6;
    
    static double const FilterEnvMaxAttackTime = 3.66;
    static double const FilterEnvMaxDecayTime = 9.6;
    static double const FilterEnvMaxReleaseTime = 9.6;
    
    static double const GlideMaxTime = 1.5;
    
    static double const FilterCutOffMax = 0.6;
    static double const FilterCutOffMin = 0.03;
    
    static double const PulseWidthMax = 75.0; //in percent
    static double const PulseWidthMin = 15.0; //in percent
    static double const pulseWidthRange = PulseWidthMax - PulseWidthMin;
    
    static float const LfoMaxSpeed = 19.34995772f; //in Midi notes - is about 25hz
    static float const LfoMinSpeed = -60.37631656f; //in Midi notes - is about 0.25hz
    static float const LfoSpeedRange = LfoMaxSpeed - LfoMinSpeed;
    
    static double const VibratoMax = 0.6;
}



#endif  // CONSTANTS_H_INCLUDED
