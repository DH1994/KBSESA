// 
// 
// 

#include "Block.h"

Block::Block(uint16_t xPos_g, uint16_t yPos_g, uint16_t color_g){
	xPos = xPos_g;
	yPos = yPos_g;
	color = color_g;
}

uint16_t Block::getX(){
	return xPos;
}

uint16_t Block::getY(){
	return yPos;
}
uint16_t Block::getColor(){
	return color;
}

