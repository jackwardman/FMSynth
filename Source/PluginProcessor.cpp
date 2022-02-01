/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
BasicSynthAudioProcessor::BasicSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    
    synth.addSound(new SynthSound());
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
    synth.addVoice(new SynthVoice());

}

BasicSynthAudioProcessor::~BasicSynthAudioProcessor()
{
    
}

//==============================================================================
const juce::String BasicSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BasicSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BasicSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
    antiAlias.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    antiAlias.updateParameters(0, 20000, 1/(sqrt(2.0)));
}

void BasicSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BasicSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            auto& oscWaveType = *apvts.getRawParameterValue("osctype");
            auto& fmDepth = *apvts.getRawParameterValue("fmdepth");
            auto& fmFreq = *apvts.getRawParameterValue("fmfreq");
            auto& modOscWaveType = *apvts.getRawParameterValue("modosctype");
            
            auto& attack = *apvts.getRawParameterValue("attack");
            auto& decay = *apvts.getRawParameterValue("decay");
            auto& sustain = *apvts.getRawParameterValue("sustain");
            auto& release = *apvts.getRawParameterValue("release");

            // voice->updateFilter();
            auto& filterType = *apvts.getRawParameterValue("filtertype");
            auto& filterCutoff = *apvts.getRawParameterValue("filtercutoff");
            auto& filterRes = *apvts.getRawParameterValue("filterresonance");
            
            auto& modAttack = *apvts.getRawParameterValue("modattack");
            auto& modDecay = *apvts.getRawParameterValue("moddecay");
            auto& modSustain = *apvts.getRawParameterValue("modsustain");
            auto& modRelease = *apvts.getRawParameterValue("modrelease");
            
            // LFO
            voice->getOscillator().setWaveType(oscWaveType.load());
            voice->getOscillator().setFMParams(fmDepth, fmFreq, modOscWaveType);
            voice->getAdsr().updateADSR(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getModAdsr().updateADSR(modAttack.load(), modDecay.load(), modSustain.load(), modRelease.load());
            voice->updateFilterParams(filterType, filterCutoff, filterRes);
        }
    }
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    antiAlias.process(buffer);
}

//==============================================================================
bool BasicSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BasicSynthAudioProcessor::createEditor()
{
    return new BasicSynthAudioProcessorEditor (*this);
}

//==============================================================================
void BasicSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void BasicSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicSynthAudioProcessor();
}

AudioProcessorValueTreeState::ParameterLayout BasicSynthAudioProcessor::createParameters() {
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    // Osc select
    params.push_back(std::make_unique<AudioParameterChoice> ("osctype", "Oscillator Type", StringArray{ "Sine", "Saw", "Square" }, 0));
    
    params.push_back(std::make_unique<AudioParameterFloat> ("fmfreq", "FM Frequency", NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 0.f));
    params.push_back(std::make_unique<AudioParameterFloat> ("fmdepth", "FM Depth", NormalisableRange<float> { 0.0f, 1.0f }, 0.5f));
    
    params.push_back(std::make_unique<AudioParameterChoice> ("modosctype", " Mod Oscillator Type", StringArray{ "Sine", "Saw", "Square" }, 0));
    
    // ADSR - Volume
    params.push_back(std::make_unique<AudioParameterFloat> ("attack", "Attack", NormalisableRange<float> { 0.0f, 1.0f }, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat> ("decay", "Decay", NormalisableRange<float> { 0.0f, 1.0f }, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat> ("sustain", "Sustain", NormalisableRange<float> { 0.0f, 1.0f }, 1.0f));
    params.push_back(std::make_unique<AudioParameterFloat> ("release", "Release", NormalisableRange<float> { 0.0f, 3.0f }, 0.4f));
    
    // Filter
    params.push_back(std::make_unique<AudioParameterChoice> ("filtertype", "Filter Type", StringArray{ "Lowpass", "Bandpass", "Highpass" }, 0));
    params.push_back(std::make_unique<AudioParameterFloat> ("filtercutoff", "Filter Cutoff", NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 500.0f));
    params.push_back(std::make_unique<AudioParameterFloat> ("filterresonance", "Filter Resonance", NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f/(sqrt(2.0f))));
    
    // ADSR - Filter
    params.push_back(std::make_unique<AudioParameterFloat> ("modattack", "Mod Attack", NormalisableRange<float> { 0.0f, 1.0f }, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat> ("moddecay", "Mod Decay", NormalisableRange<float> { 0.0f, 1.0f }, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat> ("modsustain", "Mod Sustain", NormalisableRange<float> { 0.0f, 1.0f }, 1.0f));
    params.push_back(std::make_unique<AudioParameterFloat> ("modrelease", "Mod Release", NormalisableRange<float> { 0.0f, 3.0f }, 0.4f));

    return { params.begin(), params.end() };
}
