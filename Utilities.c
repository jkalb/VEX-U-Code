///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Utilities 
// 
// Functions that are not specific to one robot, like math, PID, and LCD functions, are here. 
// This file will be "include"ed in both robots' top-level files. 
// Note: this file will not compile.  Only try to compile the top-level code that 
// "#include"'s this file. 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
  
///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Math Functions 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
  
// deadband function 
int deadband(int input, int threshold) 
{ 
    if (abs(input) < threshold) // if the input value is less than the threshold value... 
        {input = 0;}                            // ...set it to zero... 
    return input;                               // ...then return the value either way. 
} 
  
// clipping function (note: this is done automatically anyway for motor values) 
int clip(int input, int limit = 127) 
{ 
    if (input > limit)       // if the input is above the limit... 
        {input = limit;}             // set it to the lmimt. 
  else if (input < -limit) // if the input is below the negative of the limit... 
    {input = -limit;}            // set it to the negative of the limit. 
  return input;                      // ...then return the value either way. 
} 
  
  
///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          PID functions (and struct definition) 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
  
// PID struct 
typedef struct
{ 
  float kP; 
  float kI; 
  float kD; 
  float goal; 
  float integral; 
  float error; 
  float previousError; 
  float derivative; 
  
} PidState; 
  
// PID constant initialization function 
void InitPidConstants(PidState* pidState, float kP, float kI, float kD) 
{ 
  pidState->kP = kP; 
  pidState->kI = kI; 
  pidState->kD = kD; 
} 
  
// sets the goal separately 
void InitPidGoal(PidState* pidState, float goal) 
{ 
    pidState->goal = goal; 
  pidState->error = goal; 
  pidState->previousError = goal; 
  pidState->derivative = 0; 
  pidState->integral = 0; 
} 
  
// PID update function 
int UpdatePid(PidState* pidState, float currentPosition) 
{ 
  pidState->error = pidState->goal - currentPosition; 
  pidState->integral += pidState->error; 
  pidState->derivative = pidState->error - pidState->previousError; 
  pidState->previousError = pidState->error; 
  
  int output = (pidState->kP * pidState->error) 
             + (pidState->kI * pidState->integral) 
             + (pidState->kD * pidState->derivative); 
  
  return output; 
} 
  
  
///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          LCD functions 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
void displayBatteryVoltage()    // displays the current battery voltages 
{ 
  bLCDBacklight = true; // turns on the backlight 
  
  string mainBattery, backupBattery;   // these strings will be written with the battery voltages 
  
  displayLCDString(0, 0, "Primary: "); // displays "Primary: " 
  sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); // creates a string of the main battery voltage 
  displayNextLCDString(mainBattery);   // displays the string on the screen in the next avaliable row 
  
  displayLCDString(1, 0, "Backup: ");  // displays "Backup: " 
  sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');  // creates a string of the backup battery voltage 
  displayNextLCDString(backupBattery); // displays the string on the screen in the next avaliable row 
 } 
