#include <iostream>
#include "Cipher.h"
#include <string>
#include <sstream>

using namespace std;

void introduceApplication();

bool isUserWantsToRelaunchTheApplication();

int getRelaunchOperationNumber();

int getAppOperationNumber();

void performOperation(Cipher cipher, int operationNumber);

void prepareGetLineInvocation();

int main() {
    introduceApplication();
    Cipher cipher = Cipher();
    do {
        cout << "Wybierz numer akcji którą chcesz zrobić:" << endl;
        cout << "1. Zaszyfruj podany tekst." << endl;
        cout << "2. Odszyfruj podany tekst." << endl;
        cout << "3. Zaszyfruj plik tekstowy." << endl;
        cout << "4. Odszyfruj plik tekstowy." << endl;
        cout << "5. Zmień zakres znaków szyfrujących." << endl;

        int chosenOperation = getAppOperationNumber();
        prepareGetLineInvocation();
        performOperation(cipher, chosenOperation);

        if (isUserWantsToRelaunchTheApplication()) {
            continue;
        } else {
            break;
        }
    } while (true);

    return 0;
}

void introduceApplication() {
    cout << "Witaj! Podany program służy do zaszyfrowania oraz odszyfrowania wybranego tekstu, bądź pliku "
            "tekstowego." << endl;
    cout << "Autorzy: Michał Drzymała, Patryk Kubiak" << endl;
}

bool isUserWantsToRelaunchTheApplication() {
    cout << "Czy chcesz uruchomic program ponownie?" << endl;
    cout << "1. Tak" << endl;
    cout << "2. Nie" << endl;
    return getRelaunchOperationNumber() == 1;
}

int getRelaunchOperationNumber() {
    int operationNumber;
    string value;

    do {
        cin >> value;
        try {
            operationNumber = stoi(value);
            if (operationNumber == 1 || operationNumber == 2) {
                return operationNumber;
            } else {
                cout << "Nalezy podac 1 lub 2!" << endl;
            }
        } catch (invalid_argument &e) {
            cout << "To nie jest numer operacji!" << endl;
        } catch (...) {
            cout << "Wystapil blad! Spróbuj ponownie wpisujac inna wartosc." << endl;
        }
    } while (true);
}

int getAppOperationNumber() {
    int operationNumber;
    string value;

    do {
        cin >> value;
        try {
            operationNumber = stoi(value);
            if (operationNumber >= 1 && operationNumber <= 5) {
                return operationNumber;
            } else {
                cout << "Nalezy podac numer od 1 do 5!" << endl;
            }
        } catch (invalid_argument &e) {
            cout << "To nie jest numer operacji!" << endl;
        } catch (...) {
            cout << "Wystapil blad! Spróbuj ponownie wpisujac inna wartosc." << endl;
        }
    } while (true);
}

void performOperation(Cipher cipher, int operationNumber) {
    switch (operationNumber) {
        case 1: {
            string textToEncryption, key;

            cout << "Wpisz tekst, który chcesz zaszyfrować: " << endl;
            getline(cin, textToEncryption);

            cout << "Teraz podaj klucz do zaszyfrowania: " << endl;
            getline(cin, key);
            cout << "Twój zaszyfrowany tekst to: \n" << cipher.encryptText(textToEncryption, key) << endl;
            break;
        }
        case 2: {
            string textToDecryption, key;

            cout << "Wpisz tekst, który chcesz odszyfrować: " << endl;
            getline(cin, textToDecryption);

            cout << "Teraz podaj klucz do odszyfrowania: " << endl;
            getline(cin, key);

            cout << "Twój zaszyfrowany tekst to: \n" << cipher.decryptText(textToDecryption, key) << endl;
            break;
        }
        case 3: {
            string path, key;

            cout << "Wpisz ścieżkę pliku, który chcesz zaszyfować:  " << endl;
            getline(cin, path);

            cout << "Teraz podaj klucz do zaszyfrowania: " << endl;
            getline(cin, key);

            cipher.encryptFile(path, key);
            break;
        }
        case 4: {
            string path, key;

            cout << "Wpisz ścieżkę pliku, który chcesz odszyfować:  " << endl;
            getline(cin, path);

            cout << "Teraz podaj klucz do odszyfrowania: " << endl;
            getline(cin, key);

            cipher.decryptFile(path, key);
            break;
        }
        case 5: {
            cipher.changeCipherCharactersPathRange();
            break;
        }
        default:
            break;
    }

}

void prepareGetLineInvocation() {
    string empty = "";
    getline(cin, empty);
}