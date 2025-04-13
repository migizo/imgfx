/*
  ==============================================================================

    CallbackEffect.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace imgfx
{

/**
 @brief 任意のEffectをstd::function<>により指定できるImageEffectFilter
 メンバ変数で値の状態を管理する必要がない場合のEffect処理に有効(e.g. 色を反転させる等)
 std::functionがnullの場合はEffect処理を行わず元の画像をそのまま描画する。
 @see FxFunctions
 */
class CallbackEffect
  : public juce::ImageEffectFilter
{
public:
    using CallbackType = std::function<void(juce::Image &sourceImage, juce::Graphics &g, float scaleFactor, float alpha)>;
    
    CallbackEffect(const CallbackType &fn) : callback(fn) {}
    ~CallbackEffect() override {}

    void applyEffect(juce::Image &sourceImage, juce::Graphics &g, float scaleFactor, float alpha) override
    {
        if (callback == nullptr)
        {
            g.drawImageAt(sourceImage, 0, 0);
            return;
        }
        callback(sourceImage, g, scaleFactor, alpha);
    }

private:
    CallbackType callback = nullptr;

    JUCE_LEAK_DETECTOR(CallbackEffect)
};

} // namespace imgfx
