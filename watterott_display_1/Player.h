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
		int xPos, yPos;				//are the pixel coordinates of the topleft corner of the player
};

#endif