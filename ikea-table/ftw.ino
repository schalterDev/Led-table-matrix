#include "ftw.h"

void startFtw() {
  gameOver = false;
  firstPlayerWon = false;
  secondPlayerWon = false;
  playerInputPos = 0;
  currentPlayer = 1;

  resetField();
}

void resetField() {
  int x,y;
  for (x=0;x<FIELD_WIDTH;x++){
    for (y=0;y<FIELD_HEIGHT;y++){
      fieldFtw[x][y] = 0;
    }
  }
}

void updateFtw() {
  curTime = millis();
  
  if(!gameOver && curTime - prevUpdateTime > 1000 / (UPDATES_PER_SECOND / FTW_FRAMES_PER_UPDATE)) {
    if(curControl != BTN_NONE) {
      controlFtw();

      checkPlayerWon();
    }

    clearTablePixels();

    drawField();
    drawPlayerPos();

    showPixels();

    prevUpdateTime = curTime;
  } else if(gameOver && curTime - prevUpdateTime > 1000 / (UPDATES_PER_SECOND)) {
    updateFadeOut();

    showPixels();

    prevUpdateTime = curTime;

    if(fadedOut && curControl != BTN_NONE) {
      resetControl();
      startFtw();
    } 
  }
}

void controlFtw() {
  if(curControl == BTN_RIGHT) {
    navigate(false);
  } else if(curControl == BTN_LEFT) {
    navigate(true);
  } else if(curControl == BTN_DOWN || curControl == BTN_UP) {
    insert(currentPlayer, playerInputPos);
    currentPlayer = !currentPlayer;
    playerInputPos = -1;
    navigate(true);
    delay(500);
  }
  
  resetControl();
}

void navigate(bool left) {
  if(left) {
    do {
      playerInputPos++;
      checkPlayerInput();
    } while(canInsert(playerInputPos));
  } else {
    do {
      playerInputPos--;
      checkPlayerInput();
    } while(canInsert(playerInputPos));
  }
}

void checkPlayerInput() {
  if(playerInputPos < 0) {
    playerInputPos = maxUserPos;
  } else if(playerInputPos > maxUserPos) {
    playerInputPos = 0;
  }
}

void insert(bool firstPlayer, int pos) { 
  int token;
  if(firstPlayer) {
    token = colorFirst;
  } else {
    token = colorSecond;
  }
  
  if(pos < FIELD_WIDTH) { //on top
    insertIntoColum(pos, true, token);
  } else if(pos < FIELD_WIDTH + FIELD_HEIGHT) { //right side
    insertIntoRow(pos - FIELD_WIDTH, false, token);
  } else if(pos < FIELD_WIDTH * 2 + FIELD_HEIGHT) { //bottom
    insertIntoColum(FIELD_WIDTH * 2 + FIELD_HEIGHT - pos - 1, false, token);
  } else if(pos < FIELD_WIDTH * 2 + FIELD_HEIGHT * 2) { //left side
    insertIntoRow(FIELD_WIDTH * 2 + FIELD_HEIGHT * 2 - pos - 1, true, token);
  }
}

bool canInsert(int pos) {

  if(pos < FIELD_WIDTH) { //on top
    return fullColumn(pos);
  } else if(pos < FIELD_WIDTH + FIELD_HEIGHT) { //right side
    return fullRow(pos - FIELD_WIDTH);
  } else if(pos < FIELD_WIDTH * 2 + FIELD_HEIGHT) { //bottom
    return fullColumn(FIELD_WIDTH * 2 + FIELD_HEIGHT - pos);
  } else if(pos < FIELD_WIDTH * 2 + FIELD_HEIGHT * 2) { //left side
    return fullRow(FIELD_WIDTH * 2 + FIELD_HEIGHT * 2 - pos);
  }
  
  return false;
}

bool fullColumn(int column) {
  for(int i = 0; i < FIELD_HEIGHT; i++) {
    if(fieldFtw[column][i] == 0) {
      return false;
    }
  }

  return true;
}

bool fullRow(int row) {
  for(int i = 0; i < FIELD_WIDTH; i++) {
    if(fieldFtw[i][row] == 0) {
      return false;
    }
  }

  return true;
}

