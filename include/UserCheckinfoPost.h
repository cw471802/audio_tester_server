/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 15:49:42
 * @LastEditTime: 2024-03-01 10:03:49
 * @FilePath: /audio_tester/include/UserCheckinfoPost.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_USER_CHECKINFO_POST_H
#define INCLUDE_USER_CHECKINFO_POST_H

#include <string>
#include <nlohmann/json.hpp>
#include "CheckinfoFrequency.h"
#include "EnvironmentNoise.h"

namespace model {

/// <summary>
/// 普通用户检查信息存入数据
/// </summary>
class  UserCheckinfoPost
{
public:
    UserCheckinfoPost();
    virtual ~UserCheckinfoPost();

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
     * @brief 用户ID
     * @return {*}
     */
    int32_t getUserID() const;
    void setUserID(int32_t const value);
 
    // /*** 
    //  * @brief 检查时环境噪音
    //  * @return {*}
    //  */   
     
    std::vector<float> getEnvironmentNoise() const;
    void setEnvironmentNoise(std::vector<float> const value);

    /*** 
     * @brief 检查模式，有快捷模式(quick)和普通模式(normal)两种
     * @return {*}
     */    
    std::string getCheckMode() const;
    void setCheckMode(std::string const& value);

    /*** 
     * @brief 检查结果
     * @return {float}
     */    
    float getCheckResult() const;
    void setCheckResult(float const value);
    /// <summary>
    /// 检查建议
    /// </summary>
    /*** 
     * @brief 检查建议，新听力量表情况下有 '听力完好','轻度听力损失','中度听力损失','中中度听力损失',
     * '重度听力损失','极重度听力损失','完全听力丧失'这几种情况。
     * @return {*}
     */    
    std::string getCheckSuggestion() const;
    void setCheckSuggestion(std::string const& value);

    /*** 
     * @brief 检查建议
     * @return {float}
     */    
    std::string getCheckConclusion() const;
    void setCheckConclusion(std::string const& value);
    /*** 
     * @brief 检查时间
     * @return {*}
     */    
    std::string getCheckTime() const;
    void setCheckTime(std::string const& value);
    
    CheckinfoFrequency getFrequency() const;
    void setFrequency(CheckinfoFrequency const& value);

    /// <summary>
    /// 
    /// </summary>
    // EnvironmentNoise getEnvironmentNoise() const;
    // void setEnvironmentNoise(EnvironmentNoise const& value);

    friend void to_json(nlohmann::json& j, const UserCheckinfoPost& o);
    friend void from_json(const nlohmann::json& j, UserCheckinfoPost& o);
protected:
    int32_t m_UserID;      // 用户ID

    std::vector<float> m_EnvironmentNoise; // 环境噪音

    std::string m_CheckMode; // 检查模式

    float m_CheckResult;    // 检查结果

    std::string m_CheckSuggestion; // 检查建议
 
    std::string m_CheckTime;  // 检查时间

    CheckinfoFrequency m_Frequency; // 纯音频率及检查结果

    // EnvironmentNoise m_EnvironmentNoise; // 检查时环境噪音
    std::string m_CheckConclusion; // 检查结论

};

}

#endif // INCLUDE_USER_CHECKINFO_POST_H