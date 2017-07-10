/* LedTable
 *
 * Written by: Martin Schalter
 * 
 * Common code and defines for the Pong game
 */
 
#define PLAYER_HEIGHT 3
#define AUTO_PLAYER_SPEED 1 //1 every frame, 2 every second frame, ...
#define PONG_FRAMES_PER_UPDATE 4

int scorePlayerLeft;
int scorePlayerRight;
  
int positionPlayerLeft;
int positionPlayerRight;
  
int ballx;
int previousBallx;
int bally;
int previousBally;
int velocityx;
int velocityy;
int ballBounces;

boolean ki;
  
unsigned long lastAutoPlayerMoveTime;
unsigned long rumbleUntil;
unsigned long waitUntil;

