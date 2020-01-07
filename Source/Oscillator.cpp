/*
  ==============================================================================

    Oscillator.cpp
    Created: 7 Jan 2020 2:01:14pm
    Author:  sierra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator()
{
    setSize(200, 200);
    
    oscMenu.addItem("OFF", 1);
    oscMenu.addItem("SINE", 2);
    oscMenu.addItem("SQUARE", 3);
    oscMenu.addItem("SAW", 4);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    oscMenu.setJustificationType(Justification::left);

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    
}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40); //shrinks in all directions by 40 pixels
    
    oscMenu.setBounds(area.removeFromTop(20));
    
    
}

void Oscillator::comboBoxChanged(ComboBox* box)
{
    //have to implement this function for it to work, but we're not going to be using it.
}