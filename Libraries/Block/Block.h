// Block.h
/*
#ifndef _BLOCK_h
#define _BLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
*/
class Block{
	public:
		Block(uint16_t xPos_g, uint16_t yPos_g, uint16_t color_g);
		uint16_t[] getBlock();
		uint16_t getX();
		uint16_t getY();
		uint16_t getColor();
		/**int design[12][12]; design*/
	private:
		uint16_t xPos;
		uint16_t yPos;
		uint16_t color;
};
