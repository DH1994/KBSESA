// Menu.h

#ifndef _MENU_h
#define _MENU_h
#include "Menu.h"
#include "Arduino.h"
#include "Wire.h"
#include "MI0283QT9.h"
#define ADDRESS 0x52

class Menu {
	public:
	Menu(MI0283QT9 lcd);
	void ANupdate();
	void ANinit();
	void AN_sendByte(byte,byte);
	private:
	int analogX;
	int analogY;
	int accelX;
	int accelY;
	int accelZ;
	int zButton;
	int cButton;
	int beginPossX;
	int beginPossY;
	int left;
	int right;
	int up;
	int down;
};
#endif

