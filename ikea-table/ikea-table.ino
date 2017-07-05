#include "input.h"
#include "output.h"

unsigned long prevUpdateTime;
unsigned long curTime;
boolean gameOver;

/*
 * all pins are declared here
 * Buttons: have to be connected to gnd and a digital I/O pin
 */
#define FAST_LED_DATA_PIN  5
const int buttonStart = 6;
const int buttonLeft = 7;
const int buttonRight = 8;
const int buttonEnd = 9;
const int beeper = 10;
const int brightnessPot = A0;

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
    case 1:
      startRainbowPalette();
      break;
    case 2:
      startColorPalette();
      break;
    case 3:
      startStars();  
      break;
    case 4:
      //startVUmeter();
      break;
    case 5:
      startDice();
      break;    
    case 6:
      startTetris();
      break;   
    case 7:
      startSnake();
      break; 
    case 8:
      startPong();
      break;  
    case 9:       
      startBricks();
      break;   
    case 10:
      //startLeds();
      break; 
    case 11:
      //startBuzzer();
      break;   
    case 12:
      startFtw();
      break;
    }        
  }
}

void updateSelection() {
  switch(selection) {
    case 1:
      updateRainbowPalette();
      break;
    case 2:
      updateColorPalette();
      break;
    case 3:
      updateStars();
      break;
    case 4:
      //updateVUmeter();
      break;
    case 5:
      updateDice();
      break;    
    case 6:
      updateTetris();
      break;   
    case 7:
      updateSnake();
      break; 
    case 8:
      updatePong();
      break;  
    case 9:       
      updateBricks();
      break;   
    case 10:
      //updateLeds();
      break; 
    case 11:
      //updateBuzzer();
      break;    
    case 12:
      updateFtw();
      break;       
  }
}

