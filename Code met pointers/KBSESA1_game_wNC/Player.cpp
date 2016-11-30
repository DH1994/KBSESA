#include "Player.h"
#include "arduino.h"
#include "GameField.h"
#define SIZE 24
//#define DEBUG

Player::Player(NunchukLibrary* NC_g,){
  NC = NC_g;
}

void Player::setPosition(uint8_t xPos_g, uint8_t yPos_g){
	xPos = xPos_g;
	yPos = yPos_g;
	xStep = 0;
	yStep = 0;
	stepsize = 3;
}

bool Player::updatePlayer(uint8_t dir, uint8_t FV_L, uint8_t FV_R, uint8_t FV_U, uint8_t FV_D){
	bool returnbool = false;
	switch (dir)
	{
		case 3:
			if((xStep == 0)){			//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){
					if(!((FV_U == 1) || (FV_U == 2))){
						if(yPos > 0){
							yPos--;
							yStep = SIZE - stepsize;
							returnbool = true;
						}
					}
				} else {
					yStep -= stepsize;
					returnbool = true;
				}
			}
		break;

		case 4:
		  if((xStep == 0)){			//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){
					if(!((FV_D == 1) || (FV_D == 2))){
						yStep += stepsize;
						returnbool = true;
					}
				} else {
					yStep += stepsize;
					if (yStep == 24) {
						yStep = 0;
						yPos++;
					}
					returnbool = true;
				}
			}
		break;

		case 1:
			if(yStep == 0){
				if((xStep == 0)){
					if(!((FV_L == 1) || (FV_L == 2))){
						if(xPos > 0){
							xPos--;
							xStep = SIZE - stepsize;
							returnbool = true;
						}
					}
				} else {
					xStep -= stepsize;
					returnbool = true;
				}
			}
		break;

		case 2:
			if(yStep == 0){
				if((xStep == 0)){
					if(!((FV_R == 1) || (FV_R == 2))){
						xStep += stepsize;
						returnbool = true;
					}
				} else {
					xStep += stepsize;
					if (xStep >= 24) {
						xStep = 0;
						xPos++;
					}
					returnbool = true;
				}
			}
		break;
	}
	return returnbool;	
}

uint8_t Player::getxPos(){
	return xPos;
}
uint8_t Player::getyPos(){
	return yPos;
}
int Player::getxPosPx(){
	return (xPos * SIZE) + xStep;
}
int Player::getyPosPx(){
	return yPos * SIZE + yStep;
}
int Player::getOldXPosPx(){
	return oldXPos * SIZE + oldXStep;
}
int Player::getOldYPosPx(){
	return oldYPos * SIZE + oldYStep;
}
void Player::updatePos(){
	oldXPos = xPos;
	oldYPos = yPos;
	oldXStep = xStep;
	oldYStep = yStep;
}
