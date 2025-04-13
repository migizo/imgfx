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

#include "../Utility/CachedComponentImage.h"
#include "../Utility/FxFunctions.h"
#include "BackgroundBlur.h"

namespace imgfx
{

  // createComponentSnapshot()では必ずpaint()処理が走り無限ループになるため、imageを取得できるようにしたCachedComponentImageを使用する。
  // NOTE: 親階層が変更された時などにおいてsetComponent()は呼び出し側で指定する。
  //       (このクラスでComponentListenerを継承してcomponentParentHierarchyChanged()を呼んでgetTopLevelComponent()をbackgroundComponentなどとして試したが
  //        DocumentWindow初期化においてこれが頻繁に呼ばれるため、不必要に呼ばれるのを避けるため呼び出し側で任意のタイミングで呼ぶようにした)
  class BackgroundBlurEffect
      : public juce::ImageEffectFilter
  {
  public:
    explicit BackgroundBlurEffect(juce::Component *owner);
    ~BackgroundBlurEffect() override;

    void setBackgroundCachedImage(CachedComponentImage *backgroundCachedImage);
    void setPathCallback(const std::function<juce::Path()> &);
    void setProperties(float newRadius, float newSourceAlpha, float newBrightness);
    void applyEffect(juce::Image &image, juce::Graphics &g, float scaleFactor, float alpha) override;

  private:
    juce::Component *ownerComponent = nullptr;
    juce::Component *cachedComponent = nullptr;
      CachedComponentImage *cachedImage = nullptr;
    juce::Path maskPath;
    std::function<juce::Path()> pathCallback = nullptr;
    BackgroundBlur bgBlur;
    float sourceAlpha = 0.0f;
    float brightness = 0.0f;

    JUCE_LEAK_DETECTOR(BackgroundBlurEffect)
  };

} // namespace imgfx
