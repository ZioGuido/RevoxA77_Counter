///////////////////////////////////////////////////////////////////
// ReVox A77 - Digital counter
// Code by Guido Scognamiglio - www.GenuineSoundware.com
// Uses two IR proximity sensors to read take-up reel motor position
// Based on Arduino Leonardo (ProMicro) AT32u4 CPU but can also work with other boards
//
// Last update: 1 November 2025
//

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DSEG7Classic-BoldFont.h"
#include "revox_logo.h"

// This is an OLED 128x32 display module with no reset pin - Uses standard I2C port on pins 2 (SDA) and 3 (SCL) - might need 2.2K pullups
Adafruit_SSD1306 display(128, 32, &Wire, -1);

#define PIN_RESET		4
#define PIN_IR_ENC_A	5
#define PIN_IR_ENC_B	6

int Counter = 0, old_Counter = -1;
int Enc_Aold = 1;
char display_txt[8];

void setup()
{
	// SETUP DISPLAY
	delay(2000); // <--- Some display modules fail to reset at boot time, add this delay so that the CPU starts after the display - A 100uF capacitor between RST and GND pins also helps
	Wire.begin();
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.drawBitmap(0, 0, reVox_logo, 128, 32, SSD1306_WHITE);	// Intro screen with reVox logo
	display.display();
	delay(2000);
	display.setFont(&DSEG7_Classic_Bold_28);
	display.setTextColor(SSD1306_WHITE);

	pinMode(PIN_IR_ENC_A, INPUT);
	pinMode(PIN_IR_ENC_B, INPUT);
	pinMode(PIN_RESET, INPUT_PULLUP);
}

void loop()
{
	// Read encoder and advance counter
	int Enc_A = digitalRead(PIN_IR_ENC_A);
	if (Enc_A > Enc_Aold)
		Counter += digitalRead(PIN_IR_ENC_B) ? 1 : -1;
	Enc_Aold = Enc_A;

	// Counter can also go negative
	if (Counter > 9999 || Counter < -9999)
		Counter = 0;

	// Update display
	if (old_Counter != Counter)
	{
		old_Counter = Counter;
		sprintf(display_txt, "%05d", Counter);
		display.clearDisplay();
		display.setCursor(0, 32);
		display.print(display_txt);
		display.display();
	}

	// Read reset button - given its function, this doesn't need debouncing
	if (digitalRead(PIN_RESET) == LOW)
		Counter = 0;
}
