#include <stdio.h>
#include "conversion.h"

// Zmienne zawierające kody kolorów i innych operacji konsoli
const char COLOR_WHITE[] = "\033[97m";
const char COLOR_GRAY[] = "\033[37m";
const char COLOR_GREEN[] = "\033[92m";
const char COLOR_RESET[] = "\033[0m";
const char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

// Nagłówek
const char HEADER_TEXT[] =
" /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$$     /$$   /$$\n"
"| $$__  $$ /$$__  $$ /$$__  $$| $$_____/    | $$  / $$\n"
"| $$  \\ $$| $$  \\ $$| $$  \\__/| $$          |  $$/ $$/\n"
"| $$$$$$$ | $$$$$$$$|  $$$$$$ | $$$$$ /$$$$$$\\  $$$$/ \n"
"| $$__  $$| $$__  $$ \\____  $$| $$__/|______/ >$$  $$ \n"
"| $$  \\ $$| $$  | $$ /$$  \\ $$| $$           /$$/\\  $$\n"
"| $$$$$$$/| $$  | $$|  $$$$$$/| $$$$$$$$    | $$  \\ $$\n"
"|_______/ |__/  |__/ \\______/ |________/    |__/  |__/\n"
"\033[37m"
"      Konwerter systemow liczbowych w jezyku C\n"
"               Autor: Michal Pazurek\n";
// Punkt startowy programu
int main() {
    // Definiujemy zmienne systemu liczbowego i docelowego systemu liczbowego
    int currentSystem, targetSystem;

    // Liczba, którą chcemy przekonwertować
    char number[65] = { 0 };    // Najdłuższa możliwość to system dwójkowy i 64-bitowa liczba + 1 miejsce na znak '\0'

    printf("%s%s", CLEAR_SCREEN, COLOR_GREEN);
    printf("%s\n\n", HEADER_TEXT);
    printf("%s", COLOR_WHITE);

    // Pobieramy dane od użytkownika
    printf("Podaj dotychczasowy system liczbowy: ");
    getCurrentSystem:           // Etykieta, do której kod przeskoczy jeżeli dotychczasowy system jest niepoprawny
    scanf("%d", &currentSystem);
    if (currentSystem < 2 || currentSystem > 16) {
        printf("Niepoprawny system liczbowy. Podaj system z przedziału (2 - 16): ");
        goto getCurrentSystem;
    }

    // Pobieramy liczbę do konwersji
    printf("Podaj liczbe: ");
    scanf("%s", number);

    // Oraz docelowy system liczbowy
    printf("Podaj docelowy system liczbowy: ");
    getTargetSystem:            // Etykieta, do której kod przeskoczy jeżeli docelowy system jest niepoprawny
    scanf("%d", &targetSystem);
    if (targetSystem < 2 || targetSystem > 16) {
        printf("Niepoprawny system liczbowy. Podaj system z przedziału (2 - 16): ");
        goto getTargetSystem;
    }

    printf("\n");

    // Konwertujemy liczbe dotychczasowego systemu na system dziesiętny
    unsigned long long decimalNumber = anySystemToDecimal(number, currentSystem);

    // Konwersja na system docelowy:
    char convertedNumber[65] = { 0 };   // miejsce na przekonwertowany numer
    decimalToAnySystem(decimalNumber, targetSystem, convertedNumber);

    // Wyświetlamy otrzymaną liczbę
    printf("Przekonwertowana liczba w wybranym systemie to: %s%s%s\n", COLOR_GREEN, convertedNumber, COLOR_RESET);
    return 0;
}