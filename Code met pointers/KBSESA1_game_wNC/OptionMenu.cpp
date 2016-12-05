#include "OptionMenu.h"

OptionMenu::OptionMenu(MI0283QT9 *lcd_g, NunchukLibrary *nc_g)
{
	nc = nc_g;
	lcd = lcd_g;
	lcd->fillScreen(RGB(255,252,0));
	drawBar(0, 1);
	drawSlider(0, option[0], 1);

	for(uint8_t i = 1; i<4; i++)
	{
		drawBar(i, 0);
		drawSlider(i, option[i], 1);
	}
}


void OptionMenu::Update()
{
	nc->ANupdate();
	if(nc->getStatus() == 3 && menuNr !=0) menuNr--;
	
	if(nc->getStatus() == 4 && menuNr !=3) menuNr++;
	_delay_ms(100);

	switch(menuNr)
	{
		case 0:
		if(menuNr != menuLast)
		{
			lcd->drawText(40, (20+menuLast*50), optionName[menuLast], RGB(255,128,0), RGB(255,252,0), 2);
			lcd->drawText(40, (20+menuNr*50), optionName[menuNr], RGB(0,0,255), RGB(255,252,0), 2);
		}
		sliderUpdate(menuNr);
		break;
		
		case 1:
		if(menuNr != menuLast)
		{
			lcd->drawText(40, (20+menuLast*50), optionName[menuLast], RGB(255,128,0), RGB(255,252,0), 2);
			lcd->drawText(40, (20+menuNr*50), optionName[menuNr], RGB(0,0,255), RGB(255,252,0), 2);
		}
		sliderUpdate(menuNr);
		break;

		case 2:
		if(menuNr != menuLast)
		{
			lcd->drawText(40, (20+menuLast*50), optionName[menuLast], RGB(255,128,0), RGB(255,252,0), 2);
			lcd->drawText(40, (20+menuNr*50), optionName[menuNr], RGB(0,0,255), RGB(255,252,0), 2);
		}
		sliderUpdate(menuNr);
		break;

		case 3:
		if(menuNr != menuLast)
		{
			lcd->drawText(40, (20+menuLast*50), optionName[menuLast], RGB(255,128,0), RGB(255,252,0), 2);
			lcd->drawText(40, (20+menuNr*50), optionName[menuNr], RGB(0,0,255), RGB(255,252,0), 2);
		}
		sliderUpdate(menuNr);
		break;
	}
	
	menuLast = menuNr;
	if(nc->getCButton()) status = 0;		
}

void OptionMenu::sliderUpdate(int item)
{
	nc->ANupdate();
	_delay_ms(150);
	oldOption = option[item];

	if(nc->getStatus() == 1 && option[item] != 0) option[item]--;
	if(nc->getStatus() == 2 && option[item] != 9) option[item]++;

	if(option[item] != oldOption)
	{
		drawSlider(item, option[item], 1);
		drawSlider(item, oldOption, 0);
		lcd->drawInteger(280, (((item+1)*50)-5), option[item], 11, RGB(255,128,0), RGB(255,252,0), 2);
	}

}

void OptionMenu::drawSlider(int item, int slideValue, int draw)
{
	item++;
	item*=50;
	slideValue*=23;
	if(draw)
	{
		lcd->drawLine((45+slideValue), (item-10), (45+slideValue), (item+10), RGB(0,0,255));
	}
	else
	{
		lcd->drawLine((45+slideValue), (item-10), (45+slideValue), (item+10), RGB(255,252,0));
		lcd->drawPixel((45+slideValue), item, RGB(255,128,0));
	}
}


void OptionMenu::drawBar(int itemNr, int tab)
{
	int item = itemNr;
	item++;
	item*=50;
	lcd->drawText(40, (item-30), optionName[itemNr], RGB(255,128,0), RGB(255,252,0), 2); // text
	lcd->drawLine(40, item, 257, item, RGB(255,128,0)); //x
	lcd->drawLine(40, (item-10), 40, (item+10), RGB(255,128,0)); //y
	lcd->drawLine(257, (item-10), 257, (item+10), RGB(255,128,0)); //y
	lcd->drawInteger(280, (((itemNr+1)*50)-5), option[itemNr], 11, RGB(255,128,0), RGB(255,252,0), 2);

	for(int i=0; i<tab; i++) lcd->drawLine((50+(i*10)), (item-10), (50+(i*10)), (item+10), RGB(255,128,0));
}

uint8_t OptionMenu::getStatus()
{
	return status;
}