/*
  ==============================================================================

    ADSRData.h
    Created: 24 Jan 2022 5:36:10pm
    Author:  Jack Wardman

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRData : public ADSR {
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
private:
    ADSR adsr;
    ADSR::Parameters adsrParams;
    
};
