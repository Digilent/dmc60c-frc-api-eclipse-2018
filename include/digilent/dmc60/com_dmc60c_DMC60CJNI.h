/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_dmc60c_DMC60CJNI */

#ifndef _Included_com_dmc60c_DMC60CJNI
#define _Included_com_dmc60c_DMC60CJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    Create
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_Create
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    ConfigWheel
 * Signature: (IDDI)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_ConfigWheel
  (JNIEnv *, jclass, jint, jdouble, jdouble, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    ConfigPID
 * Signature: (IIFFFF)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_ConfigPID
  (JNIEnv *, jclass, jint, jint, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    ConfigClosedLoopRampRate
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_ConfigClosedLoopRampRate
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    ConfigOpenLoopRampRate
 * Signature: (IS)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_ConfigOpenLoopRampRate
  (JNIEnv *, jclass, jint, jshort);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    SetContinuousCurrentLimit
 * Signature: (ID)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_SetContinuousCurrentLimit
  (JNIEnv *, jclass, jint, jdouble);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    SetPeakCurrentLimit
 * Signature: (ID)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_SetPeakCurrentLimit
  (JNIEnv *, jclass, jint, jdouble);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    SetPeakCurrentDuration
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_SetPeakCurrentDuration
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    EnableCurrentLimiting
 * Signature: (IZ)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_EnableCurrentLimiting
  (JNIEnv *, jclass, jint, jboolean);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    IsCurrentLimitActive
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_IsCurrentLimitActive
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    DriveVoltage
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_DriveVoltage
  (JNIEnv *, jclass, jint, jdouble);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    DrivePosition
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_DrivePosition
  (JNIEnv *, jclass, jint, jdouble);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    DriveDistance
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_DriveDistance
  (JNIEnv *, jclass, jint, jdouble);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    DriveVelocity
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_DriveVelocity
  (JNIEnv *, jclass, jint, jdouble);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    DriveVoltageCompensation
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_DriveVoltageCompensation
  (JNIEnv *, jclass, jint, jdouble);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    DriveCurrent
 * Signature: (ID)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_DriveCurrent
  (JNIEnv *, jclass, jint, jdouble);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    FollowerMode
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_FollowerMode
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    SetPIDSlot
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_SetPIDSlot
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetP
 * Signature: (II)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetP
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetI
 * Signature: (II)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetI
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetD
 * Signature: (II)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetD
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetF
 * Signature: (II)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetF
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetClosedLoopError
 * Signature: (I)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetClosedLoopError
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    SetLimitSwitches
 * Signature: (IZZZ)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_SetLimitSwitches
  (JNIEnv *, jclass, jint, jboolean, jboolean, jboolean);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetFwdLimitSwitch
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_GetFwdLimitSwitch
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetRevLimitSwitch
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_GetRevLimitSwitch
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    IsFwdLimitSwitchActive
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_IsFwdLimitSwitchActive
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    IsRevLimitSwitchActive
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_IsRevLimitSwitchActive
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    IsOverTempFaultActive
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_IsOverTempFaultActive
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    IsUnderVoltageFaultActive
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_IsUnderVoltageFaultActive
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    IsGateDriveFaultActive
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_IsGateDriveFaultActive
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    SetBrakeCoast
 * Signature: (IZZ)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_SetBrakeCoast
  (JNIEnv *, jclass, jint, jboolean, jboolean);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetBusVoltage
 * Signature: (I)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetBusVoltage
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetAIN1Voltage
 * Signature: (I)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetAIN1Voltage
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetLoadCurrent
 * Signature: (I)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetLoadCurrent
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetAmbientTemp
 * Signature: (I)F
 */
JNIEXPORT jfloat JNICALL Java_com_dmc60c_DMC60CJNI_GetAmbientTemp
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    ZeroEncoderPosition
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_ZeroEncoderPosition
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetRevolutionsTraveled
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL Java_com_dmc60c_DMC60CJNI_GetRevolutionsTraveled
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetDistanceTraveled
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL Java_com_dmc60c_DMC60CJNI_GetDistanceTraveled
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetMetersPerSecond
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL Java_com_dmc60c_DMC60CJNI_GetMetersPerSecond
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetCurrentDutyCycle
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL Java_com_dmc60c_DMC60CJNI_GetCurrentDutyCycle
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetEncoderPositionCount
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_GetEncoderPositionCount
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetEncoderVelocityCount
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_dmc60c_DMC60CJNI_GetEncoderVelocityCount
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    DisableMotor
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_DisableMotor
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    IsEnabled
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_IsEnabled
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    InvertEncoder
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_InvertEncoder
  (JNIEnv *, jclass, jint, jboolean);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    SetInverted
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_com_dmc60c_DMC60CJNI_SetInverted
  (JNIEnv *, jclass, jint, jboolean);

/*
 * Class:     com_dmc60c_DMC60CJNI
 * Method:    GetInverted
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dmc60c_DMC60CJNI_GetInverted
  (JNIEnv *, jclass, jint);


#ifdef __cplusplus
}
#endif
#endif