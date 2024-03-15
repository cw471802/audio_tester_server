/*** 
 * @Author: chen wei
 * @Date: 2024-02-28 10:01:52
 * @LastEditTime: 2024-02-28 10:03:26
 * @FilePath: /audio_tester/include/Translator.h
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */
#ifndef INCLUDE_TRANSLATOR_H
#define INCLUDE_TRANSLATOR_H

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class Translator {
public:
    Translator(const std::string& appid, const std::string& key);
    ~Translator();
    std::string translate(const std::string& query, const std::string& from, const std::string& to);

private:
    std::string appid_;
    std::string key_;
    std::string generateSignature(const std::string& query, const std::string& salt) const;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
    std::string parseResult(const std::string& json) const;
};

#endif // INCLUDE_TRANSLATOR_H
