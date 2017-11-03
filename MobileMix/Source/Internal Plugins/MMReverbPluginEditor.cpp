/*
  ==============================================================================

    MMReverbPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMReverbPluginEditor.h"

MMReverbPluginEditor::MMReverbPluginEditor(MMReverbPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    
    attachTrim = createSliderAttachment(processor.paramTrim, sliderTrim);
    addAndMakeVisible(sliderTrim);
    
    attachHighPass = createSliderAttachment(processor.paramHighPass, sliderHighPass);
    addAndMakeVisible(sliderHighPass);
    
    attachLowPass = createSliderAttachment(processor.paramLowPass, sliderLowPass);
    addAndMakeVisible(sliderLowPass);
    
    attachLength = createSliderAttachment(processor.paramLength, sliderLength);
    addAndMakeVisible(sliderLength);
    
    attachDryWet = createSliderAttachment(processor.paramDryWet, sliderDryWet);
    addAndMakeVisible(sliderDryWet);
    
    addAndMakeVisible(graphReverb);
    
    //Need MMShapeButton constructors for high and low pass buttons
}

MMReverbPluginEditor::~MMReverbPluginEditor()
{

}

void MMReverbPluginEditor::resized()
{
    FlexBox layout;
    
    float vertSpace = 15.0f;
    float dynamicSpace = this->getWidth() * 0.01f;
    FlexItem::Margin standardMargin = FlexItem::Margin::Margin(15.0f, dynamicSpace, 15.0f, dynamicSpace);
    
    FlexBox graphBox;
    graphBox.flexDirection = FlexBox::Direction::column;
    graphBox.items.add(FlexItem(graphReverb).withFlex(6.0f));
    graphBox.items.add(FlexItem(sliderTrim).withMargin(FlexItem::Margin::Margin(vertSpace, 0.0f, 0.0f, 0.0f)).withFlex(1.0f));
    
    layout.items.add(FlexItem(graphBox).withMargin(FlexItem::Margin::Margin(vertSpace, dynamicSpace, vertSpace, vertSpace)).withFlex(10.0f));
    
    FlexBox highPass;
    highPass.flexDirection = FlexBox::Direction::column;
    highPass.items.add(FlexItem(sliderHighPass).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, 0.0f)).withFlex(8.0f));
    //highPass.items.add(FlexItem(buttonHighPass).withFlex(1.0f));
    
    FlexBox lowPass;
    lowPass.flexDirection = FlexBox::Direction::column;
    lowPass.items.add(FlexItem(sliderLowPass).withMargin(FlexItem::Margin::Margin(0.0f, 0.0f, vertSpace, 0.0f)).withFlex(8.0f));
    //lowPass.items.add(FlexItem(buttonLowPass).withFlex(1.0f));
    
    layout.items.add(FlexItem(highPass).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(lowPass).withMargin(standardMargin).withFlex(1.0f));
    
    layout.items.add(FlexItem(sliderLength).withMargin(standardMargin).withFlex(1.0f));
    layout.items.add(FlexItem(sliderDryWet).withMargin(FlexItem::Margin::Margin(vertSpace, vertSpace, vertSpace, dynamicSpace)).withFlex(1.0f));
    
    layout.performLayout(getLocalBounds());
    
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderHighPass);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderLowPass);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderLength);
    MobileMixPluginInstanceEditor::setVerticalRotated(&sliderDryWet);
}
