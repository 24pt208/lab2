#include <iostream>
#include <locale>
#include <string>
#include "module.h"

bool isValidKey(const std::wstring& s) {
    if (s.empty()) return false;
    for (auto c : s) {
        if (!std::iswdigit(c)) return false;
    }
    int key = std::stoi(s);
    return key > 0;
}

int main() {
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale());
    
    try {
        std::wstring key_str;
        std::wcout << L"Введите ключ (количество столбцов): ";
        std::wcin >> key_str;
        std::wcin.ignore(); 
        
        if (!isValidKey(key_str)) {
            std::wcerr << L"Ошибка: неверный ключ\n";
            return 1;
        }
        
        RouteCipher cipher(key_str);
        std::wcout << L"Ключ загружен\n";
        
        while (true) {
            std::wcout << L"\n1 - Шифровать\n2 - Дешифровать\n0 - Выход\n";
            std::wcout << L"Выберите операцию: ";
            
            int choice;
            std::wcin >> choice;
            std::wcin.ignore();
            
            if (choice == 0) break;
            
            if (choice > 2) {
                std::wcout << L"Неверная операция\n";
                continue;
            }
            
            std::wstring text;
            std::wcout << L"Введите текст: ";
            std::getline(std::wcin, text);
            
            try {
                if (choice == 1) {
                    std::wstring encrypted = cipher.encrypt(text);
                    std::wcout << L"Зашифровано: " << encrypted << std::endl;
                } else {
                    std::wstring decrypted = cipher.decrypt(text);
                    std::wcout << L"Расшифровано: " << decrypted << std::endl;
                }
            } catch (const cipher_error& e) {
                std::wcerr << L"Ошибка: " << e.what() << std::endl;
            }
        }
    } catch (const cipher_error& e) {
        std::wcerr << L"Ошибка инициализации: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
