#include "Nunchuk.h"
#include "Arduino.h"
#include <Wire.h>
#include "GraphicsLib.h"
#include <MI0283QT9.h>
#define ADDRESS 0x52

MI0283QT9 lcd;
NunchukLibrary NC;

volatile uint8_t timer2_counter;    //DIT IS DE TIMER DOMME KUT
char tmp[128];

static uint16_t last_x=0, last_y=0; //The 8 bit variables where the previous location of the player is stored
static uint16_t current_x=160, current_y=115; //The start location of the player


int main(){
	Serial.begin(9600);
	Serial.println("Start");
	init();
	lcd.begin();
	NC.ANinit();

	//clear screen
	lcd.fillScreen(RGB(255,255,255));

  //Setup timer2
	TCNT2   = 0;
	TCCR2B |= (1 << WGM21);   // Configure timer 2 for CTC mode
	TCCR2B |= (1 << CS22);    // Start timer at Fcpu/64
	TIMSK2 |= (1 << OCIE2A); // Enable CTC interrupt
	OCR2A   = 120; // Set CTC compare value with a prescaler of 64
	sei();
	
	while(1){
		NC.ANupdate();
		NC.UpdateLocation();
		
		sprintf(tmp, "X:%03i Y:%03i", current_x, current_y);

		if((last_x != current_x) || (last_y != current_y)){           //Check if the player location has changed
			lcd.drawText(50, 2, tmp, RGB(0,0,0), RGB(255,255,255), 1);  
			lcd.fillCircle(last_x, last_y, 4, RGB(255,255,255));        //Erese previous circle
			lcd.drawCircle(current_x, current_y, 3, RGB(0,0,0));        //Draw current cursor
			last_x = current_x;
			last_y = current_y;
		}

		if(NC.zButton != 0){                                          //Clear screen when z is pressed
			lcd.fillScreen(RGB(255,255,255));
		}
	}
};

ISR(TIMER2_COMPA_vect)        // interrupt service routine
{
	TCNT2 = timer2_counter;   // preload timer
	cursorMovement();         //Update the location of the player at a certain interfall
}

void cursorMovement(){      //Update the players location
	switch(NC.status){
		case 1: current_x-=1;			break;//MOVE LEFT
		case 2: current_x+=1;			break;//MOVE RIGHT
		case 3: current_y-=1;			break;//MOVE UP
		case 4: current_y+=1;			break;//MOVE DOWN
		default: current_x=current_x;	break;//DONT MOVE
	}
}
