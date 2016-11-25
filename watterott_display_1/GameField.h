// GameField.h
#include <MI0283QT9.h>
#include "Player.h"
class GameField {
	public:
		GameField(MI0283QT9 lcd_g, uint8_t game_g, Player playerA_g);
	private:
		uint8_t	game;
		MI0283QT9 lcd;
		Player playerA;
};

