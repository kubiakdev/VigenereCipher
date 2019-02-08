#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

static const char CHARACTER_DEFAULT_PATH_ARRAY[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

static const char CHARACTER_WITH_SPECIALS_PATH_ARRAY[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '{', '[', ']',
        '}', ';', ':', '"', '\'', '\\', '|', ',', '<', '>', '.', '?', '/',
        ' '
};

static const int CHARACTER_DEFAULT_PATH_ARRAY_SIZE = sizeof(CHARACTER_DEFAULT_PATH_ARRAY);

static const int CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE = sizeof(CHARACTER_WITH_SPECIALS_PATH_ARRAY);

static char CHARACTER_DEFAULT_ARRAY[CHARACTER_DEFAULT_PATH_ARRAY_SIZE][CHARACTER_DEFAULT_PATH_ARRAY_SIZE] = {0};

static char CHARACTER_WITH_SPECIALS_ARRAY
[CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE][CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE] = {0};

static bool shouldUseDefaultCharacterArray = true;

class Cipher {

public:
    void encryptFile(string path, string key) {
        writeToFile(path, getEncryptedTextFromFile(path, key));
    }

public:
    void decryptFile(string path, string key) {
        writeToFile(path, getDecryptedTextFromFile(path, key));
    }

public:
    string encryptText(string textToEncrypt, string key) {
        if (CHARACTER_DEFAULT_ARRAY[0][0] == 0) {
            initDefaultArray();
        }
        if (CHARACTER_WITH_SPECIALS_ARRAY[0][0] == 0) {
            initArrayWithSpecials();
        }
        string keyLongAsTextToEncrypt = getKeyLongAsTextToEncrypt(textToEncrypt, key);
        string result;
        for (int i = 0; i < keyLongAsTextToEncrypt.size(); ++i) {
            int rowIndex = findRowIndex(textToEncrypt[i]);

            char charToAdd;
            if (rowIndex != -1) {
                if (shouldUseDefaultCharacterArray) {
                    charToAdd = CHARACTER_DEFAULT_ARRAY[rowIndex][findColumnIndex(keyLongAsTextToEncrypt[i])];
                } else {
                    charToAdd = CHARACTER_WITH_SPECIALS_ARRAY[rowIndex][findColumnIndex(keyLongAsTextToEncrypt[i])];
                }
            } else {
                charToAdd = textToEncrypt[i];
            }

            result += charToAdd;
        }
        return result;
    }

public:
    string decryptText(string textToDecrypt, string key) {
        if (CHARACTER_DEFAULT_ARRAY[0][0] == 0) {
            initDefaultArray();
        }
        if (CHARACTER_WITH_SPECIALS_ARRAY[0][0] == 0) {
            initArrayWithSpecials();
        }
        string keyLongAsTextToDecrypt = getKeyLongAsTextToEncrypt(textToDecrypt, key);
        string result;
        for (int i = 0; i < keyLongAsTextToDecrypt.size(); ++i) {
            int rowIndex = findRowIndex(keyLongAsTextToDecrypt[i]);

            char charToAdd;
            if (rowIndex != -1) {
                if (shouldUseDefaultCharacterArray) {
                    charToAdd = CHARACTER_DEFAULT_PATH_ARRAY[findColumnIndexInArray(textToDecrypt[i], rowIndex)];
                } else {
                    charToAdd = CHARACTER_WITH_SPECIALS_PATH_ARRAY[findColumnIndexInArray(textToDecrypt[i], rowIndex)];
                }
            } else {
                charToAdd = textToDecrypt[i];
            }

            result += charToAdd;
        }
        return result;
    }

public:
    void changeCipherCharactersPathRange() {
        if (shouldUseDefaultCharacterArray) {
            shouldUseDefaultCharacterArray = false;
            cout << "Zmieniono zakres znaków do szyfrowania na rozszerzony." << endl;
        } else {
            shouldUseDefaultCharacterArray = true;
            cout << "Zmieniono zakres znaków do szyfrowania na podstawowy." << endl;
        }
    }

private:
    string getEncryptedTextFromFile(string path, string key) {
        string text, encryptedText;
        ifstream file(path);
        if (file.is_open()) {
            while (getline(file, text)) {
                encryptedText += encryptText(text, key);
            }
            file.close();
            cout << "Twój plik został zaszyfrowany." << endl;
        } else {
            cout << "Zła ścieżka do pliku. " << endl;
        }
        return encryptedText;
    }

private:
    string getDecryptedTextFromFile(string path, string key) {
        string text, decryptedText;
        ifstream file(path);
        if (file.is_open()) {
            while (getline(file, text)) {
                decryptedText += decryptText(text, key);
            }
            file.close();
            cout << "Twój plik został odszyfrowany." << endl;
        } else {
            cout << "Zła ścieżka do pliku." << endl;
        }
        return decryptedText;
    }

private:
    void writeToFile(string path, string text) {
        ofstream file(path);
        if (file.is_open()) {
            file << text;
            file.close();
        } else cout << "Błąd przy otwieraniu pliku" << endl;
    }

private:
    void initDefaultArray() {
        int shift = 0;
        for (auto &i : CHARACTER_DEFAULT_ARRAY) {
            for (int j = 0; j < CHARACTER_DEFAULT_PATH_ARRAY_SIZE; ++j) {
                if (j + shift < CHARACTER_DEFAULT_PATH_ARRAY_SIZE) {
                    i[j] = CHARACTER_DEFAULT_PATH_ARRAY[j + shift];
                } else {
                    i[j] = CHARACTER_DEFAULT_PATH_ARRAY[j - CHARACTER_DEFAULT_PATH_ARRAY_SIZE + shift];
                }
            }
            shift++;
        }
    }

private:
    void initArrayWithSpecials() {
        int shift = 0;
        for (auto &i : CHARACTER_WITH_SPECIALS_ARRAY) {
            for (int j = 0; j < CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE; ++j) {
                if (j + shift < CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE) {
                    i[j] = CHARACTER_WITH_SPECIALS_PATH_ARRAY[j + shift];
                } else {
                    i[j] = CHARACTER_WITH_SPECIALS_PATH_ARRAY[j - CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE + shift];
                }
            }
            shift++;
        }
    }

private:
    string getKeyLongAsTextToEncrypt(string value, string key) {
        string result;
        int lastKeyIndex = 0;
        for (char c : value) {
            if (isCharInPath(c)) {
                result += key[lastKeyIndex];
                if (lastKeyIndex == key.size() - 1) {
                    lastKeyIndex = 0;
                } else {
                    ++lastKeyIndex;
                }
            } else {
                result += c;
            }
        }
        return result;
    }

private:
    bool isCharInPath(char c) {
        if (shouldUseDefaultCharacterArray) {
            for (char i : CHARACTER_DEFAULT_PATH_ARRAY) {
                if (c == i) {
                    return true;
                }
            }
            return false;
        } else {
            for (char i : CHARACTER_WITH_SPECIALS_PATH_ARRAY) {
                if (c == i) {
                    return true;
                }
            }
            return false;
        }
    }

private:
    int findRowIndex(char c) {
        if (shouldUseDefaultCharacterArray) {
            for (int i = 0; i < CHARACTER_DEFAULT_PATH_ARRAY_SIZE; ++i) {
                if (c == CHARACTER_DEFAULT_PATH_ARRAY[i]) {
                    return i;
                }
            }
            return -1;
        } else {
            for (int i = 0; i < CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE; ++i) {
                if (c == CHARACTER_WITH_SPECIALS_PATH_ARRAY[i]) {
                    return i;
                }
            }
            return -1;
        }
    }

private:
    int findColumnIndex(char c) {
        if (shouldUseDefaultCharacterArray) {
            for (int i = 0; i < CHARACTER_DEFAULT_PATH_ARRAY_SIZE; ++i) {
                if (c == CHARACTER_DEFAULT_PATH_ARRAY[i]) {
                    return i;
                }
            }
            return -1;
        } else {
            for (int i = 0; i < CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE; ++i) {
                if (c == CHARACTER_WITH_SPECIALS_PATH_ARRAY[i]) {
                    return i;
                }
            }
            return -1;
        }
    }

private:
    int findColumnIndexInArray(char c, int rowIndex) {
        if (shouldUseDefaultCharacterArray) {
            for (int i = 0; i < CHARACTER_DEFAULT_PATH_ARRAY_SIZE; ++i) {
                if (c == CHARACTER_DEFAULT_ARRAY[i][rowIndex]) {
                    return i;
                }
            }
            return -1;
        } else {
            for (int i = 0; i < CHARACTER_WITH_SPECIALS_PATH_ARRAY_SIZE; ++i) {
                if (c == CHARACTER_WITH_SPECIALS_ARRAY[i][rowIndex]) {
                    return i;
                }
            }
            return -1;
        }
    }

};
