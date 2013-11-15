#include <avr/pgmspace.h>

#define STRING_ERROR 0
#define STRING_OK 1
#define STRING_BAD 2
#define STRING_200OK 3
#define STRING_200BAD 4
#define STRINGA5 5

prog_char string_0[] PROGMEM = "\n--ERROR--\n";   // "String 0" etc are strings to store - change to suit.
prog_char string_1[] PROGMEM = "OK\n";
prog_char string_2[] PROGMEM = "BAD\n";
prog_char string_3[] PROGMEM = "200 OK\n";
prog_char string_4[] PROGMEM = "404 BAD\n";

// Then set up a table to refer to your strings.

PROGMEM const char *string_table[] = 	   // change "string_table" name to suit
{   
  string_0,
  string_1,
  string_2,
  string_3,
  string_4,
};

char buffer[20];    // make sure this is large enough for the largest string it must hold

void printString(int number)			  
{
  /* Using the string table in program memory requires the use of special functions to retrieve the data.
     The strcpy_P function copies a string from program space to a string in RAM ("buffer"). 
     Make sure your receiving string in RAM  is large enough to hold whatever
     you are retrieving from program space. */

    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[number]))); // Necessary casts and dereferencing, just copy. 
    Serial.println( buffer );
    delay(50);  
}

// Use showString(PSTR("string"));
void showString (PGM_P s) {
    char c;
    while ((c = pgm_read_byte(s++)) != 0)
        Serial.print(c);
}

// Use showStringGSM(PSTR("string"));
void showStringGSM(PGM_P s) {
    char c;
    while ((c = pgm_read_byte(s++)) != 0)
        GSM_Serial.print(c);
        
    GSM_Serial.println();
}

