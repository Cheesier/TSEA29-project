/*
 * testApplication.c
 *
 * Created: 2014-11-03 12:58:58
 *  Author: Jonathan
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#define LED 0

int main(void)
{
	DDRB = 0xFF;
    while(1)
    {
		PORTB |= (1<<LED);
		_delay_ms(100);         // delay 100 ms
		PORTB &= ~(1<<LED);
		_delay_ms(900);         // delay 700 ms
    }
}