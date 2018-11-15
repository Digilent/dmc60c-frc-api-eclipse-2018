#pragma once
#include "digilent.h"

#include "CANframes.h"
#include "Commands.h"
#include "Parameters.h"
#include "time.h"

#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C"{
#endif
	int32_t c_enumerateDMCs(DMCInfo_t *deviceBuffer, int verbose);
	int c_DMC60CLowLevel_Create_DeviceNum(int deviceNumber, int verbose);
	int c_DMC60CLowLevel_Create_SessID(int sessid, int verbose);
	void c_DMC60CLowLevel_Destroy(int dev);
	DMC_Code c_DMC60CLowLevel_setDeviceNumber(int dev, uint16_t newdevnum);
	unsigned char c_DMC60CLowLevel_getDeviceNumber(int dev);
	DMC_Code c_DMC60CLowLevel_setDeviceName(int dev, char* szDevName, uint16_t cbName);
	void c_DMC60CLowLevel_getDeviceName(int dev, char* szNameBuf);
	uint16_t c_DMC60CLowLevel_getFWVerBoot(int dev);
	uint16_t c_DMC60CLowLevel_getFWVerApp(int dev);
	uint8_t c_DMC60CLowLevel_getImgType(int dev);
	uint16_t c_DMC60CLowLevel_getSessId(int dev);
	DMC_Code c_DMC60CLowLevel_fetchFWVer(int dev);
	DMC_Code c_DMC60CLowLevel_softReset(int dev);
	DMC_Code c_DMC60CLowLevel_flashLEDs(int dev);
	void c_DMC60CLowLevel_setPIDSlotLL(int dev, uint8_t slotNum);
	DMC_Code c_DMC60CLowLevel_configPID_RampRate(int dev, uint8_t slot, uint32_t ramp, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getPID_Ramprate(int dev, uint8_t slot, uint32_t *ramp, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_FwdMaxDuty(int dev, uint8_t slot, int value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getPID_FwdMaxDuty(int dev, uint8_t slot, int *value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_RevMaxDuty(int dev, uint8_t slot, int value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getPID_RevMaxDuty(int dev, uint8_t slot, int *value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_FwdNominal(int dev, uint8_t slot, int value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getPID_FwdNominal(int dev, uint8_t slot, int *value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_RevNominal(int dev, uint8_t slot, int value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getPID_RevNominal(int dev, uint8_t slot, int *value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_kP(int dev, uint8_t slot, float value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_get_kP(int dev, uint8_t slot, float* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_kI(int dev, uint8_t slot, float value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_get_kI(int dev, uint8_t slot, float* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_kD(int dev, uint8_t slot, float value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_get_kD(int dev, uint8_t slot, float* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_kF(int dev, uint8_t slot, float value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_get_kF(int dev, uint8_t slot, float* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_IZone(int dev, uint8_t slot, unsigned int value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_get_IZone(int dev, uint8_t slot, unsigned int *value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configPID_AllowableError(int dev, uint8_t slot, uint32_t value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getPID_AllowableError(int dev, uint8_t slot, uint32_t *value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configForwardLimitSwitchEnable(int dev, bool enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getForwardLimitSwitchEnable(int dev, bool *enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configForwardLimitSwitchType(int dev, bool normallyClosed, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getForwardLimitSwitchType(int dev, bool *normallyClosed, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configReverseLimitSwitchEnable(int dev, bool enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getReverseLimitSwitchEnable(int dev, bool *enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configReverseLimitSwitchType(int dev, bool normallyClosed, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getReverseLimitSwitchType(int dev, bool *normallyClosed, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configSoftFwdThreshold(int dev, bool enable, int limit, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getSoftFwdThreshold(int dev, bool *enable, int *limit, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configSoftRevThreshold(int dev, bool enable, int limit, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getSoftRevThreshold(int dev, bool *enable, int *limit, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configAnalogStatusFramePeriod(int dev, uint32_t periodMs, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getAnalogStatusFramePeriod(int dev, uint32_t *periodMs, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configEncoderStatusFramePeriod(int dev, uint32_t periodMs, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getEncoderStatusFramePeriod(int dev, uint32_t *periodMs, int tmsWait);
	DMC_Code c_DMC60CLowLevel_configGeneralStatusFramePeriod(int dev, uint32_t periodMs, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getGeneralStatusFramePeriod(int dev, uint32_t *periodMs, int tmsWait);
	DMC_Code c_DMC60CLowLevel_setEncoderPosition(int dev, int position, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getEncoderPosition(int dev, int *position, int tmsWait);
	DMC_Code c_DMC60CLowLevel_setClearPositionOnIndex(int dev, bool enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getClearPositionOnIndex(int dev, bool *enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_setClearPositionOnFwdLimit(int dev, bool enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getClearPositionOnFwdLimit(int dev, bool *enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_setClearPositionOnRevLimit(int dev, bool enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getClearPositionOnRevLimit(int dev, bool *enable, int tmsWait);
	DMC_Code c_DMC60CLowLevel_setIndexActiveEdge(int dev, bool edge, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getIndexActiveEdge(int dev, bool *edge, int tmsWait);
	DMC_Code c_DMC60CLowLevel_resetStickyFaults(int dev, int tmsWait);
	DMC_Code c_DMC60CLowLevel_resetOverTempStickyFaults(int dev, int tmsWait);
	DMC_Code c_DMC60CLowLevel_resetOverCurrentStickyFaults(int dev, int tmsWait);
	DMC_Code c_DMC60CLowLevel_resetUnderVoltageStickyFaults(int dev, int tmsWait);
	DMC_Code c_DMC60CLowLevel_resetGateDriverStickyFaults(int dev, int tmsWait);
	DMC_Code c_DMC60CLowLevel_resetCommStickyFaults(int dev, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getActiveFaults(int dev, uint32_t* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getStickyFaults(int dev, uint32_t* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getOverTempStickyFaultCount(int dev, uint32_t* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getOverCurrentStickyFaultCount(int dev, uint32_t* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getUnderVoltageStickyFaultCount(int dev, uint32_t* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getGateDriverStickyFaultCount(int dev, uint32_t* value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getCommStickyFaultCount(int dev, uint32_t* value, int tmsWait);
	void c_DMC60CLowLevel_setOverrideBC(int dev, uint8_t enable, uint8_t brakecoast);
	void c_DMC60CLowLevel_setReverse(int dev, bool reverse);
	void c_DMC60CLowLevel_setLimitSwitchOverride(int dev, bool enable, bool forwardSwitchEnable, bool reverseSwitchEnable);
	void c_DMC60CLowLevel_setReverseFeedbackSensor(int dev, bool reverse);
	void c_DMC60CLowLevel_setRampRate(int dev, unsigned short rampRate);
	void c_DMC60CLowLevel_sendControl1(int dev);
	void c_DMC60CLowLevel_sendControl2(int dev, ControlMode Mode, double trgt);
	void c_DMC60CLowLevel_sendControl3(int dev, ControlMode Mode, double trgt, uint16_t ramp, uint32_t periodMs);
	DMC_Code c_DMC60CLowLevel_getAnalogStatus(int dev, STSANALOG* analogStsOut);
	DMC_Code c_DMC60CLowLevel_getEncoderStatus(int dev, STSENCODER* stsEncoderOut);
	DMC_Code c_DMC60CLowLevel_getGeneralStatus(int dev, STSGENERAL* stsGeneralOut);
	void c_DMC60CLowLevel_SetControlMode(int dev, ControlMode Mode);
	ControlMode c_DMC60CLowLevel_GetControlMode(int dev);
	DMC_Code c_DMC60CLowLevel_setContinuousCurrentLimit(int dev, double currentAmps);
	DMC_Code c_DMC60CLowLevel_getContinuousCurrentLimit(int dev, double *currentAmps);
	DMC_Code c_DMC60CLowLevel_setPeakCurrentLimit(int dev, double currentAmps);
	DMC_Code c_DMC60CLowLevel_getPeakCurrentLimit(int dev, double *currentAmps);
	DMC_Code c_DMC60CLowLevel_setPeakCurrentDuration(int dev, int durationMs);
	DMC_Code c_DMC60CLowLevel_getPeakCurrentDuration(int dev, int *durationMs);
	DMC_Code c_DMC60CLowLevel_enableCurrentLimit(int dev, bool enabled);
	DMC_Code c_DMC60CLowLevel_isCurrentLimitEnabled(int dev, bool *enabled);
	DMC_Code c_DMC60CLowLevel_setCurrentLimitPGain(int dev, double P);
	DMC_Code c_DMC60CLowLevel_getCurrentLimitPGain(int dev, double *P);
	DMC_Code c_DMC60CLowLevel_setCurrentLimitIGain(int dev, double I);
	DMC_Code c_DMC60CLowLevel_getCurrentLimitIGain(int dev, double *I);
	DMC_Code c_DMC60CLowLevel_setCurrentLimitDGain(int dev, double D);
	DMC_Code c_DMC60CLowLevel_getCurrentLimitDGain(int dev, double *D);
	DMC_Code c_DMC60CLowLevel_setCurrentLimitFGain(int dev, double F);
	DMC_Code c_DMC60CLowLevel_getCurrentLimitFGain(int dev, double *F);
	DMC_Code c_DMC60CLowLevel_setCurrentLimitIZone(int dev, double I);
	DMC_Code c_DMC60CLowLevel_getCurrentLimitIZone(int dev, double *I);
	DMC_Code c_DMC60CLowLevel_setADCMultiplier(int dev, float value, int tmsWait);
	DMC_Code c_DMC60CLowLevel_getADCMultiplier(int dev, float* value, int tmsWait);

	DMC_Code c_DMC60CLowLevel_enterBootloader(int dev);
	DMC_Code c_DMC60CLowLevel_writeFlashPage(int dev, uint16_t imageType, uint8_t pageNum, uint8_t *pageBuf);
	DMC_Code c_DMC60CLowLevel_getFlashSequenceNumber(int dev, uint32_t *seqnum);
#ifdef __cplusplus
}
#endif
