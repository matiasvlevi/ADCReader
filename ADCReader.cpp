#include "ADCReader.h"

#include <avr/io.h>

ADCReader::ADCReader() 
{
	ADMUX = 0;

	// Enable ADC
	ADCSRA = (1<<ADEN);
}
	
uint8_t ADCReader::trailing_zeros_count(uint8_t value) 
{
	uint8_t count = 0;
	while(!(value & 1)) {
		value >>= 1;
		count++;
	}
	return count & 0x07;
}

void ADCReader::setReference(uint8_t option) 
{
	// Set option value range(0,3) and shift it to REFS0 
	ADMUX |= (option & 0x03) << REFS0;
}
	
void ADCReader::setPrescaler(uint8_t division_factor)
{
	// 
	ADCSRA |= ADCReader::trailing_zeros_count(division_factor);
}

void ADCReader::setSingleEnded()
{
	// Set MUX4:3 to 0
	ADMUX &= ~((1 << MUX4) | (1 << MUX3));
}
	
void ADCReader::setChannel(uint8_t channel)
{
	// Limit channel to 16
	channel &= 0x0F;
		
	// MUX4:0 Bits for channels 0 to 7
	ADMUX |= channel & 0x07;
		
	// MUX5 Bit for channels 8 to 15
	ADCSRB |= channel & 0x08;
}


void ADCReader::startConversion()
{
	ADCSRA |= (1<<ADSC);
}

void ADCReader::waitForConversion() 
{
	while(ADCSRA & (1<<ADSC));
}
	
uint16_t ADCReader::get() 
{
	startConversion();
	waitForConversion();
			
	return ADC;
}