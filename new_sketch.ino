// 1) allWhite, delay 1 second (no one is touching)

// 2) 1-4 ranges of pulse

// player 1: case 1-4: delay 800, 500, 300, 10
// player 2: case 1-4: offset start time

#define USE_ARDUINO_INTERRUPTS true

#include <PulseSensorPlayground.h> // TwoPulseSensor library
#include <FastLED.h>               // FastLED Blink & Color palette library

#define NUM_LEDS 240
#define DATA_PIN 3
#define CLOCK_PIN 240
#define BRIGHTNESS 20

CRGB leds[NUM_LEDS];

const int OUTPUT_TYPE = SERIAL_PLOTTER;

int PULSE_INPUT0 = A0;
// int val0;

const int PULSE_INPUT1 = A1;
// int val1;

int Threshold = 550;

const int PULSE_SENSOR_COUNT = 2;

PulseSensorPlayground pulseSensor;

bool startPhase1Enabled = false;
bool startPhase2Enabled = false;

bool player1On = false;
bool player2On = false;

const long startPhase1Interval = 3000;
unsigned long previousStartPhase1Millis = 0;

const long startPhase2Interval = 3000;
unsigned long previousStartPhase2Millis = 0;

const long player1Interval = 1000;
unsigned long previousPlayer1Millis = 0;

const long player2Interval = 1000;
unsigned long previousPlayer2Millis = 0;

const int numReadings = 10;

int readings1[numReadings];  // the readings from the analog input
int readIndex1 = 0;          // the index of the current reading
int total1 = 0;              // the running total
int average1 = 0;            // the average

int readings2[numReadings];  // the readings from the analog input
int readIndex2 = 0;          // the index of the current reading
int total2 = 0;              // the running total
int average2 = 0;            // the average


// const long player2OffsetInterval = 200;
// unsigned long previousPlayer2OffsetMillis = 0;

void allWhite()
{
    for (int x = 0; x < NUM_LEDS; x++)
    {
        leds[x] = CRGB::White;
    }
}

void startPhase()
{
    allWhite();
}

void startPhaseTimer1()
{
  
    if (startPhase1Enabled)
    {
        Serial.println("startPhase1Enabled");
        startPhase1Enabled = true;
        startPhase();
    }

    unsigned long currentMillis = millis();
    if (currentMillis - previousStartPhase1Millis >= startPhase1Interval)
    {
        // save the last time you blinked the LED
        previousStartPhase1Millis = currentMillis;
        startPhase1Enabled = false;
    }
}

void startPhaseTimer2()
{
    if (startPhase2Enabled)
    {
        Serial.println("startPhase2Enabled");
        startPhase2Enabled = true;
        startPhase();
    }

    unsigned long currentMillis = millis();
    if (currentMillis - previousStartPhase2Millis >= startPhase2Interval)
    {
        // save the last time you blinked the LED
        previousStartPhase2Millis = currentMillis;
        startPhase2Enabled = false;
    }
}

