/*
 * GameField.cpp
 *
 * Created: 24-11-2016 10:45:28
 *  Author: Rick
 */ 
 #include "GameField.h"
 #include "Player.h"
 #include "Block.h"
#include <arduino.h>
#include "MI0283QT9.h"

#define OUTSIDE		RGB(162, 152, 105)			//this is the color for the blocks on the outside as well as the blocks that are undestroyable in the game
#define FIELD		RGB(46, 41, 37)				//this is the color for the field you are standing on
#define BLOCK		RGB(168, 108, 110)			//this is the color for the block that are destroyable
#define PLAYERA		RGB(255, 0, 0)
#define PLAYERB		RGB(0, 255, 0)
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.


 GameField::GameField(MI0283QT9 lcd_g, uint8_t game_g, Player playerA_g)
{
	game = game_g;
	lcd = lcd_g;
	playerA = playerA_g;
	Block blockField[9][11];
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
			};								//0 = EMPTY, 1 = UNDESTROYABLE BLOCK and 2 = DESTROYABLE BLOCK

	lcd.fillScreen(OUTSIDE);				//resets the screen
	int leftcornerX = 48;					//is the x-as corner of the block starting by x and y as 0 of the playing field
	int leftcornerY = 13;					//is the y-as corner of the block starting by x and y as 0 of the playing field
	lcd.fillRect( leftcornerX, leftcornerY, 11*SIZE, 9*SIZE, FIELD);
	for(uint16_t i = 0; i < 9; i++)
	{
		for(uint16_t j = 0; j < 11; j++)			//those loops are looping through the whole playingfield
		{
			switch(field[i][j]){
				case 1:			//undestroyable block
					lcd.fillRect( leftcornerX, leftcornerY, SIZE, SIZE, OUTSIDE);
				break;

				case 2:			//destroyable block
					lcd.fillRect( leftcornerX + 1, leftcornerY + 1, SIZE - 2, SIZE - 2, BLOCK);
				break;

				case 3:			//player (this Arduino)
					lcd.fillCircle(leftcornerX + (SIZE / 2), leftcornerY + 1 + (SIZE / 2), (SIZE - 4)/2, PLAYERA);
					playerA.setPosition(leftcornerX,leftcornerY);
				break;

				case 4:			//player (received by IRCOM)
					lcd.fillCircle(leftcornerX + (SIZE / 2), leftcornerY + 1 + (SIZE / 2), (SIZE - 4)/2, PLAYERB);
				break;
			}
			leftcornerX = leftcornerX + SIZE;	//updates the leftcornerX for the next block
		}
		leftcornerX = 48;
		leftcornerY = leftcornerY + SIZE;
	}
}
