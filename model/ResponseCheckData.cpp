/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 17:50:54
 * @LastEditTime: 2023-12-06 11:56:44
 * @FilePath: /audio_tester_server/model/ResponseCheckData.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "ResponseCheckData.h"
#include "Helpers.h"

namespace model {

ResponseCheckData::ResponseCheckData()
{
    //m_EnvironmentNoise = std::vector<float>;
    m_CheckMode = "";
    m_CheckResult = 0.0;
    m_CheckSuggestion = "";
    m_CheckTime = 0;
}



void ResponseCheckData::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool ResponseCheckData::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool ResponseCheckData::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "ResponseCheckData" : pathPrefix;

                            
    if (!m_Frequency.validate()) {
        msg << _pathPrefix << ": Frequency is invalid;";
        success = false;
    }
    return success;
}


void to_json(nlohmann::json& j, const ResponseCheckData& o)
{
    j = nlohmann::json();
    j["environmentNoise"] = o.m_EnvironmentNoise;
    j["checkMode"] = o.m_CheckMode;
    j["checkResult"] = o.m_CheckResult;
    j["checkSuggestion"] = o.m_CheckSuggestion;
    j["checkTime"] = o.m_CheckTime;
    j["frequency"] = o.m_Frequency;
}

void from_json(const nlohmann::json& j, ResponseCheckData& o)
{
    j.at("environmentNoise").get_to(o.m_EnvironmentNoise);
    j.at("checkMode").get_to(o.m_CheckMode);
    j.at("checkResult").get_to(o.m_CheckResult);
    j.at("checkSuggestion").get_to(o.m_CheckSuggestion);
    j.at("checkTime").get_to(o.m_CheckTime);
    j.at("frequency").get_to(o.m_Frequency);
}

std::vector<float> ResponseCheckData::getEnvironmentNoise() const
{
    return m_EnvironmentNoise;
}
void ResponseCheckData::setEnvironmentNoise(std::vector<float> const value)
{
    m_EnvironmentNoise = value;
}
std::string ResponseCheckData::getCheckMode() const
{
    return m_CheckMode;
}
void ResponseCheckData::setCheckMode(std::string const& value)
{
    m_CheckMode = value;
}
double ResponseCheckData::getCheckResult() const
{
    return m_CheckResult;
}
void ResponseCheckData::setCheckResult(double const value)
{
    m_CheckResult = value;
}
std::string ResponseCheckData::getCheckSuggestion() const
{
    return m_CheckSuggestion;
}
void ResponseCheckData::setCheckSuggestion(std::string const& value)
{
    m_CheckSuggestion = value;
}
int32_t ResponseCheckData::getCheckTime() const
{
    return m_CheckTime;
}
void ResponseCheckData::setCheckTime(int32_t const value)
{
    m_CheckTime = value;
}
ResponseFrequency ResponseCheckData::getFrequency() const
{
    return m_Frequency;
}
void ResponseCheckData::setFrequency(ResponseFrequency const& value)
{
    m_Frequency = value;
}

}