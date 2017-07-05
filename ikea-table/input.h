#define FIRSTSELECTION  12;
 
 /* *** Game commonly used defines ** */
#define  DIR_UP    1
#define  DIR_DOWN  2
#define  DIR_LEFT  3
#define  DIR_RIGHT 4

#define  BTN_NONE  0
#define  BTN_UP    1
#define  BTN_DOWN  2
#define  BTN_LEFT  3
#define  BTN_RIGHT  4
#define  BTN_START  5 
#define  BTN_EXIT  6

#define  END_CHARACTER '?'

#define CONTROL_COUNT 4
uint8_t curControls[CONTROL_COUNT] = {BTN_NONE, BTN_NONE, BTN_NONE, BTN_NONE}; //we can use 4 input buttons at once
uint8_t curControl = BTN_NONE; //is the first entry from the array above

uint8_t selection;
bool selectionChanged;
bool startSelection;

void initInput();
void readInput();
void resetControl();

/*
 * Controls in pong
 * BTN_LEFT firstPlayer-left
 * BTN_RIGHT firstPlayer-right
 * BTN_UP secondPlayer-left
 * BNT_DOWN secondPlayer-right
 */

