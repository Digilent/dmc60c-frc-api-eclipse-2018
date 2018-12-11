#pragma once
#include "digilent.h"
#include "CANframes.h"
#include "Commands.h"
#include "Parameters.h"
#include "time.h"
#ifdef __cplusplus
#include <map>

namespace DMC60{
#endif
enum constructortype{ useDeviceNumber=0, useSessionID=1};
/**
 * \fn int32_t enumerateDMCs(DMCInfo_t *deviceBuffer)
 * \brief Enumerates all of the DMC60C devices on the CAN bus and stores them into the deviceBuffer.
 * \param deviceBuffer Pointer to a DMCInfo_t array to store enumerated device info.
 * \return Number of devices found on the CAN bus.
 */
int32_t enumerateDMCs(DMCInfo_t *deviceBuffer, int verbose);
void getDeviceDescriptors(DMCInfo_t *deviceBuffer, int verbose);
uint32_t parseDescriptors(uint8_t *pbDsc, uint8_t cbDsc, DMCInfo_t *dest);

/**
 * \class DMC60LowLevel
 *
 * \brief Low Level DMC60C Interface.
 *
 * This class contains all of the low level functions
 * used to communicate with the DMC60C.
 */
class DMC60LowLevel{
public:

	/**
	 * \fn DMC60LowLevel(int value = 0, int verbose = 0, constructortype type = constructortype::useDeviceNumber)
	 * \brief Creates a DMC60LowLevel object.
	 * \param value The deviceNumber of the DMC60C Motor. If type == useSessionID, this is the session ID of the device
	 * \param verbose A flag to enable verbose feedback.
	 * \param type If useDeviceNumber, value represents the deviceNumber of the DMC60C to connect to. If useSessionID, value represents the session ID of the DMC60C to connect to.
	 */
    DMC60LowLevel(int value = 0, int verbose=0, constructortype type = constructortype::useDeviceNumber);
	~DMC60LowLevel();



	/**
	 * \fn DMC_Code setDeviceNumber(uint16_t newdevnum)
	 * \brief Sets the deviceNumber of the DMC60C.
	 * \param newdevnum The desired device number (0-64).
	 * \return DMC_Code Status code.
	 */
	DMC_Code setDeviceNumber(uint16_t newdevnum);

	/**
	 * \fn uint8_t getDeviceNumber(uint16_t newdevnum)
	 * \brief Gets the deviceNumber of the DMC60C.
	 * \return Device number of DMC60C.
	 */
	uint8_t getDeviceNumber();

	/**
	 * \fn DMC_Code setDeviceName(char* szDevName, uint16_t cbName)
	 * \brief Sets the deviceName of the DMC60C.
	 * \param szDevName Character pointer to desired name.
	 * \param cbName Byte count of name.
	 * \return Status code.
	 */
	DMC_Code setDeviceName(char* szDevName, uint16_t cbName);

	/**
	 * \fn void getDeviceName(char* szNameBuf)
	 * \brief Gets the device name of the DMC60C.
	 * \param szNameBuf Buffer to store the name in.
	 */
	void getDeviceName(char* szNameBuf);

	/**
	 * \fn uint16_t getFWVerBoot()
	 * \brief Gets the bootloader firmware of the DMC60C.
	 * \return Firmware version of bootloader.
	 */
	uint16_t getFWVerBoot();

	/**
	 * \fn uint16_t getFWVerApp()
	 * \brief Gets the application firmware of the DMC60C.
	 * \return Firmware version of application.
	 */
	uint16_t getFWVerApp();

	/**
	 * \fn uint8_t getImgType()
	 * \brief Returns the currently running image type (bootloader, application, or aux bootloader).
	 * \return 0 = App, 1 = Bootloader, 2 = Aux Bootloader.
	 */
	uint8_t getImgType();

	/**
	 * \fn uint16_t getSessId()
	 * \brief Returns the session ID assigned to the DMC60C.
	 * \return Session ID.
	 */
	uint16_t getSessId();

	/**
	 * \fn DMC_Code fetchFWVer()
	 * \brief Retrieves the device's firmware version information. This includes application firmware revision, bootloader
	 * firmware revision, and the time of firmware image that is currently running. This information is stored in the private
	 * member DMCInfo, and can be read with the get commands.
	 * \return Firmware version of application.
	 */
	DMC_Code fetchFWVer();

	/**
	 * \fn DMC_Code softReset()
	 * \brief Returns the session ID assigned to the DMC60C.
	 * \return Status Code.
	 */
	DMC_Code softReset();

	/**
		 * \fn DMC_Code flashLEDs()
		 * \brief Flashes the LEDs on the DMC60C in a rainbow pattern for 5 seconds.
		 * \return Status Code.
		 */
	DMC_Code flashLEDs();

	/**
	 * \fn void setPIDSlot(uint8_t slotNum)
	 * \brief Sets the active PID slot used by the DMC60C.
	 */
	void setPIDSlot(uint8_t slotNum);

