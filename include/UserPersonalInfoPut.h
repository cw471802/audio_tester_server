/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 09:15:41
 * @LastEditTime: 2023-12-15 09:19:53
 * @FilePath: /audio_tester_server/include/UserPersonalInfoPut.h
 * @Description: 用于对普通用户个人信息进行修改时的内联函数
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_USER_PERSONAL_INFO_PUT_H
#define INCLUDE_USER_PERSONAL_INFO_PUT_H

#include <string>
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 普通用户个人信息修改数据
/// </summary>
class  UserPersonalInfoPut
{
public:
    UserPersonalInfoPut();
    virtual ~UserPersonalInfoPut();

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
    /// InlineObjectUserPersonalInfo members

    /*** 
     * @brief 获取用户姓名 
     * @return {strin}
     */    
    std::string getName() const;
    void setName(std::string const& value);
    /*** 
     * @brief 姓名是否必填
     * @return {*}
     */    
    bool nameIsSet() const;
    void unsetName();
    /*** 
     * @brief 获取用户性别
     * @return {int32_t}
     */
    int32_t getGender() const;
    void setGender(int32_t const value);
    /*** 
     * @brief 性别是否为必填项
     * @return {bool}
     */    
    bool genderIsSet() const;
    void unsetGender();
    /*** 
     * @brief 获取用户年龄
     * @return {int32_t}
     */    
    int32_t getAge() const;
    void setAge(int32_t const value);
    /*** 
     * @brief 年龄是否为必填项
     * @return {*}
     */    
    bool ageIsSet() const;
    void unsetAge();
    
    /*** 
     * @brief 密码是否为必填项
     * @return {string}
     */    
    bool passwdIsSet() const;
    void unsetPasswd();
    /*** 
     * @brief 获取电话号码
     * @return {string}
     */
    std::string getPhoneNumber() const;
    void setPhoneNumber(std::string const& value);
    /*** 
     * @brief 电话号码是否为必填项
     * @return {bool}
     */    
    bool phoneNumberIsSet() const;
    void unsetPhoneNumber();

    /*** 
     * @brief 将获取的客户端数据转化为json格式
     * @param {json&} j
     * @param {InlineObjectUserPersonalInfo&} o
     * @return {*}
     */    
    friend void to_json(nlohmann::json& j, const UserPersonalInfoPut& o);
    /*** 
     * @brief 将json格式数据转化为可存入数据库的格式
     * @param {json&} j
     * @param {InlineObjectUserPersonalInfo&} o
     * @return {*}
     */    
    friend void from_json(const nlohmann::json& j, UserPersonalInfoPut& o);
protected:
    std::string m_Name;  // 姓名
    bool m_NameIsSet;    // 是否必填
    int32_t m_Gender;    // 性别
    bool m_GenderIsSet;
    int32_t m_Age;       // 年龄
    bool m_AgeIsSet;
    std::string m_PhoneNumber;  // 电话号码
    bool m_PhoneNumberIsSet;
};

}

#endif // INCLUDE_USER_PERSONAL_INFO_PUT_H