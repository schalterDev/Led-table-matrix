 void initInput() {
  initBluetooth();
  setupButton(buttonFrontLeft);
  setupButton(buttonFrontRight);
  setupButton(buttonRightFront);
  setupButton(buttonLeftFront);
  setupButton(buttonLeftBack);
  setupButton(buttonRightBack);
  setupButton(buttonDown);

  resetControl();
  selection = FIRSTSELECTION;
  selectionChanged = true;
  startSelection = true;
}

void readInput() {  
  readButtons();
  readBluetooth();

  readBrightness();
}

void readBrightness() {
  brightness = readAnalogPing(brightnessPot, 255);
}

void readButtons() {
  if(isButtonPressed(buttonDown)) {
    selection++;
    checkSelection();
    selectionChanged = true;
    startSelection = true;
    delay(400);
  } else {
    //every selection can have their own control for each button
    switch(selection) {
      case RAINBOW:
        allButtonsStart();
        break;
      case COLOR:
        allButtonsStart();
        break;
      case STARS:
        allButtonsStart();
        break;
      case VU:
        allButtonsStart();
        break;
      case DICE:
        allButtonsStart();
        break;    
      case TETRIS:
        leftDownUpRightInput();
        break;   
      case SNAKE:
        leftDownUpRightInput();
        break; 
      case PONG:
        pongInput();
        break;  
      case BRICKS:       
        pongInput();
        break;   
      case LED:
        //updateLeds();
        break; 
      case BUZZER:
        pongInput();
        break;    
      case FTW:
        leftDownUpRightInput();
        break;   
      case SIMPLECOLOR:
        leftDownUpRightInput();  
        break;  
    }
  }
}

void allButtonsStart() {
  uint8_t i;
  for(i = 0; i < buttonsSize; i++) {
     if(isButtonPressed(buttons[i])) {
      addControl(BTN_START);
    }
  }
}

void leftRightInput() {
  if(isButtonPressed(buttonLeftFront)) {
    addControl(BTN_LEFT);
  }

  if(isButtonPressed(buttonRightFront)) {
    addControl(BTN_RIGHT);
  }

  if(isButtonPressed(buttonFrontRight)) {
    addControl(BTN_RIGHT);
  }

  if(isButtonPressed(buttonFrontLeft)) {
    addControl(BTN_LEFT);
  }

  if(isButtonPressed(buttonRightBack)) {
    addControl(BTN_RIGHT);
  }

  if(isButtonPressed(buttonLeftBack)) {
    addControl(BTN_LEFT);
  }
}

void pongInput() {
  if(isButtonPressed(buttonLeftFront)) {
    addControl(BTN_LEFT);
  }

  if(isButtonPressed(buttonRightFront)) {
    addControl(BTN_RIGHT);
  }

  if(isButtonPressed(buttonFrontRight)) {
    addControl(BTN_START);
  }

  if(isButtonPressed(buttonFrontLeft)) {
    addControl(BTN_START);
  }

  if(isButtonPressed(buttonRightBack)) {
    addControl(BTN_UP);
  }

  if(isButtonPressed(buttonLeftBack)) {
    addControl(BTN_DOWN);
  }
}

void leftDownUpRightInput() {
  if(isButtonPressed(buttonLeftFront)) {
    addControl(BTN_LEFT);
  }

  if(isButtonPressed(buttonRightFront)) {
    addControl(BTN_RIGHT);
  }

  if(isButtonPressed(buttonFrontRight)) {
    addControl(BTN_UP);
  }

  if(isButtonPressed(buttonFrontLeft)) {
    addControl(BTN_DOWN);
  }

  if(isButtonPressed(buttonRightBack)) {
    addControl(BTN_START);
  }

  if(isButtonPressed(buttonLeftBack)) {
    addControl(BTN_START);
  }
}

#define BUFF_SIZE 6
int buffer[BUFF_SIZE];

/*
Protocol for bluetooth
  End_Character is definded on top
  First character
    p for program
      1 - 12 which program
      BTN_EXIT has to be fired before you can change the program when a other program was started before
    c for control
      BTN_UP, BNT_DOWN, BTN_LEFT, BTN_RIGHT, BTN_EXIT
    l for led
      1 - 150 which led
        1 - 255: red
          1 - 255: green
            1 - 255: red
*/


void readBluetooth() {
  for(int i = 0; i < BUFF_SIZE; i++) {
    buffer[i] = NO_DATA;
  }
  
  int index = 0;
  int in = readByteByBluetooth();
  
  while(in != NO_DATA) {
    buffer[index] = in;
    index++;

    if(index == BUFF_SIZE || in == END_CHARACTER) {
      break;
    }

    Serial.println(in);
    in = readByteByBluetooth() ;
  } 

  if(index != 0) {
    //data was send
    switch(buffer[0]) {
      case 'p':
        //user want to change the selection
        selection = buffer[1] - 256; //1 is 209 (as char)
        selectionChanged = true;
        Serial.println("Selection");
        Serial.println(selection);
        resetControl();
        break;
      case 'c':
        //user send a command
        addControl( buffer[1] - 256 );
        Serial.println("Command");
        break;
      case 'l':
        //user wants to change one led
        break;
      default:
        Serial.println("Default: command not found");
        break;
    }
  }
}

void resetControl() {
  Serial.println("reset Control");
  for(uint8_t i = 0; i < CONTROL_COUNT; i++) {
    curControls[i] = BTN_NONE;
  }

  curControl = BTN_NONE;
}

/**
 * it is not possible to add a control that was added before
 */
void addControl(char control) {
  if(control != BTN_EXIT) {
    for(uint8_t i = 0; i < CONTROL_COUNT; i++) {
      if(curControls[i] == BTN_NONE && curControls[i] != control) {
        curControls[i] = control;
  
        //the first entry should be saved in curControl
        if(i == 0) {
          curControl = control;
        }
      } else if(curControls[i] == control) {
        return;
      }
    }
  } else {
    Serial.println("BTN_EXIT");
  }
  
}

void checkSelection() {
  if(selection > MAX_SELECTION) {
    selection = 1;
  } else if(selection <= 0) {
    selection = MAX_SELECTION;
  }
}

