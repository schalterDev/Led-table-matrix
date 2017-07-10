void initPixels() {
  FastLED.addLeds<FAST_LED_CHIPSET, FAST_LED_DATA_PIN, RGB>(leds, NUM_PIXELS);

  for(int i = 0; i < NUM_PIXELS; i++) {
    leds[i] = CRGB::Black;
  }
}

void setPixel(int n, int color) {
  leds[n] = CRGB(color);
}

void setPixelRGB(int n, int r, int g, int b) {
  leds[n] = CRGB(r,g,b);
}

void setDelay(int duration) {
  FastLED.delay(duration);
}

int getPixel(int n) {
  return (leds[n].r << 16) + (leds[n].g << 8) + leds[n].b;  
}

void showPixels() {
  FastLED.show();
}

void setTablePixel(int x, int y, int color) {
  #ifdef ORIENTATION_HORIZONTAL
    setPixel(y%2 ? y*FIELD_WIDTH + ((FIELD_WIDTH-1)-x) : y*FIELD_WIDTH + x,color);
  #else
    setPixel(x%2 ? x*FIELD_WIDTH + ((FIELD_HEIGHT-1)-y) : x*FIELD_WIDTH + y,color);
  #endif
}

void setTablePixelRGB(int x, int y, int r, int g, int b) {
  #ifdef ORIENTATION_HORIZONTAL
    setPixelRGB(y%2 ? y*FIELD_WIDTH + ((FIELD_WIDTH-1)-x) : y*FIELD_WIDTH + x,r,g,b);
  #else
    setPixelRGB(x%2 ? x*FIELD_WIDTH + ((FIELD_HEIGHT-1)-y) : x*FIELD_WIDTH + y,r,g,b);
  #endif
}

void clearTablePixels() {
  for (int n=0; n<FIELD_WIDTH*FIELD_HEIGHT; n++){
    setPixel(n,0);
  }
}

void dimLeds(float factor){
  //Reduce brightness of all LEDs, typical factor is 0.97
  for (int n=0; n<(FIELD_WIDTH*FIELD_HEIGHT); n++){
    int curColor = getPixel(n);
    //Derive the tree colors
    int r = ((curColor & 0xFF0000)>>16);
    int g = ((curColor & 0x00FF00)>>8);
    int b = (curColor & 0x0000FF);
    //Reduce brightness
    r = r*factor;
    g = g*factor;
    b = b*factor;
    //Pack into single variable again
    curColor = (r<<16) + (g<<8) + b;
    //Set led again
    setPixel(n,curColor);
  }
}

int fadeOutSelection;
int curColumn;
const int ColumnDelay = 10;
unsigned long timeLastColumn;
const int framesNewColumn = 3;
const int fadeOutTime = 2000; //in milliseconds
int fadeOutStart;

void startFadeOut() {
  fadeOutSelection = random(3);
  curColumn = 0;
  timeLastColumn = millis();
  
  fadedOut = false;
  fadeOutStart = millis();
}

void updateFadeOut(){
  if(millis() - fadeOutStart >= fadeOutTime) {
    fadedOut = true;
  }
  
  curTime = millis();
  if(curTime - prevUpdateTime > 1000 / UPDATES_PER_SECOND) {

    switch(fadeOutSelection){
      case 0:
      case 1:
      {
        //Fade out by dimming all pixels
        dimLeds(0.97);
        showPixels();
        break;
      }
      case 2:
      {
        //Fade out by swiping from left to right with ruler
        //After "framesNewColumn" frames init new column
        dimLeds(0.97);
        if (curColumn  < FIELD_WIDTH && curTime - timeLastColumn > 1000 / (UPDATES_PER_SECOND / framesNewColumn)){
          //Draw vertical line
          for (int y=0;y<FIELD_HEIGHT;y++){
            setTablePixel(curColumn, y, GREEN);
          }
          curColumn++;
          timeLastColumn = curTime;
        } 
         
        showPixels();
        break;
      }
    }

    prevUpdateTime = curTime;
  }
}

