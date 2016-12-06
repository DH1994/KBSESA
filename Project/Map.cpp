#include "Map.h"
#include "Arduino.h"

Map::Map(uint8_t level_g[9][11]){
	for(int y = 0; y < 9; y++){
		for(int x = 0; x < 11; x++){
			field[y][x] = level_g[y][x];
		}
	}
	//above code copies the given multi dimensional for preformance it can be replaced by a pointer
}

uint8_t Map::getFieldValue(uint8_t x, uint8_t y){
  if(y == 9 || x == 11){			//this can be replaced by enlarging the Map with one row and one column
    return 1;						//it is placed to ensure the player does not move out of the game field
  } else{
    return field[y][x];
  }
}

void Map::setFieldValue(uint8_t x, uint8_t y, uint8_t value){
  field[y][x] = value;
}

