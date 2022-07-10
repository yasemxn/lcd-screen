#include <LiquidCrystal.h>;

int rs=12, en=11, d5=6, d6=5, d7=4, d8=3;
LiquidCrystal lcd(rs, en, d5, d6, d7, d8);
		
unsigned long postponeTime;	
unsigned long buttonREdge;
unsigned long setTimeStart;
int button1 = 10;			
int button2 = 9;				
int button3 = 8;				
int button4 = 7;			
int buzzerPin = 2;			
int tmpPin = 0;		
int button1State = 0,button2State = 0, button3State = 0, button4State = 0;
int ap=0, timeFormat=0, flagAlarm=1, flagTemp=1, flagBlink=0;
int hour=10, minute=29, second=15;
int alarmHour=10, alarmMinute=32;
int lcdMode = 0;		
int celsius = 0;				
int fahrenheit = 0;	
String alarmStatus = "ON";
bool alarmOn = true;
int button1Previous, button2Previous;
bool press1Control, press2Control;
bool snoozed = false;



void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);				
  
  pinMode(button1, INPUT);		
  pinMode(button2, INPUT);		
  pinMode(button3, INPUT);		
  pinMode(button4, INPUT);		
  pinMode(tmpPin, INPUT);		
  cli();               	
  
  TCCR1A = 0;				
  TCCR1B = 0;
  TCNT1 = 3035 ;      		
  TCCR1B |= (1 << CS12);  		
  TIMSK1 |= B00000010;      
  OCR1A = 62500;			
  sei();              
}

ISR(TIMER1_COMPA_vect){      
  TCNT1 = 0;                
  timeIncrease();				
}

void loop(){
  if (lcdMode == 0){
    lcdScreen();
  }
  else if(lcdMode == 1)	{
    setTime();
  }
  else if(lcdMode == 2)	{
    setAlarm();
  }
}

void timeIncrease(){
  second += 1;						
  if (second == 60){
    second = 0;
    minute += 1;
  }
  if (minute == 60){		
    minute = 0;
    hour += 1;
  }
  if (hour >= 24) {
    hour = 0; 
    }	
  if (hour >= 12) {
    timeFormat = 1;		
    } 		
  if (hour < 12) {
    timeFormat = 0;	
  }
  
}

void controlButtonStates(){
  
  button1State = digitalRead(button1);			
  button2State = digitalRead(button2);			
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);

  if (button1State != button1Previous){
    if(button1Previous == 0){
      buttonREdge = millis();			
      press1Control = true;				
    }
    else press1Control = false;		
    button1Previous = button1State;	  }
  
  if (press1Control
      && (millis() - buttonREdge) >= 3000){ 
    lcdMode = 1;				
    press1Control = false;
  }

  if (button2State != button2Previous){
    if(button2Previous == 0){
      buttonREdge = millis();			
      press2Control = true;			
    }
    else press2Control = false;		
    button2Previous = button2State;			
  }
  
  if (press2Control
      && (millis() - buttonREdge) >= 3000){ 
    lcdMode = 2;						
    press2Control = false;
  }
  if (press2Control) {
    if(alarmOn) {
      alarmStatus = "OFF";
      alarmOn = false;
    }
    else {
      alarmStatus = "ON ";
      alarmOn = true;
    }
  }
  
  if (button4State){				
    ap = !ap;
    lcd.clear();
  }
  else if (button3State){					
    flagTemp = !flagTemp;
  }
   
}

void lcdScreen(){
  lcd.setCursor(0,0);	  
  lcd.print("   ");
  printTime(); 					

  lcd.setCursor(0,1);
  printAlarm();

  lcd.print("   ");
  setTemperature();	
  
  if (flagAlarm) controlAlarm();		
  controlButtonStates();			
  
  delay(200);
}

void printTime(){					
  String h = String(hour);
  String m = String(minute);
  String s = String(second);
  
  if (ap == 0 && hour == 12) {
    h = "12";
  }
  else if (ap == 0 && hour > 12) {
    h = String(hour % 12);

  }
  
  if ((ap==0 && hour%12<10 && h!="12")
      || (ap==1 && hour<10)){ 		
    lcd.print(0);
  }
  lcd.print(h + ":");				
  if (minute < 10)	lcd.print(0);	
  lcd.print(m + ":");			
  if (second < 10)	lcd.print(0);	
  lcd.print(s);						
  
  if (ap == 0){		
    if (timeFormat == 0) {
      lcd.print(" AM");
    }
    if (timeFormat == 1) {
      lcd.print(" PM");
    }
  } 	
}

void printAlarm(){			
  String h = String(alarmHour);
  String m = String(alarmMinute);
  
  if (ap == 0 && alarmHour == 12) h = "12";	
  else if (ap == 0 && alarmHour > 12)		
    h = String(alarmHour % 12); 
  
    
  if ((ap==0 && alarmHour%12<10 && h!="12")
      || (ap==1 && alarmHour<10)){ 				
    lcd.print(0);
  }
  lcd.print(h + ":");							
  if (alarmMinute < 10) lcd.print(0);			
  lcd.print(m + " ");							
  
  lcd.print(alarmStatus);
  
}

