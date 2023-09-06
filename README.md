# ADCReader utility

```c
int main(void) {

    ADCReader reader;

    // Set channel to ADC8 (Pin K0)
    reader.setChannel(8);

    // Set a 128 prescaler
    reader.setPrescaler(128);

    uint16_t value;

    while(1) {
        value = reader.get();    

        // do something
    };
}

```