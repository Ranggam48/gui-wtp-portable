/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen4_screen/Screen4ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


Screen4ViewBase::Screen4ViewBase() :
    buttonCallback(this, &Screen4ViewBase::buttonCallbackHandler),
    sliderValueChangedCallback(this, &Screen4ViewBase::sliderValueChangedCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 480, 272);
    box1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_FILE4628_ID));

    circleProgress1.setXY(351, 45);
    circleProgress1.setProgressIndicatorPosition(0, 0, 104, 104);
    circleProgress1.setRange(0, 15);
    circleProgress1.setCenter(52, 52);
    circleProgress1.setRadius(42);
    circleProgress1.setLineWidth(16);
    circleProgress1.setStartEndAngle(0, 360);
    circleProgress1.setCapPrecision(180);
    circleProgress1.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_MEDIUM_CIRCLE_INDICATOR_BG_LINE_FULL_ID));
    circleProgress1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    circleProgress1.setPainter(circleProgress1Painter);
    circleProgress1.setValue(0);

    buttonWithLabel1.setXY(19, 205);
    buttonWithLabel1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID));
    buttonWithLabel1.setLabelText(touchgfx::TypedText(T___SINGLEUSE_N116));
    buttonWithLabel1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel1.setAction(buttonCallback);

    circleProgress2.setXY(225, 45);
    circleProgress2.setProgressIndicatorPosition(0, 0, 104, 104);
    circleProgress2.setRange(0, 3000);
    circleProgress2.setCenter(52, 52);
    circleProgress2.setRadius(42);
    circleProgress2.setLineWidth(16);
    circleProgress2.setStartEndAngle(0, 360);
    circleProgress2.setCapPrecision(180);
    circleProgress2.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_MEDIUM_CIRCLE_INDICATOR_BG_LINE_FULL_ID));
    circleProgress2Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    circleProgress2.setPainter(circleProgress2Painter);
    circleProgress2.setValue(0);

    slider1.setXY(5, 124);
    slider1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_SMALL_SLIDER_HORIZONTAL_SMALL_ROUND_BACK_ID), touchgfx::Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_SMALL_SLIDER_HORIZONTAL_SMALL_ROUND_FILL_ID), touchgfx::Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_SMALL_INDICATORS_SLIDER_HORIZONTAL_SMALL_ROUND_KNOB_ID));
    slider1.setupHorizontalSlider(3, 7, 0, 0, 125);
    slider1.setValueRange(0, 100);
    slider1.setValue(0);
    slider1.setNewValueCallback(sliderValueChangedCallback);

    setDutyButton.setXY(5, 62);
    setDutyButton.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID));
    setDutyButton.setLabelText(touchgfx::TypedText(T___SINGLEUSE_9UR1));
    setDutyButton.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    setDutyButton.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    setDutyButton.setAction(buttonCallback);

    box2.setPosition(65, 75, 119, 33);
    box2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    buttonWithLabel3.setXY(277, 205);
    buttonWithLabel3.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID));
    buttonWithLabel3.setLabelText(touchgfx::TypedText(T___SINGLEUSE_C1Z9));
    buttonWithLabel3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setAction(buttonCallback);

    buttonWithLabel4.setXY(337, 205);
    buttonWithLabel4.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID));
    buttonWithLabel4.setLabelText(touchgfx::TypedText(T___SINGLEUSE_QDN6));
    buttonWithLabel4.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel4.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel4.setAction(buttonCallback);

    textArea1.setPosition(65, 78, 119, 27);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_8O1Z).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_K9QH));

    box3.setPosition(235, 158, 84, 22);
    box3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    box3_1.setPosition(363, 158, 81, 22);
    box3_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    textArea2.setPosition(235, 162, 84, 15);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2.setLinespacing(0);
    Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_JR84).getText());
    textArea2.setWildcard(textArea2Buffer);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_2K29));

    textArea3.setPosition(363, 162, 81, 15);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea3.setLinespacing(0);
    Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_FD95).getText());
    textArea3.setWildcard(textArea3Buffer);
    textArea3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_D0L1));

    textArea4.setXY(5, 2);
    textArea4.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea4.setLinespacing(0);
    textArea4.setTypedText(touchgfx::TypedText(T___SINGLEUSE_PFW6));

    add(__background);
    add(box1);
    add(image1);
    add(circleProgress1);
    add(buttonWithLabel1);
    add(circleProgress2);
    add(slider1);
    add(setDutyButton);
    add(box2);
    add(buttonWithLabel3);
    add(buttonWithLabel4);
    add(textArea1);
    add(box3);
    add(box3_1);
    add(textArea2);
    add(textArea3);
    add(textArea4);
}

void Screen4ViewBase::setupScreen()
{

}

void Screen4ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel1)
    {
        //Interaction1
        //When buttonWithLabel1 clicked change screen to Screen1
        //Go to Screen1 with no screen transition
        application().gotoScreen1ScreenNoTransition();
    }
    else if (&src == &setDutyButton)
    {
        //Interaction2
        //When setDutyButton clicked call virtual function
        //Call setDutyClick
        setDutyClick();
    }
    else if (&src == &buttonWithLabel3)
    {
        //Interaction3
        //When buttonWithLabel3 clicked call virtual function
        //Call runClick
        runClick();
    }
    else if (&src == &buttonWithLabel4)
    {
        //Interaction4
        //When buttonWithLabel4 clicked call virtual function
        //Call stopClick
        stopClick();
    }
}

void Screen4ViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider1)
    {
        //Interaction5
        //When slider1 value changed call virtual function
        //Call changeDuty
        changeDuty(value);
    }
}