void player1Blink(int val){
    // Serial.println("player1Blink");
    // Serial.println(player1On);
    CRGB color1 = CRGB::Cyan;
    CRGB color2 = CRGB::Blue;

    if (val < 2){
        color1 = CRGB::White;
        color2 = CRGB::White;
    }

    if (player1On) {
        player1On = false;
        color1 = CRGB::Black;
        color2 = CRGB::Black;
    } 
    else {
        player1On = true;
    }
    
    switch (val){
    case 0:
    case 1:
        fill_solid(leds + 0, 4, color1);
        fill_solid(leds + 15, 4, color1);
        fill_solid(leds + 30, 4, color1);
        fill_solid(leds + 45, 4, color1);
        fill_solid(leds + 47, 4, color1);

        fill_solid(leds + 8, 3, color1);
        fill_solid(leds + 23, 3, color1);
        fill_solid(leds + 38, 3, color1);
        fill_solid(leds + 53, 3, color1);

        fill_solid(leds + 71, 4, color1);
        fill_solid(leds + 86, 4, color1);
        fill_solid(leds + 101, 4, color1);
        fill_solid(leds + 116, 4, color1);

        fill_solid(leds + 63, 4, color1);
        fill_solid(leds + 78, 4, color1);
        fill_solid(leds + 93, 4, color1);
        fill_solid(leds + 108, 4, color1);

        fill_solid(leds + 103, 1, color1);
        fill_solid(leds + 81, 0, color1);

        fill_solid(leds + 111, 0, color1);

        fill_solid(leds + 120, 4, color1);
        fill_solid(leds + 135, 4, color1);
        fill_solid(leds + 150, 4, color1);
        fill_solid(leds + 165, 4, color1);

        fill_solid(leds + 127, 4, color1);
        fill_solid(leds + 142, 4, color1);
        fill_solid(leds + 157, 4, color1);
        fill_solid(leds + 172, 4, color1);

        fill_solid(leds + 191, 4, color1);
        fill_solid(leds + 206, 4, color1);
        fill_solid(leds + 220, 5, color1);
        fill_solid(leds + 236, 4, color1);

        fill_solid(leds + 184, 4, color1);
        fill_solid(leds + 199, 4, color1);
        fill_solid(leds + 214, 4, color1);
        fill_solid(leds + 229, 4, color1);
        fill_solid(leds + 230, 2, color1);
        FastLED.show();
        break;

    case 2:
        fill_solid(leds + 0, 4, color1);
        fill_solid(leds + 15, 4, color1);
        fill_solid(leds + 30, 4, color1);
        fill_solid(leds + 45, 4, color1);

        fill_solid(leds + 8, 3, color1);
        fill_solid(leds + 23, 3, color1);
        fill_solid(leds + 38, 3, color1);
        fill_solid(leds + 53, 3, color1);

        fill_solid(leds + 71, 0, color1);
        fill_solid(leds + 72, 3, color1);
        fill_solid(leds + 86, 4, color1);
        fill_solid(leds + 88, 2, color1);
        fill_solid(leds + 101, 2, color1);
        fill_solid(leds + 116, 1, color1);
        fill_solid(leds + 117, 3, color1);

        fill_solid(leds + 63, 5, color1);
        fill_solid(leds + 78, 1, color1);
        fill_solid(leds + 80, 2, color1);
        fill_solid(leds + 93, 3, color1);
        fill_solid(leds + 96, 1, color1);
        fill_solid(leds + 108, 2, color1);
        fill_solid(leds + 110, 2, color1);

        fill_solid(leds + 120, 4, color1);
        fill_solid(leds + 135, 4, color1);
        fill_solid(leds + 150, 4, color1);
        fill_solid(leds + 165, 4, color1);

        fill_solid(leds + 127, 4, color1);
        fill_solid(leds + 142, 4, color1);
        fill_solid(leds + 157, 4, color1);
        fill_solid(leds + 172, 4, color1);
        fill_solid(leds + 145, 0, color1);
        fill_solid(leds + 160, 0, color1);
        fill_solid(leds + 174, 1, color1);

        fill_solid(leds + 184, 4, color1);
        fill_solid(leds + 199, 4, color1);
        fill_solid(leds + 214, 4, color1);
        fill_solid(leds + 229, 4, color1);

        fill_solid(leds + 191, 4, color1);
        fill_solid(leds + 206, 4, color1);
        fill_solid(leds + 221, 4, color1);
        fill_solid(leds + 236, 4, color1);
        FastLED.show();
        break;

        case 3:
        fill_solid(leds + 0, 4, color1);
        fill_solid(leds + 15, 4, color1);
        fill_solid(leds + 30, 4, color1);
        fill_solid(leds + 45, 4, color1);

        fill_solid(leds + 8, 3, color1);
        fill_solid(leds + 23, 3, color1);
        fill_solid(leds + 38, 3, color1);
        fill_solid(leds + 53, 3, color1);

        fill_solid(leds + 71, 0, color1);
        fill_solid(leds + 72, 3, color1);
        fill_solid(leds + 86, 4, color1);
        fill_solid(leds + 88, 2, color1);
        fill_solid(leds + 101, 2, color1);
        fill_solid(leds + 116, 1, color1);
        fill_solid(leds + 117, 3, color1);

        fill_solid(leds + 63, 5, color1);
        fill_solid(leds + 78, 1, color1);
        fill_solid(leds + 80, 2, color1);
        fill_solid(leds + 93, 3, color1);
        fill_solid(leds + 96, 1, color1);
        fill_solid(leds + 108, 2, color1);
        fill_solid(leds + 110, 2, color1);

        fill_solid(leds + 120, 4, color1);
        fill_solid(leds + 135, 4, color1);
        fill_solid(leds + 150, 4, color1);
        fill_solid(leds + 165, 4, color1);

        fill_solid(leds + 127, 4, color1);
        fill_solid(leds + 142, 4, color1);
        fill_solid(leds + 157, 4, color1);
        fill_solid(leds + 172, 4, color1);
        fill_solid(leds + 145, 0, color1);
        fill_solid(leds + 160, 0, color1);
        fill_solid(leds + 174, 1, color1);

        fill_solid(leds + 184, 4, color1);
        fill_solid(leds + 199, 4, color1);
        fill_solid(leds + 214, 4, color1);
        fill_solid(leds + 229, 4, color1);

        fill_solid(leds + 191, 4, color1);
        fill_solid(leds + 206, 4, color1);
        fill_solid(leds + 221, 4, color1);
        fill_solid(leds + 236, 4, color1);
        FastLED.show();
        break;

    case 4:
        fill_solid(leds + 0, 4, color2);
        fill_solid(leds + 15, 4, color2);
        fill_solid(leds + 30, 4, color2);
        fill_solid(leds + 45, 4, color2);

        fill_solid(leds + 8, 3, color2);
        fill_solid(leds + 23, 3, color2);
        fill_solid(leds + 38, 3, color2);
        fill_solid(leds + 53, 3, color2);

        fill_solid(leds + 63, 4, color2);
        fill_solid(leds + 78, 4, color2);
        fill_solid(leds + 80, 2, color2);
        fill_solid(leds + 93, 4, color2);
        fill_solid(leds + 108, 4, color2);

        fill_solid(leds + 71, 4, color2);
        fill_solid(leds + 86, 4, color2);
        fill_solid(leds + 101, 4, color2);
        fill_solid(leds + 116, 4, color2);

        fill_solid(leds + 120, 4, color2);
        fill_solid(leds + 135, 4, color2);
        fill_solid(leds + 150, 4, color2);
        fill_solid(leds + 165, 4, color2);

        fill_solid(leds + 127, 4, color2);
        fill_solid(leds + 142, 4, color2);
        fill_solid(leds + 157, 4, color2);
        fill_solid(leds + 172, 4, color2);
        fill_solid(leds + 145, 0, color2);
        fill_solid(leds + 160, 0, color2);

        fill_solid(leds + 184, 4, color2);
        fill_solid(leds + 199, 4, color2);
        fill_solid(leds + 214, 4, color2);
        fill_solid(leds + 229, 4, color2);

        fill_solid(leds + 191, 4, color2);
        fill_solid(leds + 206, 4, color2);
        fill_solid(leds + 221, 4, color2);
        fill_solid(leds + 236, 4, color2);
        FastLED.show();
        break;

    case 5:
        fill_solid(leds + 0, 4, color2);
        fill_solid(leds + 15, 4, color2);
        fill_solid(leds + 30, 4, color2);
        fill_solid(leds + 45, 4, color2);

        fill_solid(leds + 8, 3, color2);
        fill_solid(leds + 23, 3, color2);
        fill_solid(leds + 38, 3, color2);
        fill_solid(leds + 53, 3, color2);

        fill_solid(leds + 63, 4, color2);
        fill_solid(leds + 78, 4, color2);
        fill_solid(leds + 80, 2, color2);
        fill_solid(leds + 93, 4, color2);
        fill_solid(leds + 108, 4, color2);

        fill_solid(leds + 71, 4, color2);
        fill_solid(leds + 86, 4, color2);
        fill_solid(leds + 101, 4, color2);
        fill_solid(leds + 116, 4, color2);

        fill_solid(leds + 120, 4, color2);
        fill_solid(leds + 135, 4, color2);
        fill_solid(leds + 150, 4, color2);
        fill_solid(leds + 165, 4, color2);

        fill_solid(leds + 127, 4, color2);
        fill_solid(leds + 142, 4, color2);
        fill_solid(leds + 157, 4, color2);
        fill_solid(leds + 172, 4, color2);
        fill_solid(leds + 145, 0, color2);
        fill_solid(leds + 160, 0, color2);

        fill_solid(leds + 184, 4, color2);
        fill_solid(leds + 199, 4, color2);
        fill_solid(leds + 214, 4, color2);
        fill_solid(leds + 229, 4, color2);

        fill_solid(leds + 191, 4, color2);
        fill_solid(leds + 206, 4, color2);
        fill_solid(leds + 221, 4, color2);
        fill_solid(leds + 236, 4, color2);
        FastLED.show();
        break;

    }
}

