//#include "Block.h"
#include "arduino.h"
#include "GameField.h"
#include <GraphicsLib.h>
#include <fonts.h>
#include <BMPheader.h>
#include <MI0283QT9.h>

//Declare only one display !
MI0283QT9 lcd;  //MI0283QT9 Adapter v1

int main(void){
	init();					//init display
	lcd.begin();			//spi-clk=SPI_CLOCK_DIV4
							//clear screen
	GameField gameField(lcd, 1);
}