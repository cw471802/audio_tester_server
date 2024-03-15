/*** 
 * @Author: chen wei
 * @Date: 2023-11-20 10:05:24
 * @LastEditTime: 2023-11-21 15:28:03
 * @FilePath: /audio_tester_server/include/CryptoppAes.h
 * @Description: 用户密码存储的加密和解密，采用AES方法
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */
#ifndef INCLUDE_CRYTOPP_AES_H
#define INCLUDE_CRYTOPP_AES_H

#include <cryptopp/cryptlib.h>
#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>


class CryptoppAes
{
public:
    CryptoppAes();
    ~CryptoppAes();
    /*** 
     * @brief 使用AES算法进行加密
     * @param {string} plaintext
     * @return {*}
     */    
    static std::string AesEncrypt(std::string plaintext);
    /*** 
     * @brief 使用AES算法进行解密
     * @param {string} ciphertext
     * @return {*}
     */    
    static std::string AesDecrypt(std::string ciphertext);

};

#endif // INCLUDE_CRYTOPP_AES_H