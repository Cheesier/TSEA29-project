#include <avr/io.h>
//#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "bluetooth.h"
#include "message_handler.h"

//This function is used to initialize the USART
//at a given UBRR value
void bt_init(void)
{
	/* 
		Baud rate = 19200bps
		UBRR value = 3
	*/

	UBRRL = 3;
	UBRRH = (3>>8);

	/*Set Frame Format

	>> Asynchronous mode
	>> No Parity
	>> 1 StopBit

	>> char size 8
	*/

	UCSRC=(1<<URSEL)|(3<<UCSZ0); // 8 bit

	//Enable The receiver and transmitter

	UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);


}


//This function is used to read the available data
//from USART. This function will wait until data is
//available.
char USARTReadChar(void)
{
	//Wait until a data is available

	while(!(UCSRA & (1<<RXC)))
	{
		//Do nothing
	}

	//Now USART has got data from host
	//and is available is buffer

	return UDR;
}


//This function writes the given "data" to
//the USART which then transmit it via TX line
void USARTWriteChar(char data)
{
	//Wait until the transmitter is ready

	while(!(UCSRA & (1<<UDRE)))
	{
		//Do nothing
	}

	//Now write the data to USART buffer

	UDR=data;
}

void bt_send(char header, char size, char *data) {
	// check so that we are only trying to send data to control center
	// (The only BT device)
	if (header >> 6 == 0x11) {
		USARTWriteChar(header);
		USARTWriteChar(size);
		for (int i = 0; i < size; i++)
			USARTWriteChar(((char*)data)[i]);
	}
	// not sure how to handle the other cases
	// maybe send a message to the control center?
}


/*
//interrupt when receive bluetooth message, and returns it
ISR(USARTRXC_vect){	   
	char header;
	char size;
	char data[10];

	//Read data
	header = UDR;
	size = USARTReadChar();
	for (int i = 0; i < size; i++) {
		data[i] = USARTReadChar();
	}
	USARTWriteChar(header);
	USARTWriteChar(size);
		
	for (int i = 0; i < size; i++) {
		USARTWriteChar(data[i]);
	}
}
*/

//interrupt when receive bluetooth message, and returns it
ISR(USARTRXC_vect){
	char header;
	char size;
	char data[10];

	//Read data
	header = UDR;
	size = USARTReadChar();
	for (int i = 0; i < size; i++) {
		data[i] = USARTReadChar();
	}
	
	handle_message(header, size, (char*)&data);
}