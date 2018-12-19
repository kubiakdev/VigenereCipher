#include <iostream>
#include <fstream>

using namespace std;

static const char CHARACTER_PATH_ARRAY[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

static const int CHARACTER_PATH_ARRAY_SIZE = sizeof(CHARACTER_PATH_ARRAY);

static char CHARACTER_ARRAY[CHARACTER_PATH_ARRAY_SIZE][CHARACTER_PATH_ARRAY_SIZE] = {0};

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
        initArray();
        string keyLongAsTextToEncrypt = getKeyLongAsTextToEncrypt(textToEncrypt, key);
        string result;
        for (int i = 0; i < keyLongAsTextToEncrypt.size(); ++i) {
            int rowIndex = findRowIndex(textToEncrypt[i]);

            char charToAdd;
            if (rowIndex != -1) {
                charToAdd = CHARACTER_ARRAY[rowIndex][findColumnIndex(keyLongAsTextToEncrypt[i])];
            } else {
                charToAdd = textToEncrypt[i];
            }

            result += charToAdd;
        }
        return result;
    }

public:
    string decryptText(string textToDecrypt, string key) {
        if (CHARACTER_ARRAY[0][0] == 0) {
            initArray();
        }
        string keyLongAsTextToDecrypt = getKeyLongAsTextToEncrypt(textToDecrypt, key);
        string result;
        for (int i = 0; i < keyLongAsTextToDecrypt.size(); ++i) {
            int rowIndex = findRowIndex(keyLongAsTextToDecrypt[i]);

            char charToAdd;
            if (rowIndex != -1) {
                charToAdd = CHARACTER_PATH_ARRAY[findColumnIndexInArray(textToDecrypt[i], rowIndex)];
            } else {
                charToAdd = textToDecrypt[i];
            }

            result += charToAdd;
        }
        return result;
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
            cout << "Twój plik został zaszyfrowany.";
        } else {
            cout << "Zła ścieżka do pliku. ";
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
            cout << "Twój plik został odszyfrowany.";
        } else {
            cout << "Zła ścieżka do pliku.";
        }
        return decryptedText;
    }

private:
    void writeToFile(string path, string text) {
        ofstream file(path);
        if (file.is_open()) {
            file << text;
            file.close();
        } else cout << "Błąd przy otwieraniu pliku";
    }

private:
    void initArray() {
        int shift = 0;
        for (auto &i : CHARACTER_ARRAY) {
            for (int j = 0; j < CHARACTER_PATH_ARRAY_SIZE; ++j) {
                if (j + shift < CHARACTER_PATH_ARRAY_SIZE) {
                    i[j] = CHARACTER_PATH_ARRAY[j + shift];
                } else {
                    i[j] = CHARACTER_PATH_ARRAY[j - CHARACTER_PATH_ARRAY_SIZE + shift];
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
        for (char i : CHARACTER_PATH_ARRAY) {
            if (c == i) {
                return true;
            }
        }
        return false;
    }

private:
    int findRowIndex(char c) {
        for (int i = 0; i < CHARACTER_PATH_ARRAY_SIZE; ++i) {
            if (c == CHARACTER_PATH_ARRAY[i]) {
                return i;
            }
        }
        return -1;
    }

private:
    int findColumnIndex(char c) {
        for (int i = 0; i < CHARACTER_PATH_ARRAY_SIZE; ++i) {
            if (c == CHARACTER_PATH_ARRAY[i]) {
                return i;
            }
        }
        return -1;
    }

private:
    int findColumnIndexInArray(char c, int rowIndex) {
        for (int i = 0; i < CHARACTER_PATH_ARRAY_SIZE; ++i) {
            if (c == CHARACTER_ARRAY[i][rowIndex]) {
                return i;
            }
        }
        return -1;
    }
};
