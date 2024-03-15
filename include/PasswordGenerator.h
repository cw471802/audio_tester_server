/*** 
 * @Author: chen wei
 * @Date: 2024-01-22 17:38:47
 * @LastEditTime: 2024-01-22 17:44:19
 * @FilePath: /audio_tester_server/include/PasswordGenerator.h
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_PASSWORD_GENERATOR_H
#define INCLUDE_PASSWORD_GENERATOR_H

#include <iostream>

class PasswordGenerator {
public:
    PasswordGenerator();  // 构造函数
    std::string generatePassword();   // 生成密码的方法
};

#endif //INCLUDE_PASSWORD_GENERATOR_H