void insertIntoColum(int col, bool toBottom, int value) {
  int lastFreeRow;

  if(toBottom) {
    lastFreeRow = FIELD_HEIGHT - 1;
    for(int i = FIELD_HEIGHT - 1; i >= 0; i--) {
      if( fieldFtw[col][i] == 0 ) {
        //Search for next non 0 field
        for(int j = i; j>= 0; j--) {
          if(fieldFtw[col][j] != 0) {
            Serial.println("Move stone");
            Serial.println(i);
            Serial.println(j);
            fieldFtw[col][i] = fieldFtw[col][j];
            fieldFtw[col][j] = 0;
            break;
          }
        }
      }
    }

    while(fieldFtw[col][lastFreeRow] != 0) {
      lastFreeRow--;
    }
  } else {
    lastFreeRow = 0;
    for(int i = 0; i < FIELD_HEIGHT; i++) {
      if( fieldFtw[col][i] == 0 ) {
        //Search for next non 0 field
        for(int j = i; j < FIELD_HEIGHT; j++) {
          if(fieldFtw[col][j] != 0) {
            fieldFtw[col][i] = fieldFtw[col][j];
            fieldFtw[col][j] = 0;
            break;
          }
        }
      }
    }

    while(fieldFtw[col][lastFreeRow] != 0) {
      lastFreeRow++;
    }
  }

  if(fieldFtw[col][lastFreeRow] == 0) {
    fieldFtw[col][lastFreeRow] = value;
    Serial.println("insert");
    Serial.println(value);
  }
}

void insertIntoRow(int row, bool toRight, int value) {
  int lastFreeColumn;

  if(toRight) {
    lastFreeColumn = FIELD_WIDTH - 1;
    for(int i = FIELD_WIDTH - 1; i >= 0; i--) {
      if( fieldFtw[i][row] == 0 ) {
        //Search for next non 0 field
        for(int j = i; j>= 0; j--) {
          if(fieldFtw[j][row] != 0) {
            fieldFtw[i][row] = fieldFtw[j][row];
            fieldFtw[j][row] = 0;
            break;
          }
        }
      }
    }

    while(fieldFtw[lastFreeColumn][row] != 0) {
      lastFreeColumn--;
    }
  } else {
    lastFreeColumn = 0;
    for(int i = 0; i < FIELD_WIDTH; i++) {
      if( fieldFtw[i][row] == 0 ) {
        //Search for next non 0 field
        for(int j = i; j < FIELD_WIDTH; j++) {
          if(fieldFtw[j][row] != 0) {
            fieldFtw[i][row] = fieldFtw[j][row];
            fieldFtw[j][row] = 0;
            break;
          }
        }
      }
    }
    while(fieldFtw[lastFreeColumn][row] != 0) {
      lastFreeColumn++;
    }
  }

  if(fieldFtw[lastFreeColumn][row] == 0) {
    fieldFtw[lastFreeColumn][row] = value;
  }
}

