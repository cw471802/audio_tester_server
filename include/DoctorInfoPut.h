/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 15:03:11
 * @LastEditTime: 2023-12-08 18:07:11
 * @FilePath: /audio_tester_server/include/DoctorInfoPut.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_DOCTOR_INFO_PUT_H
#define INCLUDE_DOCTOR_INFO_PUT_H

#include <string>
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 修改医生信息所用的数据
/// </summary>
class  DoctorInfoPut
{
public:
    DoctorInfoPut();
    virtual ~DoctorInfoPut();

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
     * @brief 获取医生姓名 
     * @return {string}
     */    
    std::string getName() const;
    void setName(std::string const& value);
    bool nameIsSet() const;
    void unsetName();
    /*** 
     * @brief 获取医师执业证书号码
     * @return {string}
     */    
    std::string getLicenseID() const;
    void setLicenseID(std::string const& value);
    bool licenseIDIsSet() const;
    void unsetLicenseID();
    /*** 
     * @brief 获取医师性别
     * @return {int32_t}
     */    
    int32_t getGender() const;
    void setGender(int32_t const value);
    bool genderIsSet() const;
    void unsetGender();
  /*** 
   * @brief 获取医生年龄
   * @return {int32_t}
   */
    int32_t getAge() const;
    void setAge(int32_t const value);
    bool ageIsSet() const;
    void unsetAge();
    
    /*** 
     * @brief 获取电话号码
     * @return {string}
     */    
    std::string getPhoneNumber() const;
    void setPhoneNumber(std::string const& value);
    bool phoneNumberIsSet() const;
    void unsetPhoneNumber();
    /*** 
     * @brief 获取身份证号
     * @return {string}
     */    
    std::string getIDcard() const;
    void setIDcard(std::string const& value);
    bool iDcardIsSet() const;
    void unsetIDcard();
    /*** 
     * @brief 获取医生所在省份
     * @return {string}
     */    
    std::string getProvince() const;
    void setProvince(std::string const& value);
    bool provinceIsSet() const;
    void unsetProvince();
    /*** 
     * @brief 获取类别
     * @return {string}
     */    
    std::string getCategory() const;
    void setCategory(std::string const& value);
    bool categoryIsSet() const;
    void unsetCategory();

    friend void to_json(nlohmann::json& j, const DoctorInfoPut& o);
    friend void from_json(const nlohmann::json& j, DoctorInfoPut& o);
protected:
    std::string m_Name;  // 医生用户名
    bool m_NameIsSet; 
    std::string m_LicenseID; //执业资格证号码
    bool m_LicenseIDIsSet;
    int32_t m_Gender;      //性别
    bool m_GenderIsSet;    
    int32_t m_Age;        //年龄
    bool m_AgeIsSet;
    
    std::string m_PhoneNumber; //手机号码
    bool m_PhoneNumberIsSet;
    std::string m_IDcard;   // 身份证号
    bool m_IDcardIsSet;
    std::string m_Province;  //省份
    bool m_ProvinceIsSet;
    std::string m_Category;  //类别
    bool m_CategoryIsSet;
};

}

#endif // INCLUDE_DOCTOR_INFO_PUT_H