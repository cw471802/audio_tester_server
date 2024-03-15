/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 15:36:26
 * @LastEditTime: 2023-12-07 17:17:48
 * @FilePath: /audio_tester_server/include/PatientInfoPost.h
 * @Description: 创建病人信息数据的内联函数
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_PATIENT_INFO_POST_H
#define INCLUDE_PATIENT_INFO_POST_H

#include <string>
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 新建个人信息传入数据
/// </summary>
class  PatientInfoPost
{
public:
    PatientInfoPost();
    virtual ~PatientInfoPost()=default;

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
     * @brief 获取客户端传递的医生ID
     * @return {int32_t}
     */    
    int32_t getDoctorID() const;
    void setDoctorID(int32_t const value);

    /*** 
     * @brief 病人姓名
     * @return {string}
     */    
    std::string getName() const;
    void setName(std::string const& value);

    /*** 
     * @brief 病人性别
     * @return {int32_t}
     */    
    int32_t getGender() const;
    void setGender(int32_t const value);
    bool genderIsSet() const;
    void unsetGender();

    /*** 
     * @brief 病人年龄
     * @return {int32_t}
     */    
    int32_t getAge() const;
    void setAge(int32_t const value);
    bool ageIsSet() const;
    void unsetAge();

    /*** 
     * @brief 住院号
     * @return {string}
     */    
    std::string getHospitalizedNumber() const;
    void setHospitalizedNumber(std::string const& value);
    bool hospitalizedNumberIsSet() const;
    void unsetHospitalizedNumber();
    /*** 
     * @brief 检查号
     * @return {string}
     */    
    std::string getCheckNumber() const;
    void setCheckNumber(std::string const& value);
    bool checkNumberIsSet() const;
    void unsetCheckNumber();
    /*** 
     * @brief 病人电话号码
     * @return {string}
     */    
    std::string getPhoneNumber() const;
    void setPhoneNumber(std::string const& value);

    /*** 
     * @brief 病人住址
     * @return {*}
     */    
    std::string getAddress() const;
    void setAddress(std::string const& value);
    bool addressIsSet() const;
    void unsetAddress();

    friend void to_json(nlohmann::json& j, const PatientInfoPost& o);
    friend void from_json(const nlohmann::json& j, PatientInfoPost& o);
protected:
    int32_t m_DoctorID;  // 医生ID

    std::string m_Name;  // 病人姓名

    int32_t m_Gender;   // 病人性别
    bool m_GenderIsSet;
    int32_t m_Age;     // 病人年龄
    bool m_AgeIsSet;
    std::string m_HospitalizedNumber;  // 住院号
    bool m_HospitalizedNumberIsSet;
    std::string m_CheckNumber;   // 检查号
    bool m_CheckNumberIsSet;
    std::string m_PhoneNumber;   // 电话号码

    bool m_AddressIsSet;
    std::string m_Address;         // 病人地址

};

}

#endif // INCLUDE_PATIENT_INFO_POST_H