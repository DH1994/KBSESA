#ifndef GameField_h
#define GameField_h

#include <MI0283QT9.h>

class GameField {
	public:
		GameField();
		void GFInit(MI0283QT9 lcd_g, uint8_t game_g);
		uint8_t getFieldValue(uint8_t x, uint8_t y);
		void updateGameField(int x, int y, int width, int height, int playerX, int playerY);
		uint8_t getPlayerX();
		uint8_t getPlayerY();
	private:
		uint8_t activeField[9][11];
		MI0283QT9 lcd;
		uint8_t playerX, playerY;
};
#endif
