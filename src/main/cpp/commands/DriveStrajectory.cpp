/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveStrajectory.h"

#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>

DriveStrajectory::DriveStrajectory(DriveSubsystem* subsystem) {
  AddRequirements({subsystem});
}

void DriveStrajectory::Initialize() {
  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass the config
      *m_drive->GetTrajectoryConfig());

  // Reset odometry to the starting pose of the trajectory.
  m_drive->ResetOdometry(exampleTrajectory.InitialPose());

  // this sets up the command
  // I also think it fires it off, since this is a CommandHelper?
  frc2::RamseteCommand ScurveCommand(
      exampleTrajectory, 
      [this]() { return m_drive->GetPose(); },
      frc::RamseteController(DriveConstants::kRamseteB,
                             DriveConstants::kRamseteZeta),
      frc::SimpleMotorFeedforward<units::meters>(
          DriveConstants::ks, DriveConstants::kv, DriveConstants::ka),
      DriveConstants::kDriveKinematics,
      [this] { return m_drive->GetWheelSpeeds(); },
      frc2::PIDController(DriveConstants::kPDriveVel, 0, 0),
      frc2::PIDController(DriveConstants::kPDriveVel, 0, 0),
      [this](auto left, auto right) { m_drive->TankDriveVolts(left, right); },
      {m_drive});

  // This might be what actually fires off the command
  // std::move(ScurveCommand); 
}

void DriveStrajectory::End(bool interrupted) { m_drive->TankDriveVolts(0_V, 0_V); }

bool DriveStrajectory::IsFinished() {  
  // we could add a check in here, to see where in the trajectory we currently are?
  return false;
}
