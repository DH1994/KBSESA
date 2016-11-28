/*
 * GameField.cpp
 *
 * Created: 24-11-2016 10:45:28
 *  Author: Rick
 */ 
#include "GameField.h"
#include <arduino.h>
#include "MI0283QT9.h"

#define OUTSIDE		RGB(162, 152, 105)			//this is the color for the blocks on the outside as well as the blocks that are undestroyable in the game
#define FIELD		RGB(46, 41, 37)				//this is the color for the field you are standing on
#define BLOCK		RGB(168, 108, 110)			//this is the color for the block that are destroyable
#define PLAYERA		RGB(255, 0, 0)
#define PLAYERB		RGB(0, 255, 0)
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.
#define OFFSETX 48
#define OFFSETY 13
//#define DEBUG
 GameField::GameField()
 {
	
}
void GameField::GFInit(MI0283QT9 lcd_g, uint8_t game_g){
	lcd = lcd_g;
	uint8_t field[9][11] = {
		{3,0,2,2,0,0,0,0,0,0,0},
		{0,1,2,1,0,1,0,1,0,1,0},
		{2,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,1,0,1,0,1,0,1,0},
		{0,0,0,0,0,2,0,0,0,0,0},
		{0,1,0,1,0,1,0,1,0,1,0},
		{0,0,0,0,0,0,0,0,2,0,2},
		{0,1,0,1,0,1,0,1,0,1,0},
		{0,0,0,0,0,0,0,0,2,0,4}
	};
	for(int kip = 0; kip < 9; kip++){
		for(int koe = 0; koe < 11; koe++){
			activeField[kip][koe] = field[kip][koe];
		}
	}
	lcd.fillScreen(OUTSIDE);				//resets the screen
	int leftcornerX = 48;					//is the x-as corner of the block starting by x and y as 0 of the playing field
	int leftcornerY = 13;					//is the y-as corner of the block starting by x and y as 0 of the playing field
	lcd.fillRect( leftcornerX, leftcornerY, 11*SIZE, 9*SIZE, FIELD);
	for(uint16_t i = 0; i < 9; i++)
	{
		for(uint16_t j = 0; j < 11; j++)			//those loops are looping through the whole playingfield
		{
			switch(activeField[i][j]){
				case 1:			//undestroyable block
				lcd.fillRect( leftcornerX, leftcornerY, SIZE, SIZE, OUTSIDE);
				break;

				case 2:			//destroyable block
				lcd.fillRect( leftcornerX, leftcornerY, SIZE, SIZE, BLOCK);
				break;

				case 3:			//player (this Arduino)
				lcd.fillRect(leftcornerX, leftcornerY, SIZE, SIZE, PLAYERA);
				playerX = i;
				playerY = j;
				activeField[i][j] = 0;
				break;

				case 4:			//player (received by IRCOM)
				lcd.fillRect(leftcornerX, leftcornerY, SIZE, SIZE, PLAYERA);
				activeField[i][j] = 0;
				break;
			}
			leftcornerX = leftcornerX + SIZE;	//updates the leftcornerX for the next block
		}
		leftcornerX = 48;
		leftcornerY = leftcornerY + SIZE;
	}
}

uint8_t GameField::getFieldValue(uint8_t x, uint8_t y){
	return activeField[x][y];
}

void GameField::updateGameField(int x, int y, int width, int height, int playerX, int playerY){
	#ifdef DEBUG
	Serial.println(x);
	Serial.println(y);
	Serial.println(width);
	Serial.println(height);
	Serial.println(playerX);
	Serial.println(playerY);
	#endif DEBUG
	playerX += OFFSETX;
	playerY += OFFSETY;
	lcd.fillRect(x, y, width, height, FIELD);
	lcd.fillRect(playerX, playerY, SIZE, SIZE, PLAYERA);
}
uint8_t GameField::getPlayerX(){
	return playerX;
}
uint8_t GameField::getPlayerY(){
	return playerY;
}