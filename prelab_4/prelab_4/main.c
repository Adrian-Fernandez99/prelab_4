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

void setup()
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
	DDRB &= ~((1 << PORTB4) | (1 << PORTB5));
	//PORTC |= (1 << PC0) | (1 << PC1);

}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

