/*** 
 * @Author: chen wei
 * @Date: 2024-02-28 10:03:43
 * @LastEditTime: 2024-02-28 10:06:54
 * @FilePath: /audio_tester/utils/Translator.cpp
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */
#include "Translator.h"
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <curl/curl.h>

Translator::Translator(const std::string& appid, const std::string& key) : appid_(appid), key_(key) {
    curl_global_init(CURL_GLOBAL_ALL);
}

Translator::~Translator() {
    curl_global_cleanup();
}

std::string Translator::generateSignature(const std::string& query, const std::string& salt) const {
    std::string base = appid_ + query + salt + key_;

    unsigned char result[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(base.c_str()), base.length(), result);

    std::ostringstream hexStream;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)result[i];
    }
    return hexStream.str();
}

size_t Translator::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string Translator::translate(const std::string& query, const std::string& from, const std::string& to) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    std::string salt = "123456"; // Example salt
    std::string signature = generateSignature(query, salt);

    if (curl) {
        std::string url = "https://fanyi-api.baidu.com/api/trans/vip/translate?";
        url += "q=" + std::string(curl_easy_escape(curl, query.c_str(), static_cast<int>(query.length())));
        url += "&from=" + from + "&to=" + to;
        url += "&appid=" + appid_;
        url += "&salt=" + salt;
        url += "&sign=" + signature;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }

    return parseResult(readBuffer);
}

std::string Translator::parseResult(const std::string& json) const {
    nlohmann::json json_obj = nlohmann::json::parse(json);
    return json_obj["trans_result"][0]["dst"];
}