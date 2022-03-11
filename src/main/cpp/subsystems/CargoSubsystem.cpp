/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoSubsystem.h"

#include <frc/smartdashboard/Smartdashboard.h>

#include "Constants.h"

// Constructor, set initial state to in and stopped
CargoSubsystem::CargoSubsystem() {
    IntakeWheels.StopMotor();
    BottomIndexer.StopMotor();
    TopIndexer.StopMotor();

//tie in second motor 
  ShooterFollow.Follow(Shooter);

// PID stuff for shooter
// This runs on the Talon
  Shooter.ConfigFactoryDefault();
  
  Shooter.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10); 

  Shooter.SetSensorPhase(true);
  
  Shooter.ConfigNominalOutputForward(0,10);
  Shooter.ConfigNominalOutputReverse(0,10);
  Shooter.ConfigPeakOutputForward(1,10);
  Shooter.ConfigPeakOutputReverse(-1,10);
  
  Shooter.Config_kF(0, kShootF, 10);
  Shooter.Config_kP(0, kShootP, 10);
  Shooter.Config_kI(0, kShootI, 10);
  Shooter.Config_kD(0, kShootD, 10);    
}

void CargoSubsystem::Periodic() {
  TopLaserState = TopIntakeLaser.Get();
  frc::SmartDashboard::PutBoolean("Top Intake Laser", TopLaserState);

  BottomLaserState = BottomIntakeLaser.Get();
  frc::SmartDashboard::PutBoolean("Bottom Intake Laser", BottomLaserState);

  
  RPM = -Shooter.GetSelectedSensorVelocity(0);
  frc::SmartDashboard::PutNumber("RPM", (RPM));
  frc::SmartDashboard::PutBoolean("INTAKE WOULD BE SPINNING", truth);

  averageRPMs = rollingRPMs(RPM); 
  frc::SmartDashboard::PutNumber("AvgRPM", (averageRPMs));
}

double CargoSubsystem::PutLED(double ledMotorValue) {
    //I WOULD create an enum for this, except that the list of values would take me all day, and is not worth typing out
    //PLUS you'd have to find the table anyways to know how to enter the values
    led_lights.Set(ledMotorValue);
}

void CargoSubsystem::GrabBalls() {
    if (TopLaserState) {
        TopIndexer.Set(kIndexerSpeed);
        BottomIndexer.Set(kIndexerSpeed);
        IntakeWheels.Set(kIntakeSpeed);
    } else {
        TopIndexer.StopMotor();
        if (BottomLaserState)
        {
            BottomIndexer.Set(kIndexerSpeed);
            IntakeWheels.Set(kIntakeSpeed);
        } else {
            BottomIndexer.StopMotor();
            IntakeWheels.StopMotor();
        }
    }   
}

void CargoSubsystem::BottomIn() {
    BottomIndexer.Set(kIndexerSpeed);
}

void CargoSubsystem::AllOut() {
    TopIndexer.Set(-kIndexerSpeed);
    BottomIndexer.Set(-kIndexerSpeed);
    IntakeWheels.Set(-kIndexerSpeed);
}

void CargoSubsystem::TopIn() {
    TopIndexer.Set(kIndexerSpeed);
}

void CargoSubsystem::TopOut() {
    TopIndexer.Set(-kIndexerSpeed);
}

void CargoSubsystem::AutomaticIntake() {
    TopIn();
}

void CargoSubsystem::Shoot() {
    Shooter.Set(ControlMode::Velocity, -39600);
    if (TopLaserState) {
        TopIndexer.Set(kIndexerSpeed);
        BottomIndexer.Set(kIndexerSpeed);
    } else if (-Shooter.GetSelectedSensorVelocity(0) >= 39000 && -Shooter.GetSelectedSensorVelocity(0) <= 39750) {
        truth = true;
        BottomIndexer.Set(kIndexerSpeed);
        TopIndexer.Set(kIndexerSpeed);
    } else {
        truth = 0;
        BottomIndexer.StopMotor();
        TopIndexer.StopMotor();
        }
}

void CargoSubsystem::AutoShoot() {
    Shooter.Set(ControlMode::Velocity, -39800);
    if (TopLaserState) {
        TopIndexer.Set(kIndexerSpeed);
        BottomIndexer.Set(kIndexerSpeed);
    } else if (-Shooter.GetSelectedSensorVelocity(0) >= 39000 && -Shooter.GetSelectedSensorVelocity(0) <= 39750) {
        truth = true;
        BottomIndexer.Set(kIndexerSpeed);
        TopIndexer.Set(kIndexerSpeed);
    } else {
        truth = 0;
        BottomIndexer.StopMotor();
        TopIndexer.StopMotor();
        }
}

void CargoSubsystem::LowShoot() {
    Shooter.Set(ControlMode::Velocity, -22000);
    if (TopLaserState) {
        TopIndexer.Set(kIndexerSpeed);
        BottomIndexer.Set(kIndexerSpeed);
    } else if (-Shooter.GetSelectedSensorVelocity(0) >= 19900) {
        truth = true;
        BottomIndexer.Set(kIndexerSpeed);
        TopIndexer.Set(kIndexerSpeed);
    } else {
        truth = 0;
        BottomIndexer.StopMotor();
        TopIndexer.StopMotor();
        }
}

void CargoSubsystem::Unjam() {
    Shooter.Set(ControlMode::PercentOutput, -0.5);
}

void CargoSubsystem::Stop() {
    IntakeWheels.StopMotor();
    BottomIndexer.StopMotor();
    TopIndexer.StopMotor();
    Shooter.Set(ControlMode::PercentOutput, 0.0);    
}

double CargoSubsystem::GetRPM() {
    return RPM;
}

double CargoSubsystem::rollingRPMs(double nextRPM) {
    // first thing, move all stored RPMs down one, losing the oldest one
    for (int i=(numRPMs - 2); i>=0; i--) {
        recentRPMs[i+1] = recentRPMs[i];
    }
    // store new RPM in the newest place
    recentRPMs[0] = nextRPM;

    // get an average
    double average = 0.0;
    for (int i=0; i<numRPMs; i++) {
        average += recentRPMs[i];
    }
    average = average / (double)numRPMs;
    return average;
}