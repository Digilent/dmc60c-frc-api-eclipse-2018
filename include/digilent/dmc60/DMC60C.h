#pragma once 

#include <cstdint>
#include <vector>
#include <sys/types.h>
#include "MotorSafetyHelper.h"
#include "MotorSafety.h"
#include "ErrorBase.h"
#include "DMC60LowLevel.h"
#include "SpeedController.h"
#include "SmartDashboard/SendableBase.h"
#include "SmartDashboard/SendableBuilder.h"

namespace DMC60{

/**
 * \mainpage DMC60C API Index
 *
 * \section intro_sec Introduction
 * Welcome to the DMC60C API documentation index. This documentation was generated using Doxygen.
 *
 * You can find more information on the DMC60C by going to the <a href="https://reference.digilentinc.com/dmc-60c/start">DMC60C wiki page</a>.
 *
 * For a basic getting started guide on setting up the DMC60C software and configuration server for use with FRC, visit the <a href="https://reference.digilentinc.com/dmc-60c/getting-started">DMC60C getting started guide</a>.
 */


//PID constants for 20 CPCPR Encoder for velocity control:
//P = 5
//I = 0.1
//D = 4
//
//PID Constants for 1024 CPCPR Encoder for velocity control:
//P = 0.1
//I = 0.001
//D = 0
//
//PID Constants for 1024 CPCPR encoder for position control:
//P = 2
//I = 0.01
//D = 0


/**
 * \class DMC60C
 *
 * \brief High Level DMC60C Interface
 *
 * This class contains all of the high level functions
 * used to communicate with the DMC60C.
 */
class DMC60C:
			public frc::MotorSafety,
			public frc::ErrorBase,
			public frc::SpeedController,
			public frc::SendableBase
{
public:
	/**
	 * \fn DMC60C(int deviceNumber=0)
	 * \brief Creates a DMC60C object for use in an open loop setup
	 * \param deviceNumber The deviceNumber of the DMC60C Motor
	 */
	DMC60C(int deviceNumber);
	/**
	 * \fn DMC60C(int deviceNumber=0, double wheelDiametermm, double gearRatio, int encoderTicks)
	 * \brief Creates a DMC60C object for use in a closed loop setup
	 * \param deviceNumber The deviceNumber of the DMC60C Motor
	 * \param wheelDiametermm The diameter of the wheel attached to the DMC60C in millimeters.
	 * \param gearRatio The ratio of the gearbox (EX: 12 if using a 12:1 gearbox)
	 * \param encoderTicks The number of pulses per channel per revolution on the quadrature encoder attached to the DMC60C motor.
	 */
	DMC60C(int deviceNumber, double wheelDiametermm, double gearRatio, int encoderTicks);
	~DMC60C();

	/**
	 * \fn int  getDeviceNumber()const
	 * \brief Get the device number associated with this DMC60C object.
	 * \return Device number of this DMC60C object (0 - 64)
	 */
	int getDeviceNumber()const;

	/**
	 * \fn void configWheel(double wheelDiametermm, int gearRatio, int encoderTicks)
	 * \brief Reconfigure the wheel attached to the DMC60C
	 * \param wheelDiametermm The diameter of the wheel attached to the DMC60C in millimeters.
	 * \param gearRatio The ratio of the gearbox (EX: 12 if using a 12:1 gearbox)
	 * \param encoderTicks The number of pulses per channel per revolution on the quadrature encoder attached to the DMC60C motor.
	 */
	void configWheel(double wheelDiametermm, double gearRatio, int encoderTicks);
	/**
	 * \fn DMC_Code configPID(unsigned int slot, float P, float I, float D, float F)
	 * \brief Configures the PID and F constants for use in the closed loop.
	 * \param slot 0 to configure PID slot 0, 1 to configure slot 1
	 * \param P value to set P constant to
	 * \param I value to set I constant to
	 * \param D value to set D constant to
	 * \param F value to set F constant to
	 * \return DMC_Code Status code
	 */
	DMC_Code configPID(unsigned int slot, float P, float I, float D, float F);
	/**
	 * \fn DMC_Code configClosedLoopRampRate(unsigned int slot, unsigned int rampRate)
	 * \brief Sets the Closed Loop Ramp Rate for the specified PID slot. The closed loop ramp rate specifies the maximum
	 * number of throttle units the output can change by each time the control loop executes in closed loop control mode
	 * (Velocity, Position, or Current). For example, If the closed loop ramp rate is set to 1000 and the PID update function
	 * determines that the throttle should be increased by 5000 units then the immediate throttle increase will be limited to
	 * 1000 units. If the next PID Update doesn't change the target throttle output value, the throttle will be increased by
	 * another 1000 units the next time the control loop executes. This process will continue until the target throttle is
	 * reached or a new throttle value is calculated. The control loop executes once every 500 µs. Therefore, specifying a
	 * closed loop ramp rate of 16 would result in it taking approximately 1.02 seconds to go from 0% throttle (0) to 100%
	 * throttle (32767). Specifying a value of 0 for the closed loop ramp rate disables throttling and allows the output to
	 * be immediately set to the target value. This parameter is stored in nonvolatile memory and is preserved across power
	 * cycles.
	 * \param slot PID slot to configure
	 * \param rampRate value to set ramp rate to (0 - 32767). Lower values = slower ramp rate.
	 * \return DMC_Code Status code
	 */
	DMC_Code configClosedLoopRampRate(unsigned int slot, unsigned int rampRate);
	/**
	 * \fn void configOpenLoopRampRate(unsigned short rampRate)
	 * \brief Sets the Open Loop Ramp Rate. If a value of 0 is specified in the vltgRampSet field, then the output throttle
	 * will be immediately set to the target duty cycle the next time the control loop executes. If a non-zero value is
	 * specified in the vltgRampSet field, then the number of throttle units that the output can change by each time the
	 * control loop executes will be limited to the value that was specified. For example, if the output throttle is currently
	 * set to 5000, the trgt field specifies 10000, and the vltgRampSet field specifies 2500, then the control loop will need
	 * to execute twice before the output throttle is set to a target duty cycle of 10000. The control loop executes every 500
	 * µs. In this example it may take up to 1 millisecond for the output throttle to be set to the target duty cycle.
	 * \param rampRate value to set ramp rate to (0 - 32767)
	 */
	void configOpenLoopRampRate(unsigned short rampRate);

	/**
	 * \fn DMC_Code setContinuousCurrentLimit(double currentAmps)
	 * \brief Sets the continuous current limit. This applies only if current limiting is enabled. The continuous current limit
	 * is the maximum current that can be drawn by the DMC60C AFTER the peak current limit has been hit for the peak current
	 * duration. If the continuous current limit is greater than or equal to the peak current limit, then the DMC60C will begin
	 * limiting the current immediately after the continuous current limit is exceeded.
	 * \param currentAmps The continuous current limit to set in amps.
	 * \return DMC_Code Status code
	 */
	DMC_Code setContinuousCurrentLimit(double currentAmps);

	/**
	 * \fn DMC_Code setPeakCurrentLimit(double currentAmps)
	 * \brief Sets the peak current limit. This only applies if current limiting is enabled. The peak current is the max
	 * current that can be applied to the motor at any given time. This limit can be applied for up to [peak current duration]
	 * milliseconds. Afterwards the continuous current limit will be applied. If the peak current limit is set to a value lower
	 * than the continuous current limit, the DMC60C will apply the continuous current limit immediately after it detects that
	 * the continuous current limit has been exceeded.
	 * \param currentAmps The peak current limit to set in amps.
	 * \return DMC_Code Status code
	 */
	DMC_Code setPeakCurrentLimit(double currentAmps);

	/**
	 * \fn DMC_Code setPeakCurrentDuration(int durationMs)
	 * \brief Sets the peak current duration. This only applies if current limiting is enabled. The peak current duration is
	 * the maximum amount of time the peak current can be applied to the motor. After this duration, the continuous current
	 * limit will be applied. If the duration is set to 0, the DMC60C will begin applying the continuous current limit immediately
	 * after the peak current limit has been exceeded.
	 * \param durationMs The peak current duration in milliseconds.
	 * \return DMC_Code Status code
	 */
	DMC_Code setPeakCurrentDuration(int durationMs);

	/**
	 * \fn DMC_Code enableCurrentLimiting(bool enabled)
	 * \brief Enables or disables current limiting mode.
	 * \param enabled If true, enabled current limiting. If false, disables current limiting.
	 * \return DMC_Code Status code
	 */
	DMC_Code enableCurrentLimiting(bool enabled);

	/**
	 * \fn ControlMode getControlMode()
	 * \brief Returns the currently used control mode.
	 * \return ControlMode The currently used control mode, as seen in the DMC60C general status packet.
	 */
	ControlMode getControlMode();

	/**
	 * \fn void driveVoltage(double percentVoltage)
	 * \brief Drive the motor using open loop voltage mode.
	 * \param percentVoltage Percent to set the duty cycle of the motor to (-100.00 to 100.00)
	 */
	void driveVoltage(double percentVoltage);
	/**
	 * \fn void drivePosition(double revolutions)
	 * \brief Drive the motor using closed loop position mode. This function uses the gearbox ratio and encoderticks values to
	 * set the position of the wheel and hold it there. The wheel's position is set to 0 at DMC60C power on. This position can
	 * also be reset using zeroEncoderPosition().
	 * \param revolutions Signed number of revolutions to turn the wheel relative to it's starting position.
	 */
	void drivePosition(double revolutions);
	/**
	 * \fn void driveDistance(double meters)
	 * \brief Drive the motor using closed loop position mode. This function uses the wheel's diameter, gearbox ratio, and
	 * encoderticks values to set the position of the wheel and hold it there. The wheel's position is set to 0 at DMC60C
	 * power on. This position can also be reset using zeroEncoderPosition().
	 * \param meters Signed distance to drive relative of the wheel's starting position.
	 */
	void driveDistance(double meters);
	/**
	 * \fn void driveVelocity(double metersPerSecond)
	 * \brief Drive the motor using closed loop velocity mode. This function uses the wheel's diameter, gearbox ratio, and
	 * encoderticks values to set the velocity of the wheel and maintain that speed.
	 * \param metersPerSecond Speed to set the wheel to.
	 */
	void driveVelocity(double metersPerSecond);
	/**
	 * \fn void driveVoltageCompensation(double voltage)
	 * \brief Drive the motor using open loop voltage compensation mode. This function applies the specified voltage to the motor.
	 * \param voltage Signed voltage to send to the motor. If the specified output voltage exceeds the input voltage, then the
	 * duty cycle is limited to 100% (or -100%).
	 */
	void driveVoltageCompensation(double voltage);

	/**
	 * \fn void driveCurrent(double currentAmps)
	 * \brief Drive the motor using closed loop current mode. This mode drives the motor with a specific load current.
	 * \param currentAmps The desired current in amps.
	 */
	void driveCurrent(double currentAmps);

	/**
	 * \fn void followerMode(int deviceNumbertoFollow)
	 * \brief Sets the motor to slave follower mode. This mode behaves similar to voltage mode, however the duty cycle will be
	 * set to the master's duty cycle.
	 * \param deviceNumbertoFollow Device number of the master DMC60C controller.
	 */
	void followerMode(int deviceNumbertoFollow);

	/**
	 * \fn void setPIDSlot(unsigned int slot)
	 * \brief Sets the active PID slot.
	 * \param slot 0 to use PID slot 0, 1 to use PID slot 1.
	 */
	void setPIDSlot(unsigned int slot);
	/**
	 * \fn float getP(unsigned int slot)
	 * \brief Retrieves the P gain value of the specified PID slot from the DMC60C.
	 * \param slot Which PID slot to get value from.
	 * \return Value of the P gain.
	 */
	float getP(unsigned int slot);
	/**
	 * \fn float getI(unsigned int slot)
	 * \brief Retrieves the I gain value of the specified PID slot from the DMC60C.
	 * \param slot Which PID slot to get value from.
	 * \return Value of the I gain.
	 */
	float getI(unsigned int slot);
	/**
	 * \fn float getD(unsigned int slot)
	 * \brief Retrieves the D gain value of the specified PID slot from the DMC60C.
	 * \param slot Which PID slot to get value from.
	 * \return Value of the D gain.
	 */
	float getD(unsigned int slot);
	/**
	 * \fn float getF(unsigned int slot)
	 * \brief Retrieves the F gain value of the specified PID slot from the DMC60C.
	 * \param slot Which PID slot to get value from.
	 * \return Value of the F gain.
	 */
	float getF(unsigned int slot);

	/**
	 * \fn double getClosedLoopError()
	 * \brief Gets the current closed loop error from the DMC60C. This function can be used to help configure the PID values of
	 * a closed loop system.
	 * \return Value of the closed loop error. Depending on the mode, units can vary.
	 */
	double getClosedLoopError();

	/**
	 * \fn void setLimitSwitches(bool overrideEnable, bool forwardSwitchEnable, bool reverseSwitchEnable)
	 * \brief Overrides the limit switch settings to the specified configuration.
	 * \param overrideEnable Enables the limit switch override. If disabled, the DMC60C will use the parameters stored in memory.
	 * \param forwardSwitchEnable Enables or disables the forward limit switch when override is enabled.
	 * \param reverseSwitchEnable Enables or disables the reverse limit switch when override is enabled.
	 */
	void setLimitSwitches(bool overrideEnable, bool forwardSwitchEnable, bool reverseSwitchEnable);

	/**
	 * \fn bool getFwdLimitSwitch()
	 * \brief Gets the current state of the forward limit switch pin. This does not require the limit switch to be active.
	 * \return The state of the limit switch pin.
	 */
	bool getFwdLimitSwitch();

	/**
	 * \fn bool getRevLimitSwitch()
	 * \brief Gets the current state of the reverse limit switch pin. This does not require the limit switch to be active.
	 * \return The state of the limit switch pin.
	 */
	bool getRevLimitSwitch();

	/**
	 * \fn bool isFwdLimitSwitchActive()
	 * \brief Returns whether or not the forward limit switch is active or not. This will only return true if the limit switch
	 * is enabled and active.
	 * \return True if limit switch is active, false if not.
	 */
	bool isFwdLimitSwitchActive();

	/**
	 * \fn bool isRevLimitSwitchActive()
	 * \brief Returns whether or not the reverse limit switch is active or not. This will only return true if the limit switch
	 * is enabled and active.
	 * \return True if limit switch is active, false if not.
	 */
	bool isRevLimitSwitchActive();

	/**
	 * \fn LimitSwitch getFwdLimitSwitchStatus()
	 * \brief Returns all information regarding the forward limit switch.
	 * \return A struct containing the current status of the limit switch.
	 */
	LimitSwitch getFwdLimitSwitchStatus();

	/**
	 * \fn LimitSwitch getRevLimitSwitchStatus()
	 * \brief Returns all information regarding the reverse limit switch.
	 * \return A struct containing the current status of the limit switch.
	 */
	LimitSwitch getRevLimitSwitchStatus();

	/**
	 * \fn bool isCurrentLimitActive()
	 * \brief Returns whether or not the current limit is actively throttling the output current.
	 * \return True if current limit is active.
	 */
	bool isCurrentLimitActive();

	/**
	 * \fn bool isOverTempFaultActive()
	 * \brief Returns whether or not the over temperature fault is active.
	 * \return True if there is an active over temperature fault.
	 */
	bool isOverTempFaultActive();

	/**
	 * \fn bool isUnderVoltageFaultActive()
	 * \brief Returns whether or not the under voltage fault is active.
	 * \return True if there is an active under voltage fault.
	 */
	bool isUnderVoltageFaultActive();

	/**
	 * \fn bool isGateDriveFaultActive()
	 * \brief Returns whether or not the Gate Driver fault is active.
	 * \return True if there is an active gate driver fault.
	 */
	bool isGateDriveFaultActive();
	/**
	 * \fn void setBrakeCoast(bool overrideEnable, bool brakeEnable)
	 * \brief Overrides the brake/coast settings to the specified configuration.
	 * \param overrideEnable Enables the brake/coast override. If disabled, the DMC60C will use the parameters stored in memory.
	 * \param brakeEnable If true, DMC60C will brake when neutral throttle is applied. If false, DMC60C will coast when neutral
	 * throttle is applied.
	 */
	void setBrakeCoast(bool overrideEnable, bool brakeEnable);

	/**
	 * \fn float getBusVoltage()
	 * \brief Reads the DMC60C's bus (battery) voltage.
	 * \return The input voltage applied to the DMC60C in volts.
	 */
	float getBusVoltage();
	/**
	 * \fn float getAIN1Voltage()
	 * \brief Reads the voltage applied to the AIN1 pin on the DMC60C.
	 * \return Voltage of the AIN1 pin in volts.
	 */
	float getAIN1Voltage();
	/**
	 * \fn float getLoadCurrent()
	 * \brief Reads the load current of the DMC60C. This is the current that is running through the motor.
	 * \return Load current in amps.
	 */
	float getLoadCurrent();
	/**
	 * \fn float getAmbientTemp()
	 * \brief Reads the ambient temperature of the DMC60C.
	 * \return Ambient temperature of the DMC60C in degrees C.
	 */
	float getAmbientTemp();

	/**
	 * \fn DMC_Code zeroEncoderPosition()
	 * \brief Resets the encoder position to 0. This is used in position control mode.
	 * \return Status code
	 */
	DMC_Code zeroEncoderPosition();

	/**
	 * \fn double getRevolutionsTraveled()
	 * \brief Reads the number of revolutions the DMC60C has traveled relative to the encoder's zero position.
	 * \return Signed number of revolutions.
	 */
	double getRevolutionsTraveled();
	/**
	 * \fn double getDistanceTraveled()
	 * \brief Reads the distance the DMC60C has traveled relative to the encoder's zero position.
	 * \return Distance in meters.
	 */
	double getDistanceTraveled();

	/**
	 * \fn double getMetersPerSecond()
	 * \brief Reads the current velocity in meters per second.
	 * \return Velocity in meters per second.
	 */
	double getMetersPerSecond();
	/**
	 * \fn double getCurrentDutyCycle() const
	 * \brief Get the duty cycle that is currently applied the the motor.
	 * \return Signed percent duty cycle.
	 */
	double getCurrentDutyCycle() const;
	/**
	 * \fn int getEncoderPositionCount()
	 * \brief Reads the current position count the DMC60C has logged from the encoder.
	 * \return Signed position count.
	 */
	int getEncoderPositionCount();
	/**
	 * \fn int getEncoderVelocityCount()
	 * \brief Reads the current velocity count the DMC60C has logged from the encoder in the past 100ms.
	 * \return Velocity count read from encoder.
	 */
	int getEncoderVelocityCount();
	/**
	 * \fn void disableMotor()
	 * \brief Disables the motor.
	 */
	void disableMotor();

	/**
	 * \fn bool isEnabled()
	 * \brief Checks to see if the motor is enabled.
	 * \return True if enabled, false if not.
	 */
	bool isEnabled();
	/**
	 * \fn void invertEncoder(bool isInverted)
	 * \brief Inverts the signals of the feedback sensor. This alleviates the need to swap the QEA and QEB signals when the
	 * quadrature encoder does not match that of the motor.
	 * \param isInverted True to invert, false otherwise.
	 */
	void invertEncoder(bool isInverted);

	/**
	 * \fn void configPositionReset(bool resetOnFwdLimit, bool resetOnRevLimit, bool resetOnIndex)
	 * \brief Configures the DMC60C to reset the position count when a limit switch is hit.
	 * \param resetOnFwdLimit True to reset the position count when fwd limit goes active.
	 * \param resetOnRevLimit True to reset the position count when rev limit goes active.
	 * \param resetOnIndex True to reset the position count when index pin goes active.
	 */
	void configPositionReset(bool resetOnFwdLimit, bool resetOnRevLimit, bool resetOnIndex);

	/**
	 * \fn void configIndexActiveEdge(bool edge)
	 * \brief Configures the index pin on the DMC60C to trigger on rising or falling edge.
	 * \param edge True to set active edge to rising edge, false for falling edge.
	 */
	void configIndexActiveEdge(bool edge);

	//SpeedController
	/**
	 * \fn void Set(double speed)
	 * \brief Set command used in WPI Speedcontroller class. Sets the speed to the specified duty cycle.
	 * \param speed Duty cycle (-1.0 to 1.0)
	 */
	void Set(double speed) override;
	/**
	 * \fn double Get()
	 * \brief Get command used in WPI Speedcontroller class. Gets the current duty cycle.
	 * \return Duty cycle (-1.0 to 1.0)
	 */
	double Get() const override;
	/**
	 * \fn void SetInverted(bool isInverted)
	 * \brief Inverts the motor direction.
	 * \param isInverted If true, motor will spin in reverse direction.
	 */
	void SetInverted(bool isInverted) override;
	/**
	 * \fn bool GetInverted()
	 * \brief Returns whether or not the motor is inverted.
	 * \return True if motor is inverted, false otherwise.
	 */
	bool GetInverted() const override;
	/**
	 * \fn void Disable()
	 * \brief Disable command used in WPI Speedcontroller class. Disables the motor.
	 */
	void Disable() override;

	//PIDOutput
	/**
	 * \fn void PIDWrite(double output)
	 * \brief Virtual function overload from PIDOutput class in SpeedController. Sets the duty cycle.
	 * \param output Signed duty cycle (-1 to 1).
	 */
	void PIDWrite(double output) override;

	//MotorSafety
	/**
	 * \fn void SetExpiration(double timeout)
	 * \brief Sets the motor safety timeout. When motor safety is enabled, control frames must be sent at least once every timeout period
	 * or else the motor safety will disable the motor.
	 * \param timeout Timeout value in seconds.
	 */
	void SetExpiration(double timeout) override;
	/**
	 * \fn double GetExpiration()
	 * \brief Gets the motor safety timeout.
	 * \return Motor safety timeout period in seconds.
	 */
	double GetExpiration() const override;
	/**
	 * \fn bool IsAlive()
	 * \brief Checks to see if the motor controller is still working or if it has timeout out.
	 * \return True if motor is still operating and hasn't timed out.
	 */
	bool IsAlive() const override;
	/**
	 * \fn void StopMotor()
	 * \brief Stops the motor.
	 */
	void StopMotor() override;
	/**
	 * \fn void SetSafetyEnabled(bool enabled)
	 * \brief Sets the motor safety feature on or off.
	 * \param enabled True to enable, false to disable.
	 */
	void SetSafetyEnabled(bool enabled) override;
	/**
	 * \fn bool IsSafetyEnabled()
	 * \brief Returns whether or not the motor safety feature is enabled or not.
	 * \return True if enabled, false otherwise.
	 */
	bool IsSafetyEnabled() const override;
	/**
	 * \fn void GetDescription(llvm::raw_ostream& desc)
	 * \brief Prints the DMC ID to an output stream.
	 * \param desc Address of output stream.
	 */
	void GetDescription(llvm::raw_ostream& desc) const override;

protected:
	/**
	 * \fn void InitSendable(frc::SendableBuilder& builder)
	 * \brief Initializes the DMC60C for use as a sendable object in the FRC smart dashboard.
	 */
	void InitSendable(frc::SendableBuilder& builder);
private:

	const char* getErrorMessage(DMC_Code Error) const;
	std::unique_ptr<DMC60LowLevel> _DMC60LowLevel;
	std::unique_ptr<MotorSafetyHelper> _MotorSafetyHelper;
	int _deviceNumber;
	double _wheelDiametermm;
	double _gearRatio;
	int _encoderTicks;
	ControlMode _controlMode;
	bool _isEnabled;
	bool _isMotorReversed;
	bool _isEncoderReversed;
};

}
