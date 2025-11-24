#ifndef AES_MODES_H
#define AES_MODES_H

#include "AES.h"
#include <vector>

class AESModes
{
public:
    // CBC模式加密
    static std::vector<uint8_t> encryptCBC(const std::vector<uint8_t>& plaintext, 
                                           const std::vector<uint8_t>& key,
                                           const std::vector<uint8_t>& iv);
    
    // CBC模式解密
    static std::vector<uint8_t> decryptCBC(const std::vector<uint8_t>& ciphertext, 
                                           const std::vector<uint8_t>& key,
                                           const std::vector<uint8_t>& iv);
    
    // CTR模式加密
    static std::vector<uint8_t> encryptCTR(const std::vector<uint8_t>& plaintext, 
                                           const std::vector<uint8_t>& key,
                                           const std::vector<uint8_t>& nonce);
    
    // CTR模式解密
    static std::vector<uint8_t> decryptCTR(const std::vector<uint8_t>& ciphertext, 
                                           const std::vector<uint8_t>& key,
                                           const std::vector<uint8_t>& nonce);

private:
    // PKCS7填充
    static std::vector<uint8_t> pkcs7Padding(const std::vector<uint8_t>& data, int blockSize);
    
    // 移除PKCS7填充
    static std::vector<uint8_t> removePkcs7Padding(const std::vector<uint8_t>& data);
    
    // 计数器递增
    static void incrementCounter(uint8_t* counter, int size);
};

#endif // AES_MODES_H
