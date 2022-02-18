/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakeGrabBalls.h"

IntakeGrabBalls::IntakeGrabBalls(IntakeSubsystem* subsystem) : m_intake(subsystem) {
  AddRequirements({subsystem});
}

void IntakeGrabBalls::Initialize() {

}

void IntakeGrabBalls::Execute() {
  m_intake->GrabBalls();
}

void IntakeGrabBalls::End(bool interrupted) {
  m_intake->Stop();
}

// this is a state, it lasts till it's cancelled
bool IntakeGrabBalls::IsFinished() { return false; }