#ifndef MP_CONVERSION_H
#define MP_CONVERSION_H

// Pomocnicze makra do sprawdzania znaków przy konwersji do systemu dziesiętnego
#define IS_HEX_DIGIT(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
#define IS_NUMBER(c) (c >= '0' && c <= '9')
#define IS_LOWERCASE_LETTER(c) (c >= 'a' && c <= 'f')
#define IS_UPPERCASE_LETTER(c) (c >= 'A' && c <= 'F')

// Tablica znaków dla systemów liczbowych od 2 do 16
static const char DIGIT_TABLE[17] = "0123456789ABCDEF";

// Funkcje konwertujące systemy liczbowe (z dowolnego na dziesiętny i z dziesiętnego na dowolny)
unsigned long long anySystemToDecimal(char *number, int currentSystem);
void decimalToAnySystem(long long number, int targetSystem, char *result);

#endif