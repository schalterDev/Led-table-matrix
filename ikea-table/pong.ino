/* LedTable
 *
 * Written by: Martin Schalter
 * 
 * Main code for Pong game
 */
 
#include "pong.h"
//unsigned long curTime;
//unsigned long prevUpdateTime = 0;

void startPong(){
  MAX_SCORE = 5;
  
  scorePlayerLeft  = 0;
  scorePlayerRight = 0;
  positionPlayerLeft  = FIELD_WIDTH/2;
  positionPlayerRight = FIELD_WIDTH/2;
  ballx = FIELD_WIDTH/2;
  bally = FIELD_HEIGHT/2;
  velocityx = 0; 
  velocityy = 1;
  ballBounces = 0;
  lastAutoPlayerMoveTime = 0;
  rumbleUntil = 0;
  waitUntil = 0;
  gameOver = false;
  ki = true;
}

float velocityMulti = 1;

void updatePong(){  
  
  curTime = millis();
  if(!gameOver && curTime - prevUpdateTime > 1000 / (UPDATES_PER_SECOND / PONG_FRAMES_PER_UPDATE)) {   

    if (curControl != BTN_NONE) {
      setPosition();
    } 
    
    checkBallHitByPlayer();

    if(ki) {
      if((curTime - lastAutoPlayerMoveTime) > 1000 / (UPDATES_PER_SECOND / PONG_FRAMES_PER_UPDATE / AUTO_PLAYER_SPEED)) {
        if(moveAutoPlayer()) {
          lastAutoPlayerMoveTime = curTime;
        }
      }
    } 

    checkVelocity();
    
    ballx += (velocityx * (int)(velocityMulti + 0.5));
    bally += (velocityy * (int)(velocityMulti + 0.5));
    
    checkBallOutOfBounds();
    clearTablePixels();

    // Draw ball
    setTablePixel(ballx,bally,WHITE);
    // Draw player left
    for (int y=positionPlayerLeft-PLAYER_HEIGHT/2; y<=positionPlayerLeft+PLAYER_HEIGHT/2; ++y){
      setTablePixel(y, 0, BLUE);
    }
    // Draw player right
    for (int y=positionPlayerRight-PLAYER_HEIGHT/2; y<=positionPlayerRight+PLAYER_HEIGHT/2; ++y){
      setTablePixel(y, FIELD_HEIGHT - 1, YELLOW);
    }
    
    showPixels();

    if (scorePlayerLeft == MAX_SCORE || scorePlayerRight == MAX_SCORE){
      gameOver = true;
      startFadeOut();
    }
    
    prevUpdateTime = curTime;
  } else if(gameOver) {
    updateFadeOut();

    if (fadedOut && curControl != BTN_NONE){
      resetControl();
      startPong();
    }
  }
}

void setPosition(){  
  //we have to check for more inputs when two player are playing
  bool firstPlayerMoved = false;
  bool secondPlayerMoved = false;

  for(int i = 0; i < CONTROL_COUNT; i++) {
    int control = curControls[i];
    switch(control){
      case BTN_LEFT:
        if(!secondPlayerMoved && positionPlayerRight + PLAYER_HEIGHT / 2 < FIELD_WIDTH-1){
          ++positionPlayerRight;
          secondPlayerMoved = true;
        }
        break;
      case BTN_RIGHT:
        if(!secondPlayerMoved && positionPlayerRight - PLAYER_HEIGHT / 2 > 0) {
          --positionPlayerRight;
          secondPlayerMoved = true;
        }
        break;
      case BTN_UP:
        ki = false;
        if(!firstPlayerMoved && positionPlayerLeft + PLAYER_HEIGHT / 2 < FIELD_WIDTH-1){
          ++positionPlayerLeft;
          firstPlayerMoved = true;
        }
        break;
      case BTN_DOWN:
        ki = false;
        if(!firstPlayerMoved && positionPlayerLeft - PLAYER_HEIGHT / 2 > 0) {
          --positionPlayerLeft;
          firstPlayerMoved = true;
        }
        break;
    }
  }

  resetControl();
}

