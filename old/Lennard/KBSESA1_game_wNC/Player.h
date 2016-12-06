#ifndef Player_h
#define Player_h
#include "Arduino.h"

class Player{
	public:
		Player();
		void setPosition(uint8_t xPos_g, uint8_t yPos_g);
		bool updatePlayer(uint8_t dir, uint8_t FV_L, uint8_t FV_R, uint8_t FV_U, uint8_t FV_D);
		uint8_t getxPos();
		uint8_t getyPos();
		int getxPosPx();
		int getyPosPx();
		int getOldXPosPx();
		int getOldYPosPx();
		void updatePos();
	private:
		uint8_t xPos, yPos;				//are the pixel coordinates of the topleft corner of the player
		uint8_t oldXPos, oldYPos;
		uint8_t oldXStep, oldYStep;
		uint8_t xStep, yStep;			//are the steps offset from xPos and yPos
		uint8_t stepsize;
};

#endif