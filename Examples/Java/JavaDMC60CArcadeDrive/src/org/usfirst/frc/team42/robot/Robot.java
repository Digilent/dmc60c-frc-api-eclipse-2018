/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package org.usfirst.frc.team42.robot;

import com.dmc60c.DMC60C;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 * This project demonstrates the use of Velocity mode. When the A button is held
 * the motor's velocity will be controlled by the left joystick.
 */
public class Robot extends IterativeRobot {
	private DMC60C _dmc60cR = new DMC60C(2);//DMC60C with devicenum 2
	private DMC60C _dmc60cL = new DMC60C(5);//DMC60C with devicenum 5
	private Joystick _joy = new Joystick(0);//Controller on USB slot 0
	public void robotInit() {
		_dmc60cL.SetLimitSwitches(true, false, false);
		_dmc60cL.ConfigWheel(200, 1, 1024);//20cm wheel, with encoder on the input of the gearbox (12.75:1), and 20 encoder ticks per revolution.
		_dmc60cL.ConfigPID(0, (float)5, (float).1, (float)4, (float)0);//Slot 0, P=5, I=.1, D=4, F=0.
		_dmc60cL.SetPIDSlot(0);//Set current PID slot to 0.
		_dmc60cR.SetLimitSwitches(true, false, false);
		_dmc60cR.ConfigWheel(200, 1, 1024);//20cm wheel, with encoder on the input of the gearbox (12.75:1), and 20 encoder ticks per revolution.
		_dmc60cR.ConfigPID(0, (float)5, (float).1, (float)4, (float)0);//Slot 0, P=5, I=.1, D=4, F=0.
		_dmc60cR.SetPIDSlot(0);//Set current PID slot to 0.
		_dmc60cR.SetInverted(true);
		_dmc60cR.InvertEncoder(true);
	}
	
	public void disabledInit() {
		_dmc60cL.Disable();
		_dmc60cR.Disable();
	}

	public void teleopInit() {
	}
	

	public void teleopPeriodic() {
		double Ltrigger = -_joy.getRawAxis(2);
		double Rtrigger = _joy.getRawAxis(3);
		double stickL = _joy.getRawAxis(0);
		
		double throttle = Ltrigger+Rtrigger;
		SmartDashboard.putNumber("Dutycycle L", _dmc60cL.GetCurrentDutyCycle());
		SmartDashboard.putNumber("Dutycycle R", _dmc60cR.GetCurrentDutyCycle());
		System.out.println(throttle);
		if (stickL>0) {//Right
			_dmc60cL.DriveVelocity((throttle) *100);
			_dmc60cR.DriveVelocity((throttle-throttle*stickL) * 100);
		}
		else {//Left
			_dmc60cL.DriveVelocity((throttle+throttle*stickL) *100);
			_dmc60cR.DriveVelocity((throttle)* 100);
		}
	}

}
