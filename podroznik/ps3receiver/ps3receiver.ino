#include <PS3BT.h>
#include <usbhub.h>
#include <SoftwareSerial.h>

#define DEBUG

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will just create the instance

SoftwareSerial drivercomm(2, 3); // RX, TX
void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  drivercomm.begin(9600);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
uint8_t nextmoveP = 0x29;
uint8_t nextmoveO = 0x39;
bool running = false;
bool isStop = false;
bool peruka = false;
/*
 * 0x2A do 0x2D - podróżnik, odpowiednio WSAD (ASCII *+,-)
 * 0x3A do 0x3D - obiekt, odpowiednio WSAD (ASCII :;<=)
 * 0x4A do 0x4D - obiekt, odpowiednio RGBW (ASCII JKLM)
 * 0x70 - zero (p)
 * 0x71 - stop (q)
 * 0x72 - peruka on (r)
 * 0x73 - peruka off (s)
 */
void loop() {
  Usb.Task();
  if (PS3.PS3Connected) {
    if (running) {
      if (PS3.getAnalogHat(LeftHatX) > 155) {
        nextmoveP = 0x2D;
      } else if (PS3.getAnalogHat(LeftHatX) < 100) {
        nextmoveP = 0x2C;
      } else if (PS3.getAnalogHat(LeftHatY) > 155) {
        nextmoveP = 0x2B;
      } else if (PS3.getAnalogHat(LeftHatY) < 100) {
        nextmoveP = 0x2A;
      }
      if (nextmoveP != 0x29) {
        drivercomm.write(nextmoveP);
        nextmoveP = 0x29;
      }
      if (PS3.getAnalogHat(RightHatX) > 155) {
        nextmoveO = 0x3D;
      } else if (PS3.getAnalogHat(RightHatX) < 100) {
        nextmoveO = 0x3C;
      } else if (PS3.getAnalogHat(RightHatY) > 155) {
        nextmoveO = 0x3B;
      } else if (PS3.getAnalogHat(RightHatY) < 100) {
        nextmoveO = 0x3A;
      }
      if (nextmoveO != 0x39) {
        drivercomm.write(nextmoveO);
        nextmoveO = 0x39;
      }
    }
    if (PS3.getButtonClick(PS)) {
      PS3.disconnect();
    }
    if (PS3.getButtonClick(TRIANGLE)) {
      running = !running;
    }
    if (PS3.getButtonClick(SQUARE)) {
      isStop = !isStop;
      if (isStop) {
        drivercomm.write(0x71);
      } else {
        drivercomm.write(0x70);
      }
    }
    if (PS3.getButtonClick(R1)) {
      drivercomm.write(0x70);
    }
    /*if (PS3.getButtonClick(UP)) {
      drivercomm.write(0x3A);
    } else if (PS3.getButtonClick(DOWN)) {
      drivercomm.write(0x3B);
    } else if (PS3.getButtonClick(LEFT)) {
      drivercomm.write(0x3C);
    } else if (PS3.getButtonClick(RIGHT)) {
      drivercomm.write(0x3D);
    }*/
    if (PS3.getAnalogButton(R2) > 200 && !peruka) {
      drivercomm.write(0x72);
      peruka = true;
    }
    if (PS3.getAnalogButton(R2) < 200 && peruka) {
      drivercomm.write(0x73);
      peruka = false;
    }
    if (PS3.getButtonClick(CIRCLE)) {
      drivercomm.write(0x4A);
    }
    if (PS3.getButtonClick(CROSS)) {
      drivercomm.write(0x4C);
    }
    if (PS3.getButtonClick(L3)) {
      drivercomm.write(0x4B);
    }
    if (PS3.getButtonClick(START)) {
      drivercomm.write(0x4D);
    }
  }
}

