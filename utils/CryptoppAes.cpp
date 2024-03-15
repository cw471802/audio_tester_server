/*** 
 * @Author: chen wei
 * @Date: 2023-11-20 11:13:08
 * @LastEditTime: 2023-11-21 17:03:22
 * @FilePath: /audio_tester_server/utils/CryptoppAes.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "CryptoppAes.h"
#include <cryptopp/rijndael.h>

char key[] = "9d906013b5e97a0d";


std::string CryptoppAes::AesEncrypt(std::string plaintext)
{
    std::string encrypt_str;
 
    try 
    {
        CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption ecb_encription((unsigned char*)key, 16);
        CryptoPP::StreamTransformationFilter stf_encription(
            ecb_encription,
            new CryptoPP::HexEncoder(new CryptoPP::StringSink(encrypt_str)),
            CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
        );
        stf_encription.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length() + 1);
        stf_encription.MessageEnd();
        return encrypt_str;
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
        return "";
    }
}

std::string CryptoppAes::AesDecrypt(std::string ciphertext)
{
    try
    {
        std::string aes_encrypt_data;
        CryptoPP::HexDecoder decoder;
        decoder.Attach(new CryptoPP::StringSink(aes_encrypt_data));
        decoder.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.length());
        decoder.MessageEnd();
 
        std::string decrypt_data;
        CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption ebc_description((unsigned char*)key, 16);
        CryptoPP::StreamTransformationFilter stf_description(
            ebc_description,
            new CryptoPP::StringSink(decrypt_data),
            CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
        );
 
        stf_description.Put(
            reinterpret_cast<const unsigned char*>(aes_encrypt_data.c_str()),
            aes_encrypt_data.length()
        );
        stf_description.MessageEnd();
 
        return decrypt_data;
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
        return "";
    }
}