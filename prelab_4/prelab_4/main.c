/*
Universidad del Valle de Guatemala
IE2023 : Programación de Microcontroladores

prelab_4.c

Created: 4/4/2025 10:53:22 AM
Author : Adrián Fernández

Descripción: contador de 8 bits
 */ 

// Librerias
#include <avr/io.h>
#include <avr/interrupt.h>

// Se definen variables
volatile uint8_t contador = 0;

// Prototipo de funciones
void setup();
void cont_8bits();

// Main loop
int main(void)
{
	// Se llama función para setear
   setup();
	
	// Se inicia el loop
    while (1) 
    {
		// Se llama función para mostrar contador
		cont_8bits();
    }
}

// NON-Interrupt subroutines
// Función para mostrar el contador
void cont_8bits()
{
	PORTB = (PORTB & 0xF0) | (contador & 0x0F); // se muestra el purto B los primeros 4 bits
	PORTC = (PORTC & 0xF0) | ((contador >> 4) & 0x0F); // se mueven los 4 bits menos significativos a la derecha y se muestran
}

// Función para setear
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

// Interrupt routines
// Interrupción de pinchange
ISR(PCINT0_vect)
{
	// Si el pin está encendido en el pin 4 incrementa
	if (!(PINB & (1 << PORTB4)))
	{
		contador++;
	}
	// Si el pin está encendido en el pin 5 decrementa
	if (!(PINB & (1 << PORTB5)))
	{
		contador--;
	}
}