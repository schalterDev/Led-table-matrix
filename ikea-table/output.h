#include "FastLED.h"

//LED field size
#define  FIELD_WIDTH       10
#define  FIELD_HEIGHT      15
#define  NUM_PIXELS    FIELD_WIDTH*FIELD_HEIGHT
#define  ORIENTATION_HORIZONTAL //Rotation of table, uncomment to rotate field 90 degrees
#define  ROTATE //Rotates field 180 degrees

/* *** LED color table *** */
#define  GREEN  0x00FF00
#define  RED    0xFF00FF
#define  BLUE   0x0000FF
#define  YELLOW 0xFFFF00
#define  LBLUE  0x00FFFF
#define  PURPLE 0xFF00FF
#define  WHITE  0XFFFFFF
unsigned long int colorLib[4] = {YELLOW, BLUE, WHITE, RED};

CRGB leds[NUM_PIXELS];

void initPixels();
void setPixel(int n, int color);
void setPixelRGB(int n, int r, int g, int b);
void setDelay(int duration);
int getPixel(int n);
void showPixels();
void setTablePixel(int x, int y, int color);
void setTablePixelRGB(int x, int y, int r, int g, int b);
void clearTablePixels();
void dimLeds(float factor);
