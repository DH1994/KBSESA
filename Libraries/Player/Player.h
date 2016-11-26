#ifndef Player_h
#define Player_h

class Player{
	public:
		Player(/*nunchuck*/);
		//Player(/*IRCommuncation*/);
		void setPosition(int xPos_g, int yPos_g);
		int getxPos();
		int getyPos();
	private:
		uint8_t xPos, yPos;			//block where player is standing on
		uint8_t xStep, yStep;		//is the number of steps ofset from xPos and Ypos it is the offset down and right
					//are the pixel coordinates of the topleft corner of the player
};

#endif