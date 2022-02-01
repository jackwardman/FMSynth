/*
  ==============================================================================

    ADSRData.cpp
    Created: 24 Jan 2022 5:36:10pm
    Author:  Jack Wardman

  ==============================================================================
*/

#include "ADSRData.h"

void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters(adsrParams);
}
