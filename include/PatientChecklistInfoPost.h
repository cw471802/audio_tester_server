/*** 
 * @Author: chen wei
 * @Date: 2023-11-09 08:51:58
 * @LastEditTime: 2024-03-01 10:28:45
 * @FilePath: /audio_tester/include/PatientChecklistInfoPost.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_PATIENT_CHECKLIST_INFO_POST_H
#define INCLUDE_PATIENT_CHECKLIST_INFO_POST_H

#include <string>
#include "CheckinfoFrequency.h"
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
///  添加病人检查结果记录表的数据
/// </summary>
class  PatientChecklistInfoPost
{
public:
    PatientChecklistInfoPost();
    virtual ~PatientChecklistInfoPost()=default;

    /// <summary>
    /// Validate the current data in the model. Throws a ValidationException on failure.
    /// </summary>
    bool validate() const;

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
     * @brief 获取病人ID
     * @return {int32_t}
     */
    int32_t getPatientID() const;
    void setPatientID(int32_t const value);
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
    float getCheckResult() const;
    void setCheckResult(double const value);
    /*** 
     * @brief 获取检查建议
     * @return {string}
     */    
    std::string getCheckSuggestion() const;
    void setCheckSuggestion(std::string const& value);

    /*** 
     * @brief 获取检查结论
     * @return {string}
     */    
    std::string getCheckConclusion() const;
    void setCheckConclusion(std::string const& value);
    /*** 
     * @brief 获取纯音频域下的检查结果
     * @return {CheckingoFrequency}
     */    
    CheckinfoFrequency getFrequency() const;
    void setFrequency(CheckinfoFrequency const& value);
    /*** 
     * @brief 获取检查时间
     * @return {string}
     */    
    std::string getCheckTime() const;
    void setCheckTime(std::string const& value);

    friend void to_json(nlohmann::json& j, const PatientChecklistInfoPost& o);
    friend void from_json(const nlohmann::json& j, PatientChecklistInfoPost& o);
protected:
    int32_t m_PatientID;   // 病人ID

    std::vector<float> m_EnvironmentNoise;  // 环境噪音

    std::string m_CheckMode;    // 检查模式

    float m_CheckResult;       // 检查结果

    std::string m_CheckSuggestion;  // 检查建议

    std::string m_CheckConclusion;  // 检查结论

    CheckinfoFrequency m_Frequency;  // 纯音频域

    std::string m_CheckTime;       // 检查时间


};

}


#endif // INCLUDE_PATIENT_CHECKLIST_INFO_POST_H