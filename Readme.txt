This as a single story, starting from the low-level hardware abstraction and ending with how the Morse code LED blinking works, keeping it plain and linear.

The first file, EasyREDVIO.h, is building a thin Arduino-style layer on top of the FE310 GPIO hardware. The FE310 exposes its GPIO peripheral as a block of memory-mapped registers. 

Each register lives at a fixed offset from a base address, and reading or writing that memory directly controls the pins.

The GPIO struct is a C representation of that register block. The order of the fields is critical. 

input_val corresponds to offset 0x00, input_en to 0x04, output_en to 0x08, and so on. 

Because the struct fields are laid out sequentially in memory, casting a pointer to the GPIO base address into a GPIO* lets you access registers using natural C syntax like GPIO0->output_val. 

The volatile keyword tells the compiler that these values can change outside of the program’s control, so it must not optimize reads or writes away. 

That is essential for hardware registers.

GPIO0_BASE defines the physical base address of the GPIO peripheral in the FE310 memory map. 

GPIO0 then casts that address into a pointer to the GPIO struct, which is what makes expressions like GPIO0->input_val work. 

You are not allocating memory here; you are telling the compiler “this address already exists and maps to hardware.”

pinMode configures a pin as either input or output. The GPIO registers use one bit per pin. Shifting 1 << gpio_pin creates a mask that selects the bit corresponding to that pin. 

When function is INPUT, the code sets the bit in input_en, clears the bit in output_en, and disables any hardware-controlled alternate function by clearing the bit in iof_en. 

That means the pin is controlled by software and configured strictly as an input. 

When function is OUTPUT, the opposite happens: the output enable bit is set, the input enable bit is cleared, and the alternate function is disabled. 

This mirrors the mental model of Arduino’s pinMode, but implemented by directly manipulating registers.

digitalWrite controls the logic level on an output pin. If val is nonzero, it sets the corresponding bit in output_val, driving the pin high. 

If val is zero, it clears that bit, driving the pin low. The read-modify-write pattern using |= and &= ~ ensures only the selected pin changes state while all other pins remain untouched.

digitalRead reads the current state of a pin. input_val contains a snapshot of all GPIO pin levels. 

Shifting right by gpio_pin moves the desired pin’s bit to position zero, and masking with 0x1 extracts just that single bit. The function returns either 0 or 1.

The second file, morse.c, uses this Arduino-like interface to implement Morse code blinking on an LED. 

codes is a lookup table indexed from 0 to 25, corresponding to letters A through Z. Each entry is a null-terminated string of dots and dashes. 

The expression c - 'A' converts a character like 'C' into an index like 2, which selects the correct Morse string.

DUR defines the base time unit for Morse timing. A dot lasts one unit, a dash lasts three units, the gap between elements inside a character lasts one unit, 

and the gap between characters lasts three units total. That timing rule is encoded directly in the delays.

playChar takes a single uppercase letter and blinks it. The loop walks through the Morse string for that character until it reaches the null terminator. 

For each symbol, the LED connected to GPIO pin 5 is turned on. If the symbol is a dot, the LED stays on for DUR. If it is a dash, it stays on for 3*DUR. 

The LED is then turned off, and the code waits one unit to separate symbols. After all symbols in the character are played, 

it waits an extra two units so that the total inter-character gap becomes three units.

Overall, this code shows the full stack from raw memory-mapped I/O on a RISC-V microcontroller up to a friendly, 

Arduino-style API, and then a concrete application that uses timing and bit manipulation to turn text into visible Morse code on an LED.