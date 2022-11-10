#include <gui/screen3_screen/Screen3View.hpp>
#include <touchgfx/Color.hpp>
#include "stdlib.h"

extern uint8_t rx_buffer[256];

//touchgfx::Color::getColorFromRGB(rand() % 256, rand() % 256, rand() % 256);
uint32_t brightPurpleRGB888 = 255 << 16 | 0 << 8 | 255 << 0;
uint32_t black = touchgfx::Color::getColorFromRGB(0, 0, 0);
uint32_t green = touchgfx::Color::getColorFromRGB(0, 255, 0);

Screen3View::Screen3View() {

}

void Screen3View::setupScreen() {
	Screen3ViewBase::setupScreen();
}

void Screen3View::tearDownScreen() {
	Screen3ViewBase::tearDownScreen();
}

void Screen3View::function1() {

}

void Screen3View::setIndicator(int value1, int value2) {

	if (rx_buffer[14] == 0) {
		boxOzone.setColor(black);
		boxOzone.invalidate();
	}

	if (rx_buffer[14] == 1) {
		boxOzone.setColor(green);
		boxOzone.invalidate();
	}

	if (rx_buffer[13] == 0) {
		boxCompressor.setColor(black);
		boxCompressor.invalidate();
	}

	if (rx_buffer[13] == 1) {
		boxCompressor.setColor(green);
		boxCompressor.invalidate();
	}

	if (rx_buffer[12] == 0) {
		boxEAB.setColor(black);
		boxEAB.invalidate();
	}

	if (rx_buffer[12] == 1) {
		boxEAB.setColor(green);
		boxEAB.invalidate();
	}

	if (rx_buffer[11] == 1) {
		boxValve1.setColor(green);
		boxValve1.invalidate();
	}

	if (rx_buffer[11] == 0) {
		boxValve1.setColor(black);
		boxValve1.invalidate();
	}

	if (rx_buffer[8] == 1) {
		boxPump1.setColor(green);
		boxPump1.invalidate();
	}

	if (rx_buffer[8] == 0) {
		boxPump1.setColor(black);
		boxPump1.invalidate();
	}

	if (rx_buffer[7] == 1) {
		boxPump2.setColor(green);
		boxPump2.invalidate();
	}

	if (rx_buffer[7] == 0) {
		boxPump2.setColor(black);
		boxPump2.invalidate();
	}

	if (rx_buffer[6] == 1) {
		boxPump3.setColor(green);
		boxPump3.invalidate();
	}

	if (rx_buffer[6] == 0) {
		boxPump3.setColor(black);
		boxPump3.invalidate();
	}

}
