#include "InnerShadow.h"

namespace imgfx
{

InnerShadow::InnerShadow(juce::Colour shadowColour, const int r, juce::Point<int> o) noexcept
: colour (shadowColour), radius (r), offset (o)
{
    jassert (radius > 0);
}

void InnerShadow::drawForImage(juce::Graphics& g, const juce::Image& srcImage) const
{
    // 影マスク
    auto maskImg = juce::Image(juce::Image::SingleChannel, srcImage.getWidth() + radius*2, srcImage.getHeight() + radius*2, true);
    juce::Graphics maskG(maskImg);
    maskG.drawImageAt(srcImage, radius + offset.x, radius + offset.y);
    
    juce::Image blurred;
    juce::ImageEffects::applySingleChannelBoxBlurEffect(radius,
                                                        maskImg,
                                                        blurred);
//    juce::ImageEffects::applyGaussianBlurEffect(radius, maskImg, blurred); // 重すぎて使用不可
    
    // blurredを反転
    auto inverted = FxFunctions::invert(blurred);
    
    // 影色描画
    g.reduceClipRegion(srcImage, {});
    g.setColour(colour);
    g.drawImageAt(inverted, -radius, -radius, true);
}

void InnerShadow::drawForPath(juce::Graphics& g, const juce::Path& path)
{
#if USE_MELATONIN_BLUR
    melatoninInnerShadow.setColor(colour).setRadius(radius).setOffset(offset);
    melatoninInnerShadow.render(g, path);

#else
    // reference: https://forum.juce.com/t/inner-shadow-or-workarounds/19704/4
    juce::Path shadowPath(path);
    shadowPath.addRectangle(path.getBounds().expanded(radius));
    shadowPath.setUsingNonZeroWinding(false); // パス交差箇所が内側判定になる
    
    g.reduceClipRegion(path);
    g.setColour(colour);

    juce::DropShadow ds(colour, radius, offset);
    ds.drawForPath(g, shadowPath); // drawForImage()と同様、サイズの大きいimageに描画してブラーをかけていないからかパス周辺に漏れがある?
#endif
}


} // namespace imgfx
