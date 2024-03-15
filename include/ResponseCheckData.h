/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 17:06:11
 * @LastEditTime: 2023-12-06 11:56:23
 * @FilePath: /audio_tester_server/include/ResponseCheckData.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_RESPONSE_CHECK_DATA_H
#define INCLUDE_RESPONSE_CHECK_DATA_H

#include <string>
#include "ResponseFrequency.h"
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 获取测试结果时的返回数据
/// </summary>
class  ResponseCheckData
{
public:
    ResponseCheckData();
    virtual ~ResponseCheckData()=default;

    /// <summary>
    /// Validate the current data in the model. Throws a ValidationException on failure.
    /// </summary>
    void validate() const;

    /// <summary>
    /// Validate the current data in the model. Returns false on error and writes an error
    /// message into the given stringstream.
    /// </summary>
    bool validate(std::stringstream& msg) const;

    /// <summary>
    /// Helper overload for validate. Used when one model stores another model and calls it's validate.
    /// Not meant to be called outside that case.
    /// </summary>
    bool validate(std::stringstream& msg, const std::string& pathPrefix) const;

    /*** 
     * @brief 获取环境噪音
     * @return {double}
     */   
    std::vector<float> getEnvironmentNoise() const;
    void setEnvironmentNoise(std::vector<float> const value);
    /*** 
     * @brief 获取检查模式
     * @return {string}
     */    
    std::string getCheckMode() const;
    void setCheckMode(std::string const& value);
    /*** 
     * @brief 获取检查结果
     * @return {double}
     */    
    double getCheckResult() const;
    void setCheckResult(double const value);
    /*** 
     * @brief 获取检查建议
     * @return {string}
     */    
    std::string getCheckSuggestion() const;
    void setCheckSuggestion(std::string const& value);
    /*** 
     * @brief 获取检查时间
     * @return {int32_t}
     */    
    int32_t getCheckTime() const;
    void setCheckTime(int32_t const value);
    /*** 
     * @brief 获取纯音频率下的结果
     * @return {ResponseFrequency}
     */    
    ResponseFrequency getFrequency() const;
    void setFrequency(ResponseFrequency const& value);

    friend void to_json(nlohmann::json& j, const ResponseCheckData& o);
    friend void from_json(const nlohmann::json& j, ResponseCheckData& o);
protected:
    std::vector<float> m_EnvironmentNoise;  // 环境噪音

    std::string m_CheckMode;   // 检查模式

    double m_CheckResult;     // 检查结果

    std::string m_CheckSuggestion;  // 检查建议

    int32_t m_CheckTime;          // 检查时间

    ResponseFrequency m_Frequency;  // 纯音频率
};

}


#endif // INCLUDE_RESPONSE_CHECK_DATA_H