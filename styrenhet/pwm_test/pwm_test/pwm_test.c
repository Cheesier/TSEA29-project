#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define Timer_0 TCCR0
#define Timer_1A TCCR1A
#define Timer_1B TCCR1B

int main(void){
	/************************************************************************/
	//	TCCR0, 8-bit counter, page 77
	//	Controls TEH CLAW
	//	WGM decides the pwm mode			| WGM00 & WGM01 => fast pwm
	//	CS sets the prescaler				| CS02 & CS00 => CLK/1024
	//	COM sets the compare output mode	| COM01 => Clear OC0 on match, set on BOTTOM
	/************************************************************************/
	Timer_0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS02) | (1 << CS00);
	DDRB |= (1 << PORTB3); //sets OC0 as output
	
	/************************************************************************/
	//	TCCR1A:B, 16-bit counter (running as 8-bit counter), page 104
	//	Controls the wheel servos
	//	WGM decides the pwm	mode			| WGM10 & WGM12 => fast pwm, 8-bit
	//	CS sets the prescaler				| CS12 & CS10 => CLK/1024
	//	COM sets the compare output mode	| COM1A1 & COM1B1 => Clear OC1A:B on match, set on BOTTOM
	/************************************************************************/
	Timer_1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	Timer_1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	DDRD |= (1 << PORTD4) | (1 << PORTD5); //sets 0C1A:B as outputs
	
	
	
	while(1){
		OCR0 = 13;
		OCR1AL = 13;
		OCR1BL = 13;
		
		_delay_ms(4000);
		
		OCR0 = 6;
		OCR1AL = 6;
		OCR1BL = 6;
		
		
		_delay_ms(4000);
	}
	return 0;
}