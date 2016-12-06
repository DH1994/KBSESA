/*
  S65 LS020 Display Lib for Arduino
  by Watterott electronic (www.watterott.com)
 */

#include <inttypes.h>
#if (defined(__AVR__) || defined(ARDUINO_ARCH_AVR))
# include <avr/io.h>
# include <avr/pgmspace.h>
# include <util/delay.h>
#endif
#if ARDUINO >= 100
# include "Arduino.h"
#else
# include "WProgram.h"
#endif
#include "SPI.h"
#include "digitalWriteFast.h"
#include "GraphicsLib.h"
#include "S65LS020.h"


//#define SOFTWARE_SPI //use software SPI on pins MOSI:11, MISO:12, SCK:13

#if defined(SOFTWARE_SPI)
# define RST_PIN        17 //A3=17
# define CS_PIN         16 //A2=16
# define RS_PIN         4
# define MOSI_PIN       SPI_SW_MOSI_PIN
# define MISO_PIN       SPI_SW_MISO_PIN
# define SCK_PIN        SPI_SW_SCK_PIN
#else
# define RST_PIN        17 //A3=17
# define CS_PIN         16 //A2=16
# define RS_PIN         4
# define MOSI_PIN       SPI_HW_MOSI_PIN
# define MISO_PIN       SPI_HW_MISO_PIN
# define SCK_PIN        SPI_HW_SCK_PIN
#endif

#define RST_DISABLE()   digitalWriteFast(RST_PIN, HIGH)
#define RST_ENABLE()    digitalWriteFast(RST_PIN, LOW)

#define CS_DISABLE()    digitalWriteFast(CS_PIN, HIGH)
#define CS_ENABLE()     digitalWriteFast(CS_PIN, LOW)

#define RS_DISABLE()    digitalWriteFast(RS_PIN, HIGH)
#define RS_ENABLE()     digitalWriteFast(RS_PIN, LOW)

#define MOSI_HIGH()     digitalWriteFast(MOSI_PIN, HIGH)
#define MOSI_LOW()      digitalWriteFast(MOSI_PIN, LOW)

#define SCK_HIGH()      digitalWriteFast(SCK_PIN, HIGH)
#define SCK_LOW()       digitalWriteFast(SCK_PIN, LOW)


#ifndef LCD_WIDTH
# define LCD_WIDTH      (176)
# define LCD_HEIGHT     (132)
#endif


//-------------------- Constructor --------------------


S65LS020::S65LS020(void) : GraphicsLib(LCD_WIDTH, LCD_HEIGHT)
{
  return;
}


//-------------------- Public --------------------


