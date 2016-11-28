#include <digitalWriteFast.h>
#include <SPI.h>
#include <arduino.h>
#include <MI0283QT9/MI0283QT9.h>
#include <GraphicsLib/GraphicsLib.h>
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

MI0283QT9 lcd;
NunchukLibrary NC;
Player playerNC;
GameField gameField;

volatile uint8_t timer2_counter;    //DIT IS DE TIMER
char tmp[128];

static uint16_t last_x=0, last_y=0; //The 8 bit variables where the previous location of the player is stored
static uint16_t current_x=160, current_y=115; //The start location of the player

int main(){
	init();
	NC.ANinit();
	lcd.begin();
	gameField.GFInit(lcd, 1);
	#ifdef DEBUGON
	Serial.begin(9600);
	Serial.println("setup");
	#endif
	playerNC.setPosition(gameField.getPlayerX(), gameField.getPlayerY());

	while(1){
		uint8_t NC_status = 0;
		NC_status = NC.ANupdate();
		uint8_t playerXpos = playerNC.getxPos();
		uint8_t playerYpos = playerNC.getyPos();
		uint8_t left = gameField.getFieldValue(playerXpos - 1, playerYpos);
		uint8_t right = gameField.getFieldValue(playerXpos + 1, playerYpos);
		uint8_t up = gameField.getFieldValue(playerXpos, playerYpos - 1);
		uint8_t down = gameField.getFieldValue(playerXpos, playerYpos + 1);
		bool boolkip = playerNC.updatePlayer(NC_status, left, right, up, down);
		if(boolkip){
			//Serial.println("IF");
			int x = playerNC.getOldXPosPx();
			int y = playerNC.getOldYPosPx();
			/*
			Serial.print("value old x and y\t");
			Serial.print(x);
			Serial.print("\t");
			Serial.println(y);
			*/
			int playerX = playerNC.getxPosPx();
			int playerY = playerNC.getyPosPx();
			/*
			Serial.print("value new x and y\t");
			Serial.print(playerX);
			Serial.print("\t");
			Serial.println(playerY);*/
			gameField.updateGameField(x, y, SIZE, SIZE, playerX, playerY);
			playerNC.updatePos();
		}
	}
}
/*
ISR(TIMER2_COMPA_vect)        // interrupt service routine
{
	TCNT2 = timer2_counter;   // preload timer
	cursorMovement();         //Update the location of the player at a certain interfall
}
*/


