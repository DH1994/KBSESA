#include "NunchukLibrary.h"
#include "Arduino.h"
#include "Wire.h"
#include "MI0283QT9.h"
#define ADDRESS 0x52


//Send data throug i2c
void NunchukLibrary::AN_sendByte(uint8_t data, uint8_t location)
{
  Wire.beginTransmission(ADDRESS);

  Wire.write(location);
  Wire.write(data);

  Wire.endTransmission();

  _delay_ms(10);
}

//Request data from the nunchuk
void NunchukLibrary::ANinit()
{
  Wire.begin();

  AN_sendByte(0x55, 0xF0);
  AN_sendByte(0x00, 0xFB);

  _delay_ms(100);
  //Calibrate the nunchuk
  ANupdate();
  ANupdate();
  beginPossX = analogX;           
  beginPossY = analogY;
}

//Update the values of the nunchuk
void NunchukLibrary::ANupdate()
{
  int count = 0;
  int values[6];

  Wire.requestFrom(ADDRESS, 6);

  while(Wire.available())
  {
    values[count] = Wire.read();
    count++;
  }
//Put the values in variables
  analogX = values[0];
  analogY = values[1];
  accelX = (values[2] << 2) | ((values[5] >> 2) & 3);
  accelY = (values[3] << 2) | ((values[5] >> 4) & 3);
  accelZ = (values[4] << 2) | ((values[5] >> 6) & 3);
  zButton = !((values[5] >> 0) & 1);
  cButton = !((values[5] >> 1) & 1);

  AN_sendByte(0x00, 0x00);
}
//Check in what direction the nunchuk tumbstick is moved and give it to the variable "status"
void NunchukLibrary::UpdateLocation()
{
if((analogX - beginPossX) > 5)		status = 2;//X AXIS RIGHT
else if((beginPossX - analogX) > 5) status = 1;//X AXIS LEFT
else									status = 0;//X AXIS NO MOVEMENT

if((analogY - beginPossY) > 5)		status = 3;//Y AXIS UP
else if((beginPossY - analogY) > 5) status = 4;//Y AXIS DOWN
}
