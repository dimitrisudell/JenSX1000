/*
  ==============================================================================

    Envelope.h
    Created: 5 Sep 2015 8:07:37pm
    Author:  Dimitri Sudell

  ==============================================================================
*/

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDED

class Envelope{
public:
    enum States{
        ATTACK, DECAY, SUSTAIN, RELEASE, OFF
    };
    
    Envelope(): currentAmplitude(minAmplitude), sustainAmplitude(minAmplitude) { updateState(OFF);};
    
    void begin() { updateState(ATTACK); currentAmplitude = minAmplitude;};
    
    void release() { updateState(RELEASE); };
    
    void setAttackTime(double aTime) {
        attackTime = aTime;
        attackIncrement = maxAmplitude/(attackTime + 1); //returns nan if divide by 0
        std::cout<< "attackTime: " << attackTime << "\n";
    };
    
    void setReleaseTime(double rTime) {
        jassert(sustainAmplitude >= 0);
        releaseTime = rTime;
        releaseIncrement = sustainAmplitude/(releaseTime + 1); //returns nan if divide by 0
        std::cout<< "releaseTime: " << releaseTime << "\n";
        std::cout<< "releaseIncrement: " << releaseIncrement << "\n";
    }
    
    void setDecayTime(double dTime) {
        jassert(sustainAmplitude >= 0);
        decayTime = dTime;
        decayIncrement = (maxAmplitude - sustainAmplitude) / (decayTime + 1); //returns nan if divide by 0
        std::cout<< "decayTime: " << decayTime << "\n";
    }
    
    void setSustainAmplitude(double sAmplitude){
        jassert((sAmplitude >= 0) && (sAmplitude <= 1));
        sustainAmplitude = sAmplitude;
        std::cout<< "sustainAmplitude: " << sustainAmplitude << "\n";
        setReleaseTime(releaseTime);
        setDecayTime(decayTime);
    }
    
    float getNextSample(){
        switch (state){
            case ATTACK:
                currentAmplitude += attackIncrement;
                if (currentAmplitude >= maxAmplitude) {currentAmplitude = maxAmplitude; updateState(DECAY);}
                break;
            case DECAY:
                currentAmplitude -= decayIncrement;
                if (currentAmplitude <= sustainAmplitude) {currentAmplitude = sustainAmplitude; updateState(SUSTAIN);}
                break;
            case SUSTAIN:
                break;
            case RELEASE:
                currentAmplitude -= releaseIncrement;
                if (currentAmplitude <= minAmplitude) {currentAmplitude = minAmplitude; updateState(OFF);}
            case OFF:
                break;
        }
        jassert((currentAmplitude >= 0) && (currentAmplitude <= 1));
        return currentAmplitude;
        
    };
    
private:
    States state;
    const float maxAmplitude = 1;
    const float minAmplitude = 0;
    float currentAmplitude;
    
    double attackTime;
    float attackIncrement;
    
    double decayTime;
    float decayIncrement;
    
    float sustainAmplitude;
    
    double releaseTime;
    float releaseIncrement;
    
    void updateState(States s){
        state = s;
        std::cout << "State Changed: " << state << "\n";
    }
    
};

#endif  // ENVELOPE_H_INCLUDED
