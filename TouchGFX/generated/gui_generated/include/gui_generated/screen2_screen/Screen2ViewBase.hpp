/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN2VIEWBASE_HPP
#define SCREEN2VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/progress_indicators/BoxProgress.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/clock/DigitalClock.hpp>

class Screen2ViewBase : public touchgfx::View<Screen2Presenter>
{
public:
    Screen2ViewBase();
    virtual ~Screen2ViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void setModeOn()
    {
        // Override and implement this function in Screen2
    }

    virtual void setModeOff()
    {
        // Override and implement this function in Screen2
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
    touchgfx::ButtonWithLabel buttonWithLabel1;
    touchgfx::ButtonWithLabel buttonWithLabel3;
    touchgfx::ButtonWithLabel buttonWithLabel5;
    touchgfx::Box box2;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::BoxProgress boxProgress1;
    touchgfx::TextAreaWithOneWildcard textArea2;
    touchgfx::TextArea textArea4;
    touchgfx::TextArea textArea6;
    touchgfx::TextArea textArea8;
    touchgfx::Box box3;
    touchgfx::TextAreaWithOneWildcard textStatus;
    touchgfx::Box box4;
    touchgfx::DigitalClock digitalClock1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];
    static const uint16_t TEXTAREA2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea2Buffer[TEXTAREA2_SIZE];
    static const uint16_t TEXTSTATUS_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textStatusBuffer[TEXTSTATUS_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen2ViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREEN2VIEWBASE_HPP
