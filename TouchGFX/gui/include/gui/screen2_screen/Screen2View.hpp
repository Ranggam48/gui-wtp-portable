#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View: public Screen2ViewBase {
public:
	Screen2View();
	virtual ~Screen2View() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();
	virtual void setModeOn();
	virtual void setModeOff();
	virtual void setErrorCode(int value);
	virtual void setTimeElco(int value);
	virtual void setTimeFiltrasi(int value);
	virtual void setTimeProcess(uint32_t hours, uint32_t minutes,
			uint32_t seconds);
	virtual void setStatus();
protected:
};

#endif // SCREEN2VIEW_HPP
