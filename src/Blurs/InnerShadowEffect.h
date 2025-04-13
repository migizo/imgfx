/*
  ==============================================================================

    InnerShadowEffect.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

#if USE_MELATONIN_BLUR
#include <melatonin_blur/melatonin_blur.h>
#endif

#include "InnerShadow.h"
#include "../Utility/FxFunctions.h"

namespace imgfx
{

/**
 @brief inner-shadowを付与するImageEffectFilter
*/
class InnerShadowEffect
  : public juce::ImageEffectFilter
{
public:
    InnerShadowEffect();
    ~InnerShadowEffect() override;

    //! @brief juce::Component::resized()が呼ばれることを想定して影の範囲を表すpathを返すstd::functionを指定する
    void setPathCallback(const std::function<juce::Path()>&);
    
    void setShadowProperties(const InnerShadow &newShadow);
    void applyEffect(juce::Image &image, juce::Graphics &g, float scaleFactor, float alpha) override;

private:
    InnerShadow shadow;
    juce::Path maskPath;
    std::function<juce::Path()> pathCallback = nullptr;

    JUCE_LEAK_DETECTOR(InnerShadowEffect)
};

} // imgfx
