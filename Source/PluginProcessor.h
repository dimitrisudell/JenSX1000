/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <set>

#include "../JuceLibraryCode/JuceHeader.h"
#include "PolyBlepOscillator.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "FreqControl.h"
#include "NoiseGen.h"
#include "EqControl.h"
#include "FactoryPrograms.h"
#include "NoClick.h"

#include "TestsHeader.h"


//==============================================================================
/**
*/
class JenSx1000AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JenSx1000AudioProcessor();
    ~JenSx1000AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    void parameterChange(AudioProcessorParameter*, float newValue);

    //==============================================================================
    const String getName() const override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    void setProgram(Program*);
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    PolyBlepOscillator oscillator;
    Oscillator lfo;
    FreqControl freqControl;
    Envelope ampEnvelope;
    NoiseGen noise;
    EqControl vcf;
    
    double currentSampleRate;
    float ampLevel;
    float vcoLevel = 0;
    float noiseLevel = 0;
    float masterCutoff = 0;
    
    
    //------- Parameters -----------------------------------------------------------
    
    AudioProcessorParameter* vcoTuneParam;
    AudioProcessorParameter* vcoOctaveParam;
    AudioProcessorParameter* vcoVibratoParam;
    AudioProcessorParameter* vcoWaveformParam;
    AudioProcessorParameter* vcoPulseWidthParam;
    AudioProcessorParameter* vcoPWMParam;
    AudioProcessorParameter* vcoLevelParam;
    AudioProcessorParameter* vcoGlideParam;
    
    AudioProcessorParameter* lfoSpeedParam;
    
    AudioProcessorParameter* vcfFrequencyParam;
    AudioProcessorParameter* vcfResonanceParam;
    AudioProcessorParameter* vcfLFOParam;
    AudioProcessorParameter* vcfEnvLevelParam;
    AudioProcessorParameter* vcfAttackParam;
    AudioProcessorParameter* vcfDecayParam;
    AudioProcessorParameter* vcfSustainParam;
    AudioProcessorParameter* vcfReleaseParam;
    
    AudioProcessorParameter* noiseNoiseParam;
    AudioProcessorParameter* noiseLevelParam;
    
    AudioProcessorParameter* vcaOutputVolumeParam;
    AudioProcessorParameter* vcaAttackParam;
    AudioProcessorParameter* vcaDecayParam;
    AudioProcessorParameter* vcaSustainParam;
    AudioProcessorParameter* vcaReleaseParam;
    
    
private:
    //==============================================================================
    
    FactoryPrograms programs;
    int currentProgram;
    
    std::set<int> heldNotes;
    
    int currentNote, nextNote;
    
    NoClick noClick;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JenSx1000AudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
