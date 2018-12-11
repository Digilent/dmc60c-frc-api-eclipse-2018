#if(defined(__FRC_ROBORIO__) && __FRC_ROBORIO__ == 2019)
#include "frc/MotorSafetyHelper.h"
#include "frc/MotorSafety.h"
#include "frc/ErrorBase.h"
#include "frc/SpeedController.h"
#include "frc/SmartDashboard/SendableBase.h"
#include "frc/SmartDashboard/SendableBuilder.h"
#else
#include "MotorSafetyHelper.h"
#include "MotorSafety.h"
#include "ErrorBase.h"
#include "SpeedController.h"
#include "SmartDashboard/SendableBase.h"
#include "SmartDashboard/SendableBuilder.h"
#endif
#include "digilent/dmc60/DMC60C.h"
#include "HAL/HAL.h"

namespace DMC60{
/**
 * \class WPI_DMC60C
 *
 * \brief High Level DMC60C Interface
 *
 * This class contains all of the high level functions
 * used to communicate with the DMC60C.
 */
class WPI_DMC60C:
			public virtual DMC60C,
			public virtual frc::MotorSafety,
			public frc::ErrorBase,
			public frc::SpeedController,
			public frc::SendableBase
{
public:

	/**
	 * \fn WPI_DMC60C(int deviceNumber)
	 * \brief Creates a DMC60C object for use in an open loop setup
	 * \param deviceNumber The deviceNumber of the DMC60C Motor
	 */
	WPI_DMC60C(int deviceNumber);
	/**
	 * \fn WPI_DMC60C(int deviceNumber, double wheelDiametermm, double gearRatio, int encoderTicks)
	 * \brief Creates a DMC60C object for use in a closed loop setup
	 * \param deviceNumber The deviceNumber of the DMC60C Motor
	 * \param wheelDiametermm The diameter of the wheel attached to the DMC60C in millimeters.
	 * \param gearRatio The ratio of the gearbox (EX: 12 if using a 12:1 gearbox)
	 * \param encoderTicks The number of pulses per channel per revolution on the quadrature encoder attached to the DMC60C motor.
	 */
	WPI_DMC60C(int deviceNumber, double wheelDiametermm, double gearRatio, int encoderTicks);
	~WPI_DMC60C();

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
	 * \fn void GetDescription(wpi::raw_ostream& desc)
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

		std::unique_ptr<MotorSafetyHelper> _MotorSafetyHelper;

};
}
