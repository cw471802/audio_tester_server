/*** 
 * @Author: chen wei
 * @Date: 2023-11-23 17:12:18
 * @LastEditTime: 2024-03-01 09:35:11
 * @FilePath: /audio_tester/model/PureToneFrequency.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "PureToneFrequency.h"
#include "Helpers.h"

namespace model {

PureToneFrequency::PureToneFrequency()
{
    m_125 = 0.0f;
    m_125IsSet = false;
    m_250 = 0.0f;
    m_250IsSet = false;
    m_500 = 0.0f;
    m_4000 = 0.0f;
    m_6000 = 0.0f;
    m_6000IsSet = false;
    m_8000 = 0.0f;
    m_8000IsSet = false;
    m_1000s = 0.0f;
    m_2000 = 0.0f;
    m_1000e = 0.0f;
}


bool PureToneFrequency::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
        return false;
    }
    return true;
}

bool PureToneFrequency::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool PureToneFrequency::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "PureToneFrequency" : pathPrefix;

                                            
    return success;
}

void to_json(nlohmann::json& j, const PureToneFrequency& o)
{
    j = nlohmann::json();
    if(o.t125IsSet())
        j["125"] = o.m_125;
    if(o.t250IsSet())
        j["250"] = o.m_250;
    j["500"] = o.m_500;
    j["2000"] = o.m_2000;
    j["4000"] = o.m_4000;
    if(o.t6000IsSet())
        j["6000"] = o.m_6000;
    if(o.t8000IsSet())
        j["8000"] = o.m_8000;
    j["1000s"] = o.m_1000s;
    
    j["1000e"] = o.m_1000e;
}

void from_json(const nlohmann::json& j, PureToneFrequency& o)
{
    if(j.find("125") != j.end())
    {
        j.at("125").get_to(o.m_125);
        o.m_125IsSet = true;
    } 
    if(j.find("250") != j.end())
    {
        j.at("250").get_to(o.m_250);
        o.m_250IsSet = true;
    } 
    j.at("500").get_to(o.m_500);
    j.at("4000").get_to(o.m_4000);
    if(j.find("6000") != j.end())
    {
        j.at("6000").get_to(o.m_6000);
        o.m_6000IsSet = true;
    } 
    if(j.find("8000") != j.end())
    {
        j.at("8000").get_to(o.m_8000);
        o.m_8000IsSet = true;
    } 
    j.at("1000s").get_to(o.m_1000s);
    j.at("2000").get_to(o.m_2000);
    j.at("1000e").get_to(o.m_1000e);
}

float PureToneFrequency::get125() const
{
    return m_125;
}
void PureToneFrequency::set125(float const value)
{
    m_125 = value;
    m_125IsSet = true;
}
bool PureToneFrequency::t125IsSet() const
{
    return m_125IsSet;
}
void PureToneFrequency::unset_125()
{
    m_125IsSet = false;
}
float PureToneFrequency::get250() const
{
    return m_250;
}
void PureToneFrequency::set250(float const value)
{
    m_250 = value;
    m_250IsSet = true;
}
bool PureToneFrequency::t250IsSet() const
{
    return m_250IsSet;
}
void PureToneFrequency::unset_250()
{
    m_250IsSet = false;
}
float PureToneFrequency::get500() const
{
    return m_500;
}
void PureToneFrequency::set500(float const value)
{
    m_500 = value;
}

float PureToneFrequency::get4000() const
{
    return m_4000;
}
void PureToneFrequency::set4000(float const value)
{
    m_4000 = value;
}
float PureToneFrequency::get6000() const
{
    return m_6000;
}
void PureToneFrequency::set6000(float const value)
{
    m_6000 = value;
    m_6000IsSet = true;
}
bool PureToneFrequency::t6000IsSet() const
{
    return m_6000IsSet;
}
void PureToneFrequency::unset_6000()
{
    m_6000IsSet = false;
}
float PureToneFrequency::get8000() const
{
    return m_8000;
}
void PureToneFrequency::set8000(float const value)
{
    m_8000 = value;
    m_8000IsSet = true;
}
bool PureToneFrequency::t8000IsSet() const
{
    return m_8000IsSet;
}
void PureToneFrequency::unset_8000()
{
    m_8000IsSet = false;
}
float PureToneFrequency::get1000s() const
{
    return m_1000s;
}
void PureToneFrequency::set1000s(float const value)
{
    m_1000s = value;
}
float PureToneFrequency::get2000() const
{
    return m_2000;
}
void PureToneFrequency::set2000(float const value)
{
    m_2000 = value;
}
float PureToneFrequency::get1000e() const
{
    return m_1000e;
}
void PureToneFrequency::set1000e(float const value)
{
    m_1000e = value;
}

}