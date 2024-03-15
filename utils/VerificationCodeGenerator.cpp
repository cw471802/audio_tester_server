/*** 
 * @Author: chen wei
 * @Date: 2024-01-22 11:15:33
 * @LastEditTime: 2024-01-22 16:21:20
 * @FilePath: /audio_tester_server/utils/VerificationCodeGenerator.cpp
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#include <VerificationCodeGenerator.h>
#include <cstdlib>
#include <ctime>
#include <sstream>

VerificationCodeGenerator::VerificationCodeGenerator()
{
    // 初始化随机数生成器
    srand(static_cast<unsigned int>(time(nullptr)));
}

std::string VerificationCodeGenerator::generateCode() {  
    std::stringstream ss;
    for (int i = 0; i < 6; ++i) {
        ss << (rand() % 10); // 生成一个0到9之间的随机数并添加到字符串流
    }
    return ss.str(); 
}