#include "conversion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Funkcja konwertująca dowolny system liczbowy z przedziału (2 - 16) na system dziesiętny
unsigned long long anySystemToDecimal(char *number, int currentSystem) {
    unsigned long long result = 0;
    char *digit = number + strlen(number) - 1;  // Wskaznik na ostatni znak numeru
    short currentPower = 0;                     // Potęga używana przy konwersji
    short decimalDigit = 0;                     // Cyfra w systemie dziesietnym

    // Konwertujemy system liczbowy na system dziesietny
    while (digit >= number) {
        if (!IS_HEX_DIGIT(*digit)) {
            // Gdyby okazało się, że znak nie należy do żadnego systemu liczbowego z przedziału 2-16 wywalamy błąd
            printf("\033[91merr: Niepoprawny znak \"%c\" w zapisie dotychczasowej liczby\033[0m\n", *digit);
            exit(EXIT_FAILURE);
        }

        if (IS_NUMBER(*digit)) {
            decimalDigit = (*digit - '0');      // Jeżeli znak jest cyfrą od 0 do 9 po prostu pobieramy jego wartość
                                                // i odejmujemy wartość znaku ASCII '0' aby otrzymać liczbę w poprawnym formacie
        }
        else if (IS_LOWERCASE_LETTER(*digit)) {
            decimalDigit = (*digit - 'a' + 10); // Jeżeli znak jest literą od 'a' do 'f' to odejmujemy wartość znaku ASCII 'a',
                                                // a następnie dodajemy 10 aby otrzymać liczbę w poprawnym formacie
        }
        else if (IS_UPPERCASE_LETTER(*digit)) {
            decimalDigit = (*digit - 'A' + 10); // Tutaj to samo tylko z literami w uppercasie
        }

        // Gdyby okazało się, że cyfra wykracza poza zakres dotychczasowego systemu liczbowego, wywalamy błąd
        if (decimalDigit >= currentSystem) {
            printf("\033[91merr: Cyfra \"%c\" wykracza poza zakres dotychczasowego systemu liczbowego\033[0m\n", *digit);
            exit(EXIT_FAILURE);
        }

        // Do ostatecznej liczby dodajemy kolejne potęgi dotychczasowego systemu pomnożone przez aktualną cyfrę
        result += decimalDigit * powl(currentSystem, currentPower++);
        --digit;                                // Zmniejszamy wskaźnik ostatniego znaku
    }

    return result;
}

void decimalToAnySystem(long long number, int targetSystem, char *result) {
    // Dzielimy przez docelowy system i zapisujemy reszte z dzielenia
    if (result == 0) {
        printf("\033[91merr: Nie podano docelowej zmiennej przechowującej wynik\033[0m\n");
        exit(EXIT_FAILURE);
    }

    short position = 0;                         // pozycja w której ma być wpisany znak
    while (number > 0) {
        short remainder = number % targetSystem;                // Bierzemy reszte z dzielenia przez docelowy system
        result[position++] = DIGIT_TABLE[remainder];   // Zapisujemy cyfre w docelowej liczbie
        number /= targetSystem;                                 // Dzielimy przez docelowy system
    }

    // Liczba jest odwrócona więc trzeba ją odwrócić
    for (short i = 0; i < position / 2; i++) {
        char temp = result[i];                         // Zappisujemy cyfrę w tymczasowej zmiennej
        result[i] = result[position - 1 - i]; // Przenosimy cyfre z pozycji "position - 1 - i" na pozycje i
        result[position - 1 - i] = temp;               // Zapisaną wcześniej liczbę wstawiamy na pozycję wcześniejszej liczby
    }

}