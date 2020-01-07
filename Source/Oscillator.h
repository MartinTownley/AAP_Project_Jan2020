/*
  ==============================================================================

    Oscillator.h
    Created: 7 Jan 2020 2:01:14pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Oscillator    : public Component,
                        private ComboBox::Listener
{
public:
    Oscillator();
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged (ComboBox*) override;

private:
    ComboBox oscMenu;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};