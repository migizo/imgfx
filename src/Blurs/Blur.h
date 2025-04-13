/*
  ==============================================================================

    Blur.h
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

struct Blur
{
    Blur() = default;
    Blur(int r) noexcept;
    ~Blur() = default;
    
    void setRadius(float r);
    
    void drawForImage(juce::Graphics& g, const juce::Image& srcImage);

#if USE_MELATONIN_BLUR
private:
    std::shared_ptr<melatonin::CachedBlur> melatoninBlur;
#else
    int radius = 4;
#endif

};

} // namespace imgfx
