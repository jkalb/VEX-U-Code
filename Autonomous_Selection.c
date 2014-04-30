///////////////////////////////////////////////////////////////////////////////////////// 
// 
//                          Autonomous Selector Functions 
// 
// This code allows for selecting different autonomous modes from the LCD.  It is 
// modified from: http://www.robotc.net/blog/2012/05/18/advanced-applications-with-the-vex-lcd/ 
// Note: this file will not compile.  Only try to compile the top-level code that 
// "#include"'s this file. 
// 
///////////////////////////////////////////////////////////////////////////////////////// 
  
/* 
Code Chooser 
ROBOTC on VEX 2.0 Cortex 
  
This program uses the Display functions of ROBOTC on the VEX 2.0 Cortex platform. 
It allows the user to choose from different pieces of code using the left and right buttons 
on the VEX LCD. Once the center button is pressed, the code corresponding with the choice is run. 
Make sure the LCD is plugged into UART Port 2! 
*/
  
const short leftButton = 1; 
const short centerButton = 2; 
const short rightButton = 4; 
  
int AutonomousNumber = 0;   // variable to keep track of our choice of autonomous mode 
  
void waitForPress() 
{ 
    while(nLCDButtons == 0){} 
    wait1Msec(5); 
} 
  
void waitForRelease() 
{ 
    while(nLCDButtons != 0){} 
    wait1Msec(5); 
} 
  
void incrementOrDecrement() 
{ 
    waitForPress(); 
    //Increment or decrement "AutonomousNumber" based on button press 
            if(nLCDButtons == leftButton) 
            { 
                waitForRelease(); 
                AutonomousNumber--; 
                if (AutonomousNumber < 0) 
                { 
                    AutonomousNumber = NUMBER_OF_MODES; 
                } 
            } 
            else if(nLCDButtons == rightButton) 
            { 
                waitForRelease(); 
                AutonomousNumber++; 
                if (AutonomousNumber > NUMBER_OF_MODES) 
                { 
                    AutonomousNumber = 0; 
                } 
            } 
} 
  
  
//---------- User Interface Code (called in pre-auton) ----------- 
  
void selectAutonomous() 
{ 
    // clear LCD 
    clearLCDLine(0); 
    clearLCDLine(1); 
  
    // display 
    displayLCDCenteredString(0, "Selecting"); 
    displayLCDCenteredString(1, "Autonomous"); 
  
    // blink the backlight 
    bLCDBacklight = false; 
    wait1Msec(250); 
    bLCDBacklight = true; 
    wait1Msec(250); 
    bLCDBacklight = false; 
    wait1Msec(250); 
    bLCDBacklight = true; 
    wait1Msec(250); 
  
    //Loop while center button is not pressed 
    while(nLCDButtons != centerButton) 
    { 
        //Switch case that allows the user to choose from different options 
        switch(AutonomousNumber){ 
        case 0: 
            displayLCDCenteredString(0, "Default Auto"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
        case 1: 
            displayLCDCenteredString(0, "Red Mid Offense"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
        case 2: 
            displayLCDCenteredString(0, "Red Mid Defense"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
        case 3: 
            displayLCDCenteredString(0, "Red Hang Offense"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
        case 4: 
            displayLCDCenteredString(0, "Red Hang Defense"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
        case 5: 
            displayLCDCenteredString(0, "Blu Mid Offense"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
        case 6: 
            displayLCDCenteredString(0, "Blu Mid Defense"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
        case 7: 
            displayLCDCenteredString(0, "Blu Hang Offense"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
        case 8: 
            displayLCDCenteredString(0, "Blu Hang Defense"); 
            displayLCDCenteredString(1, "<     Enter    >"); 
            incrementOrDecrement(); 
            break; 
  
        default: 
            AutonomousNumber = 0; 
            break; 
        } 
    } 
    wait1Msec(1000); 
} 
  
  
  
//---------- Robot Code (called in autonomous) ------------------- 
  
void runSelectedAutonomous() 
{ 
    //Clear LCD 
    clearLCDLine(0); 
    clearLCDLine(1); 
  
    //Switch-case that actually runs the user choice 
    switch(AutonomousNumber){ 
    case 0: 
        displayLCDCenteredString(0, "Default Auto"); 
        displayLCDCenteredString(1, "is running!"); 
        defaultAutonomous(); 
        break; 
  
    case 1: 
        displayLCDCenteredString(0, "Red Mid Offense"); 
        displayLCDCenteredString(1, "is running!"); 
        redMiddleOffense(); 
        break; 
  
    case 2: 
        displayLCDCenteredString(0, "Red Mid Defense"); 
        displayLCDCenteredString(1, "is running!"); 
        redMiddleDefense(); 
        break; 
  
    case 3: 
        displayLCDCenteredString(0, "Red Hang Offense"); 
        displayLCDCenteredString(1, "is running!"); 
        redHangingOffense(); 
        break; 
  
    case 4: 
        displayLCDCenteredString(0, "Red Hang Defense"); 
        displayLCDCenteredString(1, "is running!"); 
        redHangingDefense(); 
        break; 
  
    case 5: 
        displayLCDCenteredString(0, "Blu Mid Offense"); 
        displayLCDCenteredString(1, "is running!"); 
        blueMiddleOffense(); 
        break; 
  
    case 6: 
        displayLCDCenteredString(0, "Blu Mid Defense"); 
        displayLCDCenteredString(1, "is running!"); 
        redMiddleDefense(); 
        break; 
  
    case 7: 
        displayLCDCenteredString(0, "Blu Hang Offense"); 
        displayLCDCenteredString(1, "is running!"); 
        blueHangingOffense(); 
        break; 
  
    case 8: 
        displayLCDCenteredString(0, "Blu Hang Defense"); 
        displayLCDCenteredString(1, "is running!"); 
        blueHangingDefense(); 
        break; 
  
    default: 
        displayLCDCenteredString(0, "No valid choice"); 
        displayLCDCenteredString(1, "was made!"); 
        break; 
    } 
} 
