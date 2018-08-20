const int colorChangeFaktor = 3;

int hsvH = 0;
int hsvS = 255;
int hsvV = 255;

void startColor() {
  clearTablePixels();

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
      } else if(curControl == BTN_UP) {
        changeS(false);
      } else if(curControl == BTN_DOWN) {
        changeS(true);
      }

      resetControl();
    }

    prevUpdateTime = curTime;
  } 
}

void changeColor(bool add) {
  if(add) {
    hsvH += colorChangeFaktor;
  } else {
    hsvH -= colorChangeFaktor;
  }

  if(hsvH > 255) {
    hsvH -= 255;
  } else if(hsvH < 0) {
    hsvH += 255;
  }

  colorChanged();
}

void changeS(bool add) {
  if(add) {
    hsvS += colorChangeFaktor;
  } else {
    hsvS -= colorChangeFaktor;
  }

  if(hsvS < 0) {
    hsvS += 255;
  } else if(hsvS > 255) {
    hsvS -= 255;
  }

  colorChanged();
}

void colorChanged() { 
  setAllPixelsColor(hsvH, hsvS, hsvV);
  showPixels();
}

