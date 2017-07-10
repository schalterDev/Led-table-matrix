/* LedTable
 *
 * Written by: Ing. David Hrbaty
 * 
 * 
 * Main code for Dice game
 */
 
#include "diceCommon.h"
#define MATH_ANIMATION 20
boolean diceMath;

int color;
int mathAnimationCounter;
int const animationUpdatesPerSecond = 10;
unsigned long lastAnimationUpdate;

void startDice() {
  diceMath = true;
  randomSeed(analogRead(0));
  clearTablePixels();
  showPixels();
  lastAnimationUpdate = 0;
}

//deckared in other file
//unsigned long prevUpdateTime = 0;
//unsigned long curTime = 0;

void updateDice() {
    
  if (curControl == BTN_START) {
    resetControl();
    diceMath = true;
    Serial.println("Start Dice");
  }
  
  curTime = millis();
  if(curTime - prevUpdateTime > 1000 / UPDATES_PER_SECOND) { 
    if (diceMath) {    
      color = GREEN;
      
      if(mathAnimationCounter < MATH_ANIMATION && 
          curTime - lastAnimationUpdate > 1000 / animationUpdatesPerSecond) {
                  
        if(mathAnimationCounter == MATH_ANIMATION - 1)
          color = WHITE;

        mathAnimationCounter++;
        lastAnimationUpdate = curTime;
        
        switch (random(6)) {
        case 0:
          printDice(diceOne);
          break;
        case 1:
          printDice(diceTwo);
          break;
        case 2:
          printDice(diceThree);
          break;
        case 3:
          printDice(diceFour);
          break;
        case 4:
          printDice(diceFive);
          break;
        case 5:
          printDice(diceSix);
          break;
        }
      } else if( mathAnimationCounter >= MATH_ANIMATION) {
        mathAnimationCounter = 0;
        diceMath = false;
      }

      prevUpdateTime = curTime;
    }
  }
}

void printDice(const boolean dice[][15]){  
  int x,y;
  for (x=0;x<FIELD_HEIGHT;x++){
    for (y=0;y<FIELD_WIDTH;y++){
      if (pgm_read_byte_near ( &dice[y][x]) == 1){
        setTablePixel(y,x, color);
        //Serial.print(pgm_read_byte_near ( &dice[x][y]) == 1);
        //Serial.print(" ");
      } else {
        setTablePixel(y,x, 0x000000);
        //Serial.print(dice[y][x]);
        //Serial.print(" ");
      }
    }
  }
  
  showPixels();
}

