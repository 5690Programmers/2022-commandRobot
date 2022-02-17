/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "rev/CANSparkMax.h"

#include <frc2/command/SubsystemBase.h>


class IntakeSubsystem : public frc2::SubsystemBase {
 public:
  IntakeSubsystem();

  // Subsystem methods go here.

  /**
   * Spins intake wheels
   */
  void GrabBalls();

  /**
   * Pulls intake in, stops wheels
   */
  void Retract();

  /**
   * Bottom indexer wheels forward
   */
  void BottomIn();
  
  /**
   * Bottom indexer wheels backward
   */
  void BottomOut();
  
  /**
   * Top indexer wheels forward
   */
  void TopIn();
  
  /**
   * Top indexer wheels backward
   */
  void TopOut();

  /**
   * Stop the shooter
   */
  void Stop();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  //frc::DoubleSolenoid IntakeArm {frc::PneumaticsModuleType::CTREPCM,2,3};
  //WPI_VictorSPX IntakeWheels{10};
  rev::CANSparkMax IntakeWheels{8, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax BottomIndexer{9, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax TopIndexer{7, rev::CANSparkMax::MotorType::kBrushless};
};
