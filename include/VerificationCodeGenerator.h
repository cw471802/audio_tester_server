/*** 
 * @Author: chen wei
 * @Date: 2024-01-22 11:11:55
 * @LastEditTime: 2024-01-22 16:20:47
 * @FilePath: /audio_tester_server/include/VerificationCodeGenerator.h
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#include <iostream>
#include <random>

#ifndef INCLUDE_VERIFICATION_CODE_GENERATOR_H
#define INCLUDE_VERIFICATION_CODE_GENERATOR_H
// extern int h_errno;


class VerificationCodeGenerator
{
public:
    VerificationCodeGenerator();
    std::string  generateCode();
};

#endif // INCLUDE_VERIFICATION_CODE_GENERATOR_H