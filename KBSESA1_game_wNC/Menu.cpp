// 
// 
// 

#include "Menu.h"
#include "Arduino.h"
#include "Wire.h"
#define ADDRESS 0x52

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

//MI0283QT9 lcd;
Menu::Menu(MI0283QT9 lcd)
{
	//MI0283QT9 lcd;
	lcd->begin();
	lcd->fillScreen(RGB(255,252,0));

	int menuNr = 0;
	int menuLast = 1;
	int button;

	while(1)
	{
		//menu level 1
		this->ANupdate();
		if(up) menuNr--;
		if(down) menuNr++;
		if(menuNr > 1) menuNr = 1;
		if(menuNr < 0) menuNr = 0;
		_delay_ms(100);

		if(menuLast != menuNr)
		{
			switch(menuNr)
			{
				case 0:
				lcd->clearWriteError`(60, 150, 200, 50, 10, RGB(255,128,0));
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
		if(zButton)
		{
			break;
		}
	}
	switch(menuNr)
	{
		case 0:
		//game
		break;
		
		case 1:
		//optionMenu();
		break;
	}
}

//Data vesturen via i2c
void Menu::AN_sendByte(byte data, byte location)
{
	Wire.beginTransmission(ADDRESS);

	Wire.write(location);
	Wire.write(data);

	Wire.endTransmission();

	_delay_ms(10);
}

//Begin met het uitlezen van de nunchuk
void Menu::ANinit()
{
	Wire.begin();

	AN_sendByte(0x55, 0xF0);
	AN_sendByte(0x00, 0xFB);

	_delay_ms(100);
	ANupdate();
	ANupdate();
	beginPossX = analogX;
	beginPossY = analogY;
}

//Herlaad de waarden die de nunchuk doorgeeft.
void Menu::ANupdate()
{
	int count = 0;
	int values[6];

	Wire.requestFrom(ADDRESS, 6);

	while(Wire.available())
	{
		values[count] = Wire.read();
		count++;
	}

	analogX = values[0];
	analogY = values[1];
	accelX = (values[2] << 2) | ((values[5] >> 2) & 3);
	accelY = (values[3] << 2) | ((values[5] >> 4) & 3);
	accelZ = (values[4] << 2) | ((values[5] >> 6) & 3);
	zButton = !((values[5] >> 0) & 1);
	cButton = !((values[5] >> 1) & 1);

	if((analogX - beginPossX) > 5) right = 1;
	else right = 0;

	if((beginPossX - analogX) > 5) left = 1;
	else left = 0;

	if((analogY - beginPossY) > 5) up = 1;
	else up = 0;

	if((beginPossY - analogY) > 5) down = 1;
	else down = 0;

	this->AN_sendByte(0x00, 0x00);
}