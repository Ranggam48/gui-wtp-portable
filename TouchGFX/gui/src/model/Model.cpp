#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "stm32f7xx_hal.h"

extern "C" {
extern int erpm;
extern int indicator;
extern uint8_t indicator1, indicator2;
extern int errorCode;
extern int timeElco;
extern int timeFiltrasi;
extern void setDuty(uint8_t idSlave, float value);
extern void stopMotor(uint8_t idSlave);
extern void runMotor(uint8_t idSlave);
extern void setMode(uint8_t idSlave, uint8_t value);
extern RTC_HandleTypeDef hrtc;
extern RTC_TimeTypeDef RTC_Time;
extern RTC_DateTypeDef RTC_Date;
extern float oxygen, tempO2, flowO2;
extern uint32_t H, M, S;
}

Model::Model() :
		modelListener(0) {

}

void Model::tick() {
	HAL_RTC_GetTime(&hrtc, &RTC_Time, FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, FORMAT_BIN);
	modelListener->setCounterPresenter(erpm);
//modelListener->changeDutyPresenter(duty);
	modelListener->setIndicatorPresenter(indicator1, indicator2);
	modelListener->setErrorCode(errorCode);
	modelListener->setTimeElco(timeElco);
	modelListener->setTimeFiltrasi(timeFiltrasi);
	modelListener->updateTime(RTC_Time.Hours, RTC_Time.Minutes,
			RTC_Time.Seconds);
	modelListener->updateOxygen(oxygen, tempO2, flowO2);
	modelListener->setTimeProcess(H, M, S);
	modelListener->setStatus();

}

void Model::setModeModel(uint8_t idSlave, uint8_t value) {
	setMode(idSlave, value);
}

void Model::setDutyModel(uint8_t idSlave, float value) {
	setDuty(idSlave, value);
}

void Model::runMotorModel(uint8_t idSlave) {
	runMotor(idSlave);
}

void Model::stopMotorModel(uint8_t idSlave) {
	stopMotor(idSlave);
}
