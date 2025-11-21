#include "module.h"
#include <stdexcept>
#include <locale>
#include <string>
#include <cwctype>

RouteCipher::RouteCipher(const std::wstring& key) {
    std::wstring valid_key = getValidKey(key);
    columns = std::stoi(valid_key);
}

std::wstring RouteCipher::getValidKey(const std::wstring& s) {
    if (s.empty())
        throw cipher_error("Empty key");
    
    for (auto c : s) {
        if (!std::iswdigit(c))
            throw cipher_error("Invalid key - must contain only digits");
    }
    
    int key_value = std::stoi(s);
    if (key_value <= 0)
        throw cipher_error("Key must be greater than 0");
    
    return s;
}

std::wstring RouteCipher::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (auto c : s) {
        if (std::iswalpha(c)) {
            if (std::iswlower(c))
                tmp.push_back(std::towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

std::wstring RouteCipher::getValidCipherText(const std::wstring& s) {
    if (s.empty())
        throw cipher_error("Empty cipher text");
    
    for (auto c : s) {
        if (!std::iswupper(c))
            throw cipher_error("Invalid cipher text - must contain only uppercase letters");
    }
    return s;
}

void RouteCipher::setKey(const std::wstring& key) {
    std::wstring valid_key = getValidKey(key);
    columns = std::stoi(valid_key);
}

std::wstring RouteCipher::getKey() const {
    return std::to_wstring(columns);
}

std::wstring RouteCipher::encrypt(const std::wstring& text) {
    std::wstring clean_text = getValidOpenText(text);
    
    std::size_t text_length = clean_text.length();
    std::size_t rows = (text_length + columns - 1) / columns;
    std::wstring result;
    
    for (int col = columns - 1; col >= 0; col--) {
        for (std::size_t row = 0; row < rows; row++) {
            std::size_t pos = row * columns + col;
            if (pos < text_length) {
                result += clean_text[pos];
            }
        }
    }
    return result;
}

std::wstring RouteCipher::decrypt(const std::wstring& text) {
    std::wstring clean_text = getValidCipherText(text);
   
    std::size_t text_length = clean_text.length();
    std::size_t rows = (text_length + columns - 1) / columns;
    std::wstring result(text_length, L' ');
    std::size_t index = 0;

    for (int col = columns - 1; col >= 0; col--) {
        for (std::size_t row = 0; row < rows; row++) {
            std::size_t pos = row * columns + col;
            if (pos < text_length && index < text_length) {
                result[pos] = clean_text[index++];
            }
        }
    }
    return result;
}
