#include "Player.h"
#include "arduino.h"
Player::Player(){
	
}
void Player::setPosition(int xPos_g, int yPos_g){
	xPos = xPos_g;
	yPos = yPos_g;
}

int Player::getxPos(){
	return xPos;
}

int Player::getyPos(){
	return yPos;
}



