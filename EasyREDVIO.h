#include <stdint.h>
// Declare a GPIO structure defining the GPIO registers in the order they appear in memory mapped I/O
typedef struct
{
volatile uint32_t input_val; // (GPIO offset 0x00) Pin value
volatile uint32_t input_en; // (GPIO offset 0x04) Pin input enable*
volatile uint32_t output_en; // (GPIO offset 0x08) Pin output enable*
volatile uint32_t output_val; // (GPIO offset 0x0C) Output value
volatile uint32_t pue; // (GPIO offset 0x10) Internal pull-up enable*
volatile uint32_t ds; // (GPIO offset 0x14) Pin drive strength
volatile uint32_t rise_ie; // (GPIO offset 0x18) Rise interrupt enable
volatile uint32_t rise_ip; // (GPIO offset 0x1C) Rise interrupt pending
volatile uint32_t fall_ie; // (GPIO offset 0x20) Fall interrupt enable
volatile uint32_t fall_ip; // (GPIO offset 0x24) Fall interrupt pending
volatile uint32_t high_ie; // (GPIO offset 0x28) High interrupt enable
volatile uint32_t high_ip; // (GPIO offset 0x2C) High interrupt pending
volatile uint32_t low_ie; // (GPIO offset 0x30) Low interrupt enable
volatile uint32_t low_ip; // (GPIO offset 0x34) Low interrupt pending
volatile uint32_t iof_en; // (GPIO offset 0x38) HW-Driven functions enable
volatile uint32_t iof_sel; // (GPIO offset 0x3C) HW-Driven functions selection
volatile uint32_t out_xor; // (GPIO offset 0x40) Output XOR (invert)
} GPIO;
// Define the base address of the GPIO registers and a pointer to this structure
// The 0x…U notation in 0x10012000U indicates an unsigned hexadecimal number
#define GPIO0_BASE (0x10012000U) //Defines the starting address of the GPIO
#define GPIO0 ((GPIO*) GPIO0_BASE) //then casts that address to a pointer to the GPIO struct