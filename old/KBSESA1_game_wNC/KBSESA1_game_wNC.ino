#include "OptionMenu.h"
#include "Menu.h"
#include <digitalWriteFast.h>
#include <SPI.h>

/*
#include "NunchukLibrary.h"
#include "Arduino.h"
#include <Wire.h>
#include "GraphicsLib.h"
#include <MI0283QT9.h>
*/
#include <arduino.h>
#include <MI0283QT9/MI0283QT9.h>
#include <GraphicsLib/GraphicsLib.h>
#include "GameField.h"
#include <Wire.h>
#include "NunchukLibrary.h"
#include "Player.h"
#include "Menu.h"

#define ADDRESS 0x52
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13
#define DEBUG
MI0283QT9 lcd;
NunchukLibrary NC;
Player playerNC;
GameField gameField;
Menu menu;

volatile uint8_t timer2_counter;    //DIT IS DE TIMER
char tmp[128];

static uint16_t last_x=0, last_y=0; //The 8 bit variables where the previous location of the player is stored
static uint16_t current_x=160, current_y=115; //The start location of the player

int main(){
	init();
	NC.ANinit();
	lcd.begin();
	gameField.GFInit(lcd, 1);
	#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("setup");
	#endif
	playerNC.setPosition(gameField.getPlayerX(), gameField.getPlayerY());
	menu.Menu(lcd);

	while(1){
		#ifdef DEBUG
		Serial.println("Loop");
		#endif
		uint8_t NC_status = 0;
		NC_status = NC.ANupdate();
		#ifdef DEBUG
		Serial.print("NC_status:\t");
		Serial.println(NC_status);
		#endif
		uint8_t playerXpos = playerNC.getxPos();
		uint8_t playerYpos = playerNC.getyPos();
		uint8_t left = gameField.getFieldValue(playerXpos - 1, playerYpos);
		uint8_t right = gameField.getFieldValue(playerXpos + 1, playerYpos);
		uint8_t up = gameField.getFieldValue(playerXpos, playerYpos - 1);
		uint8_t down = gameField.getFieldValue(playerXpos, playerYpos + 1);
		bool boolkip = playerNC.updatePlayer(NC_status, left, right, up, down);
		#ifdef DEBUG
		Serial.print("update player:\t");
		Serial.println(boolkip);
		#endif
		if(boolkip){
			Serial.println("IF");
			int x = playerNC.getBlockResetX() + OFFSETX;
			int y = playerNC.getBlockResetY() + OFFSETY;
			int width = (playerNC.getBlockResetOffsetX()) ? (SIZE * 2) : (SIZE);
			int height = (playerNC.getBlockResetOffsetY()) ? (SIZE * 2) : (SIZE);
			int playerX = playerNC.getxPosPx();
			int playerY = playerNC.getyPosPx();
			gameField.updateGameField(x, y, width, height, playerX, playerY);
		}
		_delay_ms(100);	
	}
}
/*
ISR(TIMER2_COMPA_vect)        // interrupt service routine
{
	TCNT2 = timer2_counter;   // preload timer
	cursorMovement();         //Update the location of the player at a certain interfall
}
*/


