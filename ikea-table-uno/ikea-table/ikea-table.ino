#include "input.h"
#include "output.h"

unsigned long prevUpdateTime;
unsigned long curTime;
boolean gameOver;
boolean fadedOut;

//Different programs
#define RAINBOW 1
#define COLOR 2
#define STARS 3
#define DICE 4
#define TETRIS 5
#define SNAKE 6
#define PONG 7
#define SIMPLECOLOR 8

const uint8_t MAX_SELECTION = 8;

/*
 * all pins are declared here
 * Buttons: have to be connected to gnd and a digital I/O pin
 */
#define FAST_LED_DATA_PIN  5
const int buttonFrontRight = 4;
const int buttonFrontLeft = 6;
const int buttonLeftFront = 7;
const int buttonLeftBack = 8;
const int buttonRightBack = 9;
const int buttonRightFront = 10;
const int buttonDown = 11;
const int beeper = 10;
const int brightnessPot = A0;

const int buttons[] = {buttonFrontLeft, buttonFrontRight, buttonRightFront, buttonLeftFront, buttonLeftBack,
              buttonRightBack};
const int buttonsSize = 6;

/*
 * Some defines used by the FAST_LED library
 */
#define FAST_LED_CHIPSET WS2812B

uint8_t brightness = 255;
uint8_t UPDATES_PER_SECOND = 30;

void setup() {
  //Init input
  initInput();

  //Init output
  pinMode(beeper, OUTPUT);
  initPixels();
  showPixels();

  randomSeed(millis() * analogRead(3));
}

void loop() {
  int brightnessBefore = brightness;
  
  readInput(); //input is saved in curControls[CONTROL_COUNT] and curControl (first entry from curControls
  //selectionChanged and selection maybe changed

  //Update brigthness
  //use a trashhold of 5 to minimice flakering
  if(brightness - brightnessBefore > 5 || brightness - brightnessBefore < -5) {
    FastLED.setBrightness(  brightness );
    showPixels();
  } else {
    brightness = brightnessBefore;
  }

  if(selectionChanged) {
    changeSelection();
  } else {
    updateSelection();
  }
}

void changeSelection() {
  //wait for start button to be pressed
  if(curControl == BTN_START) {
    startSelection = true;
    resetControl();
  }
  
  if(startSelection) {
    selectionChanged = false;
    startSelection = false;

    switch(selection) {
    case RAINBOW:
      startRainbowPalette();
      break;
    case COLOR:
      startColorPalette();
      break;
    case STARS:
      startStars();  
      break;
    case DICE:
      startDice();
      break;    
    case TETRIS:
      startTetris();
      break;   
    case SNAKE:
      startSnake();
      break; 
    case PONG:
      startPong();
      break;       
    case SIMPLECOLOR:
      startColor();
      break;
    }        
  }
}

void updateSelection() {
  switch(selection) {
    case RAINBOW:
      updateRainbowPalette();
      break;
    case COLOR:
      updateColorPalette();
      break;
    case STARS:
      updateStars();
      break;
    case DICE:
      updateDice();
      break;    
    case TETRIS:
      updateTetris();
      break;   
    case SNAKE:
      updateSnake();
      break; 
    case PONG:
      updatePong();
      break; 
    case SIMPLECOLOR:
      updateColor();
      break;  
  }
}

