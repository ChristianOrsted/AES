#ifndef AES_H
#define AES_H
#include <cstdint>
#include <vector>
#include <string>

class AES
{
public:
    // AES-128: 密钥长度为128位(16字节)
    static const int BLOCK_SIZE = 16;  // 128位 = 16字节
    static const int KEY_SIZE = 16;    // AES-128
    static const int NK = 4;           // 密钥字数
    static const int NR = 10;          // 轮数

    AES();
    explicit AES(const std::vector<uint8_t>& key);
    
    // 设置密钥
    void setKey(const std::vector<uint8_t>& key);
    
    // AES加密单个块（16字节）
    void encryptBlock(const uint8_t* input, uint8_t* output);
    
    // AES解密单个块（16字节）
    void decryptBlock(const uint8_t* input, uint8_t* output);

private:
    std::vector<uint8_t> roundKeys;  // 扩展后的轮密钥
    
    // 密钥扩展
    void keyExpansion(const std::vector<uint8_t>& key);
    
    // AES加密的四个基本操作
    void subBytes(uint8_t state[4][4]);
    void shiftRows(uint8_t state[4][4]);
    void mixColumns(uint8_t state[4][4]);
    void addRoundKey(uint8_t state[4][4], int round);
    
    // AES解密的四个基本操作
    void invSubBytes(uint8_t state[4][4]);
    void invShiftRows(uint8_t state[4][4]);
    void invMixColumns(uint8_t state[4][4]);
    
    // 辅助函数
    uint8_t gmul(uint8_t a, uint8_t b);  // 伽罗瓦域乘法
    
    // S盒和逆S盒
    static const uint8_t sbox[256];
    static const uint8_t inv_sbox[256];
    static const uint8_t rcon[11];
};

#endif
