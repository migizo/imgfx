#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
: bgBlurFx(&bgBlurCircle)
{
    // multi stack fx
    {
        // stack#1 : callback fx
        auto callback = [](juce::Image &sourceImage, juce::Graphics &g, float scaleFactor, float alpha)
        {
            imgfx::FxFunctions::multiplyBrightness(sourceImage, 1.5f);
            g.setColour(juce::Colours::white);
            g.drawImageAt(sourceImage, 0, 0);
        };
        auto invertFx = new imgfx::CallbackEffect(callback);
        multiStackFx.add(invertFx);
        
        // stack#2 : glow fx
        auto* glowFx = new juce::GlowEffect();
        glowFx->setGlowProperties(10, multiStackCircle.colour);
        multiStackFx.add(glowFx);
        
        addAndMakeVisible(multiStackCircle);
        multiStackCircle.setBounds(50, 50, 100, 100);
        multiStackCircle.setComponentEffect(&multiStackFx);
    }

    // inner shadow
    {
        innerShadowFx.setShadowProperties(imgfx::InnerShadow(innerShadowCircle.colour.darker(), 30, juce::Point<int>(10, 4)));
        addAndMakeVisible(innerShadowCircle);
        innerShadowCircle.setBounds(100, 100, 100, 100);
        innerShadowCircle.setComponentEffect(&innerShadowFx);
    }
    
    // drop shadow
    {
        juce::DropShadow ds(dropShadowCircle.colour.darker(), 30, juce::Point<int>(10, 0));
        dropShadowFx.setShadowProperties(juce::DropShadow(ds));
        addAndMakeVisible(dropShadowCircle);
        dropShadowCircle.setBounds(150, 150, 100, 100);
        dropShadowCircle.setComponentEffect(&dropShadowFx);
    }
    
    // obj blur
    {
        const float radius = 10.0f;
        objBlurFx.setProperties(radius);
        addAndMakeVisible(objBlurCircle);
        objBlurCircle.setBounds(200, 200, 100, 100);
        objBlurCircle.setComponentEffect(&objBlurFx);
    }
    
    // background  blur
    {
        addAndMakeVisible(bgBlurCircle);
        bgBlurCircle.setBounds(250, 250, 100, 100);
        bgBlurCircle.setComponentEffect(&bgBlurFx);
        auto cachedImage = imgfx::CachedComponentImage::createAndSet(*this);
        bgBlurFx.setBackgroundCachedImage(cachedImage);
        const float radius = 30.0f;
        const float brightness = 0.2f;
        const float srcAlpha = 0.1f;
        bgBlurFx.setProperties(radius, srcAlpha, brightness);
    }

    // comp size UI
    compSizeLabel.setText("component size", juce::dontSendNotification);
    addAndMakeVisible(compSizeLabel);
    compSizeSlider.setRange(50, 200, 1);
    compSizeSlider.setValue(100);
    addAndMakeVisible(compSizeSlider);
    compSizeSlider.onValueChange = [this]
    {
        const float circleSize = compSizeSlider.getValue();
        multiStackCircle.setSize(circleSize, circleSize);
        innerShadowCircle.setSize(circleSize, circleSize);
        dropShadowCircle.setSize(circleSize, circleSize);
        objBlurCircle.setSize(circleSize, circleSize);
        bgBlurCircle.setSize(circleSize, circleSize);
    };
    
    // scale UI
    scaleLabel.setText("scale", juce::dontSendNotification);
    addAndMakeVisible(scaleLabel);
    scaleSlider.setRange(0.1, 1.0, 0.1);
    scaleSlider.setValue(1.0);
    addAndMakeVisible(scaleSlider);
    scaleSlider.onValueChange = [this]
    {
        const float scale = scaleSlider.getValue();
        multiStackCircle.scale = scale;
        innerShadowCircle.scale = scale;
        dropShadowCircle.scale = scale;
        objBlurCircle.scale = scale;
        bgBlurCircle.scale = scale;
        
        auto pathCallback = [this]{ return bgBlurCircle.getPath(); };
        auto path = bgBlurCircle.getPath();
        bgBlurFx.setPathCallback(pathCallback);
        innerShadowFx.setPathCallback(pathCallback);
    };
    scaleSlider.onDragEnd = [this]
    {
        multiStackCircle.repaint();
        innerShadowCircle.repaint();
        dropShadowCircle.repaint();
        objBlurCircle.repaint();
        bgBlurCircle.repaint();
    };

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkblue);
    
    g.setColour (juce::Colours::green);
    g.fillEllipse(getLocalBounds().reduced(100).toFloat());
    
    g.setFont (juce::FontOptions (64.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    auto pathCallback = [this]{ return bgBlurCircle.getPath(); };
    auto path = bgBlurCircle.getPath();
    bgBlurFx.setPathCallback(pathCallback);
    innerShadowFx.setPathCallback(pathCallback);
    
    auto area = getLocalBounds();
    
    auto compSizeArea = area.removeFromTop(32);
    compSizeLabel.setBounds(compSizeArea.removeFromLeft(180));
    compSizeSlider.setBounds(compSizeArea);

    auto scaleArea = area.removeFromTop(32);
    scaleLabel.setBounds(scaleArea.removeFromLeft(180));
    scaleSlider.setBounds(scaleArea);
}
