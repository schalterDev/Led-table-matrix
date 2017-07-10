#include <SoftwareSerial.h>
const uint8_t rxPin = 12;
const uint8_t txPin = 13;
SoftwareSerial bluetooth(rxPin, txPin);

class Input {

  public:    
    const static int BLUETOOTH_SPEED = 9600;
    const static char NO_DATA = -1;
  
    static void initBluetooth() {
      bluetooth.begin(BLUETOOTH_SPEED);
    }

    /**
     * Reads one byte from the bluetooth module
     * @return -1 if there was nothing to read
     */
    static char readByteByBluetooth() {
      uint8_t dataBluetooth = -1;
      
      // read the incoming byte
      if (bluetooth.available() > 0) {
        dataBluetooth = bluetooth.read();
      }

      return dataBluetooth;
    }

    /**
     * The button should be connected to gnd and a digital I/O ping
     */
    static void setupButton(int button) {
      pinMode(button, INPUT);
      digitalWrite(button, HIGH);
    }

    static bool isButtonPressed(int button) {
      return digitalRead(button) == LOW;
    }

    static int readAnalogPin(int analogPin) {
      return analogRead(analogPin);
    }

    static int readAnalogPing(int analogPin, float maxValue) {
      int sensorValue = readAnalogPin(analogPin);
      return sensorValue * (maxValue / 1023.0);
    }
  
};

