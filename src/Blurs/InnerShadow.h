/*
  ==============================================================================

    InnerShadow.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

#if USE_MELATONIN_BLUR
#include <melatonin_blur/melatonin_blur.h>
#endif

namespace imgfx
{

struct InnerShadow
{
    InnerShadow() = default;
    InnerShadow(juce::Colour shadowColour, int radius, juce::Point<int> offset) noexcept;
    ~InnerShadow() = default;

    void drawForImage(juce::Graphics &g, const juce::Image &srcImage) const;
    void drawForPath(juce::Graphics &g, const juce::Path &path);

    juce::Colour colour{0x90000000};
    int radius{4};
    juce::Point<int> offset;
    
#if USE_MELATONIN_BLUR
    melatonin::InnerShadow melatoninInnerShadow;
#endif

};

} // namespace imgfx
