// 
// 
// 
/*
#include "OptionMenu.h"



void optionMenu()
{
	lcd.fillScreen(RGB(255,252,0));

	int menuNr = 0;
	int menuLast = 1;
	int oldBrightness;

	drawBar(0, 1);
	drawSlider(0, option[0], 1);

	for(uint8_t i = 1; i<4; i++)
	{
		drawBar(i, 0);
		drawSlider(i, option[i], 1);
	}

	while(1)
	{
		ANupdate();
		if(up) menuNr--;
		if(down) menuNr++;
		if(menuNr > 3) menuNr = 3;
		if(menuNr < 0) menuNr = 0;
		_delay_ms(150);

		switch(menuNr)
		{
			case 0:
			if(menuNr != menuLast)
			{
				lcd.drawText(40, (20+menuLast*50), optionName[menuLast], RGB(255,128,0), RGB(255,252,0), 2);
				lcd.drawText(40, (20+menuNr*50), optionName[menuNr], RGB(0,0,255), RGB(255,252,0), 2);
			}
			if(zButton) sliderUpdate(menuNr);
			break;
			
			case 1:
			if(menuNr != menuLast)
			{
				lcd.drawText(40, (20+menuLast*50), optionName[menuLast], RGB(255,128,0), RGB(255,252,0), 2);
				lcd.drawText(40, (20+menuNr*50), optionName[menuNr], RGB(0,0,255), RGB(255,252,0), 2);
			}
			if(zButton) sliderUpdate(menuNr);
			break;

			case 2:
			if(menuNr != menuLast)
			{
				lcd.drawText(40, (20+menuLast*50), optionName[menuLast], RGB(255,128,0), RGB(255,252,0), 2);
				lcd.drawText(40, (20+menuNr*50), optionName[menuNr], RGB(0,0,255), RGB(255,252,0), 2);
			}
			if(zButton) sliderUpdate(menuNr);
			break;

			case 3:
			if(menuNr != menuLast)
			{
				lcd.drawText(40, (20+menuLast*50), optionName[menuLast], RGB(255,128,0), RGB(255,252,0), 2);
				lcd.drawText(40, (20+menuNr*50), optionName[menuNr], RGB(0,0,255), RGB(255,252,0), 2);
			}
			if(zButton) sliderUpdate(menuNr);
			break;
		}
		
		menuLast = menuNr;
		if(cButton)
		{
			break;
		}
		
	}
	menu();
}

void sliderUpdate(int item)
{
	int oldOption;
	while(1)
	{
		ANupdate();
		_delay_ms(150);
		oldOption = option[item];

		if(left) option[item]--;
		if(right) option[item]++;
		if(option[item]<0) option[item] = 0;
		if(option[item]>9) option[item] = 9;

		if(option[item] != oldOption)
		{
			drawSlider(item, option[item], 1);
			drawSlider(item, oldOption, 0);
			lcd.drawInteger(280, (((item+1)*50)-5), option[item], 11, RGB(255,128,0), RGB(255,252,0), 2);
		}
		if(zButton) break;
	}
}

void drawSlider(int item, int slideValue, int draw)
{
	item++;
	item*=50;
	slideValue*=23;
	if(draw)
	{
		lcd.drawLine((45+slideValue), (item-10), (45+slideValue), (item+10), RGB(0,0,255));
	}
	else
	{
		lcd.drawLine((45+slideValue), (item-10), (45+slideValue), (item+10), RGB(255,252,0));
		lcd.drawPixel((45+slideValue), item, RGB(255,128,0));
	}
}

void drawBar(int itemNr, int tab)
{
	int item = itemNr;
	item++;
	item*=50;
	lcd.drawText(40, (item-30), optionName[itemNr], RGB(255,128,0), RGB(255,252,0), 2); // text
	lcd.drawLine(40, item, 257, item, RGB(255,128,0)); //x
	lcd.drawLine(40, (item-10), 40, (item+10), RGB(255,128,0)); //y
	lcd.drawLine(257, (item-10), 257, (item+10), RGB(255,128,0)); //y
	lcd.drawInteger(280, (((itemNr+1)*50)-5), option[itemNr], 11, RGB(255,128,0), RGB(255,252,0), 2);

	for(int i=0; i<tab; i++) lcd.drawLine((50+(i*10)), (item-10), (50+(i*10)), (item+10), RGB(255,128,0));
}
*/