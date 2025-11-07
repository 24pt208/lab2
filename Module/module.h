#pragma once
#include <string>
#include <locale>
#include <stdexcept>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg):
        std::invalid_argument(what_arg) {}
};

class RouteCipher {
private:
    int columns;
    std::wstring getValidKey(const std::wstring& s);
    std::wstring getValidOpenText(const std::wstring& s);
    std::wstring getValidCipherText(const std::wstring& s);
    
public:
    RouteCipher() = delete;
    RouteCipher(const std::wstring& key);
    void setKey(const std::wstring& key);
    std::wstring getKey() const;
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& text);
};
