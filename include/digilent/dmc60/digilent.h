#pragma once
#include <stdbool.h>
/**
 * \enum DMC_Code Status and error code enums.
 */

typedef enum{
	DMC_OK=0,
	DMC_VCMDNotSupported=1,
	DMC_VCMDBadParameter=2,
	DMC_VCMDDataRcvMore=3,
	DMC_VCMDInBootloader=4,
	DMC_VCMDCrcMismatch=5,
	DMC_VCMDFlashWriteFailed=6,
	DMC_VCMDAckReset=7,

	DMC_TxTimeout=101,
	DMC_RxTimeout=102,
	DMC_ParamInvalid=103,
	DMC_ParamValueInvalid=104,
	DMC_TxFail=105,
	DMC_cercFail=106,
	DMC_UnknownError=107
}DMC_Code;

/**
 * \enum LimitSwitchType List of possible Limit Switch Modes.
 */
typedef enum LimitSwitchType
	{
    	NORMALLY_OPEN = 0,
		NORMALLY_CLOSED = 1,
		DISABLED = 2
	}LimitSwitchType;


/**
 * \enum ControlMode Control modes.
*/

typedef enum ControlMode{
	Voltage = 0,
	Velocity = 1,
	Position = 2,
	Current = 3,
	VoltageCompensation = 4,
	SlaveFollower = 5,
	Disable = 15
}ControlMode;

typedef struct LimitSwitch{
	bool pinState;
	bool activeState;
	bool overridden;
	LimitSwitchType SwitchType;
}LimitSwitch;
