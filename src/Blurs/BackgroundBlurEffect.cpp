/*
  ==============================================================================

    BackgroundBlur.cpp
    Author:  migizo

  ==============================================================================
*/

#include "BackgroundBlurEffect.h"

namespace imgfx
{

//==============================================================================
BackgroundBlurEffect::BackgroundBlurEffect(juce::Component* owner)
{
    jassert(owner);
    ownerComponent = owner;
}

BackgroundBlurEffect::~BackgroundBlurEffect()
{
}

void BackgroundBlurEffect::setBackgroundCachedImage(CachedComponentImage* backgroundCachedImage)
{
    // nullは指定されない想定。無効化したい場合はこのEffectをsetComponentEffect()で無効化すること。
    jassert(backgroundCachedImage);
    cachedImage = backgroundCachedImage;
    cachedComponent = backgroundCachedImage->getOwnerComponent();
    
    // 既にsetCachedComponentImage()でcachedImageをセットする必要がある。
    jassert(cachedComponent->getCachedComponentImage() == cachedImage);
}

void BackgroundBlurEffect::setPathCallback(const std::function<juce::Path()>& newPathCallback)
{
    pathCallback = newPathCallback;
}

void BackgroundBlurEffect::setProperties(float newRadius, float newSourceAlpha, float newBrightness)
{
    bgBlur.setRadius(newRadius);
    
    sourceAlpha = newSourceAlpha;
    brightness = newBrightness;
}

void BackgroundBlurEffect::applyEffect (juce::Image& image, juce::Graphics& g, float scaleFactor, float alpha)
{
    // 何かしら有効でなければブラー無しの通常の描画を行う
    if (ownerComponent == nullptr ||
        cachedComponent == nullptr ||
        cachedImage == nullptr ||
        cachedImage->getImage().isNull())
    {
        g.drawImageAt(image, 0, 0);
        return;
    }
    
    auto bgImage = cachedImage->getClippedImage(ownerComponent);
    
    // brightness
//    bgImage = FxFunctions::multiplyBrightness(bgImage, brightness); // 単に乗算では明るめの黄緑、とかになる。単純にRGBに値を足していった場合比率が崩れ255で丸められるのでおかしくなる。
    if (brightness < 0)
    {
        juce::Graphics tmpg(bgImage);
        tmpg.fillAll(juce::Colours::black.withAlpha(std::abs(brightness)));
    }
    else if (brightness > 0)
    {
        juce::Graphics tmpg(bgImage);
        tmpg.fillAll(juce::Colours::white.withAlpha(std::abs(brightness)));
    }
    
    // PathもしくはImageでマスク処理
    juce::Path maskPath;
    if (pathCallback) maskPath = pathCallback();
    if (maskPath.isEmpty() == false)
    {
        auto tmpPath = maskPath;
        tmpPath.applyTransform(juce::AffineTransform::scale(scaleFactor));
        bgBlur.drawForPath(g, bgImage, tmpPath);
    }
    else
    {
        bgBlur.drawForImage(g, bgImage, image);
    }
        
    // ソース画像の描画
    if (sourceAlpha > 0.0f)
    {
        g.setOpacity(sourceAlpha);
        g.drawImageAt(image, 0, 0);
    }
}

} // namespace imgfx