	/**
	 * \fn DMC_Code configPID_RampRate(uint8_t slot, uint32_t ramp, int tmsWait)
	 * \brief Configure the closed loop ramp rate used by the specified closed loop profile slot. The closed loop ramp rate
	 * specifies the maximum number of throttle units the output can change by each time the control loop executes in closed
	 * loop control mode (Velocity, Position, or Current). For example, If the closed loop ramp rate is set to 1000 and the PID
	 * update function determines that the throttle should be increased by 5000 units then the immediate throttle increase will
	 * be limited to 1000 units. If the next PID Update doesn’t change the target throttle output value, the throttle will be
	 * increased by another 1000 units the next time the control loop executes. This process will continue until the target throttle
	 * is reached or a new throttle value is calculated. The control loop executes once every 500 µs. Therefore, specifying a closed
	 * loop ramp rate of 16 would result in it taking approximately 1.02 seconds to go from 0% throttle (0) to 100% throttle (32767).
	 * Specifying a value of 0 for the closed loop ramp rate disables throttling and allows the output to be immediately set to the
	 * target value. This parameter is stored in nonvolatile memory and is preserved across power cycles.
	 * \param slot PID slot to configure.
	 * \param ramp Desired ramp rate.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_RampRate(uint8_t slot, uint32_t ramp, int tmsWait);

	/**
	 * \fn DMC_Code getPID_RampRate(uint8_t slot, uint32_t *ramp, int tmsWait)
	 * \brief Gets the ramp rate value stored in the specified PID slot.
	 * \param slot PID slot to configure.
	 * \param ramp Buffer to store ramp rate.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getPID_RampRate(uint8_t slot, uint32_t *ramp, int tmsWait);

	/**
	 * \fn DMC_Code configPID_FwdMaxDuty(uint8_t slot, int value, int tmsWait)
	 * \brief Configure the closed loop control maximum forward duty cycle used by the specified motor control profile slot. The
	 * maximum forward duty cycle is the largest positive duty cycle that may be applied to the output when motor control profile
	 * slot 0 is specified in a control frame that specifies one of the closed loop control modes (Velocity, Position, or Current).
	 * The value specified for this parameter should be restricted to be within the range of 0 to 32767. This parameter is stored
	 * in nonvolatile memory and is preserved across power cycles.
	 * \param slot PID slot to configure.
	 * \param value Max forward duty cycle (0-32767).
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_FwdMaxDuty(uint8_t slot, int value, int tmsWait);

	/**
	 * \fn DMC_Code getPID_FwdMaxDuty(uint8_t slot, int *value, int tmsWait)
	 * \brief Gets the forward max duty cycle stored in the specified PID slot.
	 * \param slot PID slot to read from.
	 * \param value Buffer to store the ramp rate value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getPID_FwdMaxDuty(uint8_t slot, int *value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_RevMaxDuty(uint8_t slot, int value, int tmsWait)
	 * \brief Configure the closed loop control maximum reverse duty cycle used by the specified motor control profile slot. The
	 * maximum reverse duty cycle is the largest negative duty cycle that may be applied to the output when motor control profile
	 * slot 0 is specified in a control frame that specifies one of the closed loop control modes (Velocity, Position, or Current).
	 * The value specified for this parameter should be restricted to be within the range of -32768 to 0. This parameter is stored in
	 * nonvolatile memory and is preserved across power cycles.
	 * \param slot PID slot to configure.
	 * \param value Max reverse duty cycle (-32768 to 0).
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_RevMaxDuty(uint8_t slot, int value, int tmsWait);

	/**
	 * \fn DMC_Code getPID_RevMaxDuty(uint8_t slot, int *value, int tmsWait)
	 * \brief Gets the reverse max duty cycle stored in the specified PID slot.
	 * \param slot PID slot to read from.
	 * \param value Buffer to store the ramp rate value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getPID_RevMaxDuty(uint8_t slot, int *value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_FwdNominal(uint8_t slot, int value, int tmsWait)
	 * \brief Configure the closed loop control nominal forward duty cycle used by the specified motor control profile slot. The nominal
	 * forward duty cycle is the smallest positive duty cycle that may be applied to the output when the closed loop error exceeds the
	 * allowable closed loop error specified for the selected motor profile slot. The closed loop nominal forward duty cycle is only utilized
	 * when the control frame specifies one of the closed loop control modes (Velocity, Position, or Current). The value specified for this
	 * parameter should be restricted to be within the range of 0 to 32767. This parameter is stored in nonvolatile memory and is preserved
	 * across power cycles.
	 * \param slot PID slot to configure.
	 * \param value Closed loop nominal duty cycle (0 to 32767).
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_FwdNominal(uint8_t slot, int value, int tmsWait);

	/**
	 * \fn DMC_Code getPID_FwdNominal(uint8_t slot, int *value, int tmsWait)
	 * \brief Gets the forward nominal duty cycle stored in the specified PID slot.
	 * \param slot PID slot to read from.
	 * \param value Buffer to store the forward nominal duty cycle value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getPID_FwdNominal(uint8_t slot, int *value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_RevNominal(uint8_t slot, int value, int tmsWait)
	 * \brief Configure the closed loop control nominal reverse duty cycle used by the specified motor control profile slot. The nominal
	 * reverse duty cycle is the smallest negative duty cycle that may be applied to the output when the closed loop error exceeds the
	 * allowable closed loop error specified for the selected motor profile slot. The closed loop nominal reverse duty cycle is only utilized
	 * when the control frame specifies one of the closed loop control modes (Velocity, Position, or Current). The value specified for this
	 * parameter should be restricted to be within the range of -32768 to 0. This parameter is stored in nonvolatile memory and is preserved
	 * across power cycles.
	 * \param slot PID slot to configure.
	 * \param value Closed loop nominal duty cycle (-32768 to 0).
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_RevNominal(uint8_t slot, int value, int tmsWait);

	/**
	 * \fn DMC_Code getPID_RevNominal(uint8_t slot, int *value, int tmsWait)
	 * \brief Gets the reverse nominal duty cycle stored in the specified PID slot.
	 * \param slot PID slot to read from.
	 * \param value Buffer to store the reverse nominal duty cycle value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getPID_RevNominal(uint8_t slot, int *value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_kP(uint8_t slot, float value, int tmsWait)
	 * \brief Configure the proportional gain constant used by the specified motor control profile slot. This constant is used during closed
	 * loop control to calculate a proportional increase or decrease in the throttle (duty cycle) due to the measured closed loop error. This
	 * parameter will be utilized for PID calculations when motor control profile slot 1 is specified in a control frame that specifies one of
	 * the closed loop control modes (Velocity, Position, or Current). This parameter is stored in nonvolatile memory and is preserved across
	 * power cycles.
	 * \param slot PID slot to configure.
	 * \param value P gain value to assign.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_kP(uint8_t slot, float value, int tmsWait);

	/**
	 * \fn DMC_Code get_kP(uint8_t slot, float* value, int tmsWait)
	 * \brief Reads the P gain value of the specified slot and stores the value into a pointer.
	 * \param slot PID slot to read.
	 * \param value Pointer to store value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code get_kP(uint8_t slot, float* value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_kI(uint8_t slot, float value, int tmsWait)
	 * \brief Configure the integral gain constant used by the specified motor control profile slot. This constant is used during closed loop
	 * control to calculate an integral increase or decrease in the throttle (duty cycle) due to the measured closed loop error. This parameter
	 * will be utilized for PID calculations when motor control profile slot 1 is specified in a control frame that specifies one of the closed
	 * loop control modes (Velocity, Position, or Current). This parameter is stored in nonvolatile memory and is preserved across power cycles.
	 * \param slot PID slot to configure.
	 * \param value I gain value to assign.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_kI(uint8_t slot, float value, int tmsWait);

	/**
	 * \fn DMC_Code get_kI(uint8_t slot, float* value, int tmsWait)
	 * \brief Reads the I gain value of the specified slot and stores the value into a pointer.
	 * \param slot PID slot to read.
	 * \param value Pointer to store value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code get_kI(uint8_t slot, float* value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_kD(uint8_t slot, float value, int tmsWait)
	 * \brief Configure the derivative gain constant used by the specified motor control profile slot. This constant is used during closed loop
	 * control to calculate the derivative increase or decrease in the throttle (duty cycle) due to the measured closed loop error. This parameter
	 * will be utilized for PID calculations when motor control profile slot 1 is specified in a control frame that specifies one of the closed
	 * loop control modes (Velocity, Position, or Current). This parameter is stored in nonvolatile memory and is preserved across power cycles.
	 * \param slot PID slot to configure.
	 * \param value D gain value to assign.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_kD(uint8_t slot, float value, int tmsWait);

	/**
	 * \fn DMC_Code get_kD(uint8_t slot, float* value, int tmsWait)
	 * \brief Reads the D gain value of the specified slot and stores the value into a pointer.
	 * \param slot PID slot to read.
	 * \param value Pointer to store value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code get_kD(uint8_t slot, float* value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_kF(uint8_t slot, float value, int tmsWait)
	 * \brief Configure the feed-forward gain constant used by the specified motor control profile slot. This constant is used during closed loop
	 * control to calculate the number of throttle units to contribute to the duty cycle as the proportion of the setpoint (target Velocity,
	 * Position, or Current) independent of the error. For example, if the target current is 20.0 amps and you want to apply 50% throttle for this
	 * setpoint then the feed forward gain would be set to (0.50×32767)/20.0=819.175. Convert this to fixed-point by multiplying by 65536. This
	 * results in a value of 0x03332CCC (hex), which is what should be sent to the DMC60 in the value field of the PARAMSET packet. The feed-forward
	 * term can be excluded from the PID calculations by specifying a value of 0 for the gain. This parameter will be utilized for PID calculations
	 * when motor control profile slot 1 is specified in a control frame that specifies one of the closed loop control modes (Velocity, Position,
	 * or Current). This parameter is stored in nonvolatile memory and is preserved across power cycles.
	 * \param slot PID slot to configure.
	 * \param value F gain value to assign.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_kF(uint8_t slot, float value, int tmsWait);

	/**
	 * \fn DMC_Code get_kF(uint8_t slot, float* value, int tmsWait)
	 * \brief Reads the F gain value of the specified slot and stores the value into a pointer.
	 * \param slot PID slot to read.
	 * \param value Pointer to store value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code get_kF(uint8_t slot, float* value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_IZone(uint8_t slot, unsigned int value, int tmsWait)
	 * \brief Configure the integral accumulator limit used by motor control profile slot 0. The integral accumulator limit, or I-zone, is used to
	 * limit how large the integral accumulator can grow during closed loop control. The value sent to the DMC60 is converted to a 32-bit signed
	 * integer and used to set the positive and negative bounds of the integral accumulator. If the integral accumulator exceeds these bounds while
	 * PID calculations are performed, then the accumulator will be capped to value or -value. This provides a mechanism for combating integral windup.
	 * Setting a value of 0 will disable the limit and allow the integral accumulator to grow without bounds. This parameter is stored in nonvolatile
	 * memory and is preserved across power cycles.
	 * \param slot PID slot to configure.
	 * \param value Izone value to assign.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_IZone(uint8_t slot, unsigned int value, int tmsWait);

	/**
	 * \fn DMC_Code get_IZone(uint8_t slot, unsigned int *value, int tmsWait)
	 * \brief Gets the current Izone value stored in the specified PID slot.
	 * \param slot PID slot to configure.
	 * \param value Buffer to store Izone value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code get_IZone(uint8_t slot, unsigned int *value, int tmsWait);

	/**
	 * \fn DMC_Code configPID_AllowableError(uint8_t slot, uint32_t value, int tmsWait)
	 * \brief Configure the allowable closed loop error used by the specified motor control profile slot. The allowable closed loop error specifies
	 * the minimum error required for the PID controller to calculate a non-zero contribution to the output throttle (duty cycle) based on the P, I,
	 * and D terms. If the allowable error is set to a non-zero value and the measured error is less than the allowable error then the P, I, and D
	 * terms will contribute 0 throttle units to the output throttle calculation and the integral accumulator will be cleared. If the allowable error
	 * is set to 0 or the measured error exceeds the allowable error then P, I, and D terms are included in the output throttle calculation. The
	 * feed-forward gain constant, or F term, is included in the output throttle calculation regardless of the allowable error setting. This parameter
	 * will be utilized for PID calculations when motor control profile slot 1 is specified in a control frame that specifies one of the closed loop
	 * control modes (Velocity, Position, or Current). This parameter is stored in nonvolatile memory and is preserved across power cycles.
	 * \param slot PID slot to configure.
	 * \param value Allowable closed loop error.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configPID_AllowableError(uint8_t slot, uint32_t value, int tmsWait);

	/**
	 * \fn DMC_Code getPID_AllowableError(uint8_t slot, uint32_t *value, int tmsWait)
	 * \brief Gets the allowable error value stored in the specified PID slot.
	 * \param slot PID slot to configure.
	 * \param value Buffer to store the allowable error value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getPID_AllowableError(uint8_t slot, uint32_t *value, int tmsWait);

	/**
	 * \fn DMC_Code configForwardLimitSwitchEnable(bool enable, int tmsWait)
	 * \brief Sets whether or not the forward limit switch is enabled or not.
	 * \param enable True if enabled, false if not.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configForwardLimitSwitchEnable(bool enable, int tmsWait);

	/**
	 * \fn DMC_Code getForwardLimitSwitchEnable(bool *enable, int tmsWait)
	 * \brief Gets whether or not the forward limit switch is enabled or not.
	 * \param enable Pointer to store the enabled value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getForwardLimitSwitchEnable(bool *enable, int tmsWait);

	/**
	 * \fn DMC_Code configForwardLimitSwitchType(bool normallyClosed, int tmsWait)
	 * \brief Sets the switch type of the forward limit switch.
	 * \param normallyClosed False if the switch is normally opened, true if normally closed.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configForwardLimitSwitchType(bool normallyClosed, int tmsWait);

	/**
	 * \fn DMC_Code getForwardLimitSwitchType(bool *normallyClosed, int tmsWait)
	 * \brief Gets the switch type of the forward limit switch.
	 * \param normallyClosed Pointer to store the switch type value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getForwardLimitSwitchType(bool *normallyClosed, int tmsWait);

	/**
	 * \fn DMC_Code configReverseLimitSwitchEnable(bool enable, int tmsWait)
	 * \brief Sets whether or not the reverse limit switch is enabled or not.
	 * \param enable True if enabled, false if not.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configReverseLimitSwitchEnable(bool enable, int tmsWait);
	/**
	 * \fn DMC_Code getReverseLimitSwitchEnable(bool *enable, int tmsWait)
	 * \brief Gets whether or not the reverse limit switch is enabled or not.
	 * \param enable Pointer to store the enabled value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getReverseLimitSwitchEnable(bool *enable, int tmsWait);

	/**
	 * \fn DMC_Code configReverseLimitSwitchType(bool normallyClosed, int tmsWait)
	 * \brief Sets the switch type of the reverse limit switch.
	 * \param normallyClosed False if the switch is normally opened, true if normally closed.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configReverseLimitSwitchType(bool normallyClosed, int tmsWait);

	/**
	 * \fn DMC_Code getReverseLimitSwitchType(bool *normallyClosed, int tmsWait)
	 * \brief Gets the switch type of the reverse limit switch.
	 * \param normallyClosed Pointer to store the switch type value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getReverseLimitSwitchType(bool *normallyClosed, int tmsWait);

	/**
	 * \fn DMC_Code configSoftFwdThreshold(bool enable, int limit, int tmsWait)
	 * \brief Configure the soft forward limit threshold. The soft forward limit threshold specifies the maximum position that the encoder can read
	 * in the forward direction. The units are native to the encoder that’s connected to the expansion header. The DMC60’s control loop runs every
	 * 500us. Each time it executes the current position of the encoder is read and compared to the soft forward limit threshold. If the encoder’s
	 * current position is greater than or equal to the specified soft forward limit threshold and the soft forward limit is enabled, then the DMC60’s
	 * output will be prevented from applying a positive voltage to the load. Both positive and negative soft limit thresholds are valid. This parameter
	 * is stored in nonvolatile memory and is preserved across power cycles
	 * \param enable Enables or disables the forward soft limit.
	 * \param limit Soft forward limit threshold.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configSoftFwdThreshold(bool enable, int limit, int tmsWait);

	/**
	 * \fn DMC_Code getSoftFwdThreshold(bool *enable, int *limit, int tmsWait)
	 * \brief Gets the current soft forward threshold value.
	 * \param enable Buffer to store the enabled bit.
	 * \param limit Buffer to store the limit value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getSoftFwdThreshold(bool *enable, int *limit, int tmsWait);

	/**
	 * \fn DMC_Code configSoftRevThreshold(bool enable, int limit, int tmsWait)
	 * \brief Configure the reverse limit switch type. The reverse limit switch be configured as a normally closed switch by setting the value field to
	 * a ‘1’ or a normally open switch by setting the value field to a ‘0’. The DMC60 uses internal (weak) pull-ups to pull the reverse limit switch pin
	 * to 3.3V. When configured as a normally closed switch the DMC60 will prevent the output from applying a negative voltage to the load when the
	 * limit switch opens, causing the DMC60 to detect a logic ‘1’ on the REVLIM pin. When configured as a normally open switch the DMC60 will prevent
	 * the output from applying a negative voltage to the load when the limit switch closes, causing the DMC60 to detect a logic ‘0’ on the REVLIM pin.
	 * This parameter is stored in nonvolatile memory and is preserved across power cycles.
	 * \param enable Enables or disables the reverse soft limit.
	 * \param limit Soft reverse limit threshold.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configSoftRevThreshold(bool enable, int limit, int tmsWait);

	/**
	 * \fn DMC_Code getSoftRevThreshold(bool *enable, int *limit, int tmsWait)
	 * \brief Gets the current soft reverse threshold value.
	 * \param enable Buffer to store the enabled bit.
	 * \param limit Buffer to store the limit value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getSoftRevThreshold(bool *enable, int *limit, int tmsWait);

	/**
	 * \fn DMC_Code configAnalogStatusFramePeriod(uint32_t periodMs, int tmsWait)
	 * \brief Configure the rate at which the DMC60 transmits Analog Input, Current, Temperature, and Battery Voltage Status Frames. These status frames are
	 * formatted as STSANALOG packets and are described in the Periodic Status Messages section. The frame rate can be set to any value between 1 millisecond
	 * and 30000 milliseconds. Power cycling the DMC60 will result in the device reverting to the default frame rate, which is 100 milliseconds.
	 * \param periodMs Frame period in milliseconds.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configAnalogStatusFramePeriod(uint32_t periodMs, int tmsWait);

	/**
	 * \fn DMC_Code getAnalogStatusFramePeriod(uint32_t *periodMs, int tmsWait)
	 * \brief Gets the current analog status frame period.
	 * \param periodMs Buffer to store the period.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getAnalogStatusFramePeriod(uint32_t *periodMs, int tmsWait);

	/**
	 * \fn DMC_Code configEncoderStatusFramePeriod(uint32_t periodMs, int tmsWait)
	 * \brief Configure the rate at which the DMC60 transmits Quadrature Encoder Status Frames. These status frames are formatted as STSENCODER packets and
	 * are described in the Periodic Status Messages section. The frame rate can be set to any value between 1 millisecond and 30000 milliseconds. Power
	 * cycling the DMC60 will result in the device reverting to the default frame rate, which is 100 milliseconds.
	 * \param periodMs Frame period in milliseconds.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configEncoderStatusFramePeriod(uint32_t periodMs, int tmsWait);

	/**
	 * \fn DMC_Code getEncoderStatusFramePeriod(uint32_t *periodMs, int tmsWait)
	 * \brief Get the current encoder status frame period.
	 * \param periodMs Buffer to store the period.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getEncoderStatusFramePeriod(uint32_t *periodMs, int tmsWait);

	/**
	 * \fn DMC_Code configGeneralStatusFramePeriod(uint32_t periodMs, int tmsWait)
	 * \brief Configure the rate at which the DMC60 transmits General Status Frames. These status frames are formatted as STSGENERAL packets and
	 * are described in the Periodic Status Messages section. The frame rate can be set to any value between 1 millisecond and 30000 milliseconds. Power
	 * cycling the DMC60 will result in the device reverting to the default frame rate, which is 10 milliseconds.
	 * \param periodMs Frame period in milliseconds.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code configGeneralStatusFramePeriod(uint32_t periodMs, int tmsWait);

	/**
	 * \fn DMC_Code getGeneralStatusFramePeriod(uint32_t *periodMs, int tmsWait)
	 * \brief Get the current general status frame period.
	 * \param periodMs Buffer to store the period.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getGeneralStatusFramePeriod(uint32_t *periodMs, int tmsWait);

	/**
	 * \fn DMC_Code setEncoderPosition(int position, int tmsWait)
	 * \brief Configure the encoder position. The encoder position is maintained by the QEI module of the DMC60’s MCU and is continuously updated by the
	 * pulse train applied to QEA and QEB inputs of the expansion header. At power on the encoder’s position is initialized to zero. This may not correspond
	 * with the zero point that’s defined in the end user application, and as such, it may be necessary to set the encoder to a specific position or reset
	 * it to 0 after performing a homing sequence. The encoder’s position is used for closed loop position control and for determining whether the forward
	 * soft limit or reverse soft limit have been hit. The encoder position should only be configured while the DMC60’s output is disabled.
	 * \param position 32 bit signed encoder position.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code setEncoderPosition(int position, int tmsWait);

	/**
	 * \fn DMC_Code getEncoderPosition(int *position, int tmsWait)
	 * \brief Configure the encoder position. The encoder position is maintained by the QEI module of the DMC60’s MCU and is continuously updated by the
	 * pulse train applied to QEA and QEB inputs of the expansion header. At power on the encoder’s position is initialized to zero. This may not correspond
	 * with the zero point that’s defined in the end user application, and as such, it may be necessary to set the encoder to a specific position or reset
	 * it to 0 after performing a homing sequence. The encoder’s position is used for closed loop position control and for determining whether the forward
	 * soft limit or reverse soft limit have been hit. The encoder position should only be configured while the DMC60’s output is disabled.
	 * \param *position Integer to store position.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getEncoderPosition(int *position, int tmsWait);

	/**
	 * \fn DMC_Code setClearPositionOnIndex(bool enable, int tmsWait)
	 * \brief Sets whether or not the index pin will cause the position count to reset.
	 * \param enable True to enable position count reset on active edge of index.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code setClearPositionOnIndex(bool enable, int tmsWait);

	/**
	 * \fn DMC_Code getClearPositionOnIndex(bool *enable, int tmsWait)
	 * \brief Gets whether or not the index pin will cause the position count to reset.
	 * \param enable Buffer to store the result.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getClearPositionOnIndex(bool *enable, int tmsWait);

	/**
	 * \fn DMC_Code setClearPositionOnFwdLimit(bool enable, int tmsWait)
	 * \brief Sets whether or not the forward limit switch pin will cause the position count to reset.
	 * \param enable True to enable position count reset on active edge of fwd limit switch.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code setClearPositionOnFwdLimit(bool enable, int tmsWait);

	/**
	 * \fn DMC_Code getClearPositionOnFwdLimit(bool *enable, int tmsWait)
	 * \brief Gets whether or not the fwd limit switch pin will cause the position count to reset.
	 * \param enable Buffer to store the result.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getClearPositionOnFwdLimit(bool *enable, int tmsWait);

	/**
	 * \fn DMC_Code setClearPositionOnRevLimit(bool enable, int tmsWait)
	 * \brief Sets whether or not the reverse limit switch pin will cause the position count to reset.
	 * \param enable True to enable position count reset on active edge of rev limit switch.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code setClearPositionOnRevLimit(bool enable, int tmsWait);

	/**
	 * \fn DMC_Code getClearPositionOnRevLimit(bool *enable, int tmsWait)
	 * \brief Gets whether or not the reverse limit switch pin will cause the position count to reset.
	 * \param enable Buffer to store the result.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getClearPositionOnRevLimit(bool *enable, int tmsWait);

	/**
	 * \fn DMC_Code setIndexActiveEdge(bool edge, int tmsWait)
	 * \brief Sets the active edge of the index  pin.
	 * \param edge True for rising edge, false for falling edge.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code setIndexActiveEdge(bool edge, int tmsWait);

	/**
	 * \fn DMC_Code getIndexActiveEdge(bool *edge, int tmsWait)
	 * \brief Gets the active edge of the index  pin.
	 * \param edge Buffer to store the result.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getIndexActiveEdge(bool *edge, int tmsWait);

	/**
	 * \fn DMC_Code resetStickyFaults(int tmsWait)
	 * \brief Resets the counts stored in the sticky faults.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code resetStickyFaults(int tmsWait);

	/**
	 * \fn DMC_Code resetOverTempStickyFaults(int tmsWait)
	 * \brief Resets the overtemp sticky fault count.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code resetOverTempStickyFaults(int tmsWait);

	/**
	 * \fn DMC_Code resetOverCurrentStickyFaults(int tmsWait)
	 * \brief Resets the overcurrent sticky fault count.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code resetOverCurrentStickyFaults(int tmsWait);

	/**
	 * \fn DMC_Code resetUnderVoltageStickyFaults(int tmsWait)
	 * \brief Resets the undervoltage sticky fault count.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code resetUnderVoltageStickyFaults(int tmsWait);

	/**
	 * \fn DMC_Code resetGateDriverStickyFaults(int tmsWait)
	 * \brief Resets the gate driver sticky fault count.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code resetGateDriverStickyFaults(int tmsWait);

	/**
	 * \fn DMC_Code resetCommStickyFaults(int tmsWait)
	 * \brief Resets the comm sticky fault count.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code resetCommStickyFaults(int tmsWait);

	/**
	 * \fn DMC_Code getActiveFaults(uint32_t* value, int tmsWait)
	 * \brief Retrieves the active fault bit field from the motor controller.
	 * \param value Buffer to store the active faults into.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getActiveFaults(uint32_t* value, int tmsWait);

	/**
	 * \fn DMC_Code getStickyFaults(uint32_t* value, int tmsWait)
	 * \brief Retrieves the sticky fault bit field from the motor controller.
	 * \param value Buffer to store the sticky faults into.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getStickyFaults(uint32_t* value, int tmsWait);

	/**
	 * \fn DMC_Code getOverTempStickyFaultCount(uint32_t* value, int tmsWait)
	 * \brief Retrieves the number of over temp sticky faults.
	 * \param value Buffer to store the number into.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getOverTempStickyFaultCount(uint32_t* value, int tmsWait);

	/**
	 * \fn DMC_Code getOverCurrentStickyFaultCount(uint32_t* value, int tmsWait)
	 * \brief Retrieves the number of over current sticky faults.
	 * \param value Buffer to store the number into.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getOverCurrentStickyFaultCount(uint32_t* value, int tmsWait);

	/**
	 * \fn DMC_Code getUnderVoltageStickyFaultCount(uint32_t* value, int tmsWait)
	 * \brief Retrieves the number of under voltage sticky faults.
	 * \param value Buffer to store the number into.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getUnderVoltageStickyFaultCount(uint32_t* value, int tmsWait);

	/**
	 * \fn DMC_Code getGateDriverStickyFaultCount(uint32_t* value, int tmsWait)
	 * \brief Retrieves the number of gate driver sticky faults.
	 * \param value Buffer to store the number into.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getGateDriverStickyFaultCount(uint32_t* value, int tmsWait);

	/**
	 * \fn DMC_Code getCommStickyFaultCount(uint32_t* value, int tmsWait)
	 * \brief Retrieves the number of comm sticky faults.
	 * \param value Buffer to store the number into.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code getCommStickyFaultCount(uint32_t* value, int tmsWait);

	/**
	 * \fn void setOverrideBC(uint8_t enable, uint8_t brakecoast)
	 * \brief Sets the brake/coast mode override.
	 * \param enable Enable the override.
	 * \param brakecoast 0: Coast when neutral throttle is applied	1: Brake when neutral throttle is applied.
	 */
	void setOverrideBC(bool enable, bool brakecoast);

