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
#define VU 4
#define DICE 5
#define TETRIS 6
#define SNAKE 7
#define PONG 8
#define BRICKS 9
#define LED 10
#define BUZZER 11
#define FTW 12

/*
 * all pins are declared here
 * Buttons: have to be connected to gnd and a digital I/O pin
 */
#define FAST_LED_DATA_PIN  5
const int buttonFrontLeft;
const int buttonFrontRight;
const int buttonRightFront;
const int buttonLeftFront;
const int buttonLeftBack;
const int buttonRightBack;
const int buttonDown;
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
  Serial.begin(230400);

  //Init input
  initInput();

  //Init output
  pinMode(beeper, OUTPUT);
  initPixels();
  showPixels();

  randomSeed(millis() * analogRead(3));
}

void loop() {
  readInput(); //input is saved in curControls[CONTROL_COUNT] and curControl (first entry from curControls
  //selectionChanged and selection maybe changed

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
    Serial.println("Start selection");
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
    case VU:
      //startVUmeter();
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
    case BRICKS:       
      startBricks();
      break;   
    case LED:
      //startLeds();
      break; 
    case BUZZER:
      //startBuzzer();
      break;   
    case FTW:
      startFtw();
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
    case VU:
      //updateVUmeter();
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
    case BRICKS:       
      updateBricks();
      break;   
    case LED:
      //updateLeds();
      break; 
    case BUZZER:
      //updateBuzzer();
      break;    
    case FTW:
      updateFtw();
      break;       
  }
}
