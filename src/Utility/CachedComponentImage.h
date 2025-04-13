/*
  ==============================================================================

    CachedComponentImage.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace imgfx
{

/**
 @brief juce::Imageを取得可能なjuce::CachedComponentImageの派生クラス。
 @see BackgroundBlurEffect
 */
struct CachedComponentImage : public juce::CachedComponentImage
{
    explicit CachedComponentImage(juce::Component& c) noexcept;
    ~CachedComponentImage();
    
    void paint (juce::Graphics& g) override;
    bool invalidateAll() override                               { validArea.clear(); return true; }
    bool invalidate (const juce::Rectangle<int>& area) override { validArea.subtract (area); return true; }
    void releaseResources() override                            { image = juce::Image(); }

    const juce::Image& getImage() { return image; }
    float getScale() const { return scale; }
    juce::Component* getOwnerComponent() { return &owner; }
    juce::Image getClippedImage(juce::Component* clipTargetComponent) const;
    static CachedComponentImage* createAndSet(juce::Component& owner);
    
private:
    juce::Image image;
    juce::RectangleList<int> validArea;
    juce::Component& owner;
    float scale = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CachedComponentImage)
};

} // imgfx