	/**
	 * \fn void setReverse(bool reverse)
	 * \brief Sets the reverse bit in control0 frame. This causes the motor controller to reverse drive of the motor.
	 * \param reverse true = Reversed, false = Not reversed.
	 */
	void setReverse(bool reverse);

	/**
	 * \fn void setLimitSwitchOverride(bool enable, bool forwardSwitchEnable, bool reverseSwitchEnable)
	 * \brief Sets the override bits in the control frame. This overrides the limit switch parameters to allow enabling and disabling
	 * the limit switches realtime,
	 * \param enable Enables the override.
	 * \param forwardSwitchEnable True = Enable forward limit switch when override is enabled. False = Disable forward limit switch
	 * when override is enabled.
	 * \param reverseSwitchEnable True = Enable reverse limit switch when override is enabled. False = Disable reverse limit switch
	 * when override is enabled.
	 */
	void setLimitSwitchOverride(bool enable, bool forwardSwitchEnable, bool reverseSwitchEnable);

	/**
	 * \fn void setReverseFeedbackSensor(bool reverse)
	 * \brief Sets the reverse bit in control0 frame. This causes the motor controller to reverse drive of the motor.
	 * \param reverse true = Reversed, false = Not reversed.
	 */
	void setReverseFeedbackSensor(bool reverse);

