/*
  ==============================================================================

    ObjectBlur.cpp
    Author:  migizo

  ==============================================================================
*/

#include "ObjectBlurEffect.h"

namespace imgfx
{

//==============================================================================
ObjectBlurEffect::ObjectBlurEffect() = default;
ObjectBlurEffect::~ObjectBlurEffect() = default;

void ObjectBlurEffect::setProperties(float newRadius)
{
    blur.setRadius(newRadius);
}

void ObjectBlurEffect::applyEffect (juce::Image& image, juce::Graphics& g, float scaleFactor, float alpha)
{
    blur.drawForImage(g, image);
}

} // imgfx
