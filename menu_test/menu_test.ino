/*
 menu_test.pde - 11/2011
 A more complicated example of ST7565_Menu Arduino library.
 
 Remember the ST7565 uses 3.3v, so a level shifter
 is needed if using a standard Arduino board.
 See Adafruit tutorial for more details:
  http://www.ladyada.net/learn/lcd/st7565.html
*/

#include <ST7565.h> // Adafruit LCD library
#include <ST7565_Menu.h>

// Menu controls:
#define UP_PIN     11  
#define DOWN_PIN   12  
#define SELECT_PIN 4  



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
Menu menu(UP_PIN, DOWN_PIN, SELECT_PIN, &glcd);

//Backlight PWM values:
uint8_t brightness_levels[7] = { 0, 20, 50, 90, 130, 190, 250 };
// Frequency and Amplitude levels
uint8_t amplitude_levels[5] = { 0, 60, 120, 180, 250};
uint8_t frequency_levels[7] = { 0, 20, 50, 90, 130, 190, 250 };

uint8_t amplitude_index; // Index of amplitude_levels
uint8_t frequency_index; // Index of frequency_levels


void setup() {
  
  
  pinMode(BACKLIGHT_LED, OUTPUT);
  glcd.begin(0x18); // Initialise LCD
  delay(10); // Just to be safe
  amplitude_index = 1; // Initial brightness
  frequency_index = 1; // Initial brightness
  set_amplitude(0);
  set_frequency(0);  
  show_main(); // Draw main menu
}

// Draw main menu screen:
void show_main() {
  menu.clear(); // Clear menu and display
  
  // If menu.update() called 70 times, light_of() will be called:
  //menu.add_timeout_function(70, light_off); 

  // Title always shown on first line:
  menu.set_title("Menu:");
  
  // Add items with function to be called when selected:
  menu.add_item("Set Frequency", show_frequency);
  menu.add_item("Set Amplitude", show_amplitude);
  menu.add_item("Set Backlight", set_backlight);
}

// Draw frequency display menu:
void show_frequency() {
  menu.clear(); 
  
  // Back to main menu after 40 a inactive loops:
  menu.add_timeout_function(40, show_main);
  
  menu.add_draw_function(draw_frequency);
  menu.set_title("Frequency:");
  
  // These items will pass their integer values
  // (1 and -1) to set_brightness:
  menu.add_item("Up", 1, set_frequency);
  menu.add_item("Down", -1, set_frequency);
  
  menu.add_item("Back", show_main);
}

// Draw Amplitude menu:
void show_amplitude() {
  menu.clear();
  
  // Back to main menu after 40 a inactive loops:
  menu.add_timeout_function(40, show_main);
  
  menu.add_draw_function(draw_amplitude);
  menu.set_title("Amplitude:");
  
  // These items will pass their integer values
  // (1 and -1) to set_brightness:
  menu.add_item("Up", 1, set_amplitude);
  menu.add_item("Down", -1, set_amplitude);
  
  menu.add_item("Back", show_main);
}

// Fill a menu to demonstrate scrolling:
void set_backlight() {
  uint8_t i;
  char value[12]; // To hold counter value
  char label[22]; // To hold item label
  menu.clear();
  menu.add_timeout_function(40, show_main);
  menu.set_title("Backlight Brightness:");
  menu.add_item("Back", show_main);
  for (i=1; i<=MAX_ITEMS-2; i++) {
    strcpy(label, "Menu Item "); // First part of label
    itoa(i, value, 10);   // Get counter value
    strcat(label, value); // Append counter string
    menu.add_item(label); // Add it
  }
  menu.add_item("Back", show_main);
}

// Convert and display ADC values from A0 and A1:
void draw_analog() {
  char buffer[12];
  int value;
  value = analogRead(A0);
  itoa(value, buffer, 10);
  glcd.drawstring(20, 3, "A0:");
  glcd.drawstring(44, 3, buffer);
  
  value = analogRead(A1);
  itoa(value, buffer, 10);
  glcd.drawstring(20, 4, "A1:");
  glcd.drawstring(44, 4, buffer);
}

// Lower Amplitude if dir<0, raise if dir>0
void set_amplitude(int dir) {
  if (dir < 0) {
    if (amplitude_index > 0) amplitude_index--;
  }
  if (dir > 0) {
    if (amplitude_index < 6) amplitude_index++;
  }
  //analogWrite(BACKLIGHT_LED, brightness_levels[amplitude_index]);
}

// Lower Frequency if dir<0, raise if dir>0
void set_frequency(int dir) {
  if (dir < 0) {
    if (frequency_index > 0) frequency_index--;
  }
  if (dir > 0) {
    if (frequency_index < 6) frequency_index++;
  }
  //analogWrite(BACKLIGHT_LED, brightness_levels[frequency_index]);
}

// Draw lower section of Amplitude screen:
void draw_amplitude() {
  char buf[12];
  // Just display brightness_index as brightness level:
  itoa(amplitude_index, buf, 10); 
  glcd.drawstring(LEFT_MARGIN+10, 5, buf);
  // Visual level display:
  glcd.drawrect(LEFT_MARGIN+17, 40, 60, 8, BLACK);
  glcd.fillrect(LEFT_MARGIN+17, 40, 10*amplitude_index, 8, BLACK);
}

// Draw lower section of Frequency screen:
void draw_frequency() {
  char buf[12];
  // Just display brightness_index as brightness level:
  itoa(frequency_index, buf, 10); 
  glcd.drawstring(LEFT_MARGIN+10, 5, buf);
  // Visual level display:
  glcd.drawrect(LEFT_MARGIN+17, 40, 60, 8, BLACK);
  glcd.fillrect(LEFT_MARGIN+17, 40, 10*frequency_index, 8, BLACK);
}
/*
void light_off() {
  uint8_t brightness = brightness_index; // Save current level
  brightness_index = 0;
  set_brightness(0);
  // Hold until button press then reset brightnes:
  while (digitalRead(UP_PIN)&digitalRead(DOWN_PIN)&digitalRead(SELECT_PIN));
  brightness_index = brightness; // 
  set_brightness(0);
}
*/
void loop() {
  // Now we just need to update the menu each time 
  // through the main loop, it takes care of the 
  // rest for us!
  menu.update();
}

