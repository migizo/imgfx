/*
  ==============================================================================

    Functions.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include "FxFunctions.h"

namespace imgfx
{

//==============================================================================
juce::Image FxFunctions::invert(juce::Image &sourceImage)
{
    auto img = sourceImage.createCopy();
    auto format = img.getFormat();
        
    int numValues = 0;
    if (format == juce::Image::ARGB) numValues = 4;
    else if (format == juce::Image::RGB) numValues = 3;
    else if (format == juce::Image::SingleChannel) numValues = 1;
    jassert(numValues > 0);

    const bool usingAlpha = (numValues == 4);
    const int numColor = std::min(numValues, 3);
    
    // setPixelAt(getPixelAt())は遅いためjuce::Image::BitmapDataを使う方が良い
    juce::Image::BitmapData inBmp(sourceImage, juce::Image::BitmapData::readOnly);
    juce::Image::BitmapData outBmp(img, juce::Image::BitmapData::writeOnly);
    for (int y = 0; y < img.getHeight(); y++)
    {
        auto inLinePtr = inBmp.getLinePointer(y);
        auto outLinePtr = outBmp.getLinePointer(y);
        for (int x = 0; x < img.getWidth(); x++)
        {
            const int offset = x * numValues;
            for (int i = 0; i < numColor; i++)
            {
                outLinePtr[offset + i] = 255 - inLinePtr[offset + i];
            }
            if (usingAlpha)
            {
                outLinePtr[offset + numColor] = inLinePtr[offset + numColor];
            }
        }
    }
    
    return img;
}

//==============================================================================
juce::Image FxFunctions::multiplyBrightness(juce::Image &sourceImage, float amount)
{
    if (amount == 1)
        return sourceImage;

    auto img = sourceImage.createCopy();
    auto format = img.getFormat();
      
    int numValues = 0;
    if (format == juce::Image::ARGB) numValues = 4;
    else if (format == juce::Image::RGB) numValues = 3;
    else if (format == juce::Image::SingleChannel) numValues = 1;
    jassert(numValues > 0);

    const bool usingAlpha = (numValues == 4);
    const int numColor = std::min(numValues, 3);
    
    // setPixelAt(getPixelAt())は遅いためjuce::Image::BitmapDataを使う方が良い
    juce::Image::BitmapData inBmp(sourceImage, juce::Image::BitmapData::readOnly);
    juce::Image::BitmapData outBmp(img, juce::Image::BitmapData::writeOnly);
    for (int y = 0; y < img.getHeight(); y++)
    {
        auto inLinePtr = inBmp.getLinePointer(y);
        auto outLinePtr = outBmp.getLinePointer(y);
        for (int x = 0; x < img.getWidth(); x++)
        {
            const int offset = x * numValues;
            for (int i = 0; i < numColor; i++)
            {
                int c = (float)inLinePtr[offset + i] * amount;
                outLinePtr[offset + i] = juce::jlimit<int>(0, 255, c);
            }
            if (usingAlpha)
            {
                outLinePtr[offset + numColor] = inLinePtr[offset + numColor];
            }
        }
    }

    return img;
  }

} // namespace imgfx
