#include <Wire.h>              //library for lcd display
#include <LiquidCrystal_I2C.h> //library for I2C moudle 
#include "DHT.h"               //library for DHT11 temperature and humidity sensor

#define DHTPIN 7
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,20,4);//initialize display

int potPin = A2; // Potentiometer output connected to analog pin 3
int potVal = 600; // Variable to store the input from the potentiometer
int greenled = 2;
int redled = 3;
int buzzer = 4;
int smokeSensor = A0;
int sensorLimit = 550;

void setup() 
{
  dht.begin(); //turn on temp sensor
  
  lcd.init();  //turn on display
  lcd.backlight();  //turn on display backlight
  lcd.clear();  //refreshing the display so there are no messages left

  pinMode(greenled, OUTPUT);
  pinMode(redled,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(smokeSensor,INPUT);
  Serial.begin(9600); //serial monitor only for testing
}

void loop() 
{
  potVal = analogRead(potPin);
  if(potVal>sensorLimit+10 || potVal<sensorLimit-10){
    sensorLimit=potVal;
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Treshold:");
    lcd.setCursor(1,1);
    lcd.print(potVal);
    delay(1000);
    continue;
  }
  float temp = dht.readTemperature();  //reads the temperature
  int gasLevel = analogRead(smokeSensor);  //reads the gas level from A0 (analog pin)
  lcd.clear();
  Serial.print(temp); //using the serial monitor for testing
  Serial.println();
  if(isnan(temp))  //Check if any reads failed and exit early
  {
    //prints appropriate message on the display
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Temp sensor");
    lcd.setCursor(4,1);
    lcd.print("problem!");
    delay(1000);
    continue;
  }
  else if(isnan(gasLevel))  //Check if any reads failed and exit early
  {
    //prints appropriate message on the display
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Gas sensor");
    lcd.setCursor(4,1);
    lcd.print("problem!");
    delay(1000);
    continue;
  }
  else
  {
    if(gasLevel > sensorLimit || temp>35) //checks the temperature and gas level and if needed starts the fire alarm
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALERT!");
      lcd.setCursor(0,1);
      lcd.print("THERE IS A FIRE!");
      //green led OFF, red led ON
      digitalWrite(redled,HIGH);
      digitalWrite(greenled,LOW);
      //alarm on
      tone(buzzer, 1000, 10000);
      for(int i=0;i<10;i++){
      	delay(100);
      	noTone(buzzer);
      	delay(100);
      }
    }
    else
    {
      lcd.clear();
      //live temperature and gas level monitoring
      lcd.setCursor(0,0);    
      lcd.print("Temp: ");
      lcd.print(temp);
      lcd.print((char)223);
      lcd.setCursor(0,1);
      lcd.print("Gas level: ");
      lcd.print(gasLevel);
      //green led ON, red led OFF
      digitalWrite(redled,LOW);
      digitalWrite(greenled,HIGH);
      //alarm stop
      noTone(buzzer);
      delay(1000);
    }
  }
}
