/* LedTable
 *
 * Written by: Martin Schalter
 * 
 * 
 * Main code for Bricks game
 */
 
#include "bricks.h"

void startBricks(){
  MAX_SCORE = numBlocks;
  
  gameOver = false;
  scorePlayer = 0;
  maxAttempt = 0;
  ballY = FIELD_HEIGHT - 2;
  ballX = FIELD_WIDTH / 2;
  for (int i=0; i<numBlocks; i++){
    bricks[i][0] = 1;
  }
}

void updateBricks(){
  curTime = millis();

  if(!gameOver && curTime - prevUpdateTime > 1000 / (UPDATES_PER_SECOND / BRICKS_FRAMES_PER_UPDATE)) {

    if (curControl != BTN_NONE){
        setPositionPaddle();
    }
    
    checkBallHitByPaddle();
    checkBlockCollision();
    
    ballX += xincrement;
    ballY += yincrement;
    
    checkBallOutOfBoundsTable();
    clearTablePixels();
    
    // Draw bricks
    for (int i=0; i<numBlocks; i++){
      if(bricks[i][0] == 1) {
        setTablePixel(bricks[i][1],bricks[i][2], WHITE);
      }
    }

    // Draw ball
    setTablePixel(ballX,ballY,YELLOW);

    // Draw player paddle
    for (int x=positionPlayer-PLAYER_HEIGHT/2; x<=positionPlayer+PLAYER_HEIGHT/2; ++x){
      setTablePixel(x, FIELD_HEIGHT-1, BLUE);
    }

    if (scorePlayer == MAX_SCORE || maxAttempt == MAX_ATTEMPT){
      gameOver = true;
      startFadeOut();
    }

    showPixels();
    
    prevUpdateTime = curTime;
  } else if(gameOver && curTime - prevUpdateTime > 1000 / (UPDATES_PER_SECOND)) {
    updateFadeOut();

    if (curControl == BTN_START){
      resetControl();
      startBricks();
    }

    showPixels();
  }
}

void setPositionPaddle(){
  switch(curControl){
    case BTN_LEFT:
      if(positionPlayer + (PLAYER_HEIGHT-1) / 2 < FIELD_WIDTH-1){
        ++positionPlayer;
      }
      break;
    case BTN_RIGHT:
      if(positionPlayer - PLAYER_HEIGHT / 2 > 0) {
        --positionPlayer;
      }
      break;
  }

  resetControl();
}

void checkBallHitByPaddle() {
  if(ballY == FIELD_HEIGHT-2)
  {
    if(ballX == positionPlayer)
    {
      yincrement = -1;
      ballY = FIELD_HEIGHT-2;
    } 
    else if(ballX < positionPlayer && ballX >= positionPlayer - PLAYER_HEIGHT / 2) 
    {
      yincrement = -1;
      xincrement = max(-1,xincrement-1); 
      ballY = FIELD_HEIGHT-2;
      ballX = positionPlayer - PLAYER_HEIGHT / 2-1;
    }    
    else if(ballX > positionPlayer && ballX <= positionPlayer + (PLAYER_HEIGHT-1) / 2) 
    {
      yincrement = -1;
      xincrement = min(1,xincrement+1); 
      ballY = FIELD_HEIGHT-2;
      ballX = positionPlayer + (PLAYER_HEIGHT-1) / 2+1;
    }    
  } 
}

void checkBallOutOfBoundsTable() {
  if(ballY < 0) 
  {
    yincrement = - yincrement;
    ballY = 1;
  } 
  else if(ballY > FIELD_HEIGHT-1) 
  {
    yincrement = - yincrement;
    xincrement = 0;
    ballY = FIELD_HEIGHT/2;
    ballX = FIELD_WIDTH/2;
    maxAttempt++;   
  } 
  if(ballX < 0) 
  {
    xincrement = - xincrement;
    ballX = 1;
  } 
  else if(ballX > FIELD_WIDTH-1) 
  {
    xincrement = - xincrement;
    ballX = FIELD_WIDTH-2;
  } 
}

boolean checkBlockCollision(){
    int ballTop = ballY-rad;                                            // Values for easy reference
    int ballBottom = ballY+rad;
    int ballLeft = ballX-rad;
    int ballRight = ballX+rad;
    
    for(int i=0;i<numBlocks;i++){                                       // Loop through the blocks
        if(bricks[i][0] == 1){                                          // If the block hasn't been eliminated
         int blockX = bricks[i][1];                                     // Grab x and y location
         int blockY = bricks[i][2];
         if(ballBottom >= blockY && ballTop <= blockY+blockHeight){     // If hitting BLOCK
           if(ballRight >= blockX && ballLeft <= blockX+blockWidth){       
             removeBlock(i);                                            // Mark the block as out of play
             return true;
           }
         }
      }
    }
  return false;                                                         // No collision detected
}
/* Removes a block from game play */
void removeBlock(int index){
      bricks[index][0] = 0;                                             // Mark it as out of play
      scorePlayer++;                                                          // Increment score
      yincrement = -yincrement;                                         // Flip the y increment
}

