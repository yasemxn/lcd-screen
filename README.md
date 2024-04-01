<h1>LCD Screen - Embedded Systems Programming</h1>

<p align="center">
<img src="https://github.com/yasemxn/lcd-screen/blob/main/Project%20Lcd%20Screen%20(2).png"/>

 ### [Project Link](https://www.tinkercad.com/things/bMtO9ST90el-project-lcdscreen/editel?sharecode=oFTBBg-3f_ZrHjXbVwW_uh5tYnFiO3AKkFeo79Sy-To)

<h2>Introduction</h2>
An Arduino microcontroller is used to create a digital alarm clock in this project. The clock offers a number of features, including the ability to switch between 12 and 24 hour modes,
display the temperature, and change the current time and alarm using four buttons.
<br />


<h2>Languages and Libraries</h2>

- <b>C++</b>
- <b>#include <LiquidCrystal.h>;</b> <br />
This library is used to include functions of LCD.

<h2>Environments Used </h2>

- <b>TinkerCad</b>

<h2>Registers </h2>

In this project timer registers are used, the timing is handled by timer1 with a prescaler of 256 and a compare match interrupt enabled. The top value of the compare match register OCR1A is set to 62,500. The interrupt is triggered when Timer 1 goes from 0 to 62500 in a second. The ISR timer's value TCNT1 is reset to 0, and then the update clock function is run, which adds one second to the clock.

<h2>Buttons </h2>
- <b>Button1: </b> when pressed 3 seconds, button1 will activate set time.<br />
In set time status:<br/>
- <b>Button 2: </b> switches between minute-hour.<br />
- <b>Button 3: </b> increases.<br />
- <b>Button 1: </b> exits set time and goes back to default mode.<br />
- <b>Button 2: </b> when pressed 3 seconds, button2 will activate set alarm.<br />
In set alarm status: <br/>
- <b>Button 1: </b> switches between minute-hour.<br />
- <b>Button 3: </b> increases. <br/>
- <b>Button 2:</b> exits set alarm and goes back to default mode.<br />
- <b>Button 3: </b> when pressed, button 3 will switch between celsius-fahrenheit. <br/>
- <b>Button 4:</b> switches between am/pm and 24h mode. when alarm is ringing, this button will snooze the alarm. <br/>

<h2>Functions </h2>
<b> 1. Setup() </b> <br/>
  
  Pin modes are defined, LCD and serial connection begin, all interrupts are disabled before timer configuretion and enabled after timer configuration. All interrupts are disabled before timer configuration and activated after timer configuration, and pin modes are defined. Serial and lcd begins. <br/>
  
<b> 2. Loop() </b> <br/>
  Switches between the modes to Show the active screen. Mode 0 shows lcd screen which is the default screen which shows current time, alarm and temperature. Mode 1 will execute set time and mode2 will execute set alarm functions. <br/>
  
<b> 3. TimeIncrease() </b> <br/>
   Increases the time and checks if the hour is larger than 12, it switches to PM, if it is lower than 12, it is AM. <br/>
  
<b> 4. controlButtonStates() </b> <br/>
  Checks if the current state is switched 0 to 1, it saves the time and compares the difference between current time and buttonREdge. If this difference is greater or equal to 3 seconds lcdMode will change. Button4State changes the AM/PM. <br/>
  
<b> 5. lcdScreen() </b> <br/>
   This function is the default mode of LCD screen. Prints the current time, temperature and alarm time and alarm’s mode of ON or OFF. <br/>
<b> 6. printTime() </b>  <br/>
  This function prints the time seen on the lcd screen. Prints the time set in setTime function. <br/>
  
<b> 7. printAlarm()</b>  <br/>
  Prints the time set in setAlarm function. <br/>
  
<b> 8. controlAlarm()</b>  <br/>
  This function controls if the chosen set alarm is equal to the current time then piezzo buzzer will ring due to time. If button 4 is pressed, the function will snooze the alarm. If button 1 , 2 or 3 are pressed, the alarm will stop. <br/>
  
<b> 9. setTime() & setAlarm()</b>  <br/>
  This functions, coordinates the x side of the cursor, and chooses the side of minute/hour with blink, then it checks the button pressed and increases the values according to the cursor’s positon. <br/>
  
<b> 10. setTemperature()</b>  <br/>
  This function checks which pin is the temperature is connected and maps it to the celcius. After mapping, it calculates the fahrenheit and controls which temperature mode is activated with flagTemp. <br/>
  
<b> 11. setBlink()</b>  <br/>
  This function sets the blink according to the cursor. When pressed button 2 , flagBlink checks if it is on the minute side or hour side. <br/>


 
