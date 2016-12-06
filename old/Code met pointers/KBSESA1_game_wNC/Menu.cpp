#include "Menu.h"

//MI0283QT9 lcd;
Menu::Menu(MI0283QT9* lcd_g, NunchukLibrary* nc_g)
{
	nc = nc_g;
	lcd = lcd_g;
	lcd->fillScreen(RGB(255,252,0));
}

void Menu::Update()
{
	nc->ANupdate();
	if(nc->getStatus() == 3) menuNr = 0;
	if(nc->getStatus() == 4) menuNr = 1;

	if(menuLast != menuNr)
	{
		switch(menuNr)
		{
			case 0:
			lcd->fillRoundRect(60, 150, 200, 50, 10, RGB(255,128,0));
			lcd->drawText(105, 170, "Options", RGB(0,0,255), RGB(255,128,0), 2);
			lcd->fillRoundRect(60, 40, 200, 50, 10, RGB(0,0,255));
			lcd->drawText(80, 60, "Start Game", RGB(255,128,0), RGB(0,0,255), 2);
			break;
			
			case 1:
			lcd->fillRoundRect(60, 150, 200, 50, 10, RGB(0,0,255));
			lcd->drawText(105, 170, "Options", RGB(255,128,0),RGB(0,0,255), 2);
			lcd->fillRoundRect(60, 40, 200, 50, 10, RGB(255,128,0));
			lcd->drawText(80, 60, "Start Game", RGB(0,0,255), RGB(255,128,0), 2);
			break;
		}
	}

	menuLast = menuNr;

	if(nc->getZButton())
	{
		switch(menuNr)
		{
			case 0:
				status = 1;
			break;
	
			case 1:
				status = 2;
			break;
		}
	}
}

uint8_t Menu::getStatus()
{
	return status;
}