/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 18:31:36
 * @LastEditTime: 2023-12-06 11:18:18
 * @FilePath: /audio_tester_server/include/PatientChecklistInfoPut.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */


#ifndef INCLUDE_PATIENT_CHECKLIST_INFO_PUT_H
#define INCLUDE_PATIENT_CHECKLIST_INFO_PUT_H


#include <string>
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 医生对病人检查表信息修改传入数据
/// </summary>
class  PatientChecklistInfoPut
{
public:
    PatientChecklistInfoPut();
    virtual ~PatientChecklistInfoPut()=default;

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

    // /*** 
    //  * @brief 获取环境噪音值
    //  * @return {double}
    //  */    
    // double getEnvironmentNoise() const;
    // void setEnvironmentNoise(double const value);
    // bool environmentNoiseIsSet() const;
    // void unsetEnvironmentNoise();
    /*** 
     * @brief 获取检查模式
     * @return {string}
     */    
    std::string getCheckMode() const;
    void setCheckMode(std::string const& value);
    bool checkModeIsSet() const;
    void unsetCheckMode();
    /*** 
     * @brief 获取检查结果
     * @return {double}
     */
    double getCheckResult() const;
    void setCheckResult(double const value);
    bool checkResultIsSet() const;
    void unsetCheckResult();
    /*** 
     * @brief 获取诊断建议
     * @return {*}
     */    
    std::string getCheckSuggestion() const;
    void setCheckSuggestion(std::string const& value);
    bool checkSuggestionIsSet() const;
    void unsetCheckSuggestion();

    friend void to_json(nlohmann::json& j, const PatientChecklistInfoPut& o);
    friend void from_json(const nlohmann::json& j, PatientChecklistInfoPut& o);
protected:
    // double m_EnvironmentNoise;    // 环境噪音
    bool m_EnvironmentNoiseIsSet;
    std::string m_CheckMode;      // 检查模式
    bool m_CheckModeIsSet;         
    double m_CheckResult;          // 检查结果
    bool m_CheckResultIsSet;
    std::string m_CheckSuggestion; // 检查建议
    bool m_CheckSuggestionIsSet;
};

}

#endif // INCLUDE_PATIENT_CHECKLIST_INFO_PUT_H