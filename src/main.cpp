#include "AES.h"
#include "AESModes.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

void printSeparator()
{
    std::cout << "\n" << std::string(80, '=') << "\n" << std::endl;
}

void testCBCCase(int caseNum, const std::string& keyHex, const std::string& ciphertextHex) {
    std::cout << "Case " << caseNum << " - CBC Mode Decryption:" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    try
    {
        // 转换密钥和密文
        std::vector<uint8_t> key = Utils::hexToBytes(keyHex);
        std::vector<uint8_t> ciphertext = Utils::hexToBytes(ciphertextHex);
        
        // 提取IV（前16字节）和实际密文
        std::vector<uint8_t> iv(ciphertext.begin(), ciphertext.begin() + AES::BLOCK_SIZE);
        std::vector<uint8_t> actualCiphertext(ciphertext.begin() + AES::BLOCK_SIZE, ciphertext.end());
        
        // 打印信息
        Utils::printHex("Key", key);
        Utils::printHex("IV", iv);
        std::cout << "Ciphertext length: " << actualCiphertext.size() << " bytes" << std::endl;
        
        // 解密
        std::vector<uint8_t> plaintext = AESModes::decryptCBC(actualCiphertext, key, iv);
        
        // 打印结果
        std::cout << "\nDecrypted plaintext (hex): " << Utils::bytesToHex(plaintext) << std::endl;
        std::cout << "Decrypted plaintext (text): " << Utils::bytesToString(plaintext) << std::endl;
        
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    printSeparator();
}

void testCTRCase(int caseNum, const std::string& keyHex, const std::string& ciphertextHex) {
    std::cout << "Case " << caseNum << " - CTR Mode Decryption:" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    try
    {
        // 转换密钥和密文
        std::vector<uint8_t> key = Utils::hexToBytes(keyHex);
        std::vector<uint8_t> ciphertext = Utils::hexToBytes(ciphertextHex);
        
        // 提取Nonce（前16字节）和实际密文
        std::vector<uint8_t> nonce(ciphertext.begin(), ciphertext.begin() + AES::BLOCK_SIZE);
        std::vector<uint8_t> actualCiphertext(ciphertext.begin() + AES::BLOCK_SIZE, ciphertext.end());
        
        // 打印信息
        Utils::printHex("Key", key);
        Utils::printHex("Nonce", nonce);
        std::cout << "Ciphertext length: " << actualCiphertext.size() << " bytes" << std::endl;
        
        // 解密
        std::vector<uint8_t> plaintext = AESModes::decryptCTR(actualCiphertext, key, nonce);
        
        // 打印结果
        std::cout << "\nDecrypted plaintext (hex): " << Utils::bytesToHex(plaintext) << std::endl;
        std::cout << "Decrypted plaintext (text): " << Utils::bytesToString(plaintext) << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    printSeparator();
}

void demonstrateEncryption()
{
    std::cout << "Demonstration - Encryption and Decryption:" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    // 准备测试数据
    std::string plaintextStr = "Hello, AES-CBC!";
    std::vector<uint8_t> plaintext(plaintextStr.begin(), plaintextStr.end());
    
    std::string keyHex = "140b41b22a29beb4061bda66b6747e14";
    std::vector<uint8_t> key = Utils::hexToBytes(keyHex);
    
    std::string ivHex = "4ca00ff4c898d61e1edbf1800618fb28";
    std::vector<uint8_t> iv = Utils::hexToBytes(ivHex);
    
    std::cout << "Original plaintext: " << plaintextStr << std::endl;
    Utils::printHex("Key", key);
    Utils::printHex("IV", iv);
    
    // CBC加密
    std::vector<uint8_t> ciphertext = AESModes::encryptCBC(plaintext, key, iv);
    std::cout << "\nCBC Encrypted ciphertext (hex):" << std::endl;
    std::cout << Utils::bytesToHex(ciphertext) << std::endl;
    
    // CBC解密
    std::vector<uint8_t> decrypted = AESModes::decryptCBC(ciphertext, key, iv);
    std::cout << "\nCBC Decrypted plaintext: " << Utils::bytesToString(decrypted) << std::endl;
    
    // CTR模式测试
    std::vector<uint8_t> ctrCiphertext = AESModes::encryptCTR(plaintext, key, iv);
    std::cout << "\nCTR Encrypted ciphertext (hex):" << std::endl;
    std::cout << Utils::bytesToHex(ctrCiphertext) << std::endl;
    
    std::vector<uint8_t> ctrDecrypted = AESModes::decryptCTR(ctrCiphertext, key, iv);
    std::cout << "\nCTR Decrypted plaintext: " << Utils::bytesToString(ctrDecrypted) << std::endl;
    
    printSeparator();
}

int main()
{
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           AES Encryption/Decryption System                     ║" << std::endl;
    std::cout << "║           CBC Mode & CTR Mode Implementation                   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════╝" << std::endl;
    printSeparator();
    
    // 加密解密演示
    demonstrateEncryption();
    
    // 测试用例1 - CBC
    testCBCCase(1, 
        "140b41b22a29beb4061bda66b6747e14",
        "4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81"
    );
    
    // 测试用例2 - CBC
    testCBCCase(2,
        "140b41b22a29beb4061bda66b6747e14",
        "5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253"
    );
    
    // 测试用例3 - CTR
    testCTRCase(3,
        "36f18357be4dbd77f050515c73fcf9f2",
        "69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329"
    );
    
    // 测试用例4 - CTR
    testCTRCase(4,
        "36f18357be4dbd77f050515c73fcf9f2",
        "770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451"
    );
    
    std::cout << "All test cases completed!" << std::endl;
    std::cout << "\n";
    
    return 0;
}
