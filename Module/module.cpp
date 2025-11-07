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
    
    int rows = (clean_text.length() + columns - 1) / columns;
    std::wstring result;
    
    for (int col = columns - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            int pos = row * columns + col;
            if (pos < clean_text.length()) {
                result += clean_text[pos];
            }
        }
    }
    return result;
}

std::wstring RouteCipher::decrypt(const std::wstring& text) {
    std::wstring clean_text = getValidCipherText(text);
   
    int rows = (clean_text.length() + columns - 1) / columns;
    std::wstring result(clean_text.length(), L' ');
    int index = 0;

    for (int col = columns - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            int pos = row * columns + col;
            if (pos < clean_text.length() && index < clean_text.length()) {
                result[pos] = clean_text[index++];
            }
        }
    }
    return result;
}
