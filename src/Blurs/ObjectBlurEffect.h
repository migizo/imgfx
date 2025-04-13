/*
  ==============================================================================

    ObjectBlurEffect.h
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

/**
 object-blurを付与するImageEffectFilter
 入力画像にブラーを適用するがjuce::DropShadowEffectと同様、radius分周囲にフェード区間が描画されるため、入力画像より広い範囲で描画される可能性がある。
 そのためjuce::Componentなどにセットする場合は、コンポーネント領域よりradius分小さい領域で描画すると正しく描画される。
 (radius分小さい領域で描画しない場合はフェード区間がクリップされたような表示になります。)
 juce::Component::setPaintingIsUnclipped()を使用すれば領域外も描画されるかもしれない
 */
class ObjectBlurEffect
: public juce::ImageEffectFilter
{
public:
    ObjectBlurEffect();
    ~ObjectBlurEffect() override;
    
    void setProperties(float newRadius);
    void applyEffect (juce::Image& image, juce::Graphics& g, float scaleFactor, float alpha) override;
    
private:
    Blur blur;
    
    JUCE_LEAK_DETECTOR (ObjectBlurEffect)
};

} // imgfx
