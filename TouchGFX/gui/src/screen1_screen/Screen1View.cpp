#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View() {

}

void Screen1View::setupScreen() {
	Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen() {
	Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateTime(int hours, int minutes, int seconds) {

	digitalClock1.setTime24Hour(hours, minutes, seconds);

}
