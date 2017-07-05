/* LedTable
 *
 * Written by: Klaas De Craemer, Ing. David Hrbaty
 * 
 * Basic animation with fading stars
 */

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{    
    for( int i = 0; i < FIELD_WIDTH * FIELD_HEIGHT; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

static uint8_t startIndex;
uint8_t secondHand;
static uint8_t lastSecond;

void startColorPalette(){
  prevUpdateTime = 0;
  startIndex = 0;
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  clearTablePixels();
  showPixels();
}

void updateColorPalette() {
  curTime = millis();
  if((curTime - prevUpdateTime) > 1000 / UPDATES_PER_SECOND) {    
    secondHand = (curTime / 1000) % 60;
    lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
    }  
    
    FillLEDsFromPaletteColors( startIndex);
    showPixels();
    startIndex = startIndex + 1;
    prevUpdateTime = curTime;
  } 
}

void startRainbowPalette() {
  prevUpdateTime = 0;
  startIndex = 0;
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  clearTablePixels();
  showPixels();
}

void updateRainbowPalette() {
  curTime = millis();
  if(curTime - prevUpdateTime > 1000/UPDATES_PER_SECOND) {
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    
    FillLEDsFromPaletteColors(startIndex);
    showPixels();
    
    startIndex = startIndex + 1;
    prevUpdateTime = curTime;
  }
}
