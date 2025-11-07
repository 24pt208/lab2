#include <iostream>
#include <locale>
#include <string>
#include "module.h"

int main() {
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    
    std::wcout << L"=== ТЕСТИРОВАНИЕ ОБРАБОТКИ ОШИБОК ===" << std::endl;
    
    // Тест конструктора с неверными ключами
    std::wcout << L"\n1. Тест конструктора:" << std::endl;
    try {
        RouteCipher cipher1(L""); // Пустой ключ
    } catch (const cipher_error& e) {
        std::wcout << L"Поймано исключение: " << e.what() << std::endl;
    }
    
    try {
        RouteCipher cipher2(L"ABC"); // Ключ с буквами
    } catch (const cipher_error& e) {
        std::wcout << L"Поймано исключение: " << e.what() << std::endl;
    }
    
    try {
        RouteCipher cipher3(L"-5"); // Отрицательный ключ
    } catch (const cipher_error& e) {
        std::wcout << L"Поймано исключение: " << e.what() << std::endl;
    }
    
    // Тест методов с неверными данными
    std::wcout << L"\n2. Тест методов:" << std::endl;
    try {
        RouteCipher cipher(L"3");
        cipher.encrypt(L""); // Пустой текст
    } catch (const cipher_error& e) {
        std::wcout << L"Поймано исключение encrypt: " << e.what() << std::endl;
    }
    
    try {
        RouteCipher cipher(L"3");
        cipher.decrypt(L"abc"); // Строчные буквы в шифротексте
    } catch (const cipher_error& e) {
        std::wcout << L"Поймано исключение decrypt: " << e.what() << std::endl;
    }
    
    try {
        RouteCipher cipher(L"3");
        cipher.decrypt(L"AB1C"); // Цифры в шифротексте
    } catch (const cipher_error& e) {
        std::wcout << L"Поймано исключение decrypt: " << e.what() << std::endl;
    }
    
    std::wcout << L"\n=== ВСЕ ТЕСТЫ ВЫПОЛНЕНЫ ===" << std::endl;
    
    return 0;
}
