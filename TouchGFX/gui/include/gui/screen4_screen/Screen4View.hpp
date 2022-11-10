#ifndef SCREEN4VIEW_HPP
#define SCREEN4VIEW_HPP

#include <gui_generated/screen4_screen/Screen4ViewBase.hpp>
#include <gui/screen4_screen/Screen4Presenter.hpp>

class Screen4View: public Screen4ViewBase {
public:
	Screen4View();
	virtual ~Screen4View() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();
	virtual void handleTickEvent();
	virtual void changeDuty(int value);
	virtual void setCounter(int value);
	virtual void setDutyClick();
	virtual void runClick();
	virtual void stopClick();
	//virtual void setDutyClick();
protected:
};

#endif // SCREEN4VIEW_HPP
