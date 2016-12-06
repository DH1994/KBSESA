#ifndef Player_h
#define Player_h
#include "Arduino.h"
#include "NunchukLibrary.h"
#include "Map.h"

class Player{
	public:
		Player(NunchukLibrary* NC_g, Map* MP_g);
		void setPosition(uint8_t xPos_g, uint8_t yPos_g);	//this is called by gamefield to set the location based on the map design in Map.cpp
		bool updatePlayer();		//updates player positions with the values of the nunchuck
		int getxPosPx();			//returns the pixel position of xPos
		int getyPosPx();			//returns the pixel position of yPos
		int getOldXPosPx();			//returns the pixel position of the old xPos
		int getOldYPosPx();			//returns the pixel position of the old yPos
		void updatePos();			//updates the old position values with the current position values
   
	private:
		NunchukLibrary* NC;
		Map* MP;

		uint8_t xPos;				//Position on the X axis range 0 - 10	
		uint8_t yPos;				//Position on the Y axis range 0 - 8
		uint8_t xStep;				//Offset of xPos can range from 0 - 23 if xStep has a value higher than 0 yStep has to be 0 and vice versa
		uint8_t yStep;				//Offset op yPos can range from 0 - 23
		uint8_t oldXPos;			//Is the old position of the xPos is kept for resetting lcd
		uint8_t oldYPos;			//Is the old position of the yPos is kept for resetting lcd
		uint8_t oldXStep;			//is the old position of the xStep is kept for resetting lcd
		uint8_t oldYStep;		    //is the old position of the yStep is kept for resetting lcd
		uint8_t stepsize;			/*is the size the Player is moving, this variable can be changed to every number between 1 - 24 if 0 there will be no movement,
									with the only distriction being that 24 devided by stepsize cannot leave a remainder possible stepsize are:
									1 - 2 - 3 - 4 - 6 - 8 - 12 - 24*/
};

#endif
