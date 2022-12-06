#include <Arduino.h>
#include <arduino-timer.h>
#include "ClueDisplay.h"
#include "Common.h"
#include "Point.h"
#include "GameBoard.h"
#include "Snake.h"
#include "ImageLoader.h"
#include "ScoreBoard.h"

#define CLUE_LEFT_PIN 5
#define CLUE_RIGHT_PIN 11

#define ARCADA_NEOPIXEL_PIN 18
#define ARCADA_NEOPIXEL_NUM 1

#define ARCADA_AUDIO_OUT 46 // PWM output
#define ARCADA_USE_JSON

auto timer = timer_create_default(); // create a timer with default settings
ClueDisplay display;
Snake snake;
ScoreBoard scoreBoard({0, 0}, 240, 40);
GameBoard gameBoard({0, 40}, 240, 200, snake, scoreBoard, CLUE_LEFT_PIN, CLUE_RIGHT_PIN);
ImageLoader imageLoader;

volatile uint16_t milliseconds;
volatile bool update = false;
volatile uint16_t frameMils = 50;

bool frameTimerCallback(void*) {
  if (!update)
  {
    if (milliseconds == 0) {
        update = true;
        milliseconds = frameMils;
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  // pulse the LED
    } else {
        milliseconds--;
    }
  }
  return true;
}

void setup()
{
  
  Serial.begin(115200);
  
  pinMode(CLUE_LEFT_PIN, INPUT_PULLUP);
  pinMode(CLUE_RIGHT_PIN, INPUT_PULLUP);

  display.BeginDisplay();

  imageLoader.Setup(display.GetDisplay());
  imageLoader.DisplayImage("/images/snake.bmp", { CLUE_LEFT_PIN, CLUE_RIGHT_PIN });

  display.GetDisplay()->fillScreen(0);

  gameBoard.Initialize(display.GetDisplay());
  
  timer.every(1, frameTimerCallback);
}

void loop()
{
  timer.tick();

  if (update)
  {
    display.GetDisplay()->startWrite();
    gameBoard.Update();
    display.GetDisplay()->endWrite();

    update = false;
  }
}