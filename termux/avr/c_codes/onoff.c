//Turns LED on and off
#include <avr/io.h>
#include <util/delay.h>

 
int main (void)
{
	
	
  /* Arduino boards have a LED at PB5 */
 //set PB5, pin 13 of arduino as output
  DDRB    |= ((1 << DDB5));
  while (1) {
//turn led on    
    PORTB = ((0 <<  PB5));

//turn led off
//    PORTB = ((1 <<  PB5));
  }

  /* . */
  return 0;

}
//Run the following command in the terminal
// to flash the hex file
//make FNAME=onoff
