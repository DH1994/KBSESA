#include <digitalWriteFast.h>
#include <SPI.h>
#include <arduino.h>
#include <MI0283QT9.h>
#include <GraphicsLib.h>
#include "GameField.h"
#include <Wire.h>
#include "NunchukLibrary.h"
#include "Player.h"

#define ADDRESS 0x52
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13
#define DEBUGON
#define DEBUG

uint8_t level1[9][11] ={
  {3,0,0,0,0,0,0,0,0,0,0},
  {0,1,2,1,0,1,0,1,0,1,0},
  {0,0,0,0,0,0,0,0,0,0,0},
  {0,1,0,1,0,1,0,1,0,1,0},
  {0,0,0,0,0,2,0,0,0,0,0},
  {0,1,0,1,0,1,0,1,0,1,0},
  {0,0,0,0,0,0,0,0,2,0,2},
  {0,1,0,1,0,1,0,1,0,1,0},
  {0,0,0,0,0,0,0,0,2,0,4}
  };

Map* MP;
MI0283QT9* lcd;
NunchukLibrary* NC;
Player* playerNC;
GameField* gameField;

volatile uint8_t timer2_counter;    //DIT IS DE TIMER
char tmp[128];

int main(void){
 	init();
	MP = new Map(level1);
	lcd = new MI0283QT9();
	lcd->begin();
	NC = new NunchukLibrary();
	playerNC = new Player(NC, MP);
	gameField = new GameField(lcd, MP, playerNC);
	while(1){
		NC->ANupdate();
		if(playerNC->updatePlayer()){
			gameField->updateGameField_pl_nc();
		}
	}
	return 0;
}
/*
ISR(TIMER2_COMPA_vect)        // interrupt service routine
{
	TCNT2 = timer2_counter;   // preload timer
	cursorMovement();         //Update the location of the player at a certain interfall
}
*/