void player2Blink(int val){
    // Serial.println("player2Blink");
    // Serial.println(player2On);
    CRGB color1 = CRGB::Magenta;
    CRGB color2 = CRGB::Red;
     if (val < 2) {
        color1 = CRGB::White;
        color2 = CRGB::White;
    }
    if (player2On) {
        player2On = false;
        color1 = CRGB::Black;
        color2 = CRGB::Black;
    
    } else {
        player2On = true;
    }
    switch (val)
{
    case 0:      
    case 1:
        fill_solid(leds + 4, 4, color1);
        fill_solid(leds + 19, 4, color1);
        fill_solid(leds + 34, 4, color1);
        fill_solid(leds + 49, 4, color1);

        fill_solid(leds + 11, 4, color1);
        fill_solid(leds + 26, 4, color1);
        fill_solid(leds + 41, 4, color1);
        fill_solid(leds + 56, 4, color1);

        fill_solid(leds + 67, 4, color1);
        fill_solid(leds + 82, 4, color1);
        fill_solid(leds + 97, 4, color1);
        fill_solid(leds + 112, 4, color1);

        fill_solid(leds + 60, 3, color1);
        fill_solid(leds + 75, 3, color1);
        fill_solid(leds + 90, 3, color1);
        fill_solid(leds + 105, 3, color1);

        fill_solid(leds + 124, 3, color1);
        fill_solid(leds + 139, 3, color1);
        fill_solid(leds + 154, 3, color1);
        fill_solid(leds + 169, 3, color1);

        fill_solid(leds + 131, 4, color1);
        fill_solid(leds + 146, 4, color1);
        fill_solid(leds + 161, 4, color1);
        fill_solid(leds + 176, 4, color1);

        fill_solid(leds + 186, 2, color1);
        fill_solid(leds + 203, 3, color1);
        fill_solid(leds + 218, 3, color1);
        fill_solid(leds + 233, 3, color1);

        fill_solid(leds + 180, 11, color1);
        fill_solid(leds + 195, 4, color1);
        fill_solid(leds + 146, 0, color1);
        fill_solid(leds + 211, 2, color1);
        fill_solid(leds + 210, 4, color1);
        fill_solid(leds + 225, 4, color1);
        FastLED.show();
        break;

    case 2:
        fill_solid(leds + 4, 4, color1);
        fill_solid(leds + 19, 4, color1);
        fill_solid(leds + 34, 4, color1);
        fill_solid(leds + 35, 2, color1);
        fill_solid(leds + 49, 4, color1);

        fill_solid(leds + 11, 4, color1);
        fill_solid(leds + 26, 4, color1);
        fill_solid(leds + 41, 4, color1);
        fill_solid(leds + 56, 4, color1);

        fill_solid(leds + 60, 3, color1);
        fill_solid(leds + 75, 4, color1);
        fill_solid(leds + 90, 4, color1);
        fill_solid(leds + 103, 4, color1);
        fill_solid(leds + 107, 4, color1);

        fill_solid(leds + 67, 5, color1);
        fill_solid(leds + 82, 4, color1);
        fill_solid(leds + 97, 4, color1);
        fill_solid(leds + 112, 2, color1);
        fill_solid(leds + 114, 2, color1);

        fill_solid(leds + 124, 3, color1);
        fill_solid(leds + 139, 3, color1);
        fill_solid(leds + 154, 3, color1);
        fill_solid(leds + 169, 3, color1);

        fill_solid(leds + 131, 4, color1);
        fill_solid(leds + 146, 4, color1);
        fill_solid(leds + 161, 4, color1);
        fill_solid(leds + 176, 4, color1);

        fill_solid(leds + 180, 4, color1);
        fill_solid(leds + 195, 4, color1);
        fill_solid(leds + 210, 4, color1);
        fill_solid(leds + 225, 4, color1);

        fill_solid(leds + 188, 4, color1);
        fill_solid(leds + 203, 3, color1);
        fill_solid(leds + 218, 3, color1);
        fill_solid(leds + 233, 3, color1);
        FastLED.show();
        break;

    case 3:
        fill_solid(leds + 4, 4, color1);
        fill_solid(leds + 19, 4, color1);
        fill_solid(leds + 34, 4, color1);
        fill_solid(leds + 35, 2, color1);
        fill_solid(leds + 49, 4, color1);

        fill_solid(leds + 11, 4, color1);
        fill_solid(leds + 26, 4, color1);
        fill_solid(leds + 41, 4, color1);
        fill_solid(leds + 56, 4, color1);

        fill_solid(leds + 60, 3, color1);
        fill_solid(leds + 75, 4, color1);
        fill_solid(leds + 90, 4, color1);
        fill_solid(leds + 103, 4, color1);
        fill_solid(leds + 107, 4, color1);

        fill_solid(leds + 67, 5, color1);
        fill_solid(leds + 82, 4, color1);
        fill_solid(leds + 97, 4, color1);
        fill_solid(leds + 112, 2, color1);
        fill_solid(leds + 114, 2, color1);

        fill_solid(leds + 124, 3, color1);
        fill_solid(leds + 139, 3, color1);
        fill_solid(leds + 154, 3, color1);
        fill_solid(leds + 169, 3, color1);

        fill_solid(leds + 131, 4, color1);
        fill_solid(leds + 146, 4, color1);
        fill_solid(leds + 161, 4, color1);
        fill_solid(leds + 176, 4, color1);

        fill_solid(leds + 180, 4, color1);
        fill_solid(leds + 195, 4, color1);
        fill_solid(leds + 210, 4, color1);
        fill_solid(leds + 225, 4, color1);

        fill_solid(leds + 188, 4, color1);
        fill_solid(leds + 203, 3, color1);
        fill_solid(leds + 218, 3, color1);
        fill_solid(leds + 233, 3, color1);
        FastLED.show();
        break;

    case 4:
        fill_solid(leds + 4, 4, color2);
        fill_solid(leds + 19, 4, color2);
        fill_solid(leds + 34, 4, color2);
        fill_solid(leds + 49, 4, color2);

        fill_solid(leds + 11, 4, color2);
        fill_solid(leds + 26, 4, color2);
        fill_solid(leds + 41, 4, color2);
        fill_solid(leds + 56, 4, color2);

        fill_solid(leds + 60, 3, color2);
        fill_solid(leds + 75, 3, color2);
        fill_solid(leds + 90, 3, color2);
        fill_solid(leds + 105, 3, color2);

        fill_solid(leds + 67, 4, color2);
        fill_solid(leds + 82, 4, color2);
        // fill_solid(leds + 87, 4, color2);
        fill_solid(leds + 97, 4, color2);
        fill_solid(leds + 112, 4, color2);

        fill_solid(leds + 70, 0, color2);
        fill_solid(leds + 84, 1, color2);

        fill_solid(leds + 124, 3, color2);
        fill_solid(leds + 139, 3, color2);
        fill_solid(leds + 154, 3, color2);
        fill_solid(leds + 169, 3, color2);

        fill_solid(leds + 131, 4, color2);
        fill_solid(leds + 146, 4, color2);
        fill_solid(leds + 161, 4, color2);
        fill_solid(leds + 176, 4, color2);

        fill_solid(leds + 180, 4, color2);
        fill_solid(leds + 195, 4, color2);
        fill_solid(leds + 210, 4, color2);
        fill_solid(leds + 225, 4, color2);

        fill_solid(leds + 188, 3, color2);
        fill_solid(leds + 203, 3, color2);
        fill_solid(leds + 218, 3, color2);

        fill_solid(leds + 205, 0, color2);
        fill_solid(leds + 233, 3, color2);
        FastLED.show();
        break;


    case 5:
        fill_solid(leds + 4, 4, color2);
        fill_solid(leds + 19, 4, color2);
        fill_solid(leds + 34, 4, color2);
        fill_solid(leds + 49, 4, color2);
        fill_solid(leds + 67, 4, color2);
        fill_solid(leds + 82, 4, color2);
        fill_solid(leds + 97, 4, color2);
        fill_solid(leds + 112, 4, color2);
        fill_solid(leds + 180, 4, color2);
        fill_solid(leds + 195, 4, color2);
        fill_solid(leds + 210, 4, color2);
        fill_solid(leds + 225, 4, color2);
        fill_solid(leds + 180, 4, color2);
        fill_solid(leds + 195, 4, color2);
        fill_solid(leds + 210, 4, color2);
        fill_solid(leds + 225, 4, color2);
        fill_solid(leds + 131, 4, color2);
        fill_solid(leds + 146, 4, color2);
        fill_solid(leds + 161, 4, color2);
        fill_solid(leds + 176, 4, color2);
        fill_solid(leds + 11, 4, color2);
        fill_solid(leds + 26, 4, color2);
        fill_solid(leds + 41, 4, color2);
        fill_solid(leds + 56, 4, color2);
        fill_solid(leds + 60, 3, color2);
        fill_solid(leds + 75, 3, color2);
        fill_solid(leds + 90, 3, color2);
        fill_solid(leds + 105, 3, color2);
        fill_solid(leds + 124, 3, color2);
        fill_solid(leds + 139, 3, color2);
        fill_solid(leds + 154, 3, color2);
        fill_solid(leds + 169, 3, color2);
        fill_solid(leds + 188, 3, color2);
        fill_solid(leds + 203, 3, color2);
        fill_solid(leds + 218, 3, color2);
        fill_solid(leds + 233, 3, color2);
        FastLED.show();
        break;
    }
}


