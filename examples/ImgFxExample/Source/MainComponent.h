#pragma once

#include <JuceHeader.h>
#include <imgfx/imgfx.h>

class CircleComponent
: public juce::Component
{
public:
    CircleComponent()
    {
        colour = juce::Colours::red.withHue(juce::Random::getSystemRandom().nextFloat());
    }
    ~CircleComponent() override {}
    
    void paint(juce::Graphics& g) override
    {
        g.setColour(colour);
        g.fillPath(getPath());
    }
    
    juce::Path getPath() const
    {
        juce::Path path;
        auto rect = getLocalBounds().toFloat();
        rect = rect.transformedBy(juce::AffineTransform::translation(-rect.getCentreX(), -rect.getCentreY())
                                  .scaled(scale)
                                  .translated(rect.getCentreX(), rect.getCentreY()));
        rect *= scale;
        path.addEllipse(rect);
        return path;
    }
    
    juce::Colour colour;
    float scale = 1.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CircleComponent)
};

//==============================================================================
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:    
    CircleComponent multiStackCircle;
    CircleComponent innerShadowCircle;
    CircleComponent dropShadowCircle;
    CircleComponent objBlurCircle;
    CircleComponent bgBlurCircle;
    
    imgfx::MultiStackEffect<> multiStackFx;
    imgfx::InnerShadowEffect innerShadowFx;
    juce::DropShadowEffect dropShadowFx;
    imgfx::ObjectBlurEffect objBlurFx;
    imgfx::BackgroundBlurEffect bgBlurFx;
    
    juce::Label compSizeLabel;
    juce::Slider compSizeSlider;
    
    juce::Label scaleLabel;
    juce::Slider scaleSlider;

    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
