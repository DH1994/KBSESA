#include "Player.h"
#include "arduino.h"
#include "Map.h"

#define SIZE 24				//is the size of one block

Player::Player(NunchukLibrary* NC_g, Map* MP_g){
  NC = NC_g;
  MP = MP_g;
}

void Player::setPosition(uint8_t xPos_g, uint8_t yPos_g){
	xPos = xPos_g;
	yPos = yPos_g;
	oldXPos = xPos_g;
	oldYPos = xPos_g;
	xStep = 0;
	yStep = 0;
	stepsize = 4;
}

bool Player::updatePlayer(){
	bool returnbool = false;
	/*
	if((xPos + yPos) == 0){
		//check if block contains a power up
	}
	*/
	switch (NC->getStatus())							//switches to the direction the nunchuck is positioned options are left - right - up - down
	{

		case 1:											//LEFT
			if(yStep == 0){								//checks if their is an ability to move up or down because of the offset on the other axis
				if((xStep == 0)){						//checks if the player is entering a new block 
					if(!((MP->getFieldValue(xPos - 1, yPos) == 1) || (MP->getFieldValue(xPos - 1, yPos) == 2))){		//checks if the block where the player is moving to can be entered
						if(xPos > 0){					//checks if player is not moving out of the field
							xPos--;						//update position
							xStep = SIZE - stepsize;
							returnbool = true;			//makes sure updatePlayer can give feedback to main about movement
						}
					}
				} else {
					xStep -= stepsize;					//updates step (position)
					returnbool = true;					//makes sure updatePlayer can give feedback to main about movement
				}
			}
		break;

		case 2:											//RIGHT
			if(yStep == 0){								//checks if their is an ability to move up or down because of the offset on the other axis
				if((xStep == 0)){						//checks if the player is entering a new block 
					if(!((MP->getFieldValue(xPos + 1, yPos) == 1) || (MP->getFieldValue(xPos + 1, yPos) == 2))){		//checks if the block where the player is moving to can be entered
						xStep += stepsize;				//updates step (position)
						returnbool = true;				//makes sure updatePlayer can give feedback to main about movement
					}
				} else {
					xStep += stepsize;					//updates step (position)
					if (xStep >= 24) {					//if step update means that player has entered a block without offset  
						xStep = 0;						//update position
						xPos++;
					}
					returnbool = true;					//makes sure updatePlayer can give feedback to main about movement
				}
			}
		break;

		case 3:											//UP
			if((xStep == 0)){							//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){							//checks if the player is entering a new block 
					if(!((MP->getFieldValue(xPos, yPos - 1) == 1) || (MP->getFieldValue(xPos, yPos - 1) == 2))){		//checks if the block where the player is moving to can be entered
						if(yPos > 0){
							yPos--;						//update position
							yStep = SIZE - stepsize;
							returnbool = true;			//makes sure updatePlayer can give feedback to main about movement
						}
					}
				} else {
					yStep -= stepsize;					//updates step (position)
					returnbool = true;					//makes sure updatePlayer can give feedback to main about movement
				}
			}
		break;

		case 4:											//DOWN			
		  if((xStep == 0)){								//checks if their is an ability to move up or down because of the offset on the other axis
				if(yStep == 0){							//checks if the player is entering a new block 
					if(!((MP->getFieldValue(xPos, yPos + 1) == 1) || (MP->getFieldValue(xPos, yPos + 1) == 2))){		//checks if the block where the player is moving to can be entered
						yStep += stepsize;				//updates step (position)
						returnbool = true;				//makes sure updatePlayer can give feedback to main about movement
					}
				} else {
					yStep += stepsize;					//updates step (position)
					if (yStep >= 24) {					//if step update means that player has entered a block without offset 
						yStep = 0;						//update position
						yPos++;
					}
					returnbool = true;					//makes sure updatePlayer can give feedback to main about movement
				}
			}
		break;
		
	}
	return returnbool;	//is return true if the players position has been updated
}
/************************************************************************/
/* Check player.h for information about those functions                 */
/************************************************************************/
int Player::getxPosPx(){
	
	return xPos * SIZE + xStep;
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