void player1Timer(int val){
  long interval = player1Interval;
    if (val == 1) {
        interval = player1Interval;
    } else if (val == 2) {
        interval = 500;
    } else if (val == 3) {
        interval = 500;
    } else if (val == 4) {
        interval = 200;
    } else if (val == 5) {
        interval = 50;
    }

    unsigned long currentMillis = millis();
    if (currentMillis - previousPlayer1Millis >= interval)
    {
        // save the last time you blinked the LED
        previousPlayer1Millis = currentMillis;
        player1Blink(val);
    }
}

void player2Timer(int val){
  long interval = player2Interval;
    if (val == 1) {
        interval = player2Interval;
    } else if (val == 2) {
        interval = 500;
    } else if (val == 3) {
        interval = 500;
    } else if (val == 4) {
        interval = 200;
    } else if (val == 5) {
        interval = 50;
    }

    unsigned long currentMillis = millis();

    if (currentMillis - previousPlayer2Millis >= interval)
    {
        // save the last time you blinked the LED
        previousPlayer2Millis = currentMillis;
        player2Blink(val);
    }
}

void setup(){
    Serial.begin(115200);

    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    pulseSensor.analogInput(PULSE_INPUT0, INPUT);
    pulseSensor.analogInput(PULSE_INPUT1, INPUT);
    pulseSensor.blinkOnPulse(DATA_PIN);
    pulseSensor.setThreshold(Threshold);

    pulseSensor.setSerial(Serial);
    pulseSensor.setOutputType(OUTPUT_TYPE);

    if (pulseSensor.begin()){
        Serial.println("We created a pulseSensor Object !"); // This prints one time at Arduino power-up,  or on Arduino reset.
    }

      // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings1[thisReading] = 0;
  }
    
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings2[thisReading] = 0;
  }

  FastLED.clear();
}


