/* LedTable
 *
 * Written by: Martin Schalter
 * 
 * Snake game
 */

#include "snake.h"

void startSnake(){
  //Snake start position and direction & initialise variables
  curLength = 3;
  xs[0]=3; xs[1]=2; xs[2]=1;
  ys[0]=FIELD_HEIGHT/2; ys[1]=FIELD_HEIGHT/2; ys[2]=FIELD_HEIGHT/2;
  dir = DIR_RIGHT;
  score = 0;
  
  //Generate random apple position
  ax = random(FIELD_WIDTH-1);
  ay = random(FIELD_HEIGHT-1);
  
  gameOver = false;
}

//unsigned long prevUpdateTime = 0;
//unsigned long curTime;

void updateSnake(){
  curTime = millis();
  
  if(!gameOver && (curTime - prevUpdateTime) > 1000 / (UPDATES_PER_SECOND / SNAKE_FRAMES_PER_UPDATE)) {   
    if (curControl != BTN_NONE){
      setDirection();
    }
    
    //Check self-collision with snake
    int i=curLength-1;
    while (i>=2){
      if (collide(xs[0], xs[i], ys[0], ys[i], SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH)){
        die();
      }
      i = i-1;
    }

    //Check collision of snake head with apple
    if (collide(xs[0], ax, ys[0], ay, SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH)){
      //Increase score and snake length;
      score = score +1;
      curLength = curLength +1;
      //Add snake segment with temporary position of new segments
      xs[curLength-1] = 255;
      ys[curLength-1] = 255;
      
      //Generate new apple position
      ax = random(FIELD_WIDTH-1);
      ay = random(FIELD_HEIGHT-1);
      //Generate apple color
      acolor = colorLib[random(1)];

      int i=curLength-1;
      for(int i=0; i<curLength; i++) {
        if (collide(ax, xs[i], ay, ys[i], SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH, SNAKEWIDTH)){
           ax = random(FIELD_WIDTH-1);
           ay = random(FIELD_HEIGHT-1);
           i=0;
        }
      }
    }
    
    //Shift snake position array by one
    i = curLength-1;
    while (i>=1){
      xs[i] = xs[i-1];
      ys[i] = ys[i-1];
      i = i-1;
    }
    //Determine new position of head of snake
    if (dir == DIR_RIGHT){
      xs[0] = xs[0] + SNAKEWIDTH;
    } 
    else if (dir == DIR_LEFT){
      xs[0] = xs[0] - SNAKEWIDTH;
    } 
    else if (dir == DIR_UP){
      ys[0] = ys[0] - SNAKEWIDTH;
    } 
    else {//DOWN
      ys[0] = ys[0] + SNAKEWIDTH;
    }
    
    //Check if outside playing field
    if ((xs[0]<0) || (xs[0]>=FIELD_WIDTH) || (ys[0]<0) || (ys[0]>=FIELD_HEIGHT)){
      if (xs[0]<0) {xs[0] =FIELD_WIDTH -1;}
      else if (xs[0]>=FIELD_WIDTH) {xs[0] = 0;}      
      else if (ys[0]<0) {ys[0] =FIELD_HEIGHT -1;}
      else if (ys[0]>=FIELD_HEIGHT) {ys[0] = 0;}    
    }
    
    clearTablePixels();
   
    //Draw apple
    setTablePixel(ax,ay,YELLOW);

    //Draw snake
    for (int i=0; i<curLength; i++){
      setTablePixel(xs[i], ys[i], WHITE);
    }
    
    showPixels();
    
    char buf[4];
    int len = sprintf(buf, "%i", score);
  
    prevUpdateTime = curTime;
  } else if(gameOver && (curTime - prevUpdateTime) > 1000 / (UPDATES_PER_SECOND)) {
    updateFadeOut();
      
    if (fadedOut && curControl != BTN_NONE){
      resetControl();
      startSnake();
    }

    showPixels();
  }
}

/* Set direction from current button state */
void setDirection(){
  switch(curControl){
    case BTN_LEFT:
      dir = DIR_RIGHT;
      break;
    case BTN_RIGHT:
      dir = DIR_LEFT;
      break;
    case BTN_DOWN:
      dir = DIR_DOWN;
      break;
    case BTN_UP:
      dir = DIR_UP;
      break;
    case BTN_START:
      startSnake();
      break;
  }

  resetControl();
}

/* Ending, show score */
void die(){
  gameOver = true;
  startFadeOut();
}

/* Collision detection function */
boolean collide(int x1, int x2, int y1, int y2, int w1, int w2, int h1, int h2){
  if ((x1+w1>x2) && (x1<x2+w2) && (y1+h1>y2) && (y1<y2+h2)){
    return true;
  } 
  else {
    return false;
  }
}

