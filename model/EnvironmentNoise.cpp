/*** 
 * @Author: chen wei
 * @Date: 2024-01-15 15:52:33
 * @LastEditTime: 2024-01-15 16:00:30
 * @FilePath: /audio_tester_server/model/EnvironmentNoise.cpp
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */


#include "EnvironmentNoise.h"

namespace model {

EnvironmentNoise::EnvironmentNoise()
{
    
}

EnvironmentNoise::~EnvironmentNoise()
{
}

void EnvironmentNoise::validate()
{
    // TODO: implement validation
}

void to_json(nlohmann::json& j, const EnvironmentNoise& o)
{
    j = nlohmann::json();
    j["noise"] = o.m_Noise;
}

void from_json(const nlohmann::json& j, EnvironmentNoise& o)
{
    j.at("noise").get_to(o.m_Noise);
}

std::vector<float>& EnvironmentNoise::getNoise()
{
    return m_Noise;
}
void EnvironmentNoise::setNoise(std::vector<float> const value)
{
    m_Noise = value;
}

}