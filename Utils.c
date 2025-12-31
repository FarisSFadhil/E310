

#include "EasyREDVIO.h"
#define INPUT 0
#define OUTPUT 1
void pinMode(int gpio_pin, int function) {
switch(function) {
case INPUT:
GPIO0->input_en |= (1 << gpio_pin); // Sets a pin as an input
GPIO0->output_en &= ~(1 << gpio_pin); // Disable output
GPIO0->iof_en &= ~(1 << gpio_pin); // Disable IOF
break;
case OUTPUT:
GPIO0->output_en |= (1 << gpio_pin); // Set pin as an output
GPIO0->input_en &= ~(1 << gpio_pin); // Disable input
GPIO0->iof_en &= ~(1 << gpio_pin); // Disable IOF
break;
    }
}
void digitalWrite(int gpio_pin, int val) {
if (val) GPIO0->output_val |= (1 << gpio_pin);
else GPIO0->output_val &= ~(1 << gpio_pin);
}
int digitalRead(int gpio_pin) {
return (GPIO0->input_val >> gpio_pin) & 0x1;
}