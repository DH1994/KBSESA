#include "Map.h"
#include "Arduino.h"

Map::Map(uint8_t* level_g){
  field = level_g;
}

uint8_t Map::getField(){
  return field;
}

uint8_t Map::getFieldValue(uint8_t x, uint8_t y){
  if(x == 10 || y ==12){
    return 1;
  } else{
    return field[x + (y*11)];
  }
}

void Map::setFieldValue(uint8_t x, uint8_t y, uint8_t value){
  field[x + (y*11)] = value;
}

