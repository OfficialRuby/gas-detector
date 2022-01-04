// Required libraries

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

//NWONU CHUKWUEMEKA SIMON/
//Reg no: 2017030182221/


#include "OswaldRegular12pt7b.h"
#include "OswaldRegular10pt7b.h"

// Display shiled pin configs
#define TFT_CS         D8
#define TFT_RST        D0
#define TFT_DC         D6
#define TFT_MOSI       D7
#define TFT_SCLK       D5
// color definitions
const uint16_t BLACK_COLOR        = 0x0000;
const uint16_t BLUE_COLOR         = 0xF800;
const uint16_t RED_COLOR          = 0x001F;
const uint16_t GREEN_COLOR        = 0x07E0;
const uint16_t CYAN_COLOR         = 0x07FF;
const uint16_t MAGENTA_COLOR      = 0xF81F;
const uint16_t YELLOW_COLOR       = 0xFFE0;
const uint16_t WHITE_COLOR        = 0xFFFF;


// Variable definitions
const size_t max_length = 6;
unsigned long sensorValue;  //variable to store sensor value

char oldSensorValue[max_length] = {0};


// Pin definitions
#define mq2sensorPin A0




// Create the TFT display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void welcomeScreen(void){

        //    Setup display
        tft.initR(INITR_GREENTAB);
        tft.fillScreen(BLUE_COLOR);
        tft.setFont(&OswaldRegular10pt7b);
        tft.setTextSize(1);
        tft.setTextColor(WHITE_COLOR);
        tft.setCursor(15,20);
        tft.println("PROJECT BY");
        tft.println("     NWONU");
        tft.println(" CHUKWUEMEKA");
        tft.println("      SIMON");
        tft.println("2017030182221");
        delay(5000);
}

void setup()
{
        Serial.begin(9600);
        // Init ST7735R chip, green tab
        tft.initR(INITR_144GREENTAB);
        // set fontname
        welcomeScreen();
        tft.fillScreen(BLUE_COLOR);
}


void loop()
{
        readSensorValue();

}




void readSensorValue()
{

        /* This function tend to solve the issue with the short blinking screen
         *  When tft.fillScreen(),
         */

        //Read the current sensor value
        sensorValue = analogRead(mq2sensorPin);
        // Initialize the new and old sensor values


        char newSensorValue[max_length] = {0};
        delay(1000);
        // Construct the new sensor value
        sprintf(newSensorValue, "%lu", sensorValue);

        // Compare the two strings to see if it has changed

       // Display current gas concentation in air
        tft.setFont(&OswaldRegular10pt7b);
        tft.setCursor(15,40);
        tft.println(" Atmospheric");
        tft.println("     LPG Gas ");
        tft.println("  Concentration");
        tft.setCursor(40,150);
        tft.println("ppm");


        if (strcmp (oldSensorValue,newSensorValue) != 0)
        {
                tft.setFont(&OswaldRegular12pt7b);
                // Change the text size
                tft.setTextSize(1);
                tft.setCursor(40,130);
                // Change text color to current background color
                tft.setTextColor(BLUE_COLOR);
                // Print the old value that will overwrite our current text
                tft.print(oldSensorValue);
                //Bring the cursor back to the starting point
                tft.setCursor(40,130);
                //Change the text size
                tft.setTextSize(1);
                // Change the text color to the foreground color
                tft.setTextColor(WHITE_COLOR);
                //Print the new sensor value
                tft.print(newSensorValue);
                // Copy the new value to old value
                strcpy(oldSensorValue,newSensorValue);
                delay(1000);
        }


}
