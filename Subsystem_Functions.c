///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Subsystem Functions 
// 
// All the robot-specific subsystem functions are defined here. 
// Note: this file will not compile.  Only try to compile the top-level code that 
// "#include"'s this file. 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Initializations/Init Functions 
// 
// These are called in Pre-Atuon (during startup). 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
PidState armPid;     // create the arm PID struct as a global so we can see the values in the debugger 
PidState drivePid; // create the drive PID struct as a global so we can see the values in the debugger 
PidState turnPid;  // create the turn PID struct as a global so we can see the values in the debugger 
// a second (more important) reason to make these globals is so that all functions can reference them 
  
void initAllPids() // sets all the PID struct constants - to be called in pre-auton 
{ 
    InitPidConstants(drivePid, driveKp, driveKi, driveKd); 
    InitPidConstants(armPid, armKp, armKi, armKd); 
    InitPidConstants(turnPid, turnKp, turnKi, turnKd); 
} 
  
float LEFT_ARM_UPPER_LIMIT = DEAD_ARM_UPPER_LIMIT;  // upper limit for arm potentiometer (default to Dead) 
float LEFT_ARM_LOWER_LIMIT = DEAD_ARM_LOWER_LIMIT;  // lower limit for arm potentiometer (default to Dead) 
  
void initArmLimits() // checks for Alive jumper and if so, sets arm upper and lower limits appropriately 
{ 
    if (SensorValue(Jumper) == 0) // if the Alive jumper clip is in 
    { 
        LEFT_ARM_UPPER_LIMIT = ALIVE_ARM_UPPER_LIMIT;  // change upper limit for arm potentiometer to Alive limit 
        LEFT_ARM_LOWER_LIMIT = ALIVE_ARM_LOWER_LIMIT;  // change lower limit for arm potentiometer to Alive limit 
    } 
} 
  
  
///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Drive Functions 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
//////////////////////////////////////////// 
//            Low-Level                   // 
//////////////////////////////////////////// 
  
void setDriveMotors(float rightValue, float leftValue) // lets you set all the drive motors in one call (skid-steer) 
{ 
    if (SensorValue(leftArmPot) > LEFT_ARM_LOWER_LIMIT + 100) // if the arm is lifted up... 
    { 
        rightValue = rightValue * SPEED_REDUCTION_FACTOR; // ...reduce the right speed by our constant factor... 
        leftValue = leftValue * SPEED_REDUCTION_FACTOR;   // ...reduce the left speed by our constant factor. 
    } 
    motor[rightFrontDrive] = rightValue; // rightFront - 2 
    motor[rightBackDrive] = rightValue;  // rightBack - 3 
    motor[leftFrontDrive] = leftValue;   // leftFront - 8 
    motor[leftBackDrive] = leftValue;    // leftBack - 9 
} 
  
//////////////////////////////////////////// 
//            Driver Control              // 
//////////////////////////////////////////// 
  
void setDrive()         // reads Joystick, calculates drive motor values and sends values to motors - used in driver control 
{ 
    int driveJoystickY = deadband(vexRT[Ch3], DRIVE_DEADBAND_THRESHOLD);    // read from the left josytick Y-axis (channel 3) and deadband value 
    int driveJoystickX = deadband(vexRT[Ch4], DRIVE_DEADBAND_THRESHOLD);    // read from the left josytick X-axis (channel 4) and deadband value 
    int rightMotorValue = driveJoystickY - driveJoystickX;                                // arcade drive left side value 
    int leftMotorValue = driveJoystickY + driveJoystickX;                                     // arcade drive right side value 
    setDriveMotors(rightMotorValue, leftMotorValue);    // send the calculated motor values to the drive sides 
} 
  
//////////////////////////////////////////// 
//            Autonomous                  // 
//////////////////////////////////////////// 
  
void initDriveEncoders() // resets both drive encoder counts to zero 
{ 
    nMotorEncoder[leftBackDrive] = 0; 
  nMotorEncoder[rightBackDrive] = 0; 
} 
  
