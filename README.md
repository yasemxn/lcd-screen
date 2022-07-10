# lcd-screen
1. Introduction
An Arduino microcontroller is used to create a digital alarm clock in this project. The clock offers a number of features, including the ability to switch between 12 and 24 hour modes,
display the temperature, and change the current time and alarm using four buttons.
Link to the project: https://www.tinkercad.com/things/bMtO9ST90el-project-lcdscreen/editel?sharecode=oFTBBg-3f_ZrHjXbVwW_uh5tYnFiO3AKkFeo79Sy-To

a. Libraries
#include <LiquidCrystal.h>;
• This library is used to include functions of LCD.
b. Registers
  In this project timer registers are used, the timing is handled by timer1 with a prescaler
  of 256 and a compare match interrupt enabled. The top value of the compare match
  register OCR1A is set to 62,500. The interrupt is triggered when Timer 1 goes from 0 to
  62500 in a second. The ISR timer's value TCNT1 is reset to 0, and then the update clock
  function is run, which adds one second to the clock.
c. Buttons
  Button 1 -> when pressed 3 seconds, button1 will activate set time.
  In set time status:
  • Button 2 -> switches between minute-hour.
  • Button 3 -> increases.
  • Button1 -> exits set time and goes back to default mode.
  Button 2 -> when pressed 3 seconds, button2 will activate set alarm.
  In set alarm status:
  • Button 1 -> switches between minute-hour.
  • Button 3 -> increases.
  • Button 2 -> exits set alarm and goes back to default mode.
   Button 3 -> when pressed, button 3 will switch between celsius-fahrenheit.
   Button 4 -> switches between am/pm and 24h mode.
• When alarm is ringing, this button will snooze the alarm.

2. Functions
  Setup()
    Pin modes are defined, LCD and serial connection begin, all interrupts are disabled before
    timer configuretion and enabled after timer configuration. All interrupts are disabled before
    timer configuration and activated after timer configuration, and pin modes are defined.
    Serial and lcd begins.
  Loop()
    Switches between the modes to Show the active screen. Mode 0 shows lcd screen which is
    the default screen which shows current time, alarm and temperature.
    Mode 1 will execute set time and mode2 will execute set alarm functions.
  TimeIncrease()
    Increases the time and checks if the hour is larger than 12, it switches to PM, if it is lower
    than 12, it is AM.
  controlButtonStates()
    Checks if the current state is switched 0 to 1, it saves the time and compares the difference
    between current time and buttonREdge. If this difference is greater or equal to 3 seconds lcdMode will change. Button4State changes the AM/PM.
  lcdScreen()
    This function is the default mode of LCD screen. Prints the current time, temperature and alarm time and alarm’s mode of ON or OFF.
  printTime()
    This function prints the time seen on the lcd screen. Prints the time set in setTime function.
  printAlarm()
    prints the time set in setAlarm function.
  controlAlarm()
    This function controls if the chosen set alarm is equal to the current time then piezzo buzzer
    will ring due to time. If button 4 is pressed, the function will snooze the alarm. If button 1 , 2
    or 3 are pressed, the alarm will stop.
  setTime() & setAlarm()
    This functions, coordinates the x side of the cursor, and chooses the side of minute/hour
    with blink, then it checks the button pressed and increases the values according to the
    cursor’s positon.
  setTemperature()
    This function checks which pin is the temperature is connected and maps it to the celcius.
    After mapping, it calculates the fahrenheit and controls which temperature mode is activated with flagTemp.
  setBlink()
    This function sets the blink according to the cursor. When pressed button 2 , flagBlink checks if it is on the minute side or hour side.
