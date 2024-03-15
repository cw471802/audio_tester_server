/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 12:00:48
 * @LastEditTime: 2023-12-06 11:08:50
 * @FilePath: /audio_tester_server/include/PatientInfoPut.h
 * @Description: 病人信息修改所使用的数据处理内联函数
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_PATIENT_INFO_PUT_H
#define INCLUDE_PATIENT_INFO_PUT_H

#include <string>
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 病人信息修改传入数据
/// </summary>
class  PatientInfoPut
{
public:
    PatientInfoPut();
    virtual ~PatientInfoPut()=default;

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
     * @brief 获取病人姓名
     * @return {*}
     */    
    std::string getName() const;
    void setName(std::string const& value);
    /*** 
     * @brief 病人姓名是否为必填项
     * @return {*}
     */    
    bool nameIsSet() const;
    void unsetName();
    /*** 
     * @brief 获取病人性别
     * @return {*}
     */
    int32_t getGender() const;
    void setGender(int32_t const value);
    /*** 
     * @brief 病人性别是否为必填写项
     * @return {*}
     */    
    bool genderIsSet() const;
    void unsetGender();
    /*** 
     * @brief 获取病人年龄
     * @return {*}
     */
    int32_t getAge() const;
    void setAge(int32_t const value);
    bool ageIsSet() const;
    void unsetAge();
    /*** 
     * @brief 获取病人住院号
     * @return {*}
     */    
    std::string getHospitalizedNumber() const;
    void setHospitalizedNumber(std::string const& value);
    bool hospitalizedNumberIsSet() const;
    void unsetHospitalizedNumber();
    /*** 
     * @brief 获取病人检查号
     * @return {*}
     */    
    std::string getCheckNumber() const;
    void setCheckNumber(std::string const& value);
    bool checkNumberIsSet() const;
    void unsetCheckNumber();
    /*** 
     * @brief 获取病人电话号码
     * @return {*}
     */    
    std::string getPhoneNumber() const;
    void setPhoneNumber(std::string const& value);
    bool phoneNumberIsSet() const;
    void unsetPhoneNumber();
    /*** 
     * @brief 获取病人住址
     * @return {*}
     */    
    std::string getAddress() const;
    void setAddress(std::string const& value);
    bool addressIsSet() const;
    void unsetAddress();

    friend void to_json(nlohmann::json& j, const PatientInfoPut& o);
    friend void from_json(const nlohmann::json& j, PatientInfoPut& o);
protected:
    std::string m_Name; // 病人姓名
    bool m_NameIsSet;
    int32_t m_Gender;  // 病人性别
    bool m_GenderIsSet;
    int32_t m_Age;  // 病人年龄
    bool m_AgeIsSet;
    std::string m_HospitalizedNumber;  // 住院号
    bool m_HospitalizedNumberIsSet;
    std::string m_CheckNumber;   // 检查号
    bool m_CheckNumberIsSet;
    std::string m_PhoneNumber;  // 病人电话号码
    bool m_PhoneNumberIsSet;

    bool m_AddressIsSet;
    std::string m_Address;         // 病人地址
};

}

#endif // INCLUDE_INLINE_OBJECT_PATIENT_INFO_H