bool firstPlayerWon;
bool secondPlayerWon;
bool currentPlayer; //true is first player, false is second player
int playerInputPos;
uint8_t const maxUserPos = FIELD_WIDTH * 2 + FIELD_HEIGHT * 2 - 1;
uint8_t const colorInput = 0;
uint8_t const colorFirst = 1;
uint8_t const colorSecond = 2;
uint8_t const tokensToWin = 4;
#define FTW_FRAMES_PER_UPDATE 2

//Save 0 for no player, 1 for player one and 2 for player two
uint8_t fieldFtw[FIELD_WIDTH][FIELD_HEIGHT];