	/**
	 * \fn void setRampRate(unsigned short rampRate)
	 * \brief Sets the open loop ramp rate that is sent within each control0 frame.
	 * \param rampRate The open loop ramp rate. The lower it is, the slower it will ramp.
	 */
	void setRampRate(unsigned short rampRate);

	/**
	 * \fn void sendControl()
	 * \brief Resends the control0 frame. If it has not been sent before, it will start sending the default _control0 frame at 100ms
	 */
	void sendControl();

	/**
	 * \fn void sendControl(ControlMode Mode, double trgt)
	 * \brief Sends the control0 frame with the specified parameters at a specified period. This is the main control of the DMC60C.
	 * This frame must be sent every 104ms or the DMC60C will go into standby mode.
	 * \param Mode The control mode.
	 * \param trgt The target setpoint of the specified control mode.
	 */
	void sendControl(ControlMode Mode, double trgt);

	/**
	 * \fn void sendControl(ControlMode Mode, double trgt, uint16_t ramp, uint32_t periodMs)
	 * \brief Sends the control0 frame with the specified parameters at a specified period. This is the main control of the DMC60C.
	 * This frame must be sent every 104ms or the DMC60C will go into standby mode.
	 * \param Mode The control mode.
	 * \param trgt The target setpoint of the specified control mode.
	 * \param ramp The open loop ramp rate (not applicable in closed loop mode).
	 * \param periodMs The period to send the control0 frame at.
	 */
	void sendControl(ControlMode Mode, double trgt, uint16_t ramp, uint32_t periodMs);

