#include <gui/screen2_screen/Screen2View.hpp>

extern uint8_t rx_buffer[256];

Screen2View::Screen2View() {

}

void Screen2View::setupScreen() {
	Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen() {
	Screen2ViewBase::tearDownScreen();
}

void Screen2View::setModeOn() {
	presenter->setModePresenter(1, 1);
}

void Screen2View::setModeOff() {
	presenter->setModePresenter(1, 0);
}

void Screen2View::setErrorCode(int value) {

	if (value != 0) {
		Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "0x%X", value);
		//Unicode::snprintf(textArea1, TEXTAREA1_SIZE, "%h", value);
		textArea1.invalidate();
	}

	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, " ");
	//Unicode::snprintf(textArea1, TEXTAREA1_SIZE, "%h", value);
	textArea1.invalidate();
}

void Screen2View::setTimeElco(int value) {
	boxProgress1.setValue(value);
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", value);
	textArea2.invalidate();
}

void Screen2View::setTimeFiltrasi(int value) {
//	boxProgress2.setValue(value);
//	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%d", value);
//	textArea3.invalidate();
}

void Screen2View::setTimeProcess(uint32_t hours, uint32_t minutes,
		uint32_t seconds) {

	digitalClock1.setTime24Hour(hours, minutes, seconds);
}

void Screen2View::setStatus() {
	if (rx_buffer[15] == 0) {
		Unicode::snprintf(textStatusBuffer, TEXTSTATUS_SIZE, "OFF");
		textStatus.invalidate();
	} else if (rx_buffer[15] == 1) {
		Unicode::snprintf(textStatusBuffer, TEXTSTATUS_SIZE, "ON");
		textStatus.invalidate();
	}
}
