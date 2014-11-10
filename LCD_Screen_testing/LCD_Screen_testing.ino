
//  *********************
// BME 464, BrachySeed Oscillator, LCD test
// Michael Rees, Rhea Chitalia, Ananya Zutshi, Karthika Rhaa

#include "ST7565.h"

int ledPin =  13;    // LED connected to digital pin 13
int Frequency = 0;
String freq = String(Frequency);

// Define array of Amplitdue and Frequency values
char Amplitude[51] = {'0', '1','2', '3', ' 4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31', '32', '33', '34', '35', '36', '37', '38', '39', '40', '41', '42', '43', '44', '45', '46', '47', '48', '49', '50' };

//char Frequency[51] = { 

// the LCD backlight is connected up to a pin so you can turn it on & off
#define BACKLIGHT_LED 10

// pin 9 - Serial data out (SID)
// pin 8 - Serial clock out (SCLK)
// pin 7 - Data/Command select (RS or A0)
// pin 6 - LCD reset (RST)
// pin 5 - LCD chip select (CS)
ST7565 glcd(9, 8, 7, 6, 5);

//#define LOGO16_GLCD_HEIGHT 16 
//#define LOGO16_GLCD_WIDTH  16 


void setup() {
  Serial.begin(9600);

  //Serial.print(freeRam());
  
  // turn on backlight
  pinMode(BACKLIGHT_LED, OUTPUT);
  digitalWrite(BACKLIGHT_LED, HIGH);

  // initialize and set the contrast to 0x18
  glcd.begin(0x18);
  glcd.clear();

  // draw a string at location (0,0)
  //glcd.drawstring(0, 0, "Welcome to           BrachyVision Mark 1");
  glcd.drawstring(0, 0, "Hello, my name is Tom Riddle. I see you   have found my        Vibrating Rectal     Probe");
  glcd.display();
  delay(2000);
  glcd.clear();
  
}

void loop() {
  /*
  glcd.drawstring(0, 0, "Amplitude");
  glcd.display();
  glcd.drawstring(15, 0, freq);
  glcd.display();
  */
  //glcd::drawLine(0, 5, 0, 5);
  
}
