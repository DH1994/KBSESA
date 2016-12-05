// Menu.h

#ifndef _MENU_h
#define _MENU_h
#include <Arduino.h>
#include <MI0283QT9.h>
#include "NunchukLibrary.h"
#define ADDRESS 0x52

class Menu {
	public:
	Menu(MI0283QT9 *lcd_g, NunchukLibrary *nc_g);
	//~Menu();
	void Update();
	uint8_t getStatus();
	private:
	NunchukLibrary *nc;
	MI0283QT9 *lcd;
	uint8_t menuNr = 0;
	uint8_t menuLast = 1;
	uint8_t status = 0;
};
#endif