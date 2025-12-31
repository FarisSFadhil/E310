#include "EasyREDVIO.h"
#include "Declarations.h"
#include "Utils.c"
// Arduino-like library for IO functions
void delay(int ms){
}
#define DUR 100
// Define Morse code for letters
// codes is a lookup table indexed from 0 to 25, corresponding to letters A through Z
// Each entry is a null-terminated string of dots and dashes
char codes[26][5] = {
".-", // A
"-...", // B
"-.-.", // C
"-..", // D
".", // E
"..-.", // F
"--.", // G
"....", // H
"..", // I
".---", // J
"-.-", // K
".-..", // L
"--", // M
"-.", // N
"---", // O
".--.", // P
"--.-", // Q
".-.", // R
"...", // S
"-", // T
"..-", // U
"...-", // V
".--", // W
"-..-", // X
"-.--", // Y
"--.." // Z
};

/* c is a variable and more precisely a fuction paramater for the character you want to play, like 'A', 'B', 'Z'.
The expression c - 'A' converts a character like 'C' into an index like 2, which selects the correct Morse string.
So codes[c - 'A'] picks the correct row for the letter */
void playChar(char c) {
int i=0;
/* A while(condition) keeps looping while condition is nonzero. Characters are just small integers, so:
'.' is nonzero → loop continues
'-' is nonzero → loop continues
'\0' is zero → loop stops
So that while loop walks through the dot/dash characters until it hits the null terminator at the end of the Morse string.*/
while (codes[c-'A'][i]) {
digitalWrite(5, 1); // turn on LED
if (codes[c-'A'][i] == '.') delay(DUR); // dot
else delay(3*DUR); // dash
digitalWrite(5, 0); // turn off LED
delay(DUR); // pause between elements
i++;
}
delay(DUR*2); // extra pause between characters
}