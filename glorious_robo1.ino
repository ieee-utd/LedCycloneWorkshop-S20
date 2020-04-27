/*
 * Filename:             glorious_robo1.ino 
 * Date:                 4-27-2020
 * Author:               IEEE Technical Committee 
 * Email:                ieeeutd.org 
 * Version:              1.0
 * Copyright 2020, All Rights Reserved 
 *
 * Description 
 *         The code here will create an LED Cyclone Game for you
 *               to play at home! You can simulate it on 
 *               TinkerCad or build it in real life 
 */

#include <LiquidCrystal.h>

//LED array 
static const uint8_t leds[] = {A5, A4, A3, A2, A1, A0, 13, 12, 11}; 
//button const 
int button = 10; 
//lcd screen
//            lcd(RS,E,DB4,DB5,DB6,DB7); 
LiquidCrystal lcd(7,6,5,4,3,2); 

//index of the LED array - marks the position of the active LED
int LEDpos = 0; 

//store the timestamp of the last active LED 
long previousMillis = 0; 

//current interval 
int interval = 300; 

//keep track of how many times we have changed interval
int level = 1; 

//keep track of how many lives you have 
int lives = 3; 

//true: LEDs moving from left to right
//false: LEDs moving from right to left 
bool status = true; 

void setup()
{
  //setup all the pins as outputs 
  for(int i = 0; i <= 8; i++)
  {
    pinMode(leds[i],OUTPUT); 
  }
  
  //setup button as input 
  pinMode(button,INPUT); 
  
  //setup LCD display 
  lcd.begin(16,2); 
  
  //display 
  lcd.print("Lives: "); 
  lcd.setCursor(0,1); 
  lcd.print("Level: "); 
  //display the next level 
  lcd.clear(); 
  lcd.print("Lives: "); 
  lcd.setCursor(10,0); 
  lcd.print(lives); 
  lcd.setCursor(0,1); 
  lcd.print("Level: "); 
  lcd.setCursor(10,1); 
  lcd.print(level);
}

void loop()
{
  //if we are starting gameplay over 
  if(lives == 0)
  {
    lcd.setCursor(0,0); 
    lcd.print("Game Over!"); 
    lcd.setCursor(0,1); 
    lcd.print("Start over!"); 
    delay(2000); 
    
    //reset interval 
    interval = 300; 
    //reset number of levels 
    level = 1; 
    //reset number of lives 
    lives = 3; 
    
    //update the display 
    lcd.clear(); 
    lcd.print("Lives: "); 
    lcd.setCursor(10,0); 
    lcd.print(lives); 
    lcd.setCursor(0,1); 
    lcd.print("Level: "); 
    lcd.setCursor(10,1); 
    lcd.print(level);
  }
  
  if(digitalRead(button) == HIGH)
  {
     if(LEDpos == 4) //correct answer! 
     {
       interval /= 1.5;   //reduce our interval time 
       level++; 
       
       //indicate level up 
       lcd.setCursor(10,1); 
       lcd.print(" +1"); 
       delay(2000); 
       
       //display the next level 
       lcd.clear(); 
       lcd.print("Lives: "); 
       lcd.setCursor(10,0); 
       lcd.print(lives); 
  	   lcd.setCursor(0,1); 
  	   lcd.print("Level: "); 
       lcd.setCursor(10,1); 
       lcd.print(level);  
     }
    else             //incorrect blue LED 
    {
       lives--; 
   
       lcd.setCursor(10,0); 
       lcd.print("-1"); 
       delay(2000); 
       
       //display the next level 
       lcd.clear(); 
       lcd.print("Lives: ");
       lcd.setCursor(10,0); 
       lcd.print(lives); 
  	   lcd.setCursor(0,1); 
  	   lcd.print("Level: ");
       lcd.setCursor(10,1); 
       lcd.print(level);
    }
  }
  
  //store the current time in milliseconds 
  unsigned long currentMillis = millis(); 
  
  //if time elapsed since last active LED has changed 
  if (currentMillis - previousMillis > interval) 
  {
    //this means the LED is moving left to right 
    if (status) 
    {
      if (LEDpos > 7) // reached the last LED 
      {
        status = false; //switching directions 
      }
      else
      {
        LEDpos++;    //if we are not switching directions, 
                     //  we increment the counter 
      }
    }
    //this means the LED is moving right to left 
    if (!status)
    {
      if (LEDpos < 1)  // reached the first LED 
      {
        status = true; //switching directions 
      }
      else
      {
         LEDpos--;    //if we are not switching directions, 
                     //  we decrement the counter 
      }
    }
    //save the new time that we've blinked the LED 
    previousMillis = currentMillis; 
    
    //turn off all the LEDS 
    for (int x = 0; x <=8; x++)
    {
      digitalWrite(leds[x],LOW); 
    }

    //turn on one LED 
    digitalWrite(leds[LEDpos],HIGH);
  }
 
}