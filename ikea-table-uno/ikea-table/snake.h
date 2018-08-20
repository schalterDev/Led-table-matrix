/* LedTable
 *
 * Written by: Martin Schalter
 * 
 * Snake game common defines/variables
 */

/* ------ Game related ------ */
#define SNAKE_FRAMES_PER_UPDATE 4

int curLength;//Curren length of snake
//TODO these arrays need a lot of memory
int xs[60];//Array containing all snake segments,
int ys[60];// max snake length is array length
int dir;//Current Direction of snake
int score;
#define SNAKEWIDTH  1 //Snake width

int ax = 0;//Apple x position
int ay = 0;//Apple y position
int acolor = BLUE;
