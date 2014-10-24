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



// Input and output variables
float Input; //variable input goes
float Output; // variable output goes

//ouput pins
int Output_Pin = 3;    // PWM enabled output pins


void setup() {

  // define pins as input

  // define pins as output
  pinMode(Output_Pin, OUTPUT);
  
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.setCursor(0,0);
  lcd.print("Oscillating at..");
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
  delay(1000);
  lcd.clear();  
}

uint8_t i=0;

void loop() {
    // check for any user input via buttons
      // increment amplitude and frequency appropriately 
  void Input()
    
    // display current frequency and amplitude
  void Display()
  
    // output current freq and amplitude to electromagnets
  void Output()
}

void Input() {
 
  if (buttons) { 
    if (buttons & BUTTON_UP) { 
      // increase frequency
   
  } 
   if (buttons & BUTTONS_DOWN) { 
    // decrease frequency
    
   }
   
   if (buttons & BUTTONS_LEFT) { 
    // decrease amplitude
   }
   if (buttons & BUTTONS_RIGHT) { 
    // decrease amplitude
   }   
     
      
}

void Display() {
        
      lcd.setCursor(0,0);
      lcd.print("Freq: ");  
      lcd.setCursor(6,0);
      lcd.print(Frequency); 
      lcd.setCursor(11,0);
      lcd.print(" Hz");     
    
    // set amplitude
      lcd.setCursor(0,1);
      lcd.print("Amp: ");
      lcd.setCursor(5,1);
      lcd.print(Amplitude);
      lcd.setCursor(11,1);
      lcd.print("mA"); 
}


void Output() {
 
 // output freq and amplitude settings 
}
