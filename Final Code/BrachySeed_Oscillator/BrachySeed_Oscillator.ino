/*********************
// BME 464, BrachySeed Oscillator
// Michael Rees, Rhea Chitalia, Ananya Zutshi, Karthika Rhaa


This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
#include <Time.h>  

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7




float Amplitude;    // variable to control amplitude. units?
int Frequency;    // variable to control frequency. Hz
float Period;        // period of the frequency

int freq_incr = 1;   // incrementing value for frequency. delta Hz 
float amp_incr  = 0.1;   // incrementing value for amplitude. delta PWM value

float freq_max = 50;       // Maximum frequency value. Hz
float freq_min = 0;       // minimun frequency value. Hz

float amp_max = 5;    // maximum amplitude value
float amp_min = 0;    // minimum aplitude value

//ouput pins
const int Amp_Pin = 3;    // PWM enabled output pins. for Amplitude adjustments
const int Freq_Pin = 8;    // Digital pin. for Frequency adjustments of H bridge half 1. Coupled TEMPORALLY with pin 4, but connects the h bridge path with pin 3
const int Freq_Pin_2 = 12; // Digital pin for frequency adjustments of H bridge half 2. Coupled TEMPORALLY with pin 4, but connects the h bridge path with pin 3
const int Freq_Pin_3 = 5;  // digital pin for frequency adjustments of H bridge half 1. Coupled TEMPORALLY with pin , but connects the h bridge path with pin 3 
const int Freq_Pin_4 = 6;  // digital pin for frequency adjustments of H bridge half 2. Coupled TEMPORALLY with pin 1, but connects the h bridge path with pin 3 

boolean Freq_State;    // on/off state of frequency modulating pin



void setup() {

  // define pins as input

  // define pins as output
  pinMode(Amp_Pin, OUTPUT);
  pinMode(Freq_Pin, OUTPUT);
  
  pinMode(Freq_Pin_2, OUTPUT);
  pinMode(Freq_Pin_3, OUTPUT);
  pinMode(Freq_Pin_4, OUTPUT);
  
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.setCursor(0,0);
  lcd.print("BrachyVision");
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
  delay(2000);
  lcd.clear();

// set default values
Frequency = 0;     // At default state, magnet does not oscillate
Amplitude = 2.5;  // At default state, current to magnet is half of pwm range

// Define default frequency pin states
Freq_State = HIGH;   // at Defualt, current is ON!: Magnet is on, oscillating at 0 Hz
digitalWrite(Freq_Pin, not Freq_State);
digitalWrite(Freq_Pin_2, Freq_State);
digitalWrite(Freq_Pin_3, not Freq_State);
digitalWrite(Freq_Pin_4, Freq_State);

// Display defaults
// (note: line 1 is the second row, since counting begins with 0):
lcd.setCursor(0,0);
lcd.print("Amp: ");
lcd.setCursor(5, 0);
lcd.print(Amplitude);
lcd.setCursor(0, 1);
lcd.print("Freq: ");
lcd.setCursor(6, 1);
lcd.print(Frequency);
lcd.setCursor(10, 1);
lcd.print(" Hz");
uint8_t i=0;

// Define default Amplitude output
analogWrite(Amp_Pin, Amplitude);
}

void loop() {
  int8_t buttons = lcd.readButtons();
    // check for any user input via buttons
      // increment amplitude and frequency appropriately 
      /*
  Input(Frequency, Amplitude, freq_incr, amp_incr)
    
    // display current frequency and amplitude
  //void Display()
  
    // output current freq and amplitude to electromagnets
  Output(Frequency, Freq_Pin)
 */
   if (buttons) { 
    if (buttons & BUTTON_UP) { 
      // increase frequency
      if (Frequency + freq_incr <= freq_max) {
       Frequency += freq_incr;
       delay(100);
      }
      // Update Freq Display
      lcd.setCursor(6, 1);
      lcd.print(Frequency);
      lcd.print(" ");
  } 
   if (buttons & BUTTON_DOWN) { 
    // decrease frequency
      if (Frequency > freq_min) {
      Frequency -= freq_incr;
      }
      delay(100);
      // Update Freq Display
      lcd.setCursor(6, 1);
      lcd.print(Frequency);
      lcd.print(" ");
   }
   
       if (buttons & BUTTON_RIGHT) { 
      // increase frequency
      if (Amplitude + amp_incr <= amp_max) {
       Amplitude += amp_incr;
       delay(100);
      }
      // Update Freq Display
      lcd.setCursor(5, 0);
      lcd.print(Amplitude);
      lcd.setCursor(9, 0);
      lcd.print("  ");
  } 
   if (buttons & BUTTON_LEFT) { 
    // decrease frequency
      if (Amplitude - amp_incr > amp_min) {
        Amplitude -= amp_incr;
      }
      delay(100);
      // Update Freq Display
      lcd.setCursor(5, 0);
      lcd.print(Amplitude);
      lcd.setCursor(9, 0);
      lcd.print("  ");
   }
  
   }  
      
  // output freq and amplitude settings 
   // if we are within a tolerance range to the frequency, switch the freq output. this creates oscillations
  Period = (1.0/float(Frequency))*1000;
  if (Frequency == 0) {
    Period = 0;
  }
  if (millis() % int(Period) <= 5 ) { // if we are within 4 msec of the time that the current frequency dictates that we switch pin modes...switch pin mode
   /*
    if (Freq_State = LOW) {
      Freq_State = HIGH;
      digitalWrite(Freq_Pin, Freq_State);
    }
    else {
      Freq_State = LOW;
      digitalWrite(Freq_Pin, Freq_State);
    }
    */

    
    Freq_State = not Freq_State;
    // modulate the frequency pins to switch which side of the H bridge is open. Add a delay BEFORE the new side OPENS to avoid shoot through currents on the transistors
    if (Freq_State == LOW) {
      digitalWrite(Freq_Pin, not Freq_State);
      digitalWrite(Freq_Pin_4, Freq_State);
      delay(5);   // add a delay to avoid "shot through" current on the transistors
      digitalWrite(Freq_Pin_2, Freq_State);
      digitalWrite(Freq_Pin_3, not Freq_State);
    } else {
        digitalWrite(Freq_Pin_2, Freq_State);
        digitalWrite(Freq_Pin_3, not Freq_State);
        delay(5);   // add a delay to avoid "shot through" current on the transistors
        digitalWrite(Freq_Pin, not Freq_State);
        digitalWrite(Freq_Pin_4, Freq_State);
    }
    
    Serial.print("hi ");
    Serial.print(Freq_State);
    Serial.print(" ");
    Serial.println(not Freq_State);
    
    }
    
    /*
    Serial.print(freq_incr);
    Serial.print(" ");
    Serial.print(Frequency);
    Serial.print(" ");
    Serial.print(int(Period));
    Serial.print(" ");    
    Serial.println(millis() % int(Period));
    */
    // update Amplitude output
    analogWrite(Amp_Pin, (Amplitude/5)*255);
    //Serial.println((Amplitude/5)*255);
}
/*
void Input(Frequency, Amplitude, freq_incr, amp_incr) {
 
  if (buttons) { 
    if (buttons & BUTTON_UP) { 
      // increase frequency
      if (Frequency + freq_incr <= freq_max) {
       Frequency = Frequency + freq_incr;
      }
      // Update Freq Display
      lcd.setCursor(6, 1);
      lcd.print(Frequency)
  } 
   if (buttons & BUTTONS_DOWN) { 
    // decrease frequency
      if (Frequency - freq_incr >= freq_min) {
      Frequency = Frequency - freq_incr;
      }
      // Update Freq Display
      lcd.setCursor(6, 1);
      lcd.print(Frequency)
   }
   
   if (buttons & BUTTONS_LEFT) { 
    // decrease amplitude
    if (Amplitude - amp_incr >= amp_min) {
      Amplitude = Amplitude - amp_incr;
      }
      // Update Amp Display
      lcd.setCursor(6, 0);
      lcd.print(Frequency)
   }
   if (buttons & BUTTONS_RIGHT) { 
    // decrease amplitude
    if (Amplitude - amp_incr >= amp_min) {
      Amplitude = Amplitude - amp_incr;
      }
      // Update AMP Display
      lcd.setCursor(6, 0);
      lcd.print(Frequency)
   }   
     
      
}




void Output(Frequency, Freq_Pin) {
 // output freq and amplitude settings 
   // if we are within a tolerance range to the frequency, switch the freq output. this creates oscillations
  Period = 1/Frequency;
  if (millis() % (Period*1000) <= 20 ) { // if we are within 20 msec of the time that the current frequency dictates that we switch pin modes...switch pin mode
    if (Freq_State = HIGH) {
      Freq_State = LOW;
      digitalWrite(Freq_Pin, Freq_State)
    }
    else if (Freq_State = LOW) {
      Freq_State = HIGH;
      digitalWrite(Freq_Pin, Freq_State)
    }
  }
}
*/
