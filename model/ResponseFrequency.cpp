/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 17:22:56
 * @LastEditTime: 2023-12-06 12:13:36
 * @FilePath: /audio_tester_server/model/ResponseFrequency.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "ResponseFrequency.h"
#include "Helpers.h"
namespace model {

ResponseFrequency::ResponseFrequency()
{
    
}

bool ResponseFrequency::validate() const
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

bool ResponseFrequency::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool ResponseFrequency::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "ResponseFrequency" : pathPrefix;

        
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

void to_json(nlohmann::json& j, const ResponseFrequency& o)
{
    j = nlohmann::json::object();
    j["L"] = o.m_L;
    j["R"] = o.m_R;
}

void from_json(const nlohmann::json& j, ResponseFrequency& o)
{
    j.at("L").get_to(o.m_L);
    j.at("R").get_to(o.m_R);
}

PureToneFrequency ResponseFrequency::getL() const
{
    return m_L;
}
void ResponseFrequency::setL(PureToneFrequency const& value)
{
    m_L = value;
}
PureToneFrequency ResponseFrequency::getR() const
{
    return m_R;
}
void ResponseFrequency::setR(PureToneFrequency const& value)
{
    m_R = value;
}

}