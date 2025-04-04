/*
Universidad del Valle de Guatemala
IE2023 : Programación de Microcontroladores

prelab_4.c

Created: 4/4/2025 10:53:22 AM
Author : Adrián Fernández

Descripción: contador de 8 bits
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t contador = 0;

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
	PORTC = (PORTC & 0xF0) | ((contador >> 4) & 0x0F);
}

void setup()
{
	cli();
	
	// Se configuran puertos
	DDRD |= 0xFF;		// Puerto D es salida
	PORTD |= 0x00;
	
	DDRC |= 0xFF;		// Puerto C es salida
	PORTC |= 0x00;
	
	DDRB |= 0x0F;		// La mitad del puerto B es salida y la otra entrada
	PORTB |= ((1 << PORTB4) | (1 << PORTB5));
	
	// Se configuran las interrupciones
	PCMSK0 |= (1 << PORTB4) | (1 << PORTB5);
	PCICR |= (1 << PCIE0);

	sei();
}

ISR(PCINT0_vect)
{
	
	if (!(PINB & (1 << PORTB4)))
	{
		contador++;
	}
	if (!(PINB & (1 << PORTB5)))
	{
		contador--;
	}
}