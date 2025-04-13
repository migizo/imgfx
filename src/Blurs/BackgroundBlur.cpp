
#include "BackgroundBlur.h"

namespace imgfx
{

//==============================================================================
BackgroundBlur::BackgroundBlur(float newRadius) noexcept
{
    setRadius(newRadius);
}

void BackgroundBlur::setRadius(float newRadius)
{
    blur.setRadius(newRadius);
}

void BackgroundBlur::drawForImage(juce::Graphics& g, const juce::Image& bgImage, const juce::Image& maskImage)
{
    g.reduceClipRegion(maskImage, {});
    blur.drawForImage(g, bgImage);
}

void BackgroundBlur::drawForPath(juce::Graphics& g, const juce::Image& bgImage, const juce::Path& maskPath) 
{
    g.reduceClipRegion(maskPath);
    blur.drawForImage(g, bgImage);
}

} // namespace imgfx