void controlAlarm(){
  
  if ((alarmHour == hour && alarmMinute == minute && !snoozed) 
      || ((millis() - postponeTime) / 1000) >= 5*60 && snoozed){
    
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("ALARM!");				
    tone(buzzerPin, 1000);    				
    while(true){
      button1State = digitalRead(button1);			
      button2State = digitalRead(button2);
      button3State = digitalRead(button3);
      button4State = digitalRead(button4);
      
      if (button1State || button2State || button3State){ 
        noTone(buzzerPin);					
        flagAlarm = 0;
        snoozed = false;
        break;
      }
      if (button4State){						
        noTone(buzzerPin);			
        postponeTime = millis();				
        snoozed = true;
        break;
      }
    }
  }
}

void setTime(){
  int lcdX = 0;								
  int varBlink = hour;					
  int switchIndex = 0;					
  lcd.clear();								
  setTimeStart = millis();				
  
  while(true){
    lcd.setCursor(0,0);					
  	lcd.print("SET TIME:");
  	
    lcd.setCursor(0,1);					
	if (hour < 10)		lcd.print("0");
	lcd.print(hour);					
   	lcd.print(":");
	if (minute < 10)	lcd.print("0");
	lcd.print(minute);					
    
    button1State = digitalRead(button1);	
  	button2State = digitalRead(button2);
  	button3State = digitalRead(button3);
    	
    if (button2State && switchIndex == 1){	
      switchIndex = 0;
      lcdX = 0;
    }
    else if (button2State && switchIndex == 0){
      switchIndex = 1; 
      lcdX = 3;
    }
    if (button3State && switchIndex == 0){	
      hour += 1;
      if(hour == 24)	hour = 0;
      	
    }
    if (button3State && switchIndex == 1){		
      minute += 1;
      if(minute == 60)	minute = 0;
      
    }
    if (button1State &&					
        (millis() - setTimeStart) >= 2000){
      lcdMode = 0;
      break;
    }	
    if (switchIndex == 0) {
        varBlink = hour;
    }
    if (switchIndex == 1) {
        varBlink = minute;
    }
    setBlink(varBlink, lcdX, 1);
  }
}

void setAlarm(){
  int lcdX = 0;						
  int varBlink = alarmHour;					
  int switchIndex = 0;						
  lcd.clear();								
  setTimeStart = millis();			

  while(true){
    lcd.setCursor(0,0);						
  	lcd.print("SET ALARM:");
  	
    lcd.setCursor(0,1);					
	if (alarmHour < 10)	lcd.print("0");
	lcd.print(alarmHour);
   	lcd.print(":");
	if (alarmMinute < 10) lcd.print("0");
	lcd.print(alarmMinute);
    
    button1State = digitalRead(button1);
  	button2State = digitalRead(button2);
  	button3State = digitalRead(button3);
    	
    if (button1State && switchIndex == 1){		
      switchIndex = 0;
      lcdX = 0;
    }
    else if (button1State && switchIndex == 0){
      switchIndex = 1; 
      lcdX = 3;
    }
    if (button3State && switchIndex == 0){	
      if(alarmHour == 24)	alarmHour = 0;
      alarmHour += 1;
    }
    if (button3State && switchIndex == 1){	
      if(alarmMinute == 60)	alarmMinute = 0;
      alarmMinute += 1;	
    }
    if (button2State &&				
        (millis() - setTimeStart) >= 2000){
      lcdMode = 0;
      break;
    }

    if (switchIndex == 0){
        varBlink = alarmHour;
    }
    if (switchIndex == 1){
        varBlink = alarmMinute;
    }
    setBlink(varBlink, lcdX, 1);	
  }
  flagAlarm = 1;						
}

void setTemperature(){
  celsius = map(((analogRead(tmpPin)-20)*3.04),0,1023,-40,125);
  fahrenheit = ((celsius*9) / 5 + 32);
  
  if (flagTemp == 0) {
    lcd.print(celsius);	
  }
  if (flagTemp == 1) {
    lcd.print(fahrenheit);
  }
 	
  lcd.print((char)0xB0);
  
  if (flagTemp == 0) {
    lcd.print("C");
  }
  if (flagTemp == 1) {
    lcd.print("F");
  }

}

void setBlink(int varBlink, int r, int c){
  lcd.setCursor(r, c);
  if (flagBlink == 0){					
    if (varBlink < 10)	lcd.print("0");
      lcd.print(varBlink);
      delay(400);
  	}
  if (flagBlink == 1){					
      lcd.print("  ");
 	  delay(400);
  }
  flagBlink = (flagBlink + 1) % 2;
}