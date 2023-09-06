#ifndef __ADC_READER_H_
#define __ADC_READER_H_

// Forward declarations
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

class ADCReader {
private:
	/** 
	* Utility four counting trailing zeros
	*
	* @param value - The value to count zeroes
	*/
	static uint8_t trailing_zeros_count(uint8_t value);

public:
	ADCReader();
	
	/************************************************************************/
	/* CONFIG METHODS														*/
	/************************************************************************/
	
	/** 
	 * Source: Atmega2560 Datasheet p. 281
	 * 
	 *     REFS1 REFS0
	 *  0:     0     0  AREF, Internal V_ref turned off
	 *  1:     0     1  AVCC with external capacitor at AREF pin
	 *  2:     1     0  Internal 1.1V Voltage Reference with external capacitor at AREF 
	 *  3:     1     1  Internal 2.56V Voltage Reference with external capacitor at AREF 
	 *
	 * @param option - The row index in the table above
	 */
	void setReference(uint8_t option);
	
	/** 
	* Set a prescaler
	*
	* @param division_factor - The division factor (2, 4, 8, 16, 32, 64, 128)
	*/
	void setPrescaler(uint8_t division_factor);

	/** 
	* Set a channel as single ended
	*/
	void setSingleEnded();
	
	/** 
	* Set a specific channel
	*
	* @param channel - ADC Channel from 0 to 15
	*/
	void setChannel(uint8_t channel);
	
	
	/************************************************************************/
	/*  READ METHODS														*/
	/************************************************************************/
	
	/**
	* Start an ADC conversion.
	*/
	void startConversion();
	
	/** 
	* Wait for aN ADC conversion to end.
	*
	* @remark This method will hold the program execution
	*/
	void waitForConversion();
	
	/**
	* Read the current Analog value.
	*
	* @remark This method will hold the program execution
	*/
	uint16_t get();
};

#endif /* __ADC_READER_H_ */