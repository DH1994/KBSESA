#ifndef GameField_h
#define GameField_h

#include <MI0283QT9.h>
#include "Map.h"

class GameField {
	public:
		GameField(MI0283QT9* lcd_g, Map* mp);
		void GFInit(uint8_t game_g);
		void updateGameField(int x, int y, int width, int height, int playerX, int playerY);
		uint8_t getPlayerX();
		uint8_t getPlayerY();
   
	private:
    MI0283QT9* lcd;
    Map* mp;
		uint8_t playerX, playerY;
};
#endif
