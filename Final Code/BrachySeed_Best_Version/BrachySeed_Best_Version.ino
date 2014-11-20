/*
Code to operate the ST7565 LCD user interface and output functionality of the BrachyVision oscillation device
    Copyright (C) 2014 Michael Rees

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
Michael Rees, Ananya Zutshi, Rhea Chitalia, Karthika Raja
Team MARK - Brachyseed Oscillation

 menu_test.pde - 11/2011
 A more complicated example of ST7565_Menu Arduino library.
 
 Remember the ST7565 uses 3.3v, so a level shifter
 is needed if using a standard Arduino board.
 See Adafruit tutorial for more details:
  http://www.ladyada.net/learn/lcd/st7565.html
*/

#include <ST7565.h> // Adafruit LCD library
//#include <ST7565_Menu.h>

// Menu controls:
const int UP_PIN     = 12;  
const int DOWN_PIN   = 11;  
const int SELECT_PIN = 4; 

int UP;
int DOWN;
int SELECT;

// LCD pins:
#define BACKLIGHT_LED 10  // Must be a PWM pin
#define LCD_SID  9
#define LCD_SCLK 8
#define LCD_A0   7 
#define LCD_RST  6
#define LCD_CS   5

// Must create an ST7565 instance before Menu:
ST7565 glcd(LCD_SID, LCD_SCLK, LCD_A0, LCD_RST, LCD_CS);


  
// Create Menu with control pins and address of glcd:
//Menu menu(UP_PIN, DOWN_PIN, SELECT_PIN, &glcd);

