#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cstdint>

class Utils
{
public:
    // 十六进制字符串转字节数组
    static std::vector<uint8_t> hexToBytes(const std::string& hex);
    
    // 字节数组转十六进制字符串
    static std::string bytesToHex(const std::vector<uint8_t>& bytes);
    
    // 字节数组转可打印字符串（处理不可打印字符）
    static std::string bytesToString(const std::vector<uint8_t>& bytes);
    
    // 打印十六进制数据
    static void printHex(const std::string& label, const std::vector<uint8_t>& data);
};

#endif // UTILS_H