	/**
	 * \fn DMC_Code getAnalogStatus(STSANALOG* stsAnalogOut)
	 * \brief Retrieves the latest STSANALOG frame from the DMC60C.
	 * \param stsAnalogOut Pointer to STSANALOG buffer to store data into.
	 * \return Status code.
	 */
	DMC_Code getAnalogStatus(STSANALOG* stsAnalogOut);

	/**
	 * \fn DMC_Code getEncoderStatus(STSENCODER* stsEncoderOut)
	 * \brief Retrieves the latest STSENCODER frame from the DMC60C.
	 * \param stsEncoderOut Pointer to STSENCODER buffer to store data into.
	 * \return Status code.
	 */
	DMC_Code getEncoderStatus(STSENCODER* stsEncoderOut);

	/**
	 * \fn DMC_Code getGeneralStatus(STSGENERAL* stsGeneralOut)
	 * \brief Retrieves the latest STSGENERAL frame from the DMC60C.
	 * \param stsGeneralOut Pointer to STSGENERAL buffer to store data into.
	 * \return Status code.
	 */
	DMC_Code getGeneralStatus(STSGENERAL* stsGeneralOut);

	/**
	 * \fn void SetControlMode(ControlMode Mode)
	 * \brief Sets the ControlMode in the control0 frame. The frame must be resent with sendControl() to have any effect, although
	 * this is not recommended in most cases.
	 * \param Mode Control mode to set to.
	 */
	void SetControlMode(ControlMode Mode);


