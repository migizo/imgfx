#include "Blur.h"

namespace imgfx
{

Blur::Blur(int r) noexcept
{
    setRadius(r);
}

void Blur::setRadius(float r)
{
#if USE_MELATONIN_BLUR
    melatoninBlur.reset(new melatonin::CachedBlur(r));
#else
    jassert(r > 0);
    radius = r;
#endif
}

void Blur::drawForImage(juce::Graphics& g, const juce::Image& srcImage)
{
#if USE_MELATONIN_BLUR
    auto tmpImg = srcImage.createCopy();
    g.drawImageAt(melatoninBlur->render(tmpImg), 0, 0);
#else
    jassert(radius > 0);
    auto tmpDstImg = juce::Image(srcImage.getFormat(), srcImage.getWidth(), srcImage.getHeight(), true);
    juce::ImageEffects::applyGaussianBlurEffect(radius, srcImage, tmpDstImg);
    g.drawImageAt(tmpDstImg, 0, 0);
#endif
}

} // namespace imgfx
