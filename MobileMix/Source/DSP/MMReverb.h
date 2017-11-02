/*
  ==============================================================================

    Reverb.h
    Created: 2 Nov 2017 4:33:59pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

/** Built on JUCE's reverb, which in turn is built on FreeVerb (algorithms at
    least). */
class MMReverb :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        float roomSize; // 0.0 - 1.0
        float damping; // 0.0 - 1.0
        float width; // 0.0 - 1.0
        bool freeze;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    MMReverb() = default;
    ~MMReverb() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        reverb.setSampleRate(spec.sampleRate);
        updateParameters();
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        updateParameters();
        if (context.getInputBlock().getNumChannels() == 1)
            reverb.processMono(context.getOutputBlock().getChannelPointer(0), static_cast<int>(context.getOutputBlock().getNumSamples()));
        else if (context.getInputBlock().getNumChannels() == 1)
            reverb.processStereo(context.getOutputBlock().getChannelPointer(0), context.getOutputBlock().getChannelPointer(1), static_cast<int>(context.getOutputBlock().getNumSamples()));
    }

    void reset() noexcept override
    {
        reverb.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    void updateParameters()
    {
        Reverb::Parameters newParameters;
        newParameters.roomSize = params->roomSize;
        newParameters.damping = params->damping;
        newParameters.wetLevel = 1.0f;
        newParameters.dryLevel = 0.0f;
        newParameters.freezeMode = static_cast<float>(params->freeze);
        reverb.setParameters(newParameters);
    }

    Reverb reverb;

};
