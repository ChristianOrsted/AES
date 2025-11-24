#include "AESModes.h"
#include <cstring>
#include <stdexcept>

// PKCS7填充
std::vector<uint8_t> AESModes::pkcs7Padding(const std::vector<uint8_t>& data, int blockSize)
{
    int paddingLength = blockSize - (data.size() % blockSize);
    std::vector<uint8_t> padded = data;
    for (int i = 0; i < paddingLength; i++)
        padded.push_back(static_cast<uint8_t>(paddingLength));
    return padded;
}

// 移除PKCS7填充
std::vector<uint8_t> AESModes::removePkcs7Padding(const std::vector<uint8_t>& data) {
    if (data.empty())
        throw std::runtime_error("Empty data for padding removal");
    
    uint8_t paddingLength = data.back();
    if (paddingLength == 0 || paddingLength > AES::BLOCK_SIZE)
        throw std::runtime_error("Invalid padding");
    
    // 验证填充的正确性
    for (size_t i = data.size() - paddingLength; i < data.size(); i++)
    {
        if (data[i] != paddingLength)
            throw std::runtime_error("Invalid padding bytes");
    }
    
    std::vector<uint8_t> result(data.begin(), data.end() - paddingLength);
    return result;
}

// CBC模式加密
std::vector<uint8_t> AESModes::encryptCBC(const std::vector<uint8_t>& plaintext, 
                                          const std::vector<uint8_t>& key,
                                          const std::vector<uint8_t>& iv)
{
    AES aes(key);
    std::vector<uint8_t> padded = pkcs7Padding(plaintext, AES::BLOCK_SIZE);
    std::vector<uint8_t> ciphertext(padded.size());
    
    uint8_t previousBlock[AES::BLOCK_SIZE];
    memcpy(previousBlock, iv.data(), AES::BLOCK_SIZE);
    
    for (size_t i = 0; i < padded.size(); i += AES::BLOCK_SIZE)
    {
        uint8_t block[AES::BLOCK_SIZE];
        
        // XOR with previous ciphertext block (or IV for first block)
        for (int j = 0; j < AES::BLOCK_SIZE; j++)
            block[j] = padded[i + j] ^ previousBlock[j];
        
        // Encrypt block
        uint8_t encrypted[AES::BLOCK_SIZE];
        aes.encryptBlock(block, encrypted);
        
        // Store encrypted block
        memcpy(&ciphertext[i], encrypted, AES::BLOCK_SIZE);
        memcpy(previousBlock, encrypted, AES::BLOCK_SIZE);
    }
    
    return ciphertext;
}

// CBC模式解密
std::vector<uint8_t> AESModes::decryptCBC(const std::vector<uint8_t>& ciphertext, 
                                          const std::vector<uint8_t>& key,
                                          const std::vector<uint8_t>& iv) {
    if (ciphertext.size() % AES::BLOCK_SIZE != 0)
        throw std::runtime_error("Ciphertext size must be multiple of block size");
    
    AES aes(key);
    std::vector<uint8_t> plaintext(ciphertext.size());
    
    uint8_t previousBlock[AES::BLOCK_SIZE];
    memcpy(previousBlock, iv.data(), AES::BLOCK_SIZE);
    
    for (size_t i = 0; i < ciphertext.size(); i += AES::BLOCK_SIZE)
    {
        uint8_t decrypted[AES::BLOCK_SIZE];
        
        // Decrypt block
        aes.decryptBlock(&ciphertext[i], decrypted);
        
        // XOR with previous ciphertext block (or IV for first block)
        for (int j = 0; j < AES::BLOCK_SIZE; j++)
            plaintext[i + j] = decrypted[j] ^ previousBlock[j];
        
        // Save current ciphertext block for next iteration
        memcpy(previousBlock, &ciphertext[i], AES::BLOCK_SIZE);
    }
    
    // Remove padding
    return removePkcs7Padding(plaintext);
}

// 计数器递增
void AESModes::incrementCounter(uint8_t* counter, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        counter[i]++;
        if (counter[i] != 0) break;  // 没有溢出则停止
    }
}

// CTR模式加密
std::vector<uint8_t> AESModes::encryptCTR(const std::vector<uint8_t>& plaintext, 
                                          const std::vector<uint8_t>& key,
                                          const std::vector<uint8_t>& nonce) {
    AES aes(key);
    std::vector<uint8_t> ciphertext(plaintext.size());
    
    uint8_t counter[AES::BLOCK_SIZE];
    memcpy(counter, nonce.data(), AES::BLOCK_SIZE);
    
    for (size_t i = 0; i < plaintext.size(); i += AES::BLOCK_SIZE)
    {
        uint8_t keystream[AES::BLOCK_SIZE];
        
        // Encrypt counter to get keystream
        aes.encryptBlock(counter, keystream);
        
        // XOR keystream with plaintext
        size_t blockSize = std::min(static_cast<size_t>(AES::BLOCK_SIZE), 
                                    plaintext.size() - i);
        for (size_t j = 0; j < blockSize; j++)
            ciphertext[i + j] = plaintext[i + j] ^ keystream[j];
        
        // Increment counter
        incrementCounter(counter, AES::BLOCK_SIZE);
    }
    
    return ciphertext;
}

// CTR模式解密（与加密相同）
std::vector<uint8_t> AESModes::decryptCTR(const std::vector<uint8_t>& ciphertext, 
                                          const std::vector<uint8_t>& key,
                                          const std::vector<uint8_t>& nonce)
{
    // CTR mode: decryption is identical to encryption
    return encryptCTR(ciphertext, key, nonce);
}
