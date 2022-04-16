#include <Wire.h>              //library for lcd display
#include <LiquidCrystal_I2C.h> //library for I2C moudle 
#include "DHT.h"               //library for DHT11 temperature and humidity sensor
#include <arduino-timer.h>

#define DHTPIN 7
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,20,4);//initialize display

int buttonStartAlarm = 5;     // the number of the pin of the start alarm button
int buttonStopAlarm = 6;     // the number of the pin of the stop alarm button
int potPin = A2; // Potentiometer output connected to analog pin 2
int potVal = 550; // Variable to store the input from the potentiometer
int greenled = 2;
int redled = 3;
int buzzer = 4;
int smokeSensor = A0;
int sensorLimit = 550;

//Alarm and Timer varialbles
bool AlarmStart=false;
bool AlarmStop=false;
//vars to known if the button is pressed
int buttonStateStart = 0;
int buttonStateStop = 0;
//var to hold function to be called back
Timer<10, millis, bool> timer; 

//when the 10 sec end, stop the button effects
bool EndButtonTimer(bool isStart)
{
  if(isStart)
  {
    AlarmStart=false;
  }
  else
  {
    AlarmStop=false;
  }
  return true;
}

//functionallity when there is no fire
void NormalMode(float temp, int gasLevel)
{
  lcd.clear();
  //live temperature and gas level monitoring
  lcd.setCursor(0,0);    
  lcd.print("Temp: ");
  lcd.print(temp);
  //show the temp with the Celcius sign
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Gas level: ");
  lcd.print(gasLevel);
  //green led ON, red led OFF
  digitalWrite(redled,LOW);
  digitalWrite(greenled,HIGH);
  //alarm stop
  noTone(buzzer);
  delay(500);  
}
//functionallity when the alarm is active
void AlarmMode(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ALERT!");
  lcd.setCursor(0,1);
  lcd.print("THERE IS A FIRE!");
  //green led OFF, red led ON
  digitalWrite(redled,HIGH);
  digitalWrite(greenled,LOW);
  //start-stop the buzzer 3 times and delay a bit the alarm
  for(int i=0;i<3;i++)
  {
    tone(buzzer, 1000, 10000);
    delay(100);
    noTone(buzzer);
    delay(100);
  }
}
void setup() 
{
  dht.begin(); //turn on temp sensor
  
  lcd.init();  //turn on display
  lcd.backlight();  //turn on display backlight
  lcd.clear();  //refreshing the display so there are no messages left

  pinMode(greenled, OUTPUT);
  pinMode(redled,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(buttonStartAlarm, INPUT);
  pinMode(buttonStopAlarm, INPUT);
  pinMode(smokeSensor,INPUT);
  Serial.begin(9600); //serial monitor only for testing
}

void loop() 
{
  timer.tick(); // tick the timer
  buttonStateStart = digitalRead(buttonStartAlarm);//get the value of the start button
  buttonStateStop = digitalRead(buttonStopAlarm);//get the value of the stop button
  if(buttonStateStart==1)
  {
    //will make the alarm start for 10 sec
    AlarmStop=false;
    AlarmStart=true;
    timer.in(10000, EndButtonTimer, true);
  }
  else if(buttonStateStop==1){
    //the alarm wont work for 10 sec
    AlarmStop=true;
    AlarmStart=false;
    timer.in(10000, EndButtonTimer, false);
  }
  //read the potentiometer
  potVal = analogRead(potPin);
  if(potVal>sensorLimit+10 || potVal<sensorLimit-10){//check if the potentiometer valued is moved over 10, otherwise it costantly sees change 
    sensorLimit=potVal;//if there is more than 10 difference, make the sensor limit as much as the potentiometer value
    //print the new threshold
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Threshold:");
    lcd.setCursor(1,1);
    lcd.print(potVal);
    delay(1000);
    return;//skip to see if the value is still being changed
  }
  float temp = dht.readTemperature();  //reads the temperature
  int gasLevel = analogRead(smokeSensor);  //reads the gas level from A0 (analog pin)
  lcd.clear();
  Serial.print(temp); //using the serial monitor for testing
  Serial.println();
  if(isnan(temp))  //Check if any reads failed and exit early - tempreture sensor
  {
    //prints appropriate message on the display
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Temp sensor");
    lcd.setCursor(4,1);
    lcd.print("problem!");
    delay(1000);
    return;
  }
  else if(isnan(gasLevel))  //Check if any reads failed and exit early - gas sensor
  {
    //prints appropriate message on the display
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Gas sensor");
    lcd.setCursor(4,1);
    lcd.print("problem!");
    delay(1000);
    return;
  }
  else
  {
    //checks the temperature and gas level and if needed starts the fire alarm
    if((gasLevel > sensorLimit || temp>35 || AlarmStart==true) && AlarmStop==false)
    {
      //activate alarm
      AlarmMode();
    }
    else
    {
      //show the normal stats on the lcd
      NormalMode(temp, gasLevel);
    }
  }
}
