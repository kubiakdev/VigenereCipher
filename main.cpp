#include <iostream>
#include "Cipher.h"
#include <string>

using namespace std;

int main() {
    cout << "Witaj! Podany program służy do zaszyfrowania oraz odszyfrowania wybranego tekstu, bądź pliku "
            "tekstowego." << endl;

    cout << "Wybierz numer akcji którą chcesz zrobić:" << endl;
    cout << "1. Zaszyfruj podany tekst." << endl;
    cout << "2. Odszyfruj podany tekst." << endl;
    cout << "3. Zaszyfruj plik tekstowy." << endl;
    cout << "4. Odszyfruj plik tekstowy." << endl;

    string chosenOption;
    getline(cin, chosenOption);

    switch (stoi(chosenOption)) {
        case 1: {
            string textToEncryption, key;

            cout << "Wpisz tekst, który chcesz zaszyfrować: ";
            getline(cin, textToEncryption);

            cout << "Teraz podaj klucz do zaszyfrowania: ";
            getline(cin, key);

            cout << "Twój zaszyfrowany tekst to: \n" << Cipher().encryptText(textToEncryption, key) << endl;
            break;
        }
        case 2: {
            string textToDecryption, key;

            cout << "Wpisz tekst, który chcesz odszyfrować: ";
            getline(cin, textToDecryption);

            cout << "Teraz podaj klucz do odszyfrowania: ";
            getline(cin, key);

            cout << "Twój zaszyfrowany tekst to: \n" << Cipher().decryptText(textToDecryption, key) << endl;
            break;
        }
        case 3: {
            string path, key;

            cout << "Wpisz ścieżkę pliku, który chcesz zaszyfować:  ";
            getline(cin, path);

            cout << "Teraz podaj klucz do zaszyfrowania: ";
            getline(cin, key);

            Cipher().encryptFile(path, key);
            break;
        }
        case 4: {
            string path, key;

            cout << "Wpisz ścieżkę pliku, który chcesz odszyfować:  ";
            getline(cin, path);

            cout << "Teraz podaj klucz do odszyfrowania: ";
            getline(cin, key);

            Cipher().decryptFile(path, key);
            break;
        }
    }
}