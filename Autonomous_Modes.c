///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Autonomous Routines 
// 
// All the autonomous mode routines are defined here. 
// Note: this file will not compile.  Only try to compile the top-level code that 
// "#include"'s this file. 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
/* 
Autonomous routines can be built from building block functions! 
Here are the available functions: 
  
driveInches(inches); 
turnDegrees(degrees); 
armHeight(percent); 
intakeIn(); 
intakeOut(); 
intakeStop(); 
wait1Msec(milliseconds); 
*/
  
const int NUMBER_OF_MODES = 8; 
  
void defaultAutonomous() // this is the default mode, so for safety, let's do nothing 
{ 
    // watch you do nothing 
} 
  
/* --------------------- Red (original versions) ------------------ */
  
// Only the Red autonomous routines are programmed, the blue version are reflected (see below). 
  
void redMiddleOffense() // scores in the stash, then drives at oppoenet's side 
{ 
    //deployIntake(); 
    intakeIn(); 
    wait1Msec(250); 
    intakeStop(); 
    driveInches(61); 
    armHeight(100); 
    wait1Msec(125); 
    driveInches(13); 
    intakeOut(); 
    wait1Msec(500); 
    intakeStop(); 
    driveInches(-13); 
    armHeight(0); 
    turnDegrees(-110); 
    driveInches(-84); 
} 
  
void redMiddleDefense() // knocks off large ball, then drives at oppoenet's side 
{ 
    //deployIntake(); 
    driveInches(61);   // drive under bridge and knock off big ball 
    turnDegrees(-110); // turn toward opponenet's side (backside first) 
    driveInches(-84);  // drive kamikaze distance 
} 
  
void redHangingOffense() // picks up balls at the wall, then goes kamikaze, then pulls back, turns and dumps over bump 
{ 
    deployIntake(); 
    intakeIn(); 
    driveInches(15); 
    wait1Msec(1000); 
    driveInches(-7); 
    turnDegrees(30); 
    driveInches(-11); 
    turnDegrees(60); 
    driveInches(-78); 
    intakeStop(); 
    //adding... 
    driveInches(55); 
    turnDegrees(90); 
    intakeOut(); 
    wait1Msec(6000); 
    intakeStop(); 
} 
  
void redHangingDefense() // immeadiate kamikaze 
{ 
    deployIntake(); 
    driveInches(-84); 
} 
  
/* --------------------- Blue (Reflected versions) ------------------ */
  
// The Blue versions of the autonomous routines are the same as the Red ones with the turn angles negated. 
  
void blueMiddleOffense() 
{ 
    bBlueAlliance = true; 
    redMiddleOffense(); 
} 
  
void blueMiddleDefense() 
{ 
    bBlueAlliance = true; 
    redMiddleDefense(); 
} 
  
void blueHangingOffense() 
{ 
    bBlueAlliance = true; 
    redHangingOffense(); 
} 
  
void blueHangingDefense() 
{ 
    bBlueAlliance = true; 
    redHangingDefense(); 
} 
