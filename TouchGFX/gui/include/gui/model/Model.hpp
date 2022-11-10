#ifndef MODEL_HPP
#define MODEL_HPP

#include "stm32f746xx.h"

class ModelListener;

class Model {
public:
	Model();

	void bind(ModelListener *listener) {
		modelListener = listener;
	}

	void tick();

	void setDutyModel(uint8_t idSlave, float value);
	void runMotorModel(uint8_t idSlave);
	void stopMotorModel(uint8_t idSlave);
	void setModeModel(uint8_t idSlave, uint8_t value);

protected:
	ModelListener *modelListener;
};

#endif // MODEL_HPP
