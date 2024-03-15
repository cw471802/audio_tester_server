/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 18:38:23
 * @LastEditTime: 2023-12-06 16:41:12
 * @FilePath: /audio_tester_server/model/PatientChecklistInfoPut.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "PatientChecklistInfoPut.h"
#include "Helpers.h"
namespace model {

PatientChecklistInfoPut::PatientChecklistInfoPut()
{
    m_EnvironmentNoiseIsSet = false;
    m_CheckMode = "";
    m_CheckModeIsSet = false;
    m_CheckResult = 0.0;
    m_CheckResultIsSet = false;
    m_CheckSuggestion = "";
    m_CheckSuggestionIsSet = false;
    
}


void PatientChecklistInfoPut::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool PatientChecklistInfoPut::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool PatientChecklistInfoPut::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "PatientChecklistInfoPut" : pathPrefix;

                    
    return success;
}


void to_json(nlohmann::json& j, const PatientChecklistInfoPut& o)
{
    j = nlohmann::json();
    if(o.checkModeIsSet())
        j["checkMode"] = o.m_CheckMode;
    if(o.checkResultIsSet())
        j["checkResult"] = o.m_CheckResult;
    if(o.checkSuggestionIsSet())
        j["checkSuggestion"] = o.m_CheckSuggestion;
}

void from_json(const nlohmann::json& j, PatientChecklistInfoPut& o)
{

    if(j.find("checkMode") != j.end())
    {
        j.at("checkMode").get_to(o.m_CheckMode);
        o.m_CheckModeIsSet = true;
    } 
    if(j.find("checkResult") != j.end())
    {
        j.at("checkResult").get_to(o.m_CheckResult);
        o.m_CheckResultIsSet = true;
    } 
    if(j.find("checkSuggestion") != j.end())
    {
        j.at("checkSuggestion").get_to(o.m_CheckSuggestion);
        o.m_CheckSuggestionIsSet = true;
    } 
}


std::string PatientChecklistInfoPut::getCheckMode() const
{
    return m_CheckMode;
}
void PatientChecklistInfoPut::setCheckMode(std::string const& value)
{
    m_CheckMode = value;
    m_CheckModeIsSet = true;
}
bool PatientChecklistInfoPut::checkModeIsSet() const
{
    return m_CheckModeIsSet;
}
void PatientChecklistInfoPut::unsetCheckMode()
{
    m_CheckModeIsSet = false;
}
double PatientChecklistInfoPut::getCheckResult() const
{
    return m_CheckResult;
}
void PatientChecklistInfoPut::setCheckResult(double const value)
{
    m_CheckResult = value;
    m_CheckResultIsSet = true;
}
bool PatientChecklistInfoPut::checkResultIsSet() const
{
    return m_CheckResultIsSet;
}
void PatientChecklistInfoPut::unsetCheckResult()
{
    m_CheckResultIsSet = false;
}
std::string PatientChecklistInfoPut::getCheckSuggestion() const
{
    return m_CheckSuggestion;
}
void PatientChecklistInfoPut::setCheckSuggestion(std::string const& value)
{
    m_CheckSuggestion = value;
    m_CheckSuggestionIsSet = true;
}
bool PatientChecklistInfoPut::checkSuggestionIsSet() const
{
    return m_CheckSuggestionIsSet;
}
void PatientChecklistInfoPut::unsetCheckSuggestion()
{
    m_CheckSuggestionIsSet = false;
}

}