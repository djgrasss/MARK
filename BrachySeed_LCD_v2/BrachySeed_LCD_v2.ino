/*
Michael Rees, Ananya Zutshi, Rhea Chitalia, Karthika Raja
Team MARK - Brachyseed Oscillation
VERSION 2.0 - Trying to write a more efficient code for the ST7565 LCD screen 


 
 Remember the ST7565 uses 3.3v, so a level shifter
 is needed if using a standard Arduino board.
 See Adafruit tutorial for more details:
  http://www.ladyada.net/learn/lcd/st7565.html
*/

#include <ST7565.h> // Adafruit LCD library


// Menu controls:
const int UP_PIN     = 11;  
const int DOWN_PIN   = 12;  
const int SELECT_PIN = 4; 

// LCD pins:
#define BACKLIGHT_LED 10  // Must be a PWM pin
#define LCD_SID  9
#define LCD_SCLK 8
#define LCD_A0   7 
#define LCD_RST  6
#define LCD_CS   5

// Must create an ST7565 instance before Menu:
ST7565 glcd(LCD_SID, LCD_SCLK, LCD_A0, LCD_RST, LCD_CS);


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

float Amplitude;    // variable to control amplitude. 
int Frequency;    // variable to control frequency. Hz
float Period;        // period of the frequency

/*
int freq_incr = 1;   // incrementing value for frequency. delta Hz 
float amp_incr  = 0.1;   // incrementing value for amplitude. delta PWM value

float freq_max = 50;       // Maximum frequency value. Hz
float freq_min = 0;       // minimun frequency value. Hz

float amp_max = 5;    // maximum amplitude value
float amp_min = 0;    // minimum aplitude value
*/

//ouput pins
const int Amp_Pin = 3;    // PWM enabled output pins. for Amplitude adjustments

const int Freq_Pin   = 2;    // Digital pin. for Frequency adjustments of H bridge half 1. Coupled TEMPORALLY with pin 4, but connects the h bridge path with pin 3
const int Freq_Pin_2 = 13; // Digital pin for frequency adjustments of H bridge half 2. Coupled TEMPORALLY with pin 3, but connects the h bridge path with pin 4
const int Freq_Pin_3 = 0;  // digital pin for frequency adjustments of H bridge half 1. Coupled TEMPORALLY with pin 2, but connects the h bridge path with pin 1 
const int Freq_Pin_4 = 1;  // digital pin for frequency adjustments of H bridge half 2. Coupled TEMPORALLY with pin 1, but connects the h bridge path with pin 2 

boolean Freq_State;    // on/off state of frequency modulating pin


// Define variables I need for menu tracking
int menu_screen = 1;  // will define which menu I am at
int cursor_loc  = 1;  // defines the cursor position on the menu
const char icon = '>';    // cursor icon

void setup() {
  pinMode(BACKLIGHT_LED, OUTPUT);
  glcd.begin(0x18); // Initialise LCD
  delay(10); // Just to be safe
  brightness_index = 1; // Initial brightness
  set_brightness(0); 
  //show_main(); // Draw main menu
  
  
  // draw Oscillating Seed Logo
  glcd.clear();
  glcd.drawbitmap(35, 2,  Icon16_glcd_bmp, 44, 55, BLACK);
  glcd.display();
  delay(3000);
  glcd.clear();
  
  // Draw BrachyVison Logo
   glcd.drawbitmap(0, 12,  logo16_glcd_bmp, 120, 27, BLACK);
   glcd.display();
   delay(3000);  
   glcd.clear();
    
  // Draw Welcome Message
  glcd.drawstring(0, 10, "Welcome to           BrachyVision Mark 1");
  glcd.display();
  delay(2000);
  glcd.clear();
  

// Define Input/Output pins

  // define pins as output
  pinMode(Amp_Pin, OUTPUT);
  pinMode(Freq_Pin, OUTPUT);
  pinMode(Freq_Pin_2, OUTPUT);
  pinMode(Freq_Pin_3, OUTPUT);
  pinMode(Freq_Pin_4, OUTPUT);
  

// Define default frequency pin states
Freq_State = HIGH;   // at Defualt, current is ON!: Magnet is on, oscillating at 0 Hz
digitalWrite(Freq_Pin, not Freq_State);
digitalWrite(Freq_Pin_2, Freq_State);
digitalWrite(Freq_Pin_3, not Freq_State);
digitalWrite(Freq_Pin_4, Freq_State);

uint8_t i=0;

// Define default Amplitude output
analogWrite(Amp_Pin, Amplitude);
  
}
// Lower brightness if dir<0, raise if dir>0
void set_brightness(int dir) {
  if (dir < 0) {
    if (brightness_index > 0) brightness_index--;
  }
  if (dir > 0) {
    if (brightness_index < 6) brightness_index++;
  }
  analogWrite(BACKLIGHT_LED, brightness_levels[brightness_index]);
}

void main_menu() {
 // draw main menu options
 glcd.drawstring(0, 0, "Main Menu"); 
 glcd.drawstring(15, 2, "Set Frequency"); 
 glcd.drawstring(15, 3, "Set Amplitude"); 
 glcd.drawstring(15, 4, "Set Backlight"); 
 
 // Display current amplitude and frequency values on the Main menu

  char buf[4];
  itoa(frequency_index, buf, 10);
  //glcd.drawstring(5, 4, "Current:");
  glcd.drawstring(30, 5, "Freq:"); 
  glcd.drawstring(70, 5, buf);
  glcd.drawstring(90, 5, "Hz");
  
  itoa(amplitude_index, buf, 10);
  glcd.drawstring(30, 7, "Amp:"); 
  glcd.drawstring(70, 7, buf);
  glcd.display();
} 
}

void loop() {
  //void main_menu()
  
  //void amp_menu()
  
  //void freq_menu()
  
  //void backlight_menu()
  
}  
