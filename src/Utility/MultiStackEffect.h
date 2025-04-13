/*
  ==============================================================================

    MultiStackEffect.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace imgfx
{

/**
 @brief 複数のImageEffectFilterを管理し、適用できるImageEffectFilter。
 juce::Component::setComponentEffect()では単一のImageEffectFilterのみセットできるため、
 複数のエフェクトを使用したい場合に使用する。
 各エフェクトの所有権はこのクラスで管理されるため、呼び出し側で削除処理を行わないようにする必要あり。
*/
template<typename Array = juce::Array<juce::ImageEffectFilter*>>
class MultiStackEffect
  : public juce::ImageEffectFilter
{
public:
    MultiStackEffect() = default;
    ~MultiStackEffect() override { clear(); }

    // juce::ImageEffectFilter
    void applyEffect(juce::Image &sourceImage, juce::Graphics &destContext, float scaleFactor, float alpha) override;
    
    void clear() { fxFilters.clear(); }
    void add(juce::ImageEffectFilter* fx) { fxFilters.add(fx); }
    void remove(juce::ImageEffectFilter* fx) { fxFilters.remove(fx); }
    int size() const { return fxFilters.size(); }
    bool isEmpty() const { return fxFilters.isEmpty(); }

//    Array& getFilters() { return fxFilters; }

private:
    Array fxFilters;

    JUCE_LEAK_DETECTOR(MultiStackEffect)
};

using OwnedMultiStackEffect = MultiStackEffect<juce::OwnedArray<juce::ImageEffectFilter>>;

template<typename Array>
void MultiStackEffect<Array>::applyEffect(juce::Image &sourceImage, juce::Graphics &destContext, float scaleFactor, float alpha)
{
    juce::Image srcImg = sourceImage.createCopy();
    juce::Image dstImg = juce::Image(srcImg.getFormat(),
                                     srcImg.getWidth(),
                                     srcImg.getHeight(),
                                     true);
    for (juce::ImageEffectFilter* fx: fxFilters)
    {
        if (fx == nullptr) continue;
        
        dstImg.clear(dstImg.getBounds());
        juce::Graphics g(dstImg);
        fx->applyEffect(srcImg, g, scaleFactor, alpha);
        
        std::swap(srcImg, dstImg);
    }
    destContext.drawImageAt(srcImg, 0, 0);
}

} // namespace imgfx