void S65LS020::begin(uint_least8_t clock_div)
{
  //init pins
#if defined(RST_PIN)
  pinMode(RST_PIN, OUTPUT);
  RST_ENABLE();
#endif
  pinMode(CS_PIN, OUTPUT);
  pinMode(RS_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  CS_DISABLE();

#if !defined(SOFTWARE_SPI)
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  //SPI.setClockDivider(clock_div);
  SPI.begin();
#endif

  //SPI speed-down
#if !defined(SOFTWARE_SPI)
# if F_CPU >= 128000000UL
  SPI.setClockDivider(SPI_CLOCK_DIV64);
# elif F_CPU >= 64000000UL
  SPI.setClockDivider(SPI_CLOCK_DIV32);
# elif F_CPU >= 32000000UL
  SPI.setClockDivider(SPI_CLOCK_DIV16);
# elif F_CPU >= 16000000UL
  SPI.setClockDivider(SPI_CLOCK_DIV8);
# else //elif F_CPU >= 8000000UL
  SPI.setClockDivider(SPI_CLOCK_DIV4);
# endif
#endif

  //reset display
  reset();

  //SPI speed-up
#if !defined(SOFTWARE_SPI)
  SPI.setClockDivider(clock_div);
#endif

  return;
}


void S65LS020::begin(void)
{
  return begin(SPI_CLOCK_DIV4);
}


void S65LS020::led(uint_least8_t power)
{
  return;
}


void S65LS020::invertDisplay(uint_least8_t invert)
{
  wr_cmd(0xEF, 0xB0);
  if(invert == 0)
  {
    wr_cmd(0x49, 0x02);
  }
  else
  {
    wr_cmd(0x49, 0x03);
  }
  wr_cmd(0xEF, 0x90);
  wr_cmd(0x00, 0x00);

  return;
}


void S65LS020::setOrientation(uint_least16_t o)
{
  uint_least8_t p1, p5;

       if((o ==   9) || 
          (o ==  90))
  {
    lcd_orientation = 90;
    lcd_width  = LCD_HEIGHT;
    lcd_height = LCD_WIDTH;
    p1 = 0x00; //x0->x1, y0->y1
    p5 = 0x00; //0x04=rotate, 0x00=normal
  }

  else if((o ==  18) || 
          (o == 180))
  {
    lcd_orientation = 180;
    lcd_width  = LCD_WIDTH;
    lcd_height = LCD_HEIGHT;
    p1 = 0x80; //x0->x1, y1->y0
    p5 = 0x04; //0x04=rotate, 0x00=normal
  }

  else if((o ==  27) || 
          (o ==  14) || 
          (o == 270))
  {
    lcd_orientation = 270;
    lcd_width  = LCD_HEIGHT;
    lcd_height = LCD_WIDTH;
    p1 = 0xC0; //x1->x0, y1->y0
    p5 = 0x00; //0x04=rotate, 0x00=normal
  }

  else
  {
    lcd_orientation = 0;
    lcd_width  = LCD_WIDTH;
    lcd_height = LCD_HEIGHT;
    p1 = 0x40; //x1->x0, y0->y1
    p5 = 0x04; //0x04=rotate, 0x00=normal
  }

  wr_cmd(0xEF, 0x90);
  wr_cmd(0x01, p1);
  wr_cmd(0x05, p5);

  setArea(0, 0, lcd_width-1, lcd_height-1);

  return;
}


void S65LS020::setArea(int_least16_t x0, int_least16_t y0, int_least16_t x1, int_least16_t y1)
{
  wr_cmd(0xEF, 0x90);

  switch(lcd_orientation)
  {
    case 0:
      wr_cmd(0x08, y0);                //set y0
      wr_cmd(0x09, y1);                //set y1
      wr_cmd(0x0A, (LCD_WIDTH-1)-x0);  //set x0
      wr_cmd(0x0B, (LCD_WIDTH-1)-x1);  //set x1
      wr_cmd(0x06, y0);                //set y cursor pos
      wr_cmd(0x07, (LCD_WIDTH-1)-x0);  //set x cursor pos
      break;
    case 90:
      wr_cmd(0x08, x0);                //set x0
      wr_cmd(0x09, x1);                //set x1
      wr_cmd(0x0A, y0);                //set y0
      wr_cmd(0x0B, y1);                //set y1
      wr_cmd(0x06, x0);                //set y cursor pos
      wr_cmd(0x07, y0);                //set x cursor pos
      break;
    case 180:
      wr_cmd(0x08, (LCD_HEIGHT-1)-y0); //set y0
      wr_cmd(0x09, (LCD_HEIGHT-1)-y1); //set y1
      wr_cmd(0x0A, x0);                //set x0
      wr_cmd(0x0B, x1);                //set x1
      wr_cmd(0x06, (LCD_HEIGHT-1)-y0); //set y cursor pos
      wr_cmd(0x07, x0);                //set x cursor pos
      break;
    case 270:
      wr_cmd(0x08, (LCD_HEIGHT-1)-x0);  //set x0
      wr_cmd(0x09, (LCD_HEIGHT-1)-x1);  //set x1
      wr_cmd(0x0A, (LCD_WIDTH-1)-y0); //set y0
      wr_cmd(0x0B, (LCD_WIDTH-1)-y1); //set y1
      wr_cmd(0x06, (LCD_HEIGHT-1)-x0);  //set x cursor pos
      wr_cmd(0x07, (LCD_WIDTH-1)-y0); //set y cursor pos
      break;
  }

  return;
}


void S65LS020::drawStart(void)
{
  RS_ENABLE(); //data
  CS_ENABLE();

  return;
}


void S65LS020::draw(uint_least16_t color)
{
  wr_spi(color>>8);
  wr_spi(color);

  return;
}


void S65LS020::drawStop(void)
{
  CS_DISABLE();

  return;
}


//-------------------- Private --------------------


const uint8_t initdataLS020[] PROGMEM = 
{
  //init
  0x40| 2, 0xFD, 0xFD,
  0x40| 2, 0xFD, 0xFD,
  0xC0|50, //50ms
  //init 1
  0x40| 2, 0xEF, 0x00,
  0x40| 2, 0xEE, 0x04,
  0x40| 2, 0x1B, 0x04,
  0x40| 2, 0xFE, 0xFE,
  0x40| 2, 0xFE, 0xFE,
  0x40| 2, 0xEF, 0x90,
  0x40| 2, 0x4A, 0x04,
  0x40| 2, 0x7F, 0x3F,
  0x40| 2, 0xEE, 0x04,
  0x40| 2, 0x43, 0x06,
  0xC0| 7, //important 7ms
  //init 2
  0x40| 2, 0xEF, 0x90,
  0x40| 2, 0x09, 0x83,
  0x40| 2, 0x08, 0x00,
  0x40| 2, 0x0B, 0xAF,
  0x40| 2, 0x0A, 0x00,
  0x40| 2, 0x05, 0x00,
  0x40| 2, 0x06, 0x00,
  0x40| 2, 0x07, 0x00,
  0x40| 2, 0xEF, 0x00,
  0x40| 2, 0xEE, 0x0C,
  0x40| 2, 0xEF, 0x90,
  0x40| 2, 0x00, 0x80,
  0x40| 2, 0xEF, 0xB0,
  0x40| 2, 0x49, 0x02,
  0x40| 2, 0xEF, 0x00,
  0x40| 2, 0x7F, 0x01,
  0x40| 2, 0xE1, 0x81,
  0x40| 2, 0xE2, 0x02,
  0x40| 2, 0xE2, 0x76,
  0x40| 2, 0xE1, 0x83,
  0xC0|50, //50ms
  //display on
  0x40| 2, 0x80, 0x01,
  0x40| 2, 0xEF, 0x90,
  0x40| 2, 0x00, 0x00,
  0xC0|10, //10ms
  //display options
  0x40| 2, 0xEF, 0x90,
  0x40| 2, 0x01, 0x40, //x1->x0, y0->y1
  0x40| 2, 0x05, 0x04, //0x04=rotate, 0x00=normal
  0x40| 2, 0x08, 0,           //set y0
  0x40| 2, 0x09, LCD_HEIGHT-1,//set y1
  0x40| 2, 0x0A, LCD_WIDTH-1, //set x0
  0x40| 2, 0x0B, 0,           //set x1
  0x40| 2, 0x06, 0,           //set y cursor pos
  0x40| 2, 0x07, LCD_WIDTH-1, //set x cursor pos
  0xFF   , 0xFF
};


void S65LS020::reset(void)
{
  uint_least8_t c, d, i;
  const PROGMEM uint8_t *ptr;

  //reset
  CS_DISABLE();
  RS_DISABLE();
#if defined(RST_PIN)
  RST_ENABLE();
  delay(50);
  RST_DISABLE();
  delay(120);
#endif

  //send init commands and data
  ptr = &initdataLS020[0];
  while(1)
  {
    c = pgm_read_byte(ptr++);
    if(c == 0xFF) //end of data
    {
      break;
    }
    switch(c&0xC0)
    {
      case 0x40: //command + data
        for(i=c&0x3F; i!=0; i-=2)
        {
          c = pgm_read_byte(ptr++);
          d = pgm_read_byte(ptr++);
          wr_cmd(c, d);
        }
        break;
      case 0xC0: //delay
        c = c&0x3F;
#if defined(__AVR__)
        if(c == 7)
        {
          _delay_ms(7); //very important
        }
        else
        {
          delay(c);
        }
#else
        delay(c);
#endif
        break;
    }
  }

  //clear display buffer
  fillScreen(0);

  return;
}


void S65LS020::wr_cmd(uint_least8_t cmd, uint_least8_t param)
{
  RS_DISABLE(); //cmd
  CS_ENABLE();
  wr_spi(cmd);
  wr_spi(param);
  CS_DISABLE();

  return;
}


void S65LS020::wr_spi(uint_least8_t data)
{
#if defined(SOFTWARE_SPI)
  for(uint_least8_t mask=0x80; mask!=0; mask>>=1)
  {
    SCK_LOW();
    if(mask & data)
    {
      MOSI_HIGH();
    }
    else
    {
      MOSI_LOW();
    }
    SCK_HIGH();
  }
  SCK_LOW();
#else
  SPI.transfer(data);
#endif
  return;
}
