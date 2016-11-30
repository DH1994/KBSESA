#include "Map.h"
#include "Arduino.h"

Map::Map(uint8_t* field_g){
  field = field_g;
}

uint8_t Map::getField(){
  return field;
}

uint8_t Map::getFieldValue(uint8_t x, uint8_t y){
  if(x > 250 || y > 250){
    return 2;
  } else(
    return field[x][y];
}

void Map::setFieldValue(uint8_t x, uint8_t y, uint8_t value){
  field[x][y] = value;
}

