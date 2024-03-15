
#include "VerificationCodeManager.h"
#include <random>
#include <cstring>
#include <glog/logging.h>

VerificationCodeManager::VerificationCodeManager(const std::string& host, int port, const std::string& _password)
    : password(_password) {
    this->connection = redisConnect(host.c_str(), port);
    if (this->connection == NULL || this->connection->err) {
        if (this->connection) {
            LOG(ERROR) << "Redis connection error: " << this->connection->errstr << std::endl;
        } else {
            LOG(ERROR) << "Redis connection error: cannot allocate redis context" << std::endl;
        }
        return;
    }

    // 进行密码认证
    redisReply* reply = (redisReply*)redisCommand(this->connection, "AUTH %s", password.c_str());
    if (reply == NULL || reply->type == REDIS_REPLY_ERROR) {
        if (reply) {
            LOG(ERROR) << "Auth error: " << reply->str << std::endl;
            freeReplyObject(reply);
        }
        redisFree(this->connection);
        this->connection = NULL;
        return;
    }
    freeReplyObject(reply);
}

VerificationCodeManager::~VerificationCodeManager() {
    if (this->connection != NULL) {
        redisFree(this->connection);
    }
}

std::string VerificationCodeManager::generateAndSaveCode(const std::string& phoneNumber) {
    if (canSendCode(phoneNumber)) {
        std::string code = generateCode(6);
        set("code:" + phoneNumber, code, 300); // 有效期5分钟
        incrementDailyCounter(phoneNumber);
        return code;
    } else {
        return "Daily limit reached";
    }
}

bool VerificationCodeManager::verifyCode(const std::string& phoneNumber, const std::string& code) {
    std::string storedCode = get("code:" + phoneNumber);
    return !storedCode.empty() && storedCode == code;
}

// Generate a random code of given length
std::string VerificationCodeManager::generateCode(int length) {
    const char* charset = "0123456789";
    std::string result;
    result.reserve(length);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, std::strlen(charset) - 1);

    for (int i = 0; i < length; i++) {
        result += charset[distribution(generator)];
    }

    return result;
}

// Check if it's possible to send a code (daily limit)
bool VerificationCodeManager::canSendCode(const std::string& phoneNumber) {
    int count = getInteger("dailyCounter:" + phoneNumber);
    return count < 10;
}

// Increment the daily counter for sending codes
void VerificationCodeManager::incrementDailyCounter(const std::string& phoneNumber) {
    std::string key = "dailyCounter:" + phoneNumber;
    increment(key);
    // Assuming reset at midnight, set to expire in 24 hours
    set(key, std::to_string(getInteger(key)), 86400);
}

// Redis set with expiration
void VerificationCodeManager::set(const std::string& key, const std::string& value, int timeout) {
    redisCommand(this->connection, "SET %s %s EX %d", key.c_str(), value.c_str(), timeout);
}

// Redis get
std::string VerificationCodeManager::get(const std::string& key) {
    redisReply* reply = (redisReply*)redisCommand(this->connection, "GET %s", key.c_str());
    std::string value = "";
    if (reply != NULL && reply->type == REDIS_REPLY_STRING) {
        value = reply->str;
    }
    freeReplyObject(reply);
    return value;
}

// Redis increment
void VerificationCodeManager::increment(const std::string& key) {
    redisCommand(this->connection, "INCR %s", key.c_str());
}

// Redis get integer value
int VerificationCodeManager::getInteger(const std::string& key) {
    redisReply* reply = (redisReply*)redisCommand(this->connection, "GET %s", key.c_str());
    int value = 0;
    if (reply != NULL && reply->type == REDIS_REPLY_STRING) {
        value = std::stoi(reply->str);
    }
    freeReplyObject(reply);
    return value;
}
