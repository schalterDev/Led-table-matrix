#include "buzzer.h"

void startBuzzer() {
  gameOver = false;
  clearField();
  resetControl();
}

void updateBuzzer() {
  curTime = millis();

  if(!gameOver) {    
    //Check for button input
    if(curControl == BTN_LEFT) {
      printBuzzer(FRONTLEFT);
      buzzerPressed();
    } else if(curControl == BTN_RIGHT) {
      printBuzzer(FRONTRIGHT);
      buzzerPressed();
    } else if(curControl == BTN_UP) {
      printBuzzer(BACKRIGHT);
      buzzerPressed();
    } else if(curControl == BTN_DOWN) {
      printBuzzer(BACKLEFT);
      buzzerPressed();
    }
  } else if(gameOver && curTime - timeGameOver > timeToResetBuzzer) {
    //After specific time table can be reseted
    if(curControl != BTN_NONE) {
      startBuzzer();
    }
  }
}

void buzzerPressed() {
  gameOver = true;
  timeGameOver = curTime;
  resetControl();    
}

void printBuzzer(const boolean buzzer[][15]){  
  color = colorLib[random(4)];
  
  int x,y;
  for (x=0;x<FIELD_HEIGHT;x++){
    for (y=0;y<FIELD_WIDTH;y++){
      if (pgm_read_byte_near ( &buzzer[y][x]) == 1){
        setTablePixel(y,x, color);
      } else {
        setTablePixel(y,x, 0x000000);
      }
    }
  }
  
  showPixels();
}