// a bitmap of the BrachySeed Icon
static unsigned char __attribute__ ((progmem)) Icon16_glcd_bmp[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x40,0x20,0x20,0x00,0x10,0x10,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x40,0x00,0x10,0x00,0x04,0xC2,0x41,0x30,0x10,0x08,0x84,0x44,0x02,0x22,0x22,0x23,0x01,0x01,0x11,0x11,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x60,0x0C,0x03,0x80,0x60,0x08,0x06,0x01,0x30,0x08,0x04,0x42,0x21,0x00,0x88,0x44,0x26,0x22,0x12,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0x1D,0x00,0x00,0x1E,0x00,0x00,0x08,0x01,0x00,0x08,0x01,0x3C,0x7E,0xFE,0xFE,0xFF,0xFE,0xFE,0xFE,0xFE,0x7C,0x3C,0x00,0x40,0x00,0x00,0x60,0x04,0x00,0xC0,0x0A,0x00,0x80,0x3F,0x00,0x00,0xC0,0x1E,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x48,0x44,0x04,0x22,0x10,0x08,0x84,0x41,0x20,0x18,0x06,0xC1,0x60,0x18,0x07,0x00,0xC0,0x38,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x08,0x08,0x08,0x08,0x08,0x88,0x80,0x84,0xC4,0x42,0x61,0x30,0x10,0x08,0x04,0x01,0x80,0x40,0x30,0x0C,0x02,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x21,0x21,0x21,0x21,0x21,0x21,0x21,0x20,0x00,0x00,0x10,0x08,0x00,0x00,0x02,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

// a bitmap of the BrachyVision Logo
// static unsigned char  logo16_glcd_bmp[]= {
PROGMEM const unsigned char logo16_glcd_bmp[]= {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0xE0,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x80,0xF0,0xE0,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA0,0x00,0x40,0x00,0x20,0x20,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xFE,0x66,0x42,0x66,0xFC,0x9C,0x00,0x00,0x00,0xFE,0x46,0x42,0x46,0xE4,0xBC,0x00,0x00,0x00,0x80,0xF8,0x9E,0x86,0xBE,0xF0,0x80,0x00,0x00,0xF0,0xFC,0x0C,0x04,0x06,0x06,0x06,0x00,0x00,0xFE,0xFE,0x60,0x60,0x60,0x60,0x6E,0xFE,0x00,0x00,0x06,0x1E,0x38,0xE0,0x70,0x1C,0x06,0x02,0x00,0x00,0x01,0x0F,0x7F,0xFE,0xE0,0x00,0xE0,0xFC,0x7F,0x0F,0x03,0x00,0x00,0x00,0xFE,0xFE,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x60,0x72,0x70,0x70,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0xE0,0xF8,0x0C,0x04,0x06,0x06,0x04,0x9C,0xF8,0x00,0x00,0x00,0xFE,0x0E,0x1C,0x70,0xC0,0x00,0xFE,0xFE,0x00,0x00,
0x00,0x00,0x07,0x04,0x04,0x04,0x06,0x03,0x01,0x00,0x00,0x07,0x00,0x00,0x00,0x03,0x07,0x04,0x00,0x04,0x07,0x01,0x00,0x00,0x00,0x03,0x07,0x04,0x00,0x01,0x03,0x03,0x06,0x04,0x04,0x06,0x00,0x00,0x07,0x07,0x00,0x00,0x00,0x00,0x06,0x07,0x00,0x00,0x00,0x00,0x00,0x07,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x04,0x00,0x00,0x00,0x00,0x04,0x07,0x00,0x00,0x00,0x03,0x03,0x06,0x04,0x04,0x06,0x03,0x01,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x01,0x07,0x07,0x07,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


//Backlight PWM values:
uint8_t brightness_levels[7] = { 0, 20, 50, 90, 130, 190, 250 };
uint8_t brightness_index; // Index of brightness_levels

// Frequency and Amplitude values
const int amp_size = 11;
const int freq_size = 51;

uint8_t amplitude_levels[amp_size] = { 0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250 };
uint8_t amplitude_index = 5; // Index of brightness_levels. default set at half of max

uint8_t frequency_levels[freq_size] = {0, 1,2, 3,  4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 };

uint8_t frequency_index = 1; // Index of brightness_levels. default set at 1 Hz


// Define variables and output pins for Amp/ freq modulation

float Amplitude = 5;    // variable to control amplitude. 
int Frequency = 1;    // variable to control frequency. Hz
float Period;        // period of the frequency
const int Freq_max = 50; // Maximum Frequency. Hz
const int Amp_max = 10;  // Maximum Amplitude.

//ouput pins
const int Amp_Pin = 3;    // PWM enabled output pins. for Amplitude adjustments

const int Freq_Pin   = 2;    // Digital pin. for Frequency adjustments of H bridge half 1. Coupled TEMPORALLY with pin 4, but connects the h bridge path with pin 3
const int Freq_Pin_2 = 13; // Digital pin for frequency adjustments of H bridge half 2. Coupled TEMPORALLY with pin 3, but connects the h bridge path with pin 4
const int Freq_Pin_3 = 0;  // digital pin for frequency adjustments of H bridge half 1. Coupled TEMPORALLY with pin 2, but connects the h bridge path with pin 1 
const int Freq_Pin_4 = 1;  // digital pin for frequency adjustments of H bridge half 2. Coupled TEMPORALLY with pin 1, but connects the h bridge path with pin 2 

boolean Freq_State;    // on/off state of frequency modulating pin

// Define variables I need for menu tracking
int cursor_loc  = 1;  // defines the cursor position on the menu
const char icon = '>'; // cursor icon
float backlight;   // variable to control backlight brighness. varies between 0 and 10
int count;
float time;  // elapsed time, in seconds
float sine;
float sine_last = 1;
void setup() {
    // Debugging output
  int time = millis();
  //Serial.begin(9600);
  //Serial.print("Took "); Serial.print(time); Serial.println(" ms");

  
  pinMode(BACKLIGHT_LED, OUTPUT);
  glcd.begin(0x18); // Initialise LCD
  delay(10); // Just to be safe
  brightness_index = 1; // Initial brightness
  //set_brightness(1); 
  
  
  // draw Oscillating Seed Logo
  glcd.clear();
  glcd.drawbitmap(35, 2,  Icon16_glcd_bmp, 44, 55, BLACK);
  glcd.display();
  delay(3);
  glcd.clear();
  
  // Draw BrachyVison Logo
   glcd.drawbitmap(0, 12,  logo16_glcd_bmp, 120, 27, BLACK);
   glcd.display();
   delay(3);  
   glcd.clear();
    
  // Draw Welcome Message
  glcd.drawstring(0, 2, "Welcome to           BrachyVision Mark 1");
  glcd.display();
  delay(2);
  glcd.clear();
  

// Define Input/Output pins

  // define pins as output
  pinMode(Amp_Pin, OUTPUT);
  pinMode(Freq_Pin, OUTPUT);
  pinMode(Freq_Pin_2, OUTPUT);
  pinMode(Freq_Pin_3, OUTPUT);
  pinMode(Freq_Pin_4, OUTPUT);
  
  // define button pins as inputs
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(SELECT_PIN, INPUT);



// Define default frequency pin states
Freq_State = HIGH;   // at Defualt, current is ON!: Magnet is on, oscillating at 0 Hz
digitalWrite(Freq_Pin, not Freq_State);
digitalWrite(Freq_Pin_2, Freq_State);
digitalWrite(Freq_Pin_3, not Freq_State);
digitalWrite(Freq_Pin_4, Freq_State);



uint8_t i=0;

// Define default Amplitude output
analogWrite(Amp_Pin, Amplitude);

set_backlight();

}

void set_backlight() {
  
  while(1) {
  // draw menu option
  glcd.clear();
  glcd.drawstring(0, 0, "Set Backlight");
  glcd.drawstring(10, 2, "Up");
  glcd.drawstring(10, 3, "Down");
  glcd.drawstring(10, 4, "Finished"); 
  // display brightness 
  draw_brightness();
  // draw cursor
  glcd.drawstring(0, cursor_loc + 1, ">");
  glcd.display();
  
  // digital read all input pins 
   UP = digitalRead(UP_PIN);
   DOWN = digitalRead(DOWN_PIN);
   SELECT = digitalRead(SELECT_PIN);
  
  // evaluate button states
  // may need to debounce buttons
    if ( UP == 1) {
      // cursor up one if not already at top. Up means up on the screen, so actually decreases
      if (cursor_loc > 1) {
        cursor_loc--;
      }
    }
    else if (DOWN == 1) {
      // cursor down one if not already at bottom. down means down on the screen, so actually increases
      if (cursor_loc < 3) {
        cursor_loc++;
      }
    }
    else if (SELECT == 1 and cursor_loc == 1) {
      // if cursor is at the "UP" icon, exit this screen, increase brightness
      if (backlight < 10) {
        backlight++;
      }
    }
    else if (SELECT == 1 and cursor_loc == 2) {
      // if cursor is at the "finished" icon, exit this screen, decrease brighness
      if (backlight > 0) {
        backlight--;
      }
    }    
    else if (SELECT == 1 and cursor_loc == 3) {
      // if cursor is at the "finished" icon, exit this screen, set cursor back to 1
      cursor_loc = 1;
      break;
    }
    // analog write the new brightness value to the backlight
    analogWrite(BACKLIGHT_LED, (backlight/10.0)*255);
   // Serial.println(cursor_loc);
    
  }
  
  
}
void draw_brightness() {
  char buf[12];
  // Just display brightness_index as brightness level:
  itoa(backlight, buf, 10); 
  glcd.drawstring(15, 6, buf);
  // Visual level display:
  glcd.drawrect(30, 47, 60, 8, BLACK);
  glcd.fillrect(30, 47, 6*backlight, 8, BLACK);
}

void draw_frequency_and_amp() {
  char buf[12];
  // Just display brightness_index as brightness level:
  itoa(Frequency, buf, 10); 
  glcd.drawstring(15, 2, buf);
  glcd.drawstring(25, 1, "Frequency (Hz)");
  // Visual level display:
  glcd.drawrect(30, 17, 60, 8, BLACK);
  glcd.fillrect(30, 17, 1.2*Frequency, 8, BLACK);

  char buffer[12];
  // Just display brightness_index as brightness level:
  itoa(Amplitude, buffer, 10); 
  glcd.drawstring(15, 6, buffer);
  glcd.drawstring(30, 5, "Amplitude");
  // Visual level display:
  glcd.drawrect(30, 48, 60, 8, BLACK);
  glcd.fillrect(30, 48, 6*Amplitude, 8, BLACK);
}

void draw_cursor(){
  if (cursor_loc == 1) {
     glcd.drawstring(0, 1, ">>");
    glcd.drawstring(110, 1, "<<"); 
  }
  else if (cursor_loc == 2) {
     glcd.drawstring(0, 5, ">>");
    glcd.drawstring(110, 5, "<<"); 
  }  
}

void modulate_output() {
    //Serial.println(Period);

      Period = (1.0/float(Frequency))*1000;
  if (Frequency == 0) {
    Period = 0;
  }
  //if (millis() % int(Period) <= 2 ) { // if we are within 4 msec of the time that the current frequency dictates that we switch pin modes...switch pin mode
  //Serial.println(Period);
    time = millis()/(1000/6.282);
    sine = sin(time*Frequency)/sqrt(pow(sin(time*Frequency), 2));
    
    if (int(sine) != int(sine_last)) {
      Freq_State = not Freq_State;
      sine_last = sine;
      // modulate the frequency pins to switch which side of the H bridge is open. Add a delay BEFORE the new side OPENS to avoid shoot through currents on the transistors
     
     if (sine > 0) {
        digitalWrite(Freq_Pin, not Freq_State);
        digitalWrite(Freq_Pin_4, Freq_State);
        delay(5);   // add a delay to avoid "shoot through" current on the transistors
        digitalWrite(Freq_Pin_2, Freq_State);
        digitalWrite(Freq_Pin_3, not Freq_State);
      } 
      else {
          digitalWrite(Freq_Pin_2, Freq_State);
          digitalWrite(Freq_Pin_3, not Freq_State);
          delay(5);   // add a delay to avoid "shoot through" current on the transistors
          digitalWrite(Freq_Pin, not Freq_State);
          digitalWrite(Freq_Pin_4, Freq_State);
      }
      
      //digitalWrite(Freq_Pin_2, Freq_State);
      /*
      Serial.print("hi ");
      Serial.print(digitalRead(Freq_Pin_2));
      Serial.print(" ");
      Serial.print(Freq_State);
      Serial.println(" ");
      Serial.println(millis() % int(Period));
      delay(2);
      */
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
    analogWrite(Amp_Pin, (amplitude_index/10)*255);  // Amplitude value has to be converted to pwm range, which is from 0--> 255
    //Serial.println((float(amplitude_index)/10.0)*255);
    /*
    Serial.print(frequency_index);
    Serial.print(" ");
    Serial.print(frequency_levels[frequency_index]);
    Serial.print(" ");
    Serial.print(int(Period));
    Serial.print(" ");    
    Serial.println(millis() % int(Period));
    */
    

 delay(4);
}

void loop() {
  //Serial.print(millis());
  //Serial.print(" ");
  if (count == 0) { 
  glcd.clear();
// display frequency and amplitude
  draw_frequency_and_amp();
// display cursor location
  draw_cursor();
  glcd.display();
  count++;
  }
// take in input
  // digital read all input pins 
   UP = digitalRead(UP_PIN);
   DOWN = digitalRead(DOWN_PIN);
   SELECT = digitalRead(SELECT_PIN);
  
  // evaluate button states
  // may need to debounce buttons
    if ( UP == 1) {
      if (cursor_loc == 1 and Frequency < Freq_max) {
        Frequency++;
        count = 0;
      } else if (cursor_loc == 2 and Amplitude < Amp_max) {
        Amplitude++;
        count = 0;
      }
    }
    else if (DOWN == 1) {
      if (cursor_loc == 1 and Frequency > 0) {
        Frequency--;
        count = 0;
      } else if (cursor_loc == 2 and Amplitude > 0) {
        Amplitude--;
        count = 0;
      }
    }
    else if (SELECT == 1 and cursor_loc == 1) {
      // if cursor is at the top icon, put it at the bottom
      cursor_loc = 2;
      count = 0;
      delay(5); // add a delay to avoid the cursor bouncing up and down on one button press
    }
    else if (SELECT == 1 and cursor_loc == 2) {
      // if cursor is at the bottom icon, put it at the top
      cursor_loc = 1;
      count = 0;
      delay(5); // add a delay to avoid the cursor bouncing up and down on one button press
    }    
   
   // modulate output
  modulate_output(); 
  //Serial.println(millis());
  //time = millis()/(1000/6.282);
  //sine = sin(time)/sqrt(pow(sin(time), 2));
  /*
  if (millis() < 15000) {
    Serial.print(millis());
    Serial.print(" ");
    Serial.println(sine);
  }
  */
  //digitalWrite(Freq_Pin_4, HIGH);
  //delay(500);
  //digitalWrite(Freq_Pin_4, LOW);
  //delay(500);
  
  
  
}

