///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Constants 
// 
// All the constants referenced in functions are here for easy editing. 
// Note: this file will not compile.  Only try to compile the top-level code that 
// "#include"'s this file. 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
// joystick deadband 
const float DRIVE_DEADBAND_THRESHOLD = 20; // joystick values below this are filtered out 
  
// arm limits (Dead or Alive robot is determined by jumper clip in Pre-Auton) 
const float DEAD_ARM_UPPER_LIMIT = 3500; // upper limit for arm potentiometer (Dead robot) 
const float DEAD_ARM_LOWER_LIMIT = 750;  // lower limit for arm potentiometer (Dead robot) 
  
const float ALIVE_ARM_UPPER_LIMIT = 3150; // upper limit for arm potentiometer (Alive robot) 
const float ALIVE_ARM_LOWER_LIMIT = 500;  // lower limit for arm potentiometer (Alive robot) 
  
// intake speeds 
const float INTAKE_SPEED = 127;   // speed to spin intake wheels to collect balls 
const float OUTTAKE_SPEED = -127; // speed to spin intake wheels to score balls (may be reduced for ease in scoring) 
  
//conversion factors 
const float TICKS_PER_INCH = 29.5 ;  // conversion factor from inches to encoder ticks (autonomous driving) 
const float TICKS_PER_DEGREE = 3.58; // conversion factor from degrees to encoder ticks (autonomous turning) 
  
// PID constants 
const float armKp = 0.4; 
const float armKi = 0.0; 
const float armKd = 0.8; 
const float armErrorThreshold = 120.0;     // error threshold for exiting arm PID loop 
const float armDerivativeThreshold = 3.0;  // derivative threshold for exiting arm PID loop 
  
const float driveKp = 0.8; 
const float driveKi = 0.0; 
const float driveKd = 3.2; 
const float driveErrorThreshold = 30.0;     // error threshold for exiting drive PID loop 
const float driveDerivativeThreshold = 0.1; // derivative threshold for exiting arm PID loop 
  
const float turnKp = 0.8; 
const float turnKi = 0.0; 
const float turnKd = 3.2; 
const float turnErrorThreshold = 20.0;     // error threshold for exiting turn PID loop 
const float turnDerivativeThreshold = 0.1; // derivative threshold for exiting arm PID loop 
// note: thresholds are only used in autonomous; Kp, Ki, Kd are for both auto and user control 
  
//other factors 
const float PID_UPDATE_TIME = 30;          // time to wait between PID updates (in ms) 
const float DRIVE_STRAIGHT_FACTOR = 0.4;   // factor for driving straight proportioanl correction in autonomous 
const float SPEED_REDUCTION_FACTOR = 0.4;  // scaling factor for drive speed when the arm is up 
const float ARM_PASS_HEIGHT = 55;          // percent of max arm height to raise to in order to pass in autonomous 
const float TIME_BETWEEN_AUTONOMOUS_ACTIONS = 50; // wait this long at the end of each autonomous step to let things settle 
  
/* 
Power Expander assignments: 
port 3 -> A 
port 5 -> B 
port 7 -> C 
port 9 -> D 
*/
