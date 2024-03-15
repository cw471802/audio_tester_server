/*** 
 * @Author: chen wei
 * @Date: 2024-01-22 17:44:50
 * @LastEditTime: 2024-01-22 17:45:22
 * @FilePath: /audio_tester_server/utils/PasswordGenerator.cpp
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#include "PasswordGenerator.h"
#include <cstdlib>
#include <ctime>
#include <vector>

PasswordGenerator::PasswordGenerator() {
    // 初始化随机数生成器
    srand(static_cast<unsigned int>(time(nullptr)));
}

std::string PasswordGenerator::generatePassword() {
    std::vector<char> chars = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 
        'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!', '@', '#', '$', '%', '&', '*'
    };

    std::string password;
    for (int i = 0; i < 12; ++i) {
        password += chars[rand() % chars.size()];
    }
    return password;
}