#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View &v) :
		view(v) {

}

void Screen2Presenter::activate() {

}

void Screen2Presenter::deactivate() {

}

void Screen2Presenter::setModePresenter(uint8_t idSlave, uint8_t value) {
	model->setModeModel(idSlave, value);
}

void Screen2Presenter::setErrorCode(int value) {
	view.setErrorCode(value);
}

void Screen2Presenter::setTimeElco(int value) {
	view.setTimeElco(value);
}

void Screen2Presenter::setTimeFiltrasi(int value) {
	view.setTimeFiltrasi(value);
}

void Screen2Presenter::setTimeProcess(uint32_t hours, uint32_t minutes,
		uint32_t seconds) {

	view.setTimeProcess(hours, minutes, seconds);

}

void Screen2Presenter::setStatus() {
	view.setStatus();
}
