/*
  ==============================================================================

    CachedComponentImage.cpp
    Author:  migizo

  ==============================================================================
*/

#include "CachedComponentImage.h"

namespace imgfx
{

//==============================================================================
CachedComponentImage::CachedComponentImage(juce::Component& c) noexcept
: owner (c)
{
}

CachedComponentImage::~CachedComponentImage() = default;

void CachedComponentImage::paint (juce::Graphics& g)
{
    scale = g.getInternalContext().getPhysicalPixelScaleFactor();
    auto compBounds = owner.getLocalBounds();
    auto imageBounds = compBounds * scale;

    if (image.isNull() || image.getBounds() != imageBounds)
    {
        image = juce::Image (owner.isOpaque() ? juce::Image::RGB
                                        : juce::Image::ARGB,
                       juce::jmax (1, imageBounds.getWidth()),
                       juce::jmax (1, imageBounds.getHeight()),
                       ! owner.isOpaque());

        validArea.clear();
    }

    if (! validArea.containsRectangle (compBounds))
    {
        juce::Graphics imG (image);
        auto& lg = imG.getInternalContext();

        lg.addTransform (juce::AffineTransform::scale (scale));

        for (auto& i : validArea)
            lg.excludeClipRectangle (i);

        if (! owner.isOpaque())
        {
            lg.setFill (juce::Colours::transparentBlack);
            lg.fillRect (compBounds, true);
            lg.setFill (juce::Colours::black);
        }

        owner.paintEntireComponent (imG, true);
    }

    validArea = compBounds;

    g.setColour (juce::Colours::black.withAlpha (owner.getAlpha()));
    g.drawImageTransformed (image, juce::AffineTransform::scale ((float) compBounds.getWidth()  / (float) imageBounds.getWidth(),
                                                           (float) compBounds.getHeight() / (float) imageBounds.getHeight()), false);
}

juce::Image CachedComponentImage::getClippedImage(juce::Component* clipTargetComponent) const
{
    // cachedImageを管理しているコンポーネントを基点として相対座標での対象コンポーネント範囲を取得
    auto snapArea = (owner.getLocalArea(clipTargetComponent, clipTargetComponent->getLocalBounds()).toFloat() * getScale()).toNearestInt();
    auto ownerBounds = owner.getLocalBounds();
    
    // 対象コンポーネント範囲が含まれる場合
    if (ownerBounds.contains(snapArea))
    {
        return image.getClippedImage(snapArea);
    }
    
    // 対象コンポーネント範囲がはみ出ている場合
    // clippedImageはownerBounds内でsnapAreaと交差する範囲のみ返す。コンポーネントで扱う場合にはマイナス側にはみ出ている場合に位置のオフセット調整を行う。
    auto clippedImage = image.getClippedImage(snapArea);
    juce::Image tmpImg(image.getFormat(), image.getWidth(), snapArea.getHeight(), true);
    juce::Graphics tmpG(tmpImg);
    tmpG.drawImageAt(clippedImage,
                     snapArea.getX() < 0 ? -snapArea.getX() : 0,
                     snapArea.getY() < 0 ? -snapArea.getY() : 0);
    return tmpImg;
}

CachedComponentImage* CachedComponentImage::createAndSet(juce::Component& owner) // static
{
    auto cachedImage = new CachedComponentImage(owner);
    owner.setCachedComponentImage(cachedImage);
    return cachedImage;
}

} // namespace imgfx
