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
#define SIZE 24									//is the amount of pixels of on block the game has 9 (y) by 11 (x) blocks and is 216 by 264 px.

 GameField::GameField(MI0283QT9 lcd_g, int game_g)
{
	game = game_g;
	lcd = lcd_g;
	int field[9][11] = {
			{0,0,2,2,0,0,0,0,0,0,0},
			{0,1,2,1,0,1,0,1,0,1,0},
			{2,0,0,0,0,0,0,0,0,0,0},
			{0,1,0,1,0,1,0,1,0,1,0},
			{0,0,0,0,0,2,0,0,0,0,0},
			{0,1,0,1,0,1,0,1,0,1,0},
			{0,0,0,0,0,0,0,0,2,0,2},
			{0,1,0,1,0,1,0,1,0,1,0},
			{0,0,0,0,0,0,0,0,2,0,0}
			};								//0 = EMPTY, 1 = UNDESTROYABLE BLOCK and 2 = DESTROYABLE BLOCK
	lcd.fillScreen(OUTSIDE);				//resets the screen
	int leftcornerX = 48;					//is the x-as corner of the block starting by x and y as 0 of the playing field
	int leftcornerY = 13;					//is the y-as corner of the block starting by x and y as 0 of the playing field
	lcd.fillRect( leftcornerX, leftcornerY, 11*SIZE, 9*SIZE, FIELD);
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 11; j++)			//those loops are looping through the whole playingfield
		{
			
			if(field[i][j]){				//if number in field array is not zero
				if(field[i][j] == 2){		//if number = 2 than there is a destroyable block
					lcd.fillRect( leftcornerX + 1, leftcornerY + 1, SIZE - 2, SIZE - 2, BLOCK);
				} else {					//if number = 1 than there is a undestroyable block
					lcd.fillRect( leftcornerX, leftcornerY, SIZE, SIZE, OUTSIDE);
					/*
					for (int k = 0; k < 24; k++){
						for (int l = 0; l < 24; l++){
							lcd.drawPixel(leftcornerX + k, leftcornerY + l, OUTSIDE);
						}
					}
					*/
					
				}							//in case of number = 0 the background is already set so the screen does not need an update
			}
			leftcornerX = leftcornerX + SIZE;	//updates the leftcornerX for the next block
		}
		leftcornerX = 48;
		leftcornerY = leftcornerY + SIZE;
	}
}
/*
GameField::setLCD(lcd)
{
	MI0283QT9 lcd = lcd;
}
*/
