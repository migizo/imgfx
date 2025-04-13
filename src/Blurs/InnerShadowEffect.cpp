/*
  ==============================================================================

    InnerShadowEffect.cpp
    Author:  migizo

  ==============================================================================
*/

#include "InnerShadowEffect.h"

namespace imgfx
{

//==============================================================================
InnerShadowEffect::InnerShadowEffect() = default;
InnerShadowEffect::~InnerShadowEffect() = default;

void InnerShadowEffect::setPathCallback(const std::function<juce::Path()>& newPathCallback)
{
    pathCallback = newPathCallback;
}

void InnerShadowEffect::setShadowProperties (const InnerShadow& newShadow)
{
    shadow = newShadow;
}

void InnerShadowEffect::applyEffect (juce::Image& image, juce::Graphics& g, float scaleFactor, float alpha)
{
    InnerShadow s (shadow);
    s.radius = juce::roundToInt((float) s.radius * scaleFactor);
    s.colour = s.colour.withMultipliedAlpha (alpha);
    s.offset.x = juce::roundToInt((float) s.offset.x * scaleFactor);
    s.offset.y = juce::roundToInt((float) s.offset.y * scaleFactor);

    g.setOpacity (alpha);
    g.drawImageAt(image, 0, 0);
    
    juce::Path maskPath;
    if (pathCallback) maskPath = pathCallback();
    if (maskPath.isEmpty() == false)
    {
        auto tmpPath = maskPath;
        tmpPath.applyTransform(juce::AffineTransform::scale(scaleFactor));
        s.drawForPath(g, tmpPath);
    }
    else
    {
        s.drawForImage(g, image);
    }
}

} // imgfx
