/*// OptionMenu.h
#ifndef _OPTIONMENU_h
#define _OPTIONMENU_h

public:
optionMenu(lcd_g, nc_g);

private:
//------Game Options------//
String optionName[4] = {
	"BrightNess",
	"GameSpeed",
	"Bomb Density",
	"Level Select"
};
//-----Startup Default----//
int option[4] = {
	0, //Brightness
	4, //GameSpeed
	7,  //Bomb Density
	0   //level
};
//------------------------//

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




#endif
*/