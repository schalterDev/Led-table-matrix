/* LedTable
 *
 * Written by: Ing. David Hrbaty
 * 
 * Common code and defines for the Bricks game
 */
 
float ballX = 10;
float ballY = FIELD_WIDTH / 2;
float xincrement = 1;
float yincrement = 1;
int rad = 1;
int scorePlayer = 0;
int blockWidth = 0;
int blockHeight = 1;
int maxAttempt = 1;

int positionPlayer = 6;

int numBlocks = 30;
#define BRICKS_FRAMES_PER_UPDATE 4
int MAX_SCORE;
#define MAX_ATTEMPT 5
#define PLAYER_HEIGHT 3
boolean continueGame = true;

char bricks[30][3] = {
  // in play, xloc, yloc 
   {1,0,0}  ,
   {1,1,0}  ,
   {1,2,0}  ,
   {1,3,0}  ,
   {1,4,0}  ,
   {1,5,0}  ,
   {1,6,0}  ,
   {1,7,0}  ,
   {1,8,0}  ,
   {1,9,0}  ,
   {1,0,1}  ,
   {1,1,1}  ,
   {1,2,1}  ,
   {1,3,1}  ,
   {1,4,1}  ,
   {1,5,1}  ,
   {1,6,1}  ,
   {1,7,1}  ,
   {1,8,1}  ,
   {1,9,1}  , 
   {1,0,2}  ,
   {1,1,2}  ,
   {1,2,2}  ,
   {1,3,2}  ,
   {1,4,2}  ,
   {1,5,2}  ,
   {1,6,2}  ,
   {1,7,2}  ,
   {1,8,2}  ,   
   {1,9,2}  
};
/* Block shape */
static const uint8_t brick[] PROGMEM = {
  10,
  8,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
