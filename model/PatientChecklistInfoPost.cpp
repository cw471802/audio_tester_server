// -*- encoding: utf-8 -*-
/*
@File    :   PatientChecklistInfoPost.cpp
@Time    :   2023/11/14 15:05:29
@Author  :   wei chen 
@Version :   
*/


#include "PatientChecklistInfoPost.h"
#include "Helpers.h"

namespace model {

PatientChecklistInfoPost::PatientChecklistInfoPost()
{
    m_PatientID = 0;
    m_CheckMode = "";
    m_CheckResult = 0.0;
    m_CheckSuggestion = "";
    m_CheckConclusion = "";
    m_CheckTime = "";
}


bool PatientChecklistInfoPost::validate() const
{
    bool success = true;
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
        success = false;
    }
    return success;
}

bool PatientChecklistInfoPost::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool PatientChecklistInfoPost::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "PatientChecklistInfoPost" : pathPrefix;

                                
    if (!m_Frequency.validate()) {
        msg << _pathPrefix << ": Frequency is invalid;";
        success = false;
    }
    return success;
}


void to_json(nlohmann::json& j, const PatientChecklistInfoPost& o)
{
    j = nlohmann::json();
    j["patientID"] = o.m_PatientID;
    j["environmentNoise"] = o.m_EnvironmentNoise;
    j["checkMode"] = o.m_CheckMode;
    j["checkResult"] = o.m_CheckResult;
    j["checkSuggestion"] = o.m_CheckSuggestion;
    j["checkConclusion"] = o.m_CheckConclusion;
    j["frequency"] = o.m_Frequency;
    j["checkTime"] = o.m_CheckTime;
}

void from_json(const nlohmann::json& j, PatientChecklistInfoPost& o)
{
    j.at("patientID").get_to(o.m_PatientID);
    j.at("environmentNoise").get_to(o.m_EnvironmentNoise);
    j.at("checkMode").get_to(o.m_CheckMode);
    j.at("checkResult").get_to(o.m_CheckResult);
    j.at("checkSuggestion").get_to(o.m_CheckSuggestion);
    j.at("checkConclusion").get_to(o.m_CheckConclusion);
    j.at("frequency").get_to(o.m_Frequency);
    j.at("checkTime").get_to(o.m_CheckTime);
}

int32_t PatientChecklistInfoPost::getPatientID() const
{
    return m_PatientID;
}
void PatientChecklistInfoPost::setPatientID(int32_t const value)
{
    m_PatientID = value;
}
std::vector<float> PatientChecklistInfoPost::getEnvironmentNoise() const
{
    return m_EnvironmentNoise;
}
void PatientChecklistInfoPost::setEnvironmentNoise(std::vector<float> const value)
{
    m_EnvironmentNoise = value;
}
std::string PatientChecklistInfoPost::getCheckMode() const
{
    return m_CheckMode;
}
void PatientChecklistInfoPost::setCheckMode(std::string const& value)
{
    m_CheckMode = value;
}
float PatientChecklistInfoPost::getCheckResult() const
{
    return m_CheckResult;
}
void PatientChecklistInfoPost::setCheckResult(double const value)
{
    m_CheckResult = value;
}
std::string PatientChecklistInfoPost::getCheckSuggestion() const
{
    return m_CheckSuggestion;
}
void PatientChecklistInfoPost::setCheckSuggestion(std::string const& value)
{
    m_CheckSuggestion = value;
}

std::string PatientChecklistInfoPost::getCheckConclusion() const
{
    return m_CheckConclusion;
}
void PatientChecklistInfoPost::setCheckConclusion(std::string const& value)
{
    m_CheckConclusion = value;
}
CheckinfoFrequency PatientChecklistInfoPost::getFrequency() const
{
    return m_Frequency;
}
void PatientChecklistInfoPost::setFrequency(CheckinfoFrequency const& value)
{
    m_Frequency = value;
}
std::string PatientChecklistInfoPost::getCheckTime() const
{
    return m_CheckTime;
}
void PatientChecklistInfoPost::setCheckTime(std::string const& value)
{
    m_CheckTime = value;
}

}