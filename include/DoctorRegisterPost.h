/*** 
 * @Author: chen wei
 * @Date: 2023-11-07 16:46:42
 * @LastEditTime: 2024-02-28 11:24:40
 * @FilePath: /audio_tester/include/DoctorRegisterPost.h
 * @Description: 医生注册时的内联函数，用于对请求数据进行操作
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_DOCTOR_REGISTER_POST_H
#define INCLUDE_DOCTOR_REGISTER_POST_H

#include <string>
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 医生注册传入数据
/// </summary>
class  DocterRegisterPost
{
public:
    DocterRegisterPost();
    virtual ~DocterRegisterPost();

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
     * @brief 获取电话号码
     * @return {string}
     */    
    std::string getPhoneNumber() const;
    void setPhoneNumber(std::string const& value);
    /*** 
     * @brief 获取验证码
     * @return {string}
     */    
    std::string getVerificationCode() const;
    void setVerificationCode(std::string const& value);
    /*** 
     * @brief 获取医生资格证号
     * @return {string}
     */    
    std::string getLicenseID() const;
    void setLicenseID(std::string const& value);
    /*** 
     * @brief 获取医生姓名
     * @return {string}
     */    
    std::string getName() const;
    void setName(std::string const& value);
    // /*** 
    //  * @brief 医生姓名是否为必填项
    //  * @return {bool}
    //  */    
    // bool nameIsSet() const;
    // void unsetName();

    /*** 
     * @brief 获取医生年龄
     * @return {string}
     */    
    int32_t getAge() const;
    void setAge(int32_t const& value);
    /*** 
     * @brief 医生年龄是否为必填项
     * @return {bool}
     */    
    bool ageIsSet() const;
    void unsetAge();

    /*** 
     * @brief 获取医生性别
     * @return {string}
     */    
    int32_t getGender() const;
    void setGender(int32_t const& value);
    /*** 
     * @brief 医生性别是否为必填项
     * @return {bool}
     */    
    bool genderIsSet() const;
    void unsetGender();
    /*** 
     * @brief 获取登录密码
     * @return {*}
     */    
    std::string getPassword() const;
    void setPassword(std::string const& value);

    std::string getIDcard() const;
    void setIDcard(std::string const& value);
    /// <summary>
    /// 
    /// </summary>
    std::string getProvince() const;
    void setProvince(std::string const& value);
    /// <summary>
    /// 
    /// </summary>
    std::string getCategory() const;
    void setCategory(std::string const& value);

    /*** 
     * @brief 将获取的数据转化为json格式
     * @param {json&} j
     * @param {InlineObjectDocterRegister&} o
     * @return {*}
     */    
    friend void to_json(nlohmann::json& j, const DocterRegisterPost& o);
    /*** 
     * @brief 将json格式数据转换为内联对象医生登录数据
     * @param {json&} j
     * @param {InlineObjectDocterRegister&} o
     * @return {*}
     */    
    friend void from_json(const nlohmann::json& j, DocterRegisterPost& o);
protected:
    // 医生电话号码
    std::string m_PhoneNumber;
    // 手机验证码
    std::string m_VerificationCode;
    // 医生资格证号码
    std::string m_LicenseID;
    // 医生姓名
    std::string m_Name;
    // 医生姓名是否为必填项
    // bool m_NameIsSet;
    // 登录密码
    std::string m_Password;
    // 身份证号
    std::string m_IDcard;
    // 省份
    std::string m_Province;
    // 类别
    std::string m_Category;

    // 医生年龄
    int32_t m_Age;
    // 医生年龄是否为必填项
    bool m_AgeIsSet;
    // 医生性别
    int32_t m_Gender;
    // 医生性别是否为必填项
    bool m_GenderIsSet;

};

}

#endif // DOCTOR_REGISTER_POST_H