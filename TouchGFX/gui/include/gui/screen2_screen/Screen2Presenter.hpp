#ifndef SCREEN2PRESENTER_HPP
#define SCREEN2PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen2View;

class Screen2Presenter: public touchgfx::Presenter, public ModelListener {
public:
	Screen2Presenter(Screen2View &v);

	/**
	 * The activate function is called automatically when this screen is "switched in"
	 * (ie. made active). Initialization logic can be placed here.
	 */
	virtual void activate();

	/**
	 * The deactivate function is called automatically when this screen is "switched out"
	 * (ie. made inactive). Teardown functionality can be placed here.
	 */
	virtual void deactivate();

	virtual ~Screen2Presenter() {
	}
	;
	virtual void setModePresenter(uint8_t idSlave, uint8_t value);
	virtual void setErrorCode(int value);
	virtual void setTimeElco(int value);
	virtual void setTimeFiltrasi(int value);
	virtual void setTimeProcess(uint32_t hours, uint32_t minutes,
			uint32_t seconds);
	virtual void setStatus();

private:
	Screen2Presenter();

	Screen2View &view;
};

#endif // SCREEN2PRESENTER_HPP
