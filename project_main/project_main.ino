// Required libraries

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
//#include <Fonts/user/OswaldVariable8pt7b.h> // User a custom font
//#include <Fonts/user/UbuntuLightItalic9pt7b.h> // User a custom font
//#include <Fonts/user/UbuntuRegular8pt7b.h> // User a custom font

// Variable definitions
int sensorValue;
const size_t maxValue =4;
char oldSensorValue[maxValue] = {0};


// Pin definitions
#define sensorPin A0



// color definitions
const uint16_t  Black        = 0x0000;
const uint16_t  Blue         = 0x001F;
const uint16_t  Red          = 0xF800;
const uint16_t  Green        = 0x07E0;
const uint16_t  Cyan         = 0x07FF;
const uint16_t  Magenta      = 0xF81F;
const uint16_t  Yellow       = 0xFFE0;
const uint16_t  White        = 0xFFFF;

// Pin definfitions 

  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8


  // Create the TFT display object

  Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

  void setup()
  {
    // Init ST7735R chip, green tab

    tft.initR(INITR_144GREENTAB); 

    // initialise the display
    
    tft.setFont();
    tft.fillScreen(Red);
    tft.setTextColor(White);
    Serial.begin(9600);


  }

  void loop()
  {
    tft.setTextSize(1);
    tft.setCursor(5,15);
    tft.print("NET: ");
    tft.print(90);
    tft.println("%");
    tft.setCursor(15,40);
    tft.print("Sensor Value:");


   readSensorValue();




    
   

  }


  void readSensorValue()
  {

    /* This function tend to solve the issue with the short blinking screen 
     *  When tft.fillScreen, This issue was solved my ovewriting the recent 
     *  Value by a copy of it with the background color as display color
     */



    
    //Read the current sensor value
    sensorValue = analogRead(sensorPin);
    // Initialize the new and old sensor values

    char newSensorValue[maxValue] = {0};
    // Construct the new sensor value
     sprintf(newSensorValue, "%d", sensorValue);
     
    if (strcmp (oldSensorValue,newSensorValue) != 0)
    {
      // Change the text size
      tft.setTextSize(2);
      tft.setCursor(35,70);
      // Change text color to current background color
      tft.setTextColor(Red);
      // Print the old value that will overwrite our current text
      tft.print(oldSensorValue);
      //Bring the cursor back to the starting point
      tft.setCursor(35,70);
      //Change the text size
      tft.setTextSize(2);
      // Change the text color to the foreground color
      tft.setTextColor(White);
      //Print the new sensor value
      tft.print(newSensorValue);
      // Copy the new value to old value
      strcpy(oldSensorValue,newSensorValue); 
      delay(1000);
    } 
  }