	/**
	 * \fn ControlMode GetControlMode()const
	 * \brief Returns the current controlMode in the control0 frame.
	 * \return The current control mode.
	 */
	ControlMode GetControlMode()const;

	/**
	 * \fn DMC_Code setContinuousCurrentLimit(double currentAmps)
	 * \brief Sets the continuous current limit. This applies only if current limiting is enabled. The continuous current limit is the maximum current
	 * that can be drawn by the DMC60C AFTER the peak current limit has been hit for the peak current duration. If the continuous current limit is greater
	 * than or equal to the peak current limit, then the DMC60C will begin limiting the current immediately after the continuous current limit is exceeded.
	 * \param currentAmps The continuous current limit to set in amps.
	 * \return DMC_Code Status code.
	 */
	DMC_Code setContinuousCurrentLimit(double currentAmps);

	/**
	 * \fn DMC_Code getContinuousCurrentLimit(double currentAmps)
	 * \brief Gets the continuous current limit.
	 * \param currentAmps Buffer to store the value.
	 * \return DMC_Code Status code.
	 */
	DMC_Code getContinuousCurrentLimit(double *currentAmps);

	/**
	 * \fn DMC_Code setPeakCurrentLimit(double currentAmps)
	 * \brief Sets the peak current limit. This only applies if current limiting is enabled. The peak current is the max current that can be applied to the
	 * motor at any given time. This limit can be applied for up to [peak current duration] milliseconds. Afterwards the continuous current limit will be
	 * applied. If the peak current limit is set to a value lower than the continuous current limit, the DMC60C will apply the continuous current limit
	 * immediately after it detects that
	 * the continuous current limit has been exceeded.
	 * \param currentAmps The peak current limit to set in amps.
	 * \return DMC_Code Status code.
	 */
	DMC_Code setPeakCurrentLimit(double currentAmps);

