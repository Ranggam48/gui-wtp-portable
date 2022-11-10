/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen3ViewBase::Screen3ViewBase() :
    buttonCallback(this, &Screen3ViewBase::buttonCallbackHandler)
{

    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 480, 272);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_FLOWN_ID));

    buttonWithLabel1.setXY(407, 207);
    buttonWithLabel1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID));
    buttonWithLabel1.setLabelText(touchgfx::TypedText(T___SINGLEUSE_AGFD));
    buttonWithLabel1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel1.setAction(buttonCallback);

    boxEAB.setPosition(20, 142, 15, 15);
    boxEAB.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxValveDrain.setPosition(66, 237, 15, 15);
    boxValveDrain.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxValve1.setPosition(139, 153, 15, 15);
    boxValve1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxPump1.setPosition(191, 153, 15, 15);
    boxPump1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxFilter.setPosition(268, 153, 15, 15);
    boxFilter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxPump2.setPosition(312, 153, 15, 15);
    boxPump2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxPump3.setPosition(273, 212, 15, 15);
    boxPump3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxCompressor.setPosition(128, 8, 15, 15);
    boxCompressor.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxOzone.setPosition(338, 92, 15, 15);
    boxOzone.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box2.setPosition(444, 23, 15, 16);
    box2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box3.setPosition(444, 4, 15, 15);
    box3.setColor(touchgfx::Color::getColorFromRGB(38, 255, 0));

    textArea1.setXY(407, 4);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_W1IP));

    textArea2.setXY(407, 24);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_O0DT));

    add(__background);
    add(box1);
    add(image1);
    add(buttonWithLabel1);
    add(boxEAB);
    add(boxValveDrain);
    add(boxValve1);
    add(boxPump1);
    add(boxFilter);
    add(boxPump2);
    add(boxPump3);
    add(boxCompressor);
    add(boxOzone);
    add(box2);
    add(box3);
    add(textArea1);
    add(textArea2);
}

void Screen3ViewBase::setupScreen()
{

}

void Screen3ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel1)
    {
        //Interaction1
        //When buttonWithLabel1 clicked change screen to Screen1
        //Go to Screen1 with no screen transition
        application().gotoScreen1ScreenNoTransition();

        //Interaction2
        //When buttonWithLabel1 clicked call virtual function
        //Call function1
        function1();
    }
}
