#include <gui/screen4_screen/Screen4View.hpp>
#include <gui/screen4_screen/Screen4Presenter.hpp>
#include <touchgfx/hal/Types.hpp>
#include "stm32f746xx.h"
//extern uint16_t counter;

Screen4Presenter::Screen4Presenter(Screen4View& v)
    : view(v)
{

}

void Screen4Presenter::activate()
{

}

void Screen4Presenter::deactivate()
{

}

void Screen4Presenter::setCounterPresenter(int value)
{
	view.setCounter(value);
}

//void changeDutyPresenter(int value)
//{
//	view->changeDuty(value);
//}

//void setDutyClickPresenter(int value)
//{
//	//view.
//}

void Screen4Presenter::setDutyPresenter(uint8_t idSlave, float value)
{
	model->setDutyModel(idSlave, value);
}

void Screen4Presenter::runMotorPresenter(uint8_t idSlave)
{
	model->runMotorModel(idSlave);
}

void Screen4Presenter::stopMotorPresenter(uint8_t idSlave)
{
	model->stopMotorModel(idSlave);
}

