#include "Player.h"
#include "arduino.h"
#define SIZE 24
//#define DEBUG

Player::Player(){
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
	Serial.println(FV_L);
	Serial.println(FV_R);
	Serial.println(FV_U);
	Serial.println(FV_D);
	switch (dir)
	{
		case 3:/*
			Serial.println("dir = UP");
				Serial.println("updatePlayer before");
				Serial.print("X:\t");
				Serial.print(xPos);
				Serial.print("\t");
				Serial.println(xStep);
				Serial.print("Y:\t");
				Serial.print(yPos);
				Serial.print("\t");
				Serial.println(yStep);*/
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
			/*
				Serial.println("updatePlayer after");
				Serial.print("X:\t");
				Serial.print(xPos);
				Serial.print("\t");
				Serial.println(xStep);
				Serial.print("Y:\t");
				Serial.print(yPos);
				Serial.print("\t");
				Serial.println(yStep);*/
		break;

		case 4:/*
			Serial.println("dir = DOWN");
				Serial.println("updatePlayer before");
				Serial.print("X:\t");
				Serial.print(xPos);
				Serial.print("\t");
				Serial.println(xStep);
				Serial.print("Y:\t");
				Serial.print(yPos);
				Serial.print("\t");
				Serial.println(yStep);*/
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
					/*yStep += stepsize;
					if(yStep >= 24){
						if(yPos < 8){
							yPos++;
							yStep = 0;
							
						} else {
							yStep -= stepsize;
						}
					} */
					/*
					if ((yStep + stepsize) >= 24) {
						if(yPos < 7){
							yPos++;
							yStep = 0;
							
						} else {
							yStep += stepsize;
						}
					} else {
						yStep += stepsize;
						
					}
					*/
				}
			}/*
				Serial.println("updatePlayer after");
				Serial.print("X:\t");
				Serial.print(xPos);
				Serial.print("\t");
				Serial.println(xStep);
				Serial.print("Y:\t");
				Serial.print(yPos);
				Serial.print("\t");
				Serial.println(yStep);*/
		break;

		case 1:
			Serial.println("dir = LEFT");
				Serial.println("updatePlayer before");
				Serial.print("X:\t");
				Serial.print(xPos);
				Serial.print("\t");
				Serial.println(xStep);
				Serial.print("Y:\t");
				Serial.print(yPos);
				Serial.print("\t");
				Serial.println(yStep);
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
			
				Serial.println("updatePlayer after");
				Serial.print("X:\t");
				Serial.print(xPos);
				Serial.print("\t");
				Serial.println(xStep);
				Serial.print("Y:\t");
				Serial.print(yPos);
				Serial.print("\t");
				Serial.println(yStep);
		break;

		case 2:
			
			Serial.println("dir = RIGHT");
				Serial.println("updatePlayer before");
				Serial.print("X:\t");
				Serial.print(xPos);
				Serial.print("\t");
				Serial.println(xStep);
				Serial.print("Y:\t");
				Serial.print(yPos);
				Serial.print("\t");
				Serial.println(yStep);
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
					/*
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
					*/
				}
			}
			
				Serial.println("updatePlayer after");
				Serial.print("X:\t");
				Serial.print(xPos);
				Serial.print("\t");
				Serial.println(xStep);
				Serial.print("Y:\t");
				Serial.print(yPos);
				Serial.print("\t");
				Serial.println(yStep);
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



