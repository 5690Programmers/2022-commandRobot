/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/ParallelCommandGroup.h>

#include "commands/TurnToAngle.h"
#include "commands/TurnToAngleNew.h"
#include "commands/TurnToLimelight.h"
#include "commands/DriveStraight.h"

#include "commands/autos/DriveTwoBallUnoTrajectory.h"
#include "commands/autos/DriveTwoBallDosTrajectory.h"
#include "commands/autos/CenterAuto.h"

#include "commands/IntakeGrabBalls.h"
#include "commands/IntakeAllOut.h"

#include "commands/ShooterShoot.h"
#include "commands/ShooterAutoShoot.h"
#include "commands/ShooterLowShoot.h"

#include "commands/DriveDistance.h"
#include "Constants.h"
#include <pathplanner/lib/PathPlanner.h>
#include "subsystems/DriveSubsystem.h"

/**
 * An auto for declaring individual move commands, leaving the rest the same
 */
class LeftAuto
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, LeftAuto> {
 public:
  /**
   * Creates a new LeftAuto.
   *
   * @param drive The drive subsystem this command will run on
   */
  LeftAuto(DriveSubsystem* drive, CargoSubsystem* cargo);
};

/**
 * An auto for jamming everything into one file. Like RobotContainer.cpp
 */
class CenterAuto
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, CenterAuto> {
 public:
  /**
   * Creates a new LeftAuto.
   *
   * @param drive The drive subsystem this command will run on
   */
  CenterAuto(DriveSubsystem* drive, CargoSubsystem* cargo);
};

/**
 * An auto for declaring move commands in DriveSubsystem.cpp method
 */
class RightAuto
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, RightAuto> {
 public:
  /**
   * Creates a new RightAuto.
   *
   * @param drive The drive subsystem this command will run on
   */
  RightAuto(DriveSubsystem* drive, CargoSubsystem* cargo);
};

