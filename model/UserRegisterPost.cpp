/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 11:43:25
 * @LastEditTime: 2024-02-28 11:48:12
 * @FilePath: /audio_tester/model/UserRegisterPost.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "UserRegisterPost.h"
#include "Helpers.h"
namespace model {

UserRegisterPost::UserRegisterPost()
{
    m_PhoneNumber = "";
    m_VerificationCode = "";
    m_Password = "";
    m_Name = "";
    m_NameIsSet = false;
    m_Age = 0;
    m_Gender = 2;
}


void UserRegisterPost::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool UserRegisterPost::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool UserRegisterPost::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "UserRegisterPost" : pathPrefix;

                
    return success;
}

void to_json(nlohmann::json& j, const UserRegisterPost& o)
{
    j = nlohmann::json();
    j["phoneNumber"] = o.m_PhoneNumber;
    j["verificationCode"] = o.m_VerificationCode;
    j["password"] = o.m_Password;
    if(o.nameIsSet())
        j["name"] = o.m_Name;
    if(o.ageIsSet())
        j["age"] = o.m_Age;
    if(o.genderIsSet())
        j["gender"] = o.m_Gender;
}

void from_json(const nlohmann::json& j, UserRegisterPost& o)
{
    j.at("phoneNumber").get_to(o.m_PhoneNumber);
    j.at("verificationCode").get_to(o.m_VerificationCode);
    j.at("password").get_to(o.m_Password);
    if(j.find("name") != j.end())
    {
        j.at("name").get_to(o.m_Name);
        o.m_NameIsSet = true;
    } 

    if(j.find("age") != j.end())
    {
        j.at("age").get_to(o.m_Age);
        o.m_AgeIsSet = true;
    } 
    if(j.find("gender") != j.end())
    {
        j.at("gender").get_to(o.m_Gender);
        o.m_GenderIsSet = true;
    } 
}

std::string UserRegisterPost::getPhoneNumber() const
{
    return m_PhoneNumber;
}
void UserRegisterPost::setPhoneNumber(std::string const& value)
{
    m_PhoneNumber = value;
}

std::string UserRegisterPost::getVerificationCode() const
{
    return m_VerificationCode;
}
void UserRegisterPost::setVerificationCode(std::string const& value)
{
    m_VerificationCode = value;
}
std::string UserRegisterPost::getPassword() const
{
    return m_Password;
}
void UserRegisterPost::setPassword(std::string const& value)
{
    m_Password = value;
}

std::string UserRegisterPost::getName() const
{
    return m_Name;
}
void UserRegisterPost::setName(std::string const& value)
{
    m_Name = value;
    m_NameIsSet = true;
}
bool UserRegisterPost::nameIsSet() const
{
    return m_NameIsSet;
}
void UserRegisterPost::unsetName()
{
    m_NameIsSet = false;
}

int32_t UserRegisterPost::getAge() const
{
    return m_Age;
}
void UserRegisterPost::setAge(int32_t const& value)
{
    m_Age = value;
    m_AgeIsSet = true;
}
bool UserRegisterPost::ageIsSet() const
{
    return m_AgeIsSet;
}
void UserRegisterPost::unsetAge()
{
    m_AgeIsSet = false;
}
int32_t UserRegisterPost::getGender() const
{
    return m_Gender;
}
void UserRegisterPost::setGender(int32_t const& value)
{
    m_Gender = value;
    m_GenderIsSet = true;
}
bool UserRegisterPost::genderIsSet() const
{
    return m_GenderIsSet;
}
void UserRegisterPost::unsetGender()
{
    m_GenderIsSet = false;
}

}