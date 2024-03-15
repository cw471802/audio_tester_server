/*** 
 * @Author: chen wei
 * @Date: 2024-02-28 10:14:34
 * @LastEditTime: 2024-02-28 12:16:24
 * @FilePath: /audio_tester/include/VerificationCodeManager.h
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_VERIFICATIONCODEMANAGER_H
#define INCLUDE_VERIFICATIONCODEMANAGER_H

#include <hiredis/hiredis.h>
#include <string>

class VerificationCodeManager {
public:
    VerificationCodeManager(const std::string& host, int port, const std::string& password);
    ~VerificationCodeManager();

    std::string generateAndSaveCode(const std::string& phoneNumber);
    bool verifyCode(const std::string& phoneNumber, const std::string& code);

private:
    redisContext* connection;
    std::string password;
    std::string generateCode(int length);
    bool canSendCode(const std::string& phoneNumber);
    void incrementDailyCounter(const std::string& phoneNumber);
    void set(const std::string& key, const std::string& value, int timeout);
    std::string get(const std::string& key);
    void increment(const std::string& key);
    int getInteger(const std::string& key);
};

#endif // INCLUDE_VERIFICATIONCODEMANAGER_H