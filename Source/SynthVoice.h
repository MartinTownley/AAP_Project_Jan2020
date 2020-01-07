/*==============================================================================

    SynthVoice.h
    Created: 2 Jan 2020 7:20:22pm
    Author:  sierra

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

#include "maximilian.h"


class SynthVoice : public SynthesiserVoice
{
public:
    
    
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        // Trying to cast the sound as the class SynthSound, if it's successful it'll return true.
        return dynamic_cast <SynthSound*> (sound) != nullptr;
    }
    //==========================================
    
    void getParam (float* ATTACK_ID, float* RELEASE_ID, float* HARMDIAL_ID, float* MODINDEX_ID, float* ONOFF_ID)
    {
        // get parameter from the slider and pass to the attack variable:
        env1.setAttack(int(*ATTACK_ID)); //cast as a float since envelope attack takes a double. or could just have it as a double in the plugineditor H
        env1.setRelease(int(*RELEASE_ID));
        
        // Harmonicity Radio
        harmRatio = (int(*HARMDIAL_ID));
        
        // Modulation Index
        modIndex = (double(*MODINDEX_ID));
        
        //boolean for modulator
        isModulator = (int(*ONOFF_ID));
        
        
        
    }
    
    //==========================================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        // Velocity will be a value between 0 and 1, instantiated when you press a key:
        
        env1.trigger = 1;
        
        level = velocity;
        
        carrierFreq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        
        std::cout << midiNoteNumber << std::endl;
        
        
    }
    
    //==========================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        //clearCurrentNote();
        //velocity = 0; //stop the note on key release
        
        // When we release a key, we want to be able to use that voice for the next key we press.
        // Allow tailOff boolean
        allowTailOff = true;
        
        
        env1.trigger = 0;
        
        if (velocity == 0)
        {clearCurrentNote();} // Unused voice can be allocated to next keypress
    }
    
    //==========================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    //==========================================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //==========================================
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
            // This gets called in the process block of PluginProcessor
        // This is where we'll put our audio callback.
        
        // Set arguments for envelope:
       
        // May not be best place to set these variables:
        //env1.setAttack(2000);
        env1.setDecay(500);
        env1.setSustain(0.8);
        
        
        
        mod1amp = 19;
        mod1freq = 2;
        
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            
            mod0freq = harmRatio * carrierFreq;
            //modIndex = mod1freq * mod1amp;
            mod0amp = mod0freq * modIndex;
            
            if(isModulator)
            {
                mod1wave = modulator1.phasor(mod1freq);
            } else {
                mod1wave = 1;
            }
            
            
           // = modulator1.phasor(mod1freq);
            
            double theWave = carrier.sinewave(carrierFreq
                                              + (modulator0.sinewave(mod0freq)
                                                 * (mod0amp * mod1wave)));
                                              
            double theSound = (env1.adsr(theWave, env1.trigger) * level);
            
            //double filteredSound = filter1.lores(theSound, 200, 0.1);
            
            // Iterate the channels
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, (theSound * 0.1)); //args: (destChannel, destSample, valueToAdd)
            }
            // Advance startSample after channel iterator:
            ++startSample;
        }
        
        
    }
    
    //==========================================
    
private:
    double level;
    double carrierFreq;
    double mod0freq;
    double mod0amp;
    double modIndex;
    double mod1amp;
    double mod1freq;
    int harmRatio;
    
               bool isModulator;
    double mod1wave;
    
    
    //Create an oscillator:
    maxiOsc carrier, modulator0, modulator1;
    
    
    
    maxiEnv env1;
    //maxiFilter filter1;
};