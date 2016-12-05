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

GameField::GameField(MI0283QT9* lcd_g, Map* mp_g, Player* pl_nc_g){
  lcd = lcd_g;
  mp = mp_g;
  pl_nc = pl_nc_g;
  lcd->fillScreen(OUTSIDE);				//resets the screen
  int leftcornerX = 48;					//is the x-as corner of the block starting by x and y as 0 of the playing field
  int leftcornerY = 13;					//is the y-as corner of the block starting by x and y as 0 of the playing field
  lcd->fillRect( leftcornerX, leftcornerY, 11*SIZE, 9*SIZE, FIELD);

  for(uint8_t y = 0; y < 9; y++)
  {
	  for(uint8_t x = 0; x < 11; x++)			//those loops are looping through the whole playing field
	  {
		  switch(mp->getFieldValue(x, y)){
			  case 1:			//undestroyable block
			  lcd->fillRect( leftcornerX, leftcornerY, SIZE, SIZE, OUTSIDE);
			  break;

			  case 2:			//destroyable block
			  lcd->fillRect( leftcornerX, leftcornerY, SIZE, SIZE, BLOCK);
			  break;

			  case 3:			//player (Nunchuck)
			  lcd->fillRect(leftcornerX, leftcornerY, SIZE, SIZE, PLAYERA);
			  pl_nc->setPosition(x, y);			//update player position so it is able to move
			  mp->setFieldValue(x,y,0);			//update map so the place the player is standing on is 0 needed for updating lcd
			  break;

			  case 4:			//player (received by IRCOM)
			  lcd->fillRect(leftcornerX, leftcornerY, SIZE, SIZE, PLAYERA);
			  mp->setFieldValue(x,y,0);			//update map so the place the player is standing on is 0 needed for updating lcd
			  break;
		  }
		  leftcornerX = leftcornerX + SIZE;	//updates the leftcornerX for the next block so the next row can be filled
	  }
	  leftcornerX = OFFSETX;
	  leftcornerY = leftcornerY + SIZE;
  }
}
/************************************************************************/
/* for information about what those functions are doing see GameField.h */
/************************************************************************/
void GameField::updateGameField_pl_nc(){
	lcd->fillRect(pl_nc->getOldXPosPx() + OFFSETX, pl_nc->getOldYPosPx() + OFFSETY, SIZE, SIZE, FIELD);	//draw background
	lcd->fillRect(pl_nc->getxPosPx() + OFFSETX, pl_nc->getyPosPx() + OFFSETY, SIZE, SIZE, PLAYERA);		//draw player
	pl_nc->updatePos();		//update player so the old position is the current position
}
