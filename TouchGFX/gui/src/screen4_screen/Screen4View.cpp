#include <gui/screen4_screen/Screen4View.hpp>
#include "stm32f746xx.h"
Screen4View::Screen4View() {

}

void Screen4View::setupScreen() {
	Screen4ViewBase::setupScreen();
}

void Screen4View::tearDownScreen() {
	Screen4ViewBase::tearDownScreen();
}

void Screen4View::handleTickEvent() {
//	circleProgress1.setValue(counter);
//	circleProgress2.setValue(counter);
//	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE,"%u", counter);
//	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE,"%u", counter);
//	textArea2.invalidate();
//	textArea3.invalidate();
}

extern int duty;

void Screen4View::changeDuty(int value) {
	duty = value;
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%u", duty);
	textArea1.invalidate();
}

void Screen4View::setCounter(int value) {
	circleProgress1.setValue(value);
	circleProgress2.setValue(value);
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%u", value);
	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%u", value);
	textArea2.invalidate();
	textArea3.invalidate();
}

void Screen4View::setDutyClick() {
	float value = duty / 100.0;
	presenter->setDutyPresenter(3, value);
}

void Screen4View::runClick() {
	presenter->runMotorPresenter(3);
}

void Screen4View::stopClick() {
	presenter->stopMotorPresenter(3);
}

//void Screen4View::setDutyClick()
//{
//	//setDutyButton();
//}
