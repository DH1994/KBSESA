#include "Player.h"
#include "arduino.h"
#define SIZE 24
//#define DEBUG

Player::Player(){
	//Serial.begin(9600);
}
void Player::setPosition(uint8_t xPos_g, uint8_t yPos_g){
	xPos = xPos_g;
	yPos = yPos_g;
	xStep = 0;
	yStep = 0;
	stepsize = 3;
}

bool Player::updatePlayer(uint8_t dir, uint8_t FV_L, uint8_t FV_R, uint8_t FV_U, uint8_t FV_D){
	
	Serial.println("updatePlayer player");
	blockReset[0][0] = xPos;
	blockReset[0][1] = yPos;
	blockReset[1][0] = (xStep) ? (xPos + 1) : (xPos);
	blockReset[1][1] = (yStep) ? (yPos + 1) : (yPos);

	bool returnbool = false;

	switch (dir)
	{
		case 3:
			#ifdef DEBUG
			Serial.println("dir = 3 UP:\t");
			#endif
			if((xStep == 0)){			//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){
					if(!((FV_U == 1) || (FV_U == 2))){
						yPos--;
						yStep = SIZE - stepsize;
						returnbool = true;
					}
				} else {
					yStep -= stepsize;
					returnbool = true;
				}
			}
		break;

		case 4:
			#ifdef DEBUG
			Serial.println("dir = 4 DOWN:\t");
			#endif
			if((xStep == 0)){			//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){
					if(!((FV_D == 1) || (FV_D == 2))){
						yStep += stepsize;
						returnbool = true;
					}
				} else {
					if ((yStep + stepsize) == 24) {
						yPos++;
						yStep = 0;
						returnbool = true;
					} else {
						yStep += stepsize;
						returnbool = true;
					}
				}
			}
		break;

		case 1:
			
			#ifdef DEBUG
			Serial.println("dir = 1 LEFT:\t");
			#endif
			if(yStep == 0){
				if((xStep == 0)){
					if(!((FV_L == 1) || (FV_L == 2))){
						xPos--;
						xStep = SIZE - stepsize;
						returnbool = true;
					}
				} else {
					xStep -= stepsize;
					returnbool = true;
				}
			}
		break;

		case 2:
			
			#ifdef DEBUG
			Serial.println("dir = 3 RIGHT:\t");
			#endif
			if(yStep == 0){
				if((xStep == 0)){
					if(!((FV_R == 1) || (FV_R == 2))){
						xStep += stepsize;
						returnbool = true;
					}
				} else {
					if ((xStep + stepsize) == 24) {
						xPos++;
						xStep = 0;
						returnbool = true;
					} else {
						xStep += stepsize;
						returnbool = true;
					}
				}
			}
		break;
	}
	#ifdef DEBUG
	Serial.print("X:\t");
	Serial.print(xPos);
	Serial.print("\t");
	Serial.println(xStep);
	Serial.print("Y:\t");
	Serial.print(yPos);
	Serial.print("\t");
	Serial.println(yStep);
	Serial.print("bool");
	Serial.println(returnbool);
	#endif
	return returnbool;	
}

uint8_t Player::getBlockResetX(){
	return blockReset[0][0];
}
uint8_t Player::getBlockResetY(){
	return blockReset[0][1];
}
bool Player::getBlockResetOffsetX(){
	return (blockReset[0][0] > blockReset[1][0]) ? (true) : (false);
}
bool Player::getBlockResetOffsetY(){
	return (blockReset[0][1] > blockReset[1][1]) ? (true) : (false);
}
int Player::getxPosPx(){
	return (xPos * SIZE) + xStep;
}
int Player::getyPosPx(){
	return yPos * SIZE + yStep;
}
uint8_t Player::getxPos(){
	return xPos;
}
uint8_t Player::getyPos(){
	return yPos;
}



