/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 11:13:42
 * @LastEditTime: 2024-02-28 11:35:52
 * @FilePath: /audio_tester/include/UserRegisterPost.h
 * @Description: 普通用户注册所需数据处理的内联函数
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_USER_REGISTER_POST_H
#define INCLUDE_USER_REGISTER_POST_H

#include <string>
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 用户注册数据
/// </summary>
class  UserRegisterPost
{
public:
    UserRegisterPost();
    virtual ~UserRegisterPost()=default;

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


    /////////////////////////////////////////////
    /// Inline_object members

    /*** 
     * @brief 获取普通用户的电话号码
     * @return {string}
     */
    std::string getPhoneNumber() const;
    void setPhoneNumber(std::string const& value);
    /*** 
     * @brief 获取手机验证码
     * @return {string}
     */
    std::string getVerificationCode() const;
    void setVerificationCode(std::string const& value);
    /*** 
     * @brief 获取普通用户的密码
     * @return {*}
     */    
    std::string getPassword() const;
    void setPassword(std::string const& value);
    /*** 
     * @brief 获取不同用户的用户名
     * @return {*}
     */    
    std::string getName() const;
    void setName(std::string const& value);
    bool nameIsSet() const;
    void unsetName();

    /*** 
     * @brief 获取用户的年龄
     * @return {*}
     */    
    int32_t getAge() const;
    void setAge(int32_t const& value);
    bool ageIsSet() const;
    void unsetAge();

     /*** 
     * @brief 获取用户性别
     * @return {string}
     */    
    int32_t getGender() const;
    void setGender(int32_t const& value);
    /*** 
     * @brief 用户性别是否为必填项
     * @return {bool}
     */    
    bool genderIsSet() const;
    void unsetGender();

    /*** 
     * @brief 将获取的客户端数据转化为json格式
     * @param {json&} j
     * @param {InlineObjectUserRegister&} o
     * @return {*}
     */    
    friend void to_json(nlohmann::json& j, const UserRegisterPost& o);
    /*** 
     * @brief 将json格式数据转化为可存入数据库的格式
     * @param {json&} j
     * @param {InlineObjectUserRegister&} o
     * @return {*}
     */    
    friend void from_json(const nlohmann::json& j, UserRegisterPost& o);
protected:
    std::string m_PhoneNumber;
    std::string m_VerificationCode;
    std::string m_Password;

    std::string m_Name;
    bool m_NameIsSet;

    int32_t m_Age;
    bool m_AgeIsSet;

    int32_t m_Gender;
    bool m_GenderIsSet;
};

}

#endif // INCLUDE_USER_REGISTER_POST_H