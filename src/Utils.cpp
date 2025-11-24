#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

// 十六进制字符串转字节数组
std::vector<uint8_t> Utils::hexToBytes(const std::string& hex)
{
    std::vector<uint8_t> bytes;
    
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        if (i + 1 >= hex.length())
            throw std::runtime_error("Invalid hex string length");
        
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        bytes.push_back(byte);
    }
    
    return bytes;
}

// 字节数组转十六进制字符串
std::string Utils::bytesToHex(const std::vector<uint8_t>& bytes)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (uint8_t byte : bytes)
        ss << std::setw(2) << static_cast<int>(byte);
    
    return ss.str();
}

// 字节数组转可打印字符串
std::string Utils::bytesToString(const std::vector<uint8_t>& bytes)
{
    std::string result;
    for (uint8_t byte : bytes)
    {
        if (byte >= 32 && byte <= 126) // 可打印ASCII字符
            result += static_cast<char>(byte);
        else
            result += '.';  // 不可打印字符用点表示
    }
    return result;
}

// 打印十六进制数据
void Utils::printHex(const std::string& label, const std::vector<uint8_t>& data)
{
    std::cout << label << ": " << bytesToHex(data) << std::endl;
}