void driveInches(int inches)  // uses a PID loop to drive (straight) a given distance - used in autonomous 
{ 
    float goal = inches * TICKS_PER_INCH; // conversion factor from inches to encoder ticks 
    int output;                           // speed to send to the drive motots, set in the loop 
    initDriveEncoders();          // reset drive encoder counts to zero 
    InitPidGoal(drivePid, goal);  // initialize the drive PID with the goal 
    ClearTimer(T1);               // clear the timer 
  
    while( (abs(drivePid.error) > driveErrorThreshold) 
          || (abs(drivePid.derivative) > driveDerivativeThreshold) ) // until both the error and speed drop below acceptable thresholds... 
    { 
        if (time1(T1) > PID_UPDATE_TIME) // if enough time has passed since the last PID update... 
        { 
          float currentPosition = (-nMotorEncoder[leftBackDrive]-nMotorEncoder[rightBackDrive]) / 2.0; // (the current position is the average of the drive encoders) 
          output = UpdatePid(drivePid, currentPosition);  // ...update the motor speed with the drive PID... 
          float offset = DRIVE_STRAIGHT_FACTOR * ( (-nMotorEncoder[leftBackDrive]) - (-nMotorEncoder[rightBackDrive]) ) ; // (proportional correction to straighten out) 
          setDriveMotors(output - offset, output + offset);  // ...and send that speed to the drive motors (left and right) 
          ClearTimer(T1); // reset the timer so it starts counting again 
        } 
    } 
  setDriveMotors(0, 0);        // remember to stop the motors! 
  wait1Msec(TIME_BETWEEN_AUTONOMOUS_ACTIONS); // lets things settle before moving to next action 
} 
  
bool bBlueAlliance = false; 
  
void turnDegrees(int degrees)  // uses a PID loop to turn a given angle (clockwise) - used in autonomous 
{ 
    float goal = degrees * TICKS_PER_DEGREE; // conversion factor from degrees to encoder ticks 
  
    if (bBlueAlliance == true) // this reflects the turns if we're on the blue alliance 
    { 
        goal = goal * -1; 
    } 
  
    int output;                         // speed to send to the drive motots, set in the loop 
    initDriveEncoders();        // reset drive encoder counts to zero 
    InitPidGoal(turnPid, goal); // initialize the drive PID with the goal 
    ClearTimer(T2);             // clear the timer 
  
    while( (abs(turnPid.error) > turnErrorThreshold) 
          || (abs(turnPid.derivative) > turnDerivativeThreshold) ) // until both the error and speed drop below acceptable thresholds... 
    { 
        if (time1(T2) > PID_UPDATE_TIME) // if enough time has passed since the last PID update... 
        { 
          float currentPosition = (nMotorEncoder[leftBackDrive]-nMotorEncoder[rightBackDrive]) / 2.0; // (the current position is the (+) average of the drive encoders) 
          output = UpdatePid(turnPid, currentPosition);  // ...update the motor speed with the drive PID... 
          setDriveMotors(-output, output);  // ...and send that speed to the drive motors (left and right) 
          ClearTimer(T2); // clear the timer 
        } 
    } 
  setDriveMotors(0, 0); // remember to stop the motors! 
  wait1Msec(TIME_BETWEEN_AUTONOMOUS_ACTIONS); // lets things settle before moving to next action 
} 
  
  
///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Arm Functions 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
//////////////////////////////////////////// 
//            Low-Level                   // 
//////////////////////////////////////////// 
  
void setArmMotors(int value)  // lets you set the arm motor values in one call 
{                                                           // this function also limits the motors at the top/bottom of arm travel for safety 
    if (value > 0 && SensorValue(leftArmPot) > LEFT_ARM_UPPER_LIMIT)      // if we're above the upper limit and going up... 
    { value = 0; }                                                                                                        // ...set the arm motor value to 0 
  else if (value < 0 && SensorValue(leftArmPot) < LEFT_ARM_LOWER_LIMIT) // if we're below the lower limit and going down... 
    { value = 0; }                                                                                                        // ...set the arm motor value to 0 
    motor[rightTopArm] = value;       // rightTop - 4 
    motor[rightBottomArm] = value;  // rightBottom - 5 
    motor[leftTopArm] = value;        // leftTop - 6 
    motor[leftBottomArm] = value;     // leftBottom - 7 
} 
  
//////////////////////////////////////////// 
//            Driver Control              // 
//////////////////////////////////////////// 
  
bool bHoldHeight = false; // this tells whether or not we want the arm to hold its position 
  
