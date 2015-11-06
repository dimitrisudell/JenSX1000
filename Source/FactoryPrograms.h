/*
  ==============================================================================

    FactoryPrograms.h
    Created: 23 Oct 2015 6:15:35pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef FACTORYPROGRAMS_H_INCLUDED
#define FACTORYPROGRAMS_H_INCLUDED

class Program{
public:
    
    Program(String name) : programName(name) {};
    
    float vcoTune, vcoOctave, vcoVibrato, vcoWaveform, vcoPulseWidth, vcoPWM, vcoLevel, vcoGlide, lfoSpeed, vcfFrequency, vcfResonance, vcfLFO, vcfEnvLevel, vcfAttack, vcfDecay, vcfSustain, vcfRelease, noiseNoise, noiseLevel, vcaOutputVolume, vcaAttack, vcaDecay, vcaSustain, vcaRelease = 0.0;
    
    String programName;
    
    XmlElement getProgrameAsXmlElement(){
        
        XmlElement xml ("JEN1000PROGRAM");
        
        xml.setAttribute("Name", programName);
        xml.setAttribute("vcoTune", vcoTune);
        xml.setAttribute("vcoOctave", vcoOctave);
        xml.setAttribute("vcoVibrato", vcoVibrato);
        xml.setAttribute("vcoWaveform", vcoWaveform);
        xml.setAttribute("vcoPulseWidth", vcoPulseWidth);
        xml.setAttribute("vcoPWM", vcoPWM);
        xml.setAttribute("vcoLevel", vcoLevel);
        xml.setAttribute("vcoGlide", vcoGlide);
    
        //------- LFO --------------------------------------------------------------
        xml.setAttribute("lfoSpeed", lfoSpeed);
    
        //------- VCF --------------------------------------------------------------
        xml.setAttribute("vcfFrequency", vcfFrequency);
        xml.setAttribute("vcfResonance", vcfResonance);
        xml.setAttribute("vcfLFO", vcfLFO);
        xml.setAttribute("vcfEnvLevel", vcfEnvLevel);
        xml.setAttribute("vcfAttack", vcfAttack);
        xml.setAttribute("vcfDecay", vcfDecay);
        xml.setAttribute("vcfSustain", vcfSustain);
        xml.setAttribute("vcfRelease", vcfRelease);
    
        //------- Noise ------------------------------------------------------------
        xml.setAttribute("noiseNoise", noiseNoise);
        xml.setAttribute("noiseLevel", noiseLevel);
    
        //------- VCA --------------------------------------------------------------
        xml.setAttribute("vcaOutput", vcaOutputVolume);
        xml.setAttribute("vcaAttack", vcaAttack);
        xml.setAttribute("vcaDecay", vcaDecay);
        xml.setAttribute("vcaSustain", vcaSustain);
        xml.setAttribute("vcaRelease", vcaRelease);
        
        return xml;
    }
    
    void setProgramFromXml(ScopedPointer<XmlElement> xml){
        if (xml != nullptr)
        {
            // make sure that it's actually our type of XML object..
            if (xml->hasTagName ("JEN1000PROGRAM"))
            {
                vcoTune = ((float) xml->getDoubleAttribute ("vcoTune", 0.5));
                vcoOctave =((float) xml->getDoubleAttribute ("vcoOctave", 0));
                vcoVibrato = ((float) xml->getDoubleAttribute ("vcoVibrato", 0));
                vcoWaveform = ((float) xml->getDoubleAttribute ("vcoWaveform", 0));
                vcoPulseWidth = ((float) xml->getDoubleAttribute ("vcoPulseWidth", 0));
                vcoPWM = ((float) xml->getDoubleAttribute ("vcoPWM", 0));
                vcoLevel = ((float) xml->getDoubleAttribute ("vcoLevel", 0));
                vcoGlide = ((float) xml->getDoubleAttribute ("vcoGlide", 0));
                lfoSpeed = ((float) xml->getDoubleAttribute ("lfoSpeed", 0));
                vcfFrequency = ((float) xml->getDoubleAttribute ("vcfFrequency", 0));
                vcfResonance = ((float) xml->getDoubleAttribute ("vcfResonance", 0));
                vcfLFO = ((float) xml->getDoubleAttribute ("vcfLFO", 0));
                vcfEnvLevel = ((float) xml->getDoubleAttribute ("vcfEnvLevel", 0));
                vcfAttack = ((float) xml->getDoubleAttribute ("vcfAttack", 0));
                vcfDecay =((float) xml->getDoubleAttribute ("vcfDecay", 0));
                vcfSustain = ((float) xml->getDoubleAttribute ("vcfSustain", 0));
                vcfRelease = ((float) xml->getDoubleAttribute ("vcfRelease", 0));
                noiseNoise = ((float) xml->getDoubleAttribute ("noiseNoise", 0));
                noiseLevel = ((float) xml->getDoubleAttribute ("noiseLevel", 0));
                vcaOutputVolume = ((float) xml->getDoubleAttribute ("vcaOutput", 0));
                vcaAttack = ((float) xml->getDoubleAttribute ("vcaAttack", 0));
                vcaDecay = ((float) xml->getDoubleAttribute ("vcaDecay", 0));
                vcaSustain = ((float) xml->getDoubleAttribute ("vcaSustain", 0));
                vcaRelease = ((float) xml->getDoubleAttribute ("vcaRelease", 0));
            }
        }
    }
                         
};

class FactoryPrograms{
public:
    enum Programs{
        PIANO, FLUTE, HUMAN_VOICE_1, HUMAN_VOICE_2, SYNTHESIZER, ELECTRONIC_DRUM, HAMMOND_ORGAN_1, HAMMOND_ORGAN_2, VIOLIN, CELLO, BRASS_1, BRASS_2, FACTORY_PROGRAMS_COUNT
    };

    FactoryPrograms(){
        piano.vcoTune = 0.5; piano.vcoOctave = 0.0; piano.vcoVibrato = 0.0; piano.vcoWaveform = 1.0; piano.vcoPulseWidth = 0.778; piano.vcoPWM = 0.4; piano.vcoLevel = 1.0; piano.vcoGlide = 0.0; piano.lfoSpeed = 0.0; piano.vcfFrequency = 0.5; piano.vcfResonance = 0.1; piano.vcfLFO = 0.0; piano.vcfEnvLevel = 0.5; piano.vcfAttack = 0.0; piano.vcfDecay = 0.5; piano.vcfSustain = 0.0; piano.vcfRelease = 0.1; piano.noiseNoise = 0.0; piano.noiseLevel = 0.0; piano.vcaOutputVolume = 0.3; piano.vcaAttack = 0.0; piano.vcaDecay = 0.6; piano.vcaSustain = 0.25; piano.vcaRelease = 0.4;
        
        flute.vcoTune = 0.5; flute.vcoOctave = 0.67; flute.vcoVibrato = 0.15; flute.vcoWaveform = 0.5; flute.vcoPulseWidth = 0.0; flute.vcoPWM = 0.0; flute.vcoLevel = 1.0; flute.vcoGlide = 0.4; flute.lfoSpeed = 0.6; flute.vcfFrequency = 0.3; flute.vcfResonance = 0.25; flute.vcfLFO = 0.15; flute.vcfEnvLevel = 0.0; flute.vcfAttack = 0.0; flute.vcfDecay = 0.0; flute.vcfSustain = 0.0; flute.vcfRelease = 0.0; flute.noiseNoise = 0.0; flute.noiseLevel = 0.0; flute.vcaOutputVolume = 0.3; flute.vcaAttack = 0.2; flute.vcaDecay = 0.0; flute.vcaSustain = 1.0; flute.vcaRelease = 0.2;
        
        humanVoice1.vcoTune = 0.5; humanVoice1.vcoOctave = 0.67; humanVoice1.vcoVibrato = 0.48; humanVoice1.vcoWaveform = 1.0; humanVoice1.vcoPulseWidth = 0.61; humanVoice1.vcoPWM = 0.8; humanVoice1.vcoLevel = 1.0; humanVoice1.vcoGlide = 0.62; humanVoice1.lfoSpeed = 0.6; humanVoice1.vcfFrequency = 0.52; humanVoice1.vcfResonance = 0.52; humanVoice1.vcfLFO = 0.0; humanVoice1.vcfEnvLevel = 0.0; humanVoice1.vcfAttack = 0.0; humanVoice1.vcfDecay = 0.0; humanVoice1.vcfSustain = 0.0; humanVoice1.vcfRelease = 0.0; humanVoice1.noiseNoise = 0.0; humanVoice1.noiseLevel = 0.0; humanVoice1.vcaOutputVolume = 0.55; humanVoice1.vcaAttack = 0.62; humanVoice1.vcaDecay = 0.0; humanVoice1.vcaSustain = 1.0; humanVoice1.vcaRelease = 0.375;
        
        humanVoice2.vcoTune = 0.5; humanVoice2.vcoOctave = 0.67; humanVoice2.vcoVibrato = 0.48; humanVoice2.vcoWaveform = 0.0; humanVoice2.vcoPulseWidth = 0.61; humanVoice2.vcoPWM = 0.8; humanVoice2.vcoLevel = 1.0; humanVoice2.vcoGlide = 0.62; humanVoice2.lfoSpeed = 0.6; humanVoice2.vcfFrequency = 0.52; humanVoice2.vcfResonance = 0.52; humanVoice2.vcfLFO = 0.0; humanVoice2.vcfEnvLevel = 0.0; humanVoice2.vcfAttack = 0.0; humanVoice2.vcfDecay = 0.0; humanVoice2.vcfSustain = 0.0; humanVoice2.vcfRelease = 0.0; humanVoice2.noiseNoise = 0.0; humanVoice2.noiseLevel = 0.0; humanVoice2.vcaOutputVolume = 0.55; humanVoice2.vcaAttack = 0.62; humanVoice2.vcaDecay = 0.0; humanVoice2.vcaSustain = 1.0; humanVoice2.vcaRelease = 0.375;
        
        synthesizer.vcoTune = 0.5; synthesizer.vcoOctave = 0.0; synthesizer.vcoVibrato = 0.65; synthesizer.vcoWaveform = 1.0; synthesizer.vcoPulseWidth = 1.0; synthesizer.vcoPWM = 0.65; synthesizer.vcoLevel = 1.0; synthesizer.vcoGlide = 0.0; synthesizer.lfoSpeed = 0.65; synthesizer.vcfFrequency = 0.0; synthesizer.vcfResonance = 0.45; synthesizer.vcfLFO = 0.5; synthesizer.vcfEnvLevel = 1.0; synthesizer.vcfAttack = 0.0; synthesizer.vcfDecay = 0.5; synthesizer.vcfSustain = 0.0; synthesizer.vcfRelease = 0.6; synthesizer.noiseNoise = 0.0; synthesizer.noiseLevel = 0.0; synthesizer.vcaOutputVolume = 0.3; synthesizer.vcaAttack = 0.0; synthesizer.vcaDecay = 0.5; synthesizer.vcaSustain = 1.0; synthesizer.vcaRelease = 1.0;
        
        electronicDrum.vcoTune = 0.5; electronicDrum.vcoOctave = 0.0; electronicDrum.vcoVibrato = 0.0; electronicDrum.vcoWaveform = 0.0; electronicDrum.vcoPulseWidth = 0.0; electronicDrum.vcoPWM = 0.0; electronicDrum.vcoLevel = 0.0; electronicDrum.vcoGlide = 0.0; electronicDrum.lfoSpeed = 0.0; electronicDrum.vcfFrequency = 0.0; electronicDrum.vcfResonance = 1.0; electronicDrum.vcfLFO = 0.0; electronicDrum.vcfEnvLevel = 0.5; electronicDrum.vcfAttack = 0.0; electronicDrum.vcfDecay = 0.5; electronicDrum.vcfSustain = 0.0; electronicDrum.vcfRelease = 0.0; electronicDrum.noiseNoise = 0.0; electronicDrum.noiseLevel = 0.0; electronicDrum.vcaOutputVolume = 0.3; electronicDrum.vcaAttack = 0.0; electronicDrum.vcaDecay = 0.5; electronicDrum.vcaSustain = 0.0; electronicDrum.vcaRelease = 0.0;
        
        hammondOrgan1.vcoTune = 0.5; hammondOrgan1.vcoOctave = 0.34; hammondOrgan1.vcoVibrato = 0.32; hammondOrgan1.vcoWaveform = 0.0; hammondOrgan1.vcoPulseWidth = 0.0; hammondOrgan1.vcoPWM = 0.0; hammondOrgan1.vcoLevel = 1.0; hammondOrgan1.vcoGlide = 0.0; hammondOrgan1.lfoSpeed = 0.55; hammondOrgan1.vcfFrequency = 0.42; hammondOrgan1.vcfResonance = 0.575; hammondOrgan1.vcfLFO = 0.0; hammondOrgan1.vcfEnvLevel = 0.65; hammondOrgan1.vcfAttack = 0.0; hammondOrgan1.vcfDecay = 0.0; hammondOrgan1.vcfSustain = 0.2; hammondOrgan1.vcfRelease = 0.275; hammondOrgan1.noiseNoise = 0.0; hammondOrgan1.noiseLevel = 0.0; hammondOrgan1.vcaOutputVolume = 0.7; hammondOrgan1.vcaAttack = 0.0; hammondOrgan1.vcaDecay = 0.0; hammondOrgan1.vcaSustain = 0.8; hammondOrgan1.vcaRelease = 0.0;
        
        hammondOrgan2.vcoTune = 0.5; hammondOrgan2.vcoOctave = 0.34; hammondOrgan2.vcoVibrato = 0.32; hammondOrgan2.vcoWaveform = 1.0; hammondOrgan2.vcoPulseWidth = 0.0; hammondOrgan2.vcoPWM = 0.0; hammondOrgan2.vcoLevel = 1.0; hammondOrgan2.vcoGlide = 0.0; hammondOrgan2.lfoSpeed = 0.65; hammondOrgan2.vcfFrequency = 0.55; hammondOrgan2.vcfResonance = 0.575; hammondOrgan2.vcfLFO = 0.0; hammondOrgan2.vcfEnvLevel = 0.65; hammondOrgan2.vcfAttack = 0.0; hammondOrgan2.vcfDecay = 0.0; hammondOrgan2.vcfSustain = 0.4; hammondOrgan2.vcfRelease = 0.275; hammondOrgan2.noiseNoise = 0.0; hammondOrgan2.noiseLevel = 0.0; hammondOrgan2.vcaOutputVolume = 0.7; hammondOrgan2.vcaAttack = 0.0; hammondOrgan2.vcaDecay = 0.0; hammondOrgan2.vcaSustain = 0.8; hammondOrgan2.vcaRelease = 0.0;
        
        violin.vcoTune = 0.5; violin.vcoOctave = 1.0; violin.vcoVibrato = 0.2; violin.vcoWaveform = 0.0; violin.vcoPulseWidth = 0.0; violin.vcoPWM = 0.0; violin.vcoLevel = 1.0; violin.vcoGlide = 0.3; violin.lfoSpeed = 0.65; violin.vcfFrequency = 0.75; violin.vcfResonance = 0.0; violin.vcfLFO = 0.0; violin.vcfEnvLevel = 0.0; violin.vcfAttack = 0.0; violin.vcfDecay = 0.0; violin.vcfSustain = 0.0; violin.vcfRelease = 0.0; violin.noiseNoise = 0.0; violin.noiseLevel = 0.0; violin.vcaOutputVolume = 0.68; violin.vcaAttack = 0.52; violin.vcaDecay = 0.52; violin.vcaSustain = 0.6; violin.vcaRelease = 0.1;
        
        cello.vcoTune = 0.5; cello.vcoOctave = 0.34; cello.vcoVibrato = 0.2; cello.vcoWaveform = 0.0; cello.vcoPulseWidth = 0.0; cello.vcoPWM = 0.0; cello.vcoLevel = 1.0; cello.vcoGlide = 0.3; cello.lfoSpeed = 0.65; cello.vcfFrequency = 0.75; cello.vcfResonance = 0.0; cello.vcfLFO = 0.0; cello.vcfEnvLevel = 0.0; cello.vcfAttack = 0.0; cello.vcfDecay = 0.0; cello.vcfSustain = 0.0; cello.vcfRelease = 0.0; cello.noiseNoise = 0.0; cello.noiseLevel = 0.0; cello.vcaOutputVolume = 0.68; cello.vcaAttack = 0.52; cello.vcaDecay = 0.52; cello.vcaSustain = 0.6; cello.vcaRelease = 0.1;
        
        brass1.vcoTune = 0.5; brass1.vcoOctave = 0.34; brass1.vcoVibrato = 0.05; brass1.vcoWaveform = 0.0; brass1.vcoPulseWidth = 0.0; brass1.vcoPWM = 0.0; brass1.vcoLevel = 1.0; brass1.vcoGlide = 0.0; brass1.lfoSpeed = 0.6; brass1.vcfFrequency = 0.48; brass1.vcfResonance = 0.0; brass1.vcfLFO = 0.0; brass1.vcfEnvLevel = 0.78; brass1.vcfAttack = 0.32; brass1.vcfDecay = 0.3; brass1.vcfSustain = 0.32; brass1.vcfRelease = 0.0; brass1.noiseNoise = 0.0; brass1.noiseLevel = 0.0; brass1.vcaOutputVolume = 0.62; brass1.vcaAttack = 0.2; brass1.vcaDecay = 0.52; brass1.vcaSustain = 0.52; brass1.vcaRelease = 0.12;
        
        brass2.vcoTune = 0.5; brass2.vcoOctave = 0.67; brass2.vcoVibrato = 0.05; brass2.vcoWaveform = 0.0; brass2.vcoPulseWidth = 0.0; brass2.vcoPWM = 0.0; brass2.vcoLevel = 1.0; brass2.vcoGlide = 0.0; brass2.lfoSpeed = 0.6; brass2.vcfFrequency = 0.3; brass2.vcfResonance = 0.1; brass2.vcfLFO = 0.0; brass2.vcfEnvLevel = 1.0; brass2.vcfAttack = 0.32; brass2.vcfDecay = 0.3; brass2.vcfSustain = 0.32; brass2.vcfRelease = 0.0; brass2.noiseNoise = 0.0; brass2.noiseLevel = 0.0; brass2.vcaOutputVolume = 0.62; brass2.vcaAttack = 0.2; brass2.vcaDecay = 0.52; brass2.vcaSustain = 0.52; brass2.vcaRelease = 0.2;
        
    }
    
    Program* getProgramPointer(Programs p){
        switch (p) {
            case PIANO:
                return &piano;
            case FLUTE:
                return &flute;
            case HUMAN_VOICE_1:
                return &humanVoice1;
            case HUMAN_VOICE_2:
                return &humanVoice2;
            case SYNTHESIZER:
                return &synthesizer;
            case ELECTRONIC_DRUM:
                return &electronicDrum;
            case HAMMOND_ORGAN_1:
                return &hammondOrgan1;
            case HAMMOND_ORGAN_2:
                return &hammondOrgan2;
            case VIOLIN:
                return &violin;
            case CELLO:
                return &cello;
            case BRASS_1:
                return &brass1;
            case BRASS_2:
                return &brass2;
            default:
                return &piano;
        }
    }
    
private:
    Program piano{"Piano"}, flute{"Flute"}, humanVoice1{"Human Voice 1"}, humanVoice2{"Human Voice 2"}, synthesizer{"Synthesizer"}, electronicDrum{"Electronic Drum"}, hammondOrgan1{"Hammond Organ 1"}, hammondOrgan2{"Hammond Organ 2"}, violin{"Violin"}, cello{"Cello"}, brass1{"Brass 1"}, brass2{"Brass 2"};
    
};



#endif  // FACTORYPROGRAMS_H_INCLUDED