void checkBallHitByPlayer() {
  if(bally == 1) 
  {
    velocityMulti += 0.05;
    if(ballx == positionPlayerLeft)
    {
      velocityy = 1;
      bally = 1;
      ++ballBounces;
      rumbleUntil = curTime + 200;
    } 
    else if(ballx < positionPlayerLeft && ballx >= positionPlayerLeft - PLAYER_HEIGHT / 2) 
    {
      velocityy = 1;
      velocityx = max(-1,velocityx-1); 
      bally = 1;
      ballx = positionPlayerLeft - PLAYER_HEIGHT / 2-1;
      ++ballBounces;
      rumbleUntil = curTime + 200;
    }    
    else if(ballx > positionPlayerLeft && ballx <= positionPlayerLeft + (PLAYER_HEIGHT-1) / 2) 
    {
      velocityy = 1;
      velocityx = min(1,velocityx+1); 
      bally = 1;
      ballx = positionPlayerLeft + (PLAYER_HEIGHT-1) / 2+1;
      ++ballBounces;
      rumbleUntil = curTime + 200;
    }    
  } 
  else if(bally == FIELD_HEIGHT-2)
  {
    velocityMulti += 0.05;
    if(ballx == positionPlayerRight)
    {
      velocityy = -1;
      bally = FIELD_HEIGHT-2;
      ++ballBounces;
      rumbleUntil = curTime + 200;
    } 
    else if(ballx < positionPlayerRight && ballx >= positionPlayerRight - PLAYER_HEIGHT / 2) 
    {
      velocityy = -1;
      velocityx = max(-1,velocityx-1); 
      bally = FIELD_HEIGHT-2;
      ballx = positionPlayerRight - PLAYER_HEIGHT / 2-1;
      ++ballBounces;
      rumbleUntil = curTime + 200;
    }    
    else if(ballx > positionPlayerRight && ballx <= positionPlayerRight + (PLAYER_HEIGHT-1) / 2) 
    {
      velocityy = -1;
      velocityx = min(1,velocityx+1); 
      bally = FIELD_HEIGHT-2;
      ballx = positionPlayerRight + (PLAYER_HEIGHT-1) / 2+1;
      ++ballBounces;
      rumbleUntil = curTime + 200;
    }    
  } 
}

void checkBallOutOfBounds() {
  if(ballx < 0) 
  {
    velocityx = - velocityx;
    //bally = 0;
    ballx = 1;
  } else if(ballx > FIELD_WIDTH-1) 
  {
    velocityx = -velocityx;
    ballx = FIELD_WIDTH-2;
    //bally = FIELD_HEIGHT-1;
  } 
  if(bally < 0) 
  {
    velocityy = - velocityy;
    velocityx = 0;
    bally = FIELD_HEIGHT/2;
    ballx = FIELD_WIDTH/2;
    ++scorePlayerRight;
    ballBounces = 0;
    waitUntil = curTime + 2000;
    velocityMulti = 1;
    Serial.print("Score Player right");
  } 
  else if(bally > FIELD_HEIGHT-1) 
  {
    velocityy = - velocityy;
    velocityx = 0;
    bally = FIELD_HEIGHT/2;
    ballx = FIELD_WIDTH/2;
    ++scorePlayerLeft;
    ballBounces = 0;
    waitUntil = curTime + 2000;
    velocityMulti = 1;
    Serial.print("Score Player left");
  } 
}

boolean moveAutoPlayer()
{
  if(ballx < positionPlayerLeft)
  {
    if(positionPlayerLeft - PLAYER_HEIGHT / 2>0) 
    {
      --positionPlayerLeft;
      return true;
    }
  } 
  else if(ballx > positionPlayerLeft) 
  {
    if(positionPlayerLeft + (PLAYER_HEIGHT-1) / 2 < FIELD_HEIGHT -1)
    {
      ++positionPlayerLeft;
      return true;
    }      
  } 
  return false;
}

void checkVelocity() {
   if(velocityMulti > 2)
      velocityMulti = 2;
}


