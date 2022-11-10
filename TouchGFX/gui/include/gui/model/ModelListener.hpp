#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener {
public:
	ModelListener() :
			model(0) {
	}

	virtual ~ModelListener() {
	}

// fungsi yang dibuat sendiri-----------------
	virtual void setCounterPresenter(int value) {
	}
	virtual void changeDutyPresenter(int value) {
	}
	virtual void setIndicatorPresenter(int value1, int value2) {
	}
	virtual void setErrorCode(int value) {

	}
	virtual void setTimeElco(int value) {

	}
	virtual void setTimeFiltrasi(int value) {

	}

	virtual void updateTime(int hours, int minutes, int seconds) {

	}

	virtual void updateOxygen(float oxygen, float flow, float temp) {

	}

	virtual void setTimeProcess(uint32_t value1, uint32_t value2,
			uint32_t value3) {

	}

	virtual void setStatus() {

	}

//-------------------------------------
	void bind(Model *m) {
		model = m;
	}
protected:
	Model *model;
};

#endif // MODELLISTENER_HPP
