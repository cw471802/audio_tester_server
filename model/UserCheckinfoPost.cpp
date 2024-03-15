/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 16:53:01
 * @LastEditTime: 2024-03-01 10:04:29
 * @FilePath: /audio_tester/model/UserCheckinfoPost.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "UserCheckinfoPost.h"
#include "Helpers.h"

namespace model {

UserCheckinfoPost::UserCheckinfoPost()
{
    m_UserID = 0;
    // m_EnvironmentNoise = 0.0f;
    m_CheckMode = "";
    m_CheckResult = 0.0f;
    m_CheckSuggestion = "";
    m_CheckConclusion = "";
    m_CheckTime = "";
    
}

UserCheckinfoPost::~UserCheckinfoPost()
{
}

void UserCheckinfoPost::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool UserCheckinfoPost::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool UserCheckinfoPost::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "UserCheckinfoPost" : pathPrefix;

                                
    if (!m_Frequency.validate()) {
        msg << _pathPrefix << ": Frequency is invalid;";
        success = false;
    }
    return success;
}


void to_json(nlohmann::json& j, const UserCheckinfoPost& o)
{
    j = nlohmann::json();
    j["userID"] = o.m_UserID;
    j["environmentNoise"] = o.m_EnvironmentNoise;
    j["checkMode"] = o.m_CheckMode;
    j["checkResult"] = o.m_CheckResult;
    j["checkSuggestion"] = o.m_CheckSuggestion;
    j["checkConclusion"] = o.m_CheckConclusion;
    j["checkTime"] = o.m_CheckTime;
    j["frequency"] = o.m_Frequency;
}

void from_json(const nlohmann::json& j, UserCheckinfoPost& o)
{
    j.at("userID").get_to(o.m_UserID);
    j.at("environmentNoise").get_to(o.m_EnvironmentNoise);
    j.at("checkMode").get_to(o.m_CheckMode);
    j.at("checkResult").get_to(o.m_CheckResult);
    j.at("checkSuggestion").get_to(o.m_CheckSuggestion);
    j.at("checkConclusion").get_to(o.m_CheckConclusion);
    j.at("checkTime").get_to(o.m_CheckTime);
    j.at("frequency").get_to(o.m_Frequency);
}

int32_t UserCheckinfoPost::getUserID() const
{
    return m_UserID;
}
void UserCheckinfoPost::setUserID(int32_t const value)
{
    m_UserID = value;
}
std::vector<float> UserCheckinfoPost::getEnvironmentNoise() const
{
    return m_EnvironmentNoise;
}
void UserCheckinfoPost::setEnvironmentNoise(std::vector<float> const value)
{
    m_EnvironmentNoise = value;
}
std::string UserCheckinfoPost::getCheckMode() const
{
    return m_CheckMode;
}
void UserCheckinfoPost::setCheckMode(std::string const& value)
{
    m_CheckMode = value;
}
float UserCheckinfoPost::getCheckResult() const
{
    return m_CheckResult;
}
void UserCheckinfoPost::setCheckResult(float const value)
{
    m_CheckResult = value;
}
std::string UserCheckinfoPost::getCheckSuggestion() const
{
    return m_CheckSuggestion;
}
void UserCheckinfoPost::setCheckSuggestion(std::string const& value)
{
    m_CheckSuggestion = value;
}
std::string UserCheckinfoPost::getCheckConclusion() const
{
    return m_CheckConclusion;
}
void UserCheckinfoPost::setCheckConclusion(std::string const& value)
{
    m_CheckConclusion = value;
}
std::string UserCheckinfoPost::getCheckTime() const
{
    return m_CheckTime;
}
void UserCheckinfoPost::setCheckTime(std::string const& value)
{
    m_CheckTime = value;
}
CheckinfoFrequency UserCheckinfoPost::getFrequency() const
{
    return m_Frequency;
}
void UserCheckinfoPost::setFrequency(CheckinfoFrequency const& value)
{
    m_Frequency = value;
}

}