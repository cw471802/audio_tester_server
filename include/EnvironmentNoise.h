/*** 
 * @Author: chen wei
 * @Date: 2024-01-15 15:47:34
 * @LastEditTime: 2024-01-15 16:00:10
 * @FilePath: /audio_tester_server/include/EnvironmentNoise.h
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_DOCTOR_ENVIRONMENT_NOISE_POST_H
#define INCLUDE_DOCTOR_ENVIRONMENT_NOISE_POST_H

#include <string>
#include <nlohmann/json.hpp>

namespace model {
/// <summary>
/// 检查时环境噪音
/// </summary>
class  EnvironmentNoise
{
public:
    EnvironmentNoise();
    virtual ~EnvironmentNoise();

    void validate();

    /////////////////////////////////////////////
    /// environmentNoise members

    /// <summary>
    /// 
    /// </summary>
    std::vector<float>& getNoise();
    void setNoise(std::vector<float> const value);

    friend void to_json(nlohmann::json& j, const EnvironmentNoise& o);
    friend void from_json(const nlohmann::json& j, EnvironmentNoise& o);
protected:
    std::vector<float> m_Noise;

};
}

#endif // INCLUDE_DOCTOR_ENVIRONMENT_NOISE_POST_H

