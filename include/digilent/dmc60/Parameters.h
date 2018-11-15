#pragma once
#include <stdint.h>
/* Define parameters that may be set or retrieved using the CAN
** interface. Please note that the parameter field is 8-bits and
** we are therefore limited to a maximum of 256 parameters.
*/
const uint16_t paramLimitSwtFwdNormClosed      =1;
const uint16_t paramLimitSwtFwdDisabled        =2;
const uint16_t paramLimitSwtRevNormClosed      =3;
const uint16_t paramLimitSwtRevDisabled        =4;
const uint16_t paramLimitSoftFwdThreshold      =5;
const uint16_t paramLimitSoftFwdEnable         =6;
const uint16_t paramLimitSoftRevThreshold      =7;
const uint16_t paramLimitSoftRevEnable         =8;

const uint16_t paramAdcCurrentMultiplier		=9;

const uint16_t paramClosedLoopPGainSlot0           =10;
const uint16_t paramClosedLoopIGainSlot0           =11;
const uint16_t paramClosedLoopDGainSlot0           =12;
const uint16_t paramClosedLoopIZoneSlot0           =13;
const uint16_t paramClosedLoopFGainSlot0           =14;
const uint16_t paramClosedLoopAllowableErrorSlot0  =15;
const uint16_t paramClosedLoopRampRateSlot0        =16;
const uint16_t paramClosedLoopFwdMaxSlot0          =17;
const uint16_t paramClosedLoopRevMaxSlot0          =18;
const uint16_t paramClosedLoopFwdNominalSlot0      =19;
const uint16_t paramClosedLoopRevNominalSlot0      =20;
const uint16_t paramClosedLoopPGainSlot1           =21;
const uint16_t paramClosedLoopIGainSlot1           =22;
const uint16_t paramClosedLoopDGainSlot1           =23;
const uint16_t paramClosedLoopIZoneSlot1           =24;
const uint16_t paramClosedLoopFGainSlot1           =25;
const uint16_t paramClosedLoopAllowableErrorSlot1  =26;
const uint16_t paramClosedLoopRampRateSlot1        =27;
const uint16_t paramClosedLoopFwdMaxSlot1          =28;
const uint16_t paramClosedLoopRevMaxSlot1          =29;
const uint16_t paramClosedLoopFwdNominalSlot1      =30;
const uint16_t paramClosedLoopRevNominalSlot1      =31;

const uint16_t paramCurrentLimitPGain			=32;
const uint16_t paramCurrentLimitIGain			=33;
const uint16_t paramCurrentLimitDGain			=34;
const uint16_t paramCurrentLimitIZone			=35;
const uint16_t paramCurrentLimitFGain			=36;

const uint16_t paramEncoderPosition            	=41;

const uint16_t paramClearPositionOnIndex		=42;
const uint16_t paramClearPositionOnFwdLimit		=43;
const uint16_t paramClearPositionOnRevLimit		=44;
const uint16_t paramIndexActiveEdge				=45;

const uint16_t paramActiveFaults				=51;
const uint16_t paramStickyFaults				=52;
const uint16_t paramOverCurrentStickyFault		=53;
const uint16_t paramOverTempStickyFault			=54;
const uint16_t paramUnderVoltageStickyFault		=55;
const uint16_t paramGateDriverStickyFault		=56;
const uint16_t paramCommsStickyFault			=57;

const uint16_t paramContinuousCurrentLimit		=61;
const uint16_t paramPeakCurrentLimit			=62;
const uint16_t paramPeakCurrentDuration			=63;
const uint16_t paramCurrentLimitEnable			=64;

const uint16_t paramAnalogStatusFrameRate            =91;
const uint16_t paramEncoderStatusFrameRate           =92;
const uint16_t paramGeneralStatusFrameRate			=93;


const uint8_t percNoError				=0;
const uint8_t percBadParameter		=1;
const uint8_t percBadValue			=2;

const uint8_t faultOverCurrentBit = 0x1;
const uint8_t faultOverTempBit = 0x2;
const uint8_t faultUnderVoltageBit = 0x4;
const uint8_t faultGateDriverBit = 0x8;
const uint8_t faultCommBit = 0x10;
