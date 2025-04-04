/*
Universidad del Valle de Guatemala
IE2023 : Programación de Microcontroladores

prelab_4.c

Created: 4/4/2025 10:53:22 AM
Author : adria

Descripcion: contador de 8 bits
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t contador = 0;
volatile uint8_t boton = 0;

void setup();
void cont_8bits();

int main(void)
{
   setup();
	
    while (1) 
    {
		cont_8bits();
    }
}

void cont_8bits()
{
	PORTB = (PORTB & 0xF0) | (contador & 0x0F);
	PORTB = (PORTB & 0xF0) | (contador & 0xF0);
}

void setup()
{
	cli();
	
	DDRD = 0xFF;
	PORTD = 0x00;
	
	DDRB &= ~((1 << PORTB4) | (1 << PORTB5));
	PORTB |= ((1 << PORTB4) | (1 << PORTB5));
	
	PCMSK0 |= ~((1 << PORTB4) | (1 << PORTB5));
	PCICR |= (1 << PCIE0);
	
	DDRD = 0x00;
	PORTD = 0xFF;

	sei();
}

ISR(PCINT0_vect)
{
	uint8_t boton = PINB & ((1 << PORTB4) | (1 << PORTB5));
	
	if (!(boton & (1 << PORTB4)))
	{
		contador++;
	}
	if (!(boton & (1 << PORTB5)))
	{
		contador--;
	}
}