void checkPlayerWon() {
  int x,y, prev, count, playerAtField, rowCounter;
  
  //check rows
  for(x = 0; x < FIELD_WIDTH; x++) {
    count = 1;
    prev = 0;
    for(y = 0; y < FIELD_HEIGHT; y++) {
      playerAtField = fieldFtw[x][y];
      if(playerAtField != prev) {
        prev = playerAtField;
        count = 1;
      } else if(playerAtField == 1) { //first player
        count++;
        if(count >= tokensToWin) {
          firstPlayerWon = true;
        }
      } else if(playerAtField == 2) { //second player
        count++;
        if(count >= tokensToWin) {
          secondPlayerWon = true;
        }
      }
    }
  }
  
  //check columns
  for(y = 0; y < FIELD_HEIGHT; y++) {
    count = 1;
    prev = 0;
    for(x = 0; x < FIELD_WIDTH; x++) {
      playerAtField = fieldFtw[x][y];
      if(playerAtField != prev) {
        prev = playerAtField;
        count = 1;
      } else if(playerAtField == 1) { //first player
        count++;
        if(count >= tokensToWin) {
          firstPlayerWon = true;
        }
      } else if(playerAtField == 2) { //second player
        count++;
        if(count >= tokensToWin) {
          secondPlayerWon = true;
        }
      }
    }
  }
  
  //check diagonal
  for(x = 0; x < FIELD_WIDTH; x++) {
    count = 1;
    prev = 0;
    rowCounter = 0;
    while(x + rowCounter < FIELD_WIDTH && rowCounter < FIELD_HEIGHT) {
      playerAtField = fieldFtw[x + rowCounter][rowCounter];
      if(playerAtField != prev) {
        prev = playerAtField;
        count = 1;
      } else if(playerAtField == 1) { //first player
        count++;
        if(count >= tokensToWin) {
          firstPlayerWon = true;
        }
      } else if(playerAtField == 2) { //second player
        count++;
        if(count >= tokensToWin) {
          secondPlayerWon = true;
        }
      }

      rowCounter++;
    }
  }
  for(y = 0; y < FIELD_HEIGHT; y++) {
    count = 1;
    prev = 0;
    rowCounter = 0;
    while(x + rowCounter < FIELD_HEIGHT && rowCounter < FIELD_WIDTH) {
      playerAtField = fieldFtw[rowCounter][y + rowCounter];
      if(playerAtField != prev) {
        prev = playerAtField;
        count = 1;
      } else if(playerAtField == 1) { //first player
        count++;
        if(count >= tokensToWin) {
          firstPlayerWon = true;
        }
      } else if(playerAtField == 2) { //second player
        count++;
        if(count >= tokensToWin) {
          secondPlayerWon = true;
        }
      }

      rowCounter++;
    }
  }
  
  for(x = 0; x < FIELD_WIDTH; x++) {
    count = 1;
    prev = 0;
    rowCounter = 0;
    while(x - rowCounter >= 0 && rowCounter < FIELD_HEIGHT) {
      playerAtField = fieldFtw[x - rowCounter][rowCounter];
      if(playerAtField != prev) {
        prev = playerAtField;
        count = 1;
      } else if(playerAtField == 1) { //first player
        count++;
        if(count >= tokensToWin) {
          firstPlayerWon = true;
        }
      } else if(playerAtField == 2) { //second player
        count++;
        if(count >= tokensToWin) {
          secondPlayerWon = true;
        }
      }

      rowCounter++;
    }
  }
  for(y = 0; y < FIELD_HEIGHT; y++) {
    count = 1;
    prev = 0;
    rowCounter = 0;
    while(y - rowCounter >= 0 && rowCounter < FIELD_WIDTH) {
      playerAtField = fieldFtw[rowCounter][y - rowCounter];
      if(playerAtField != prev) {
        prev = playerAtField;
        count = 1;
      } else if(playerAtField == 1) { //first player
        count++;
        if(count >= tokensToWin) {
          firstPlayerWon = true;
        }
      } else if(playerAtField == 2) { //second player
        count++;
        if(count >= tokensToWin) {
          secondPlayerWon = true;
        }
      }

      rowCounter++;
    }
  }

  if(firstPlayerWon or secondPlayerWon) {
    gameLost();
  }
  
}

void gameLost() {
  gameOver = true;

  startFadeOut();
}

void drawField() {
  int x,y, color;
  for (x=0;x<FIELD_WIDTH;x++){
    for (y=0;y<FIELD_HEIGHT;y++){
      color = fieldFtw[x][y];
      if (color != 0){
        setTablePixel(x,y, colorLib[color]);
      } 
    }
  }
}

void drawPlayerPos() {
  int x,y;

  //Serial.println(playerInputPos);

  if(playerInputPos < FIELD_WIDTH) { //on top
    x = playerInputPos;
    y = 0;
    //Serial.println("top");
  } else if(playerInputPos < FIELD_WIDTH + FIELD_HEIGHT) { //right side
    x = FIELD_WIDTH - 1;
    y = playerInputPos - FIELD_WIDTH;
    //Serial.println("right");
  } else if(playerInputPos < FIELD_WIDTH * 2 + FIELD_HEIGHT) { //bottom
    x = FIELD_WIDTH * 2 + FIELD_HEIGHT - playerInputPos - 1;
    y = FIELD_HEIGHT - 1;
    //Serial.println("bottom");
  } else if(playerInputPos < FIELD_WIDTH * 2 + FIELD_HEIGHT * 2) { //left side
    x = 0;
    y = FIELD_WIDTH * 2 + FIELD_HEIGHT * 2 - playerInputPos - 1;
    //Serial.println("left");
  } else {
    Serial.println("none-error input");
  }
  
  //x is width
  //y is height
  setTablePixel(x,y, colorLib[colorInput]);
}