	/**
	 * \fn DMC_Code getPeakCurrentLimit(double currentAmps)
	 * \brief Gets the peak current limit.
	 * \param currentAmps Buffer to store the value.
	 * \return DMC_Code Status code.
	 */
	DMC_Code getPeakCurrentLimit(double *currentAmps);

	/**
	 * \fn DMC_Code setPeakCurrentDuration(int durationMs)
	 * \brief Sets the peak current duration. This only applies if current limiting is enabled. The peak current duration is the maximum amount of time the
	 * peak current can be applied to the motor. After this duration, the continuous current limit will be applied. If the duration is set to 0, the DMC60C
	 * will begin applying the continuous current limit immediately after the peak current limit has been exceeded.
	 * \param durationMs The peak current duration in milliseconds.
	 * \return DMC_Code Status code.
	 */
	DMC_Code setPeakCurrentDuration(int durationMs);

	/**
	 * \fn DMC_Code getPeakCurrentDuration(int *durationMs)
	 * \brief Gets the peak current duration.
	 * \param durationMs Buffer to store the value.
	 * \return DMC_Code Status code.
	 */
	DMC_Code getPeakCurrentDuration(int *durationMs);

	/**
	 * \fn DMC_Code enableCurrentLimit(bool enabled)
	 * \brief Enables or disables current limiting mode.
	 * \param enabled If true, enabled current limiting. If false, disables current limiting.
	 * \return DMC_Code Status code.
	 */
	DMC_Code enableCurrentLimit(bool enabled);

	/**
	 * \fn DMC_Code isCurrentLimitEnabled(bool *enabled)
	 * \brief Returns whether or not the current limit is enabled.
	 * \param enabled Buffer to store the result.
	 * \return DMC_Code Status code.
	 */
	DMC_Code isCurrentLimitEnabled(bool *enabled);

	DMC_Code setCurrentLimitPGain(double P);
	DMC_Code getCurrentLimitPGain(double *P);
	DMC_Code setCurrentLimitIGain(double I);
	DMC_Code getCurrentLimitIGain(double *I);
	DMC_Code setCurrentLimitDGain(double D);
	DMC_Code getCurrentLimitDGain(double *D);
	DMC_Code setCurrentLimitFGain(double F);
	DMC_Code getCurrentLimitFGain(double *F);
	DMC_Code setCurrentLimitIZone(double I);
	DMC_Code getCurrentLimitIZone(double *I);