void setArm()             // reads Joystick, determines arm motor values and sends values to motors - used in driver control 
{                                                 // uses PID to hold the arm up when buttons are released 
                            // note: this function does not decide where the upper/lower limits are, setArmMotors does 
    int currentPosition = SensorValue(leftArmPot); 
    if (vexRT[Btn5U] == 1)                        // if button 5 Up is pressed... 
          { 
            bHoldHeight = false;                // ...don't hold position, instead... 
            armPid.goal = LEFT_ARM_UPPER_LIMIT; // ...set the goal to the upper limit. 
        } 
    else if (vexRT[Btn5D] == 1)               // if button 5 Down is pressed... 
          { 
            bHoldHeight = false;                // ...don't hold position, instead... 
            armPid.goal = LEFT_ARM_LOWER_LIMIT; // ...set the goal to the lower limit. 
           } 
  else                                                                // if neither button is pressed... 
          { 
           if (bHoldHeight == false)                // ...and we weren't previously holding position... 
           { 
             bHoldHeight = true;                    // ...now we want to hold position, so... 
             armPid.goal = SensorValue(leftArmPot); // ...set the goal to the current height. 
            } 
          } 
    if (time1(T3) > PID_UPDATE_TIME)                      // if enough time has passed since the last PID update... 
        { 
            float output = UpdatePid(armPid, currentPosition); // ...update the motor speed with the arm PID... 
          setArmMotors(output);                              // ...and send that speed to the arm motors... 
          ClearTimer(T3);                                    // ...and reset the timer for the next update. 
         } 
} 
  
//////////////////////////////////////////// 
//            Autonomous                  // 
//////////////////////////////////////////// 
  
void armHeight(float percent) // uses a PID loop to drive the arm to a given height - used in autonomous 
{ 
    float goal = ( (percent/100) * (LEFT_ARM_UPPER_LIMIT - LEFT_ARM_LOWER_LIMIT) ) + LEFT_ARM_LOWER_LIMIT; 
    int output;                // speed to send to the arm motots, set in the loop 
    InitPidGoal(armPid, goal); // initialize the arm PID with the goal 
    ClearTimer(T3);            // clear the timer 
  
    while( (abs(armPid.error) > armErrorThreshold) 
          || (abs(armPid.derivative) > armDerivativeThreshold) ) // until both the error and speed drop below acceptable thresholds... 
    { 
        if (time1(T3) > PID_UPDATE_TIME) // if enough time has passed since the last PID update... 
        { 
            output = UpdatePid(armPid, SensorValue(leftArmPot));  // ...update the motor speed with the arm PID... 
          setArmMotors(output); // ...and send that speed to the arm motors 
          ClearTimer(T3); 
         } 
    } 
    // don't set the motors back to 0 afterwards, we want them to hold position 
    wait1Msec(TIME_BETWEEN_AUTONOMOUS_ACTIONS); // lets things settle before moving to next action 
} 
  
  
///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Intake Functions 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
//////////////////////////////////////////// 
//            Low-Level                   // 
//////////////////////////////////////////// 
  
void setIntakeMotors(int value) // lets you set both intake motor values in one call 
{ 
    motor[rightIntake]= value;  // rightIntake - 1 
    motor[leftIntake]= value;     // rightIntake - 10 
} 
  
void intakeIn() 
{ setIntakeMotors(INTAKE_SPEED); } // this is full speed in 
  
void intakeOut() 
{ setIntakeMotors(OUTTAKE_SPEED); } // speed out can be reduced for ease of scoring 
  
void intakeStop() 
{ setIntakeMotors(0); } // stop the intake motors 
  
//////////////////////////////////////////// 
//            Driver Control              // 
//////////////////////////////////////////// 
  
void setIntake()    // reads the Joystick, determines the state of the intake and sends values to motors - used in driver control 
{ 
    if(vexRT[Btn6U] == 1)           // if button 6 Up is pressed... 
        {intakeIn();}                       // ...intake balls. 
    else if(vexRT[Btn6D] == 1)  // if button 6 Down is pressed... 
        {intakeOut();}                      // ...outtake balls (possibly at reduced speed). 
    else                                                // if neither button is pressed... 
        {intakeStop();}           // ...stop the motors. 
} 
  
//////////////////////////////////////////// 
//            Autonomous                  // 
//////////////////////////////////////////// 
  
void deployIntake()  // jerks the robot back and forth to deploy the intake arms 
{ 
    setDriveMotors(127,127); 
    wait1Msec(100); 
    setDriveMotors(-127,-127); 
    wait1Msec(100); 
    setDriveMotors(0,0); 
    wait1Msec(TIME_BETWEEN_AUTONOMOUS_ACTIONS); // lets things settle before moving to next action 
} 
  
void passPreload() 
{ 
    armHeight(ARM_PASS_HEIGHT); 
    intakeOut(); 
    wait1Msec(500); 
    intakeStop(); 
    armHeight(0); 
} 