void loop()
{
    // Player1 mapping
    int val0 = analogRead(PULSE_INPUT0);

    // int mapping_value = map(val0, 0, 1023, 4, 0);     // maps your value to cases
    // int mapping_sensor = map(val0, 0, 1023, 1023, 0); // reverses the sensor data

    total1 = total1 - readings1[readIndex1];
    // read from the sensor:
   readings1[readIndex1] = val0;
  // add the reading to the total:
   total1 = total1 + readings1[readIndex1];
  // advance to the next position in the array:
   readIndex1 = readIndex1 + 1;

    // if we're at the end of the array...
  if (readIndex1 >= numReadings) {
    // ...wrap around to the beginning:
    readIndex1 = 0;
    
  }
  average1 = total1 / numReadings;
  int mapping_value = map(average1, 0, 1023, 5, 0); // reverses the sensor data

    mapping_value = constrain(mapping_value, 0, 5);

    Serial.print("Player1: ");
    Serial.println(mapping_value);

    // Player2 mapping
    int val1 = analogRead(PULSE_INPUT1);

    // int mapping_value1 = map(val1, 0, 1023, 4, 0);
    // int mapping_sensor1 = map(val1, 0, 1023, 1023, 0); // reverses the sensor data

  total2 = total2 - readings2[readIndex2];
    // read from the sensor:
   readings2[readIndex2] = val1;
  // add the reading to the total:
   total2 = total2 + readings2[readIndex2];
  // advance to the next position in the array:
   readIndex2 = readIndex2 + 1;
  
    // if we're at the end of the array...
  if (readIndex2 >= numReadings) {
    // ...wrap around to the beginning:
    readIndex2 = 0;
  }
  average2 = total2 / numReadings;
  int mapping_value1 = map(average2, 0, 1023, 5, 0); // reverses the sensor data

    mapping_value1 = constrain(mapping_value1, 0, 5);

    Serial.print("Player2: ");
    Serial.println(mapping_value1);

    // if (mapping_value == 0 && mapping_value1 == 0){
    //   startPhaseTimer
    // }

    // mapping_value = 0;
    // mapping_value1 = 0;

    switch (mapping_value)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        player1Timer(mapping_value);
        break;
    }

    switch (mapping_value1)
    {
    // case 0:
    // case 1:
    // case 2:
    // case 3:
    // case 4:
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        player2Timer(mapping_value1);
        break;
    }
}