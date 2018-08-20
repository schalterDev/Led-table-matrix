/* LedTable
 *
 * Written by: Klaas De Craemer, Ing. David Hrbaty
 * 
 * Basic animation with fading stars
 */

#define  NB_NEWSTARS  2
unsigned int timeNextStar = 500;
boolean starsRunning;

void startStars(){
  clearTablePixels();
  showPixels();  
}

unsigned long prevStarsCreationTime = 0;
//unsigned long prevUpdateTime = 0;
//unsigned long curTime = 0;

void updateStars(){
  curTime = millis();

  if(curTime - prevUpdateTime > 1000 / UPDATES_PER_SECOND) {
    dimLeds(0.97);
    
    //Create new stars if enough time has passed since last time
    if ((curTime - prevStarsCreationTime) > timeNextStar){
      for (int i=0; i<NB_NEWSTARS; i++){
        boolean positionOk = false;
        int n = 0;
        //Generate random positions until valid
        while (!positionOk){
          n = random(FIELD_WIDTH*FIELD_HEIGHT);
          if (getPixel(n) == 0)
            positionOk = true;
        }
  //        //Get random color
  //        if (random(2)==0)
  //          leds.setPixel(n,YELLOW);
  //        else
          setPixel(n,BLUE);
      }
      prevStarsCreationTime = curTime;
    }
      
    showPixels();
    prevUpdateTime = curTime;
  }
}
