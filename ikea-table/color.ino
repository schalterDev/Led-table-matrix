int curColor;
const int colorChangeFaktor = 10;

void startColor() {
  clearTablePixels();
  curColor = 0XFFFFFF;

  colorChanged();
}

void updateColor() {
  curTime = millis();

  if(curTime - prevUpdateTime > 1000 / UPDATES_PER_SECOND) {
    if(curControl != BTN_NONE) {
      if(curControl == BTN_LEFT) {
        changeColor(true);
      } else if(curControl == BTN_RIGHT) {
        changeColor(false);
      }

      resetControl();
    }

    prevUpdateTime = curTime;
  } 
}

void changeColor(bool add) {
  if(add) {
    curColor += colorChangeFaktor;
  } else {
    curColor -= colorChangeFaktor;
  }

  colorChanged();
}

void colorChanged() {
  if(curColor > 0XFFFFFF) {
    curColor -= 0XFFFFFF;
  } else if (curColor < 0X000000) {
    curColor += 0XFFFFFF;
  }
  
  setAllPixelsColor(curColor);
  showPixels();
}

void setCurColor(int newColor) {
  curColor = newColor;
  colorChanged();
}

