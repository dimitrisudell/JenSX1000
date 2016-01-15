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
    
    static double const AmpEnvMaxAttackTime = 2;
    static double const AmpEnvMaxDecayTime = 2;
    static double const AmpEnvMaxReleaseTime = 2;
    
    static double const FilterEnvMaxAttackTime = 2;
    static double const FilterEnvMaxDecayTime = 2;
    static double const FilterEnvMaxReleaseTime = 2;
    
    static double const GlideMaxTime = 2;
    
    static double const FilterCutOffMax = 0.8;
    static double const FilterCutOffMin = 0.06;
    
}



#endif  // CONSTANTS_H_INCLUDED