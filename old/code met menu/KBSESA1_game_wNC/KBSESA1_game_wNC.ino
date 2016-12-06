#include <digitalWriteFast.h>
#include <SPI.h>
#include <arduino.h>
#include <MI0283QT9.h>
#include <GraphicsLib.h>
//#include "GameField.h"
#include <Wire.h>
#include "NunchukLibrary.h"
#include "Menu.h"
//#include "Player.h"

#define ADDRESS 0x52
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13
#define DEBUGON
#define DEBUG

//Map* MP = new Map(*level);




//Player* playerNC = new Player(NC, MP);
//GameField* gameField = new GameField(lcd, MP);
uint8_t gameStatus = 0;

volatile uint8_t timer2_counter;    //DIT IS DE TIMER
char tmp[128];

int main(){
	init();
	MI0283QT9* lcd = new MI0283QT9();
	lcd->begin();
	NunchukLibrary* NC = new NunchukLibrary();
	
	while(1)
	{	
		if(gameStatus == 0)
		{
			Menu* menu = new Menu(lcd, NC);
			while(1)
			{
				menu->Update();
				if(menu->getStatus() != 0) 
				{
					gameStatus = menu->getStatus();
					break;
				}
			}
			//destruct menu
		}
		
		if(gameStatus == 2)
		{
			
		}
	}
	
	//gameField->GFInit(1);
	//menu(lcd);
	/*
	#ifdef DEBUGON
	#endif
	
	playerNC->setPosition(gameField->getPlayerX(), gameField->getPlayerY());

	while(1){
		uint8_t NC_status = 0;
		NC_status = NC->ANupdate();
		uint8_t playerXpos = playerNC->getxPos();
		uint8_t playerYpos = playerNC->getyPos();
		uint8_t left = MP->getFieldValue(playerXpos - 1, playerYpos);
		uint8_t right = MP->getFieldValue(playerXpos + 1, playerYpos);
		uint8_t up = MP->getFieldValue(playerXpos, playerYpos - 1);
		uint8_t down = MP->getFieldValue(playerXpos, playerYpos + 1);
		bool boolkip = playerNC->updatePlayer(NC_status, left, right, up, down);
		if(boolkip){
			int x = playerNC->getOldXPosPx();
			int y = playerNC->getOldYPosPx();
			int playerX = playerNC->getxPosPx();
			int playerY = playerNC->getyPosPx();
			gameField->updateGameField(x, y, SIZE, SIZE, playerX, playerY);
			playerNC->updatePos();
		}
	}
	*/
}
/*
ISR(TIMER2_COMPA_vect)        // interrupt service routine
{
	TCNT2 = timer2_counter;   // preload timer
	cursorMovement();         //Update the location of the player at a certain interfall
}
*/


