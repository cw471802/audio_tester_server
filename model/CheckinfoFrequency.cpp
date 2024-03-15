/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 16:08:50
 * @LastEditTime: 2023-12-05 14:15:46
 * @FilePath: /audio_tester_server/model/CheckinfoFrequency.cpp
 * @Description: 在不同纯音频率下，受试者的听力损失值
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "CheckinfoFrequency.h"
#include "Helpers.h"
namespace model {

CheckinfoFrequency::CheckinfoFrequency()
{
    
}

CheckinfoFrequency::~CheckinfoFrequency()
{
}

bool CheckinfoFrequency::validate() const
{
    bool success = true;
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
        success = false;
    }
    return true;
}

bool CheckinfoFrequency::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool CheckinfoFrequency::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "CheckinfoFrequency" : pathPrefix;

        
    if (!m_L.validate()) {
        msg << _pathPrefix << ": L is invalid;";
        success = false;
    }    
    if (!m_R.validate()) {
        msg << _pathPrefix << ": R is invalid;";
        success = false;
    }
    return success;
}


void to_json(nlohmann::json& j, const CheckinfoFrequency& o)
{
    j = nlohmann::json();
    j["L"] = o.m_L;
    j["R"] = o.m_R;
}

void from_json(const nlohmann::json& j, CheckinfoFrequency& o)
{
    j.at("L").get_to(o.m_L);
    j.at("R").get_to(o.m_R);
}

PureToneFrequency CheckinfoFrequency::getL() const
{
    return m_L;
}
void CheckinfoFrequency::setL(PureToneFrequency const& value)
{
    m_L = value;
}
PureToneFrequency CheckinfoFrequency::getR() const
{
    return m_R;
}
void CheckinfoFrequency::setR(PureToneFrequency const& value)
{
    m_R = value;
}

}