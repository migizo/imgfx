/*
  ==============================================================================

    Functions.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace imgfx
{

//! @brief juce::Imageに簡易的にエフェクト処理を行うための関数群。
struct FxFunctions
{
    FxFunctions() = delete;
    ~FxFunctions() = delete;

    static juce::Image invert(juce::Image &sourceImage);
    static juce::Image multiplyBrightness(juce::Image &sourceImage, float amount);
};

} // namespace imgfx
