#ifndef Map_h
#define Map_h


class Map{
  public:
    Map(uint8_t *Field[10][12]);
    uint8_t getField();
    uint8_t getFieldValue(uint8_t x, uint8_t y);
    void setFieldValue(uint8_t x, uint8_t y, uint8_t value);
    
  private:
    uint8_t* field[10][12];
};
#endif
