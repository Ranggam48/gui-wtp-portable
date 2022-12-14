/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN4VIEWBASE_HPP
#define SCREEN4VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen4_screen/Screen4Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class Screen4ViewBase : public touchgfx::View<Screen4Presenter>
{
public:
    Screen4ViewBase();
    virtual ~Screen4ViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void setDutyClick()
    {
        // Override and implement this function in Screen4
    }

    virtual void runClick()
    {
        // Override and implement this function in Screen4
    }

    virtual void stopClick()
    {
        // Override and implement this function in Screen4
    }

    virtual void changeDuty(int value)
    {
        // Override and implement this function in Screen4
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::Image image1;
    touchgfx::CircleProgress circleProgress1;
    touchgfx::PainterRGB565 circleProgress1Painter;
    touchgfx::ButtonWithLabel buttonWithLabel1;
    touchgfx::CircleProgress circleProgress2;
    touchgfx::PainterRGB565 circleProgress2Painter;
    touchgfx::Slider slider1;
    touchgfx::ButtonWithLabel setDutyButton;
    touchgfx::Box box2;
    touchgfx::ButtonWithLabel buttonWithLabel3;
    touchgfx::ButtonWithLabel buttonWithLabel4;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::Box box3;
    touchgfx::Box box3_1;
    touchgfx::TextAreaWithOneWildcard textArea2;
    touchgfx::TextAreaWithOneWildcard textArea3;
    touchgfx::TextArea textArea4;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];
    static const uint16_t TEXTAREA2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea2Buffer[TEXTAREA2_SIZE];
    static const uint16_t TEXTAREA3_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea3Buffer[TEXTAREA3_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen4ViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<Screen4ViewBase, const touchgfx::Slider&, int> sliderValueChangedCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // SCREEN4VIEWBASE_HPP
