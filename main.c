/*
 * CSE412FinalProject.c
 *
 * Created: 7/27/2021 12:15:56 AM
 * Author : Karthik Malyala
 */ 

#define F_CPU 16000000UL // Internal Clock Speed
#include <avr/io.h>
#include <util/delay.h>

// Declares the functions that receive input from the mobile app using USART
void USART_Init(unsigned int);
unsigned int USART_Receive(void);

#define LED PORTB
#define BAUD 9600
// Sets asynchronous normal mode (U2XN = 0) (103)
#define BAUD_PRESCALE ((F_CPU / (BAUD * 16UL)) - 1) 

int main(void)
{
	// Variable to receive user's input from mobile app
	unsigned int usrInput;
	// Make Port B as the output for the nightlight
	DDRB = 0xff;	
	// Initialize USART with 9600 Baud Rate and appropriate prescaler					
	USART_Init(BAUD);		
	// Initially, the LEDs are turned off				
	LED = 0;
	
	// Set up Timer/Counter control registers for the following:
	// 1. Fast PWM Mode (with WGM11, WGM12, WGM13 all set to 1)
	// 2. Set OC1A at Bottom for non-inverting mode (with COM1A1 set to 1)
	// 3. Set the clock prescaler to 8 (CS11 to 1)
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);

	// Sets the PWM period using the ICR1 register. For a 16 MHz clock, 3999 is ideal period
	ICR1 = 39999;

	// Offset variable used to manipulate the angle of the servo upon receiving input from app
	int offset = 450;
	
	// Infinite loop that keeps taking requests from app
	while(1)
	{
		// Receives the data from the app using USART
		usrInput = USART_Receive();			
		// Enters a switch structure to operate the servo and LEDs with a specific instruction for the input received
		switch(usrInput)
		{
			// When user presses ON(1) in the app, this case will turn the servo up to turn ON the switch
			// Then, the LEDs are sequentially turned OFF because the light switch has been turned ON
			case 0: OCR1A = 3999 - offset; // Changes duty cycle for PWM of servo
					_delay_ms(100);
					LED &= ~(1<<PB4);
					_delay_ms(100);
					LED &= ~(1<<PB3);
					_delay_ms(100);
					LED &= ~(1<<PB2);
					_delay_ms(100);
					LED &= ~(1<<PB0);
					break;
			// When user presses OFF(0) in the app, this case will turn the servo down to turn OFF the switch
			// Then, the LEDs are sequentially turned ON because the light switch has been turned OFF
			case 1: OCR1A = 3900 + offset; // Changes duty cycle for PWM of servo
					_delay_ms(100);
					LED |= (1<<PB0);
					_delay_ms(100);
					LED |= (1<<PB2);
					_delay_ms(100);
					LED |= (1<<PB3);
					_delay_ms(100);
					LED |= (1<<PB4);
					break;
			// By default, all the LEDs are turned off
			default: LED &= ~(1<<PB0);
					 LED &= ~(1<<PB2);
					 LED &= ~(1<<PB3);
					 LED &= ~(1<<PB4);
					 break;
		}
	}
}

// Function that initializes USART with the appropriate baud rate
void USART_Init(unsigned int BAUDRATE)	
{
	// Sets the Baud Rate
	UBRR0H = (unsigned char) (BAUD_PRESCALE >> 8);
	UBRR0L = (unsigned char) (BAUD_PRESCALE);
	// Enables the receiver and transmitter for reading input from mobile app
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);	
	// Sets frame format: 8 data bits, 1 stop bit			
	UCSR0C = (1<<USBS0) | (1<<UCSZ00) | (1<<UCSZ01);
}

// Function that receives data
unsigned int USART_Receive(void)						
{
	// Waits for data to be received
	while (!(UCSR0A & (1 << RXC0)));
	// Gets and returns the received data from the buffer
	return(UDR0);			
}
