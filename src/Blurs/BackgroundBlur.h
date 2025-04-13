/*
  ==============================================================================

    BackgroundBlurEffect.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

#if USE_MELATONIN_BLUR
#include <melatonin_blur/melatonin_blur.h>
#endif

#include "Blur.h"

namespace imgfx
{

struct BackgroundBlur
{
    BackgroundBlur() = default;
    BackgroundBlur(float newRadius) noexcept;
    ~BackgroundBlur() = default;

    void setRadius(float newRadius);
    
    void drawForImage(juce::Graphics &g, const juce::Image &bgImage, const juce::Image &maskImage);
    void drawForPath(juce::Graphics &g, const juce::Image &bgImage, const juce::Path &maskPath);

    Blur blur;
};

} // namespace imgfx
