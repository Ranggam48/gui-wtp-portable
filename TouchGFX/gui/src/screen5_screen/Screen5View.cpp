#include <gui/screen5_screen/Screen5View.hpp>
#include "stm32f746xx.h"

Screen5View::Screen5View() {

}

void Screen5View::setupScreen() {
	Screen5ViewBase::setupScreen();
}

void Screen5View::tearDownScreen() {
	Screen5ViewBase::tearDownScreen();
}

void Screen5View::handleTick(float value) {
//	Unicode::snprintf(textOxygenBuffer, TEXTOXYGEN_SIZE, "%d", erpm);
//	textOxygen.invalidate();
//	Unicode::snprintf(textFlowOxyBuffer, TEXTFLOWOXY_SIZE, "%.2f", flowO2);
//	textFlowOxy.invalidate();
//	Unicode::snprintf(textTempOxyBuffer, TEXTTEMPOXY_SIZE, "%.2f", tempO2);
//	textTempOxy.invalidate();
//	textProgress1.setValue(oxygen);

}

void Screen5View::updateOxygen(float oxygen, float flow, float temp) {

	Unicode::snprintfFloat(textOxygenBuffer, TEXTOXYGEN_SIZE, "%.2f", oxygen);
	textOxygen.invalidate();
	Unicode::snprintfFloat(textFlowOxyBuffer, sizeof(textFlowOxyBuffer), "%.2f",
			flow);
	textFlowOxy.invalidate();
	Unicode::snprintfFloat(textTempOxyBuffer, sizeof(textTempOxyBuffer), "%.2f",
			temp);
	textTempOxy.invalidate();

}