	/**
	 * \fn DMC_Code setADCMultiplier(float value, int tmsWait)
	 * \brief Configure the constant used by the DMC60 to convert ADC measurements into an associated load current in amps. The DMC60 uses a combination of a
	 * current sense resistor, bidirectional current sense amplifier with a 50V/V gain, and a 3.3V reference to measure load currents. The current sense amplifier
	 * is biased at 1.65V, which means a load current of 0 amps will result in the current sense amplifier outputting 1.65V. At power on the DMC60 performs a
	 * calibration procedure to determine the ADC sample value (smpZeroCurrent) corresponding to no current flow between the M+ and M- terminals. When current
	 * flows from the M+ terminal to the M- terminal the current sense amplifier outputs a voltage between 1.65V and 3.3V, which corresponds to positive current
	 * flow. When current flows from the M- terminal to the M+ terminal the current sense amplifier outputs a voltage between 1.65V and 0V, corresponding to
	 * negative current flow. The DMC60 uses an internal 12-bit ADC to convert this voltage into digitized value every 500 microseconds. The digitized value is
	 * then converted into a signed 16.6 fixed point current measurement (in Amps) using the following formula: crntLoad=(smpAdc-smpZeroCurrent)×mplrAdcCurrent.
	 * The multiplier (mplrAdcCurrent) that corresponds to a given sense resistance (resCrntSns, in ohms) can be calculated using the following formula:
	 * mplrAdcCurrent=(vref/4096×1/(resCrntSns×50))×65536. For example, if the sense resistor has a nominal value of 500 µohms then the
	 * mplrAdcCurrent=(3.3/4096×1/(0.0005×50))×65536=2112 or 0x00000840 in hexadecimal. The DMC60 comes pre-programmed with a multiplier that corresponds to the
	 * expected sense resistance (approximately 510 µohms) so it should not be necessary to configure the multiplier. However, if current measurements appear to
	 * be off then paramAdcCurrentMultiplier can be used to adjust the multiplier used. This parameter is stored in nonvolatile memory and is preserved across power cycles.
	 * \param value Signed 16.16 value to set the ADC Multiplier to
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return Status code.
	 */
	DMC_Code setADCMultiplier(float value, int tmsWait);

	/**
		 * \fn DMC_Code getADCMultiplier(float *value, int tmsWait)
		 * \brief Gets the currently stored value for
		 * \param value Buffer to store the value.
		 * \param tmsWait Max time in milliseconds to wait for a response.
		 * \return Status code.
		 */
	DMC_Code getADCMultiplier(float* value, int tmsWait);



	/**
	 * \fn DMC_Code enterBootloader()
	 * \brief Sends the DMC60C into bootloader mode.
	 * \return Status code.
	 */
	DMC_Code enterBootloader();
	/**
	 * \cond PRIVATE
	 * \fn DMC_Code writeFlashPage(uint16_t imageType, uint16_t *pageNum, uint32_t *pageBuf)
	 */
	DMC_Code writeFlashPage(uint16_t imageType, uint8_t pageNum, uint8_t *pageBuf);
	/**
	 * \fn DMC_Code getFlashSequenceNumber(uint32_t *seqnum)
	 */
	DMC_Code getFlashSequenceNumber(uint32_t *seqnum);
	/**
	 * \endcond
	 */


private:
	DMCInfo_t DMCInfo;

	int verbose;

	typedef struct {
		uint32_t arbId;
		uint8_t sendBuf[8];
		uint8_t cbSend;
		uint32_t periodMs;
	}controlFrame_t;
	std::map <uint32_t, controlFrame_t> _controlFrames;
	CANCTRL0 _control0 = {0,0,0,0,0,0,0,0,0,0,0,0,1024};

	typedef struct{
		struct timespec time;
		uint8_t bytes[8];
	} RXFrame_t;
	std::map <uint32_t,  RXFrame_t> _rxFrames;



	DMC_Code sendVendorCmd(uint16_t cmd, uint16_t param1, uint16_t param2, uint8_t* pbSnd, uint16_t cbSnd, uint8_t* pbRcv, uint8_t* cbRcv, int tmsWait, uint16_t cercExpect);
	DMC_Code sendVendorCmd(uint16_t cmd, uint16_t param1, uint16_t param2, uint8_t* pbSnd, uint16_t cbSnd, uint8_t* pbRcv, uint8_t* cbRcv, int tmsWait){
		return sendVendorCmd(cmd, param1, param2, pbSnd, cbSnd, pbRcv, cbRcv, tmsWait, cercNoError);
	}
	/**
	 * \fn DMC_Code setParameter(uint16_t param, uint32_t value, int tmsWait)
	 * \brief Sets the specified parameter to the specified value. This function shouldn't need to be used as there are get/set functions for each parameter.
	 * \param param The parameter to set.
	 * \param value The (type converted) value to write.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return DMC_Code Status code
	 */
	DMC_Code setParameter(uint16_t param, uint32_t value, int tmsWait);

	/**
	 * \fn DMC_Code getParameter(uint16_t param, uint32_t *value, int tmsWait)
	 * \brief Gets the specified parameter. This function shouldn't need to be used as there are get/set functions for each parameter.
	 * \param param The parameter to get.
	 * \param value Buffer to store the received value.
	 * \param tmsWait Max time in milliseconds to wait for a response.
	 * \return DMC_Code Status code
	 */
	DMC_Code getParameter(uint16_t param, uint32_t *value, int tmsWait);

//	DMC_Code sendDataOut(uint8_t* dataToSend, uint32_t cbData);



	double GetTrgt()const;
	void SetTrgt(double value);
	DMC_Code getRx(uint32_t arbId, uint8_t *recvBuf, int tmsWait);
	void addTx (uint32_t arbId, uint8_t* sendBuf, uint8_t cbSend, uint32_t periodMs);
	void removeTx(uint32_t arbId);
	bool changeTxPeriod(uint32_t arbId, uint32_t periodMs);
	void printError(DMC_Code Error);
};

#ifdef __cplusplus
}//namespace DMC60
#endif
