#pragma once
#include <sys/types.h>
#include "MotorSafetyHelper.h"
#include "MotorSafety.h"
#include "ErrorBase.h"
#include "DMC60LowLevel.h"
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C"{
#endif

	int c_DMC60C_Create1(int deviceNumber);
	int c_DMC60C_Create2(int deviceNumber, double wheelDiametermm, double gearRatio, int encoderTicks);
	void c_DMC60C_Destroy(int dev);

	void c_DMC60C_configWheel(int dev, double wheelDiametermm, double gearRatio, int encoderTicks);
	DMC_Code c_DMC60C_configPID(int dev, unsigned int slot, float P, float I, float D, float F);

	DMC_Code c_DMC60C_configClosedLoopRampRate(int dev, unsigned int slot, unsigned int rampRate);
	void c_DMC60C_configOpenLoopRampRate(int dev, unsigned short rampRate);

	DMC_Code c_DMC60C_setContinuousCurrentLimit(int dev, double currentAmps);
	DMC_Code c_DMC60C_setPeakCurrentLimit(int dev, double currentAmps);
	DMC_Code c_DMC60C_setPeakCurrentDuration(int dev, int durationMs);
	DMC_Code c_DMC60C_enableCurrentLimiting(int dev, bool enabled);
	bool c_DMC60C_isCurrentLimitActive(int dev);

	ControlMode c_DMC60C_getControlMode(int dev);

	void c_DMC60C_driveVoltage(int dev, double percentVoltage);
	void c_DMC60C_drivePosition(int dev, double revolutions);
	void c_DMC60C_driveDistance(int dev, double meters);
	void c_DMC60C_driveVelocity(int dev, double metersPerSecond);
	void c_DMC60C_driveVoltageCompensation(int dev, double voltage);
	void c_DMC60C_driveCurrent(int dev, double currentAmps);
	void c_DMC60C_followerMode(int dev, int deviceNumbertoFollow);

	void c_DMC60C_setPIDSlot(int dev, unsigned int slot);
	float c_DMC60C_getP(int dev, unsigned int slot);
	float c_DMC60C_getI(int dev, unsigned int slot);
	float c_DMC60C_getD(int dev, unsigned int slot);
	float c_DMC60C_getF(int dev, unsigned int slot);
	float c_DMC60C_getClosedLoopError(int dev);

	void c_DMC60C_setLimitSwitches(int dev, bool overrideEnable, bool forwardSwitchEnable, bool reverseSwitchEnable);
	bool c_DMC60C_getFwdLimitSwitch(int dev);
	bool c_DMC60C_getRevLimitSwitch(int dev);
	bool c_DMC60C_isFwdLimitSwitchActive(int dev);
	bool c_DMC60C_isRevLimitSwitchActive(int dev);

	LimitSwitch c_DMC60C_getFwdLimitSwitchStatus(int dev);
	LimitSwitch c_DMC60C_getRevLimitSwitchStatus(int dev);

	bool c_DMC60C_isOverTempFaultActive(int dev);
	bool c_DMC60C_isUnderVoltageFaultActive(int dev);
	bool c_DMC60C_isGateDriveFaultActive(int dev);

	void c_DMC60C_setBrakeCoast(int dev, bool overrideEnable, bool brakeEnable);

	float c_DMC60C_getBusVoltage(int dev);
	float c_DMC60C_getAIN1Voltage(int dev);
	float c_DMC60C_getLoadCurrent(int dev);
	float c_DMC60C_getAmbientTemp(int dev);

	DMC_Code c_DMC60C_zeroEncoderPosition(int dev);
	double c_DMC60C_getRevolutionsTraveled(int dev);
	double c_DMC60C_getDistanceTraveled(int dev);
	double c_DMC60C_getMetersPerSecond(int dev);
	double c_DMC60C_getCurrentDutyCycle(int dev);
	int c_DMC60C_getEncoderPositionCount(int dev);
	int c_DMC60C_getEncoderVelocityCount(int dev);

	void c_DMC60C_disableMotor(int dev);

	bool c_DMC60C_isEnabled(int dev);
	void c_DMC60C_invertEncoder(int dev, bool isInverted);

	void c_DMC60C_configPositionReset(int dev, bool resetOnFwdLimit, bool resetOnRevLimit, bool resetOnIndex);
	void c_DMC60C_configIndexActiveEdge(int dev, bool edge);

	void c_DMC60C_Set(int dev, double speed);
	double c_DMC60C_Get(int dev);
	void c_DMC60C_SetInverted(int dev, bool isInverted);
	bool c_DMC60C_GetInverted(int dev);
	void c_DMC60C_Disable(int dev);

	//MotorSafety
	void c_DMC60C_SetExpiration(int dev, double timeout);
	double c_DMC60C_GetExpiration(int dev);
	bool c_DMC60C_IsAlive(int dev);
	void c_DMC60C_StopMotor(int dev);
	void c_DMC60C_SetSafetyEnabled(int dev, bool enabled);
	bool c_DMC60C_IsSafetyEnabled(int dev);
//	void c_DMC60C_GetDescription(int dev, llvm::raw_ostream& desc);




#ifdef __cplusplus
}
#endif
