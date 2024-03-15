/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 11:09:58
 * @LastEditTime: 2023-12-15 09:20:43
 * @FilePath: /audio_tester_server/model/UserPersonalInfoPut.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "UserPersonalInfoPut.h"
#include "Helpers.h"
namespace model {

UserPersonalInfoPut::UserPersonalInfoPut()
{
    m_Name = "";
    m_NameIsSet = false;
    m_Gender = 0;
    m_GenderIsSet = false;
    m_Age = 0;
    m_AgeIsSet = false;
    m_PhoneNumber = "";
    m_PhoneNumberIsSet = false;
    
}

UserPersonalInfoPut::~UserPersonalInfoPut()
{
}

void UserPersonalInfoPut::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool UserPersonalInfoPut::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool UserPersonalInfoPut::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "UserPersonalInfoPut" : pathPrefix;       
    return success;
}

void to_json(nlohmann::json& j, const UserPersonalInfoPut& o)
{
    j = nlohmann::json();
    if(o.nameIsSet())
        j["name"] = o.m_Name;
    if(o.genderIsSet())
        j["gender"] = o.m_Gender;
    if(o.ageIsSet())
        j["age"] = o.m_Age;
    
    if(o.phoneNumberIsSet())
        j["phoneNumber"] = o.m_PhoneNumber;
}

void from_json(const nlohmann::json& j, UserPersonalInfoPut& o)
{
    if(j.find("name") != j.end())
    {
        j.at("name").get_to(o.m_Name);
        o.m_NameIsSet = true;
    } 
    if(j.find("gender") != j.end())
    {
        j.at("gender").get_to(o.m_Gender);
        o.m_GenderIsSet = true;
    } 
    if(j.find("age") != j.end())
    {
        j.at("age").get_to(o.m_Age);
        o.m_AgeIsSet = true;
    } 
    
    if(j.find("phoneNumber") != j.end())
    {
        j.at("phoneNumber").get_to(o.m_PhoneNumber);
        o.m_PhoneNumberIsSet = true;
    } 
}

std::string UserPersonalInfoPut::getName() const
{
    return m_Name;
}
void UserPersonalInfoPut::setName(std::string const& value)
{
    m_Name = value;
    m_NameIsSet = true;
}
bool UserPersonalInfoPut::nameIsSet() const
{
    return m_NameIsSet;
}
void UserPersonalInfoPut::unsetName()
{
    m_NameIsSet = false;
}
int32_t UserPersonalInfoPut::getGender() const
{
    return m_Gender;
}
void UserPersonalInfoPut::setGender(int32_t const value)
{
    m_Gender = value;
    m_GenderIsSet = true;
}
bool UserPersonalInfoPut::genderIsSet() const
{
    return m_GenderIsSet;
}
void UserPersonalInfoPut::unsetGender()
{
    m_GenderIsSet = false;
}
int32_t UserPersonalInfoPut::getAge() const
{
    return m_Age;
}
void UserPersonalInfoPut::setAge(int32_t const value)
{
    m_Age = value;
    m_AgeIsSet = true;
}
bool UserPersonalInfoPut::ageIsSet() const
{
    return m_AgeIsSet;
}
void UserPersonalInfoPut::unsetAge()
{
    m_AgeIsSet = false;
}

std::string UserPersonalInfoPut::getPhoneNumber() const
{
    return m_PhoneNumber;
}
void UserPersonalInfoPut::setPhoneNumber(std::string const& value)
{
    m_PhoneNumber = value;
    m_PhoneNumberIsSet = true;
}
bool UserPersonalInfoPut::phoneNumberIsSet() const
{
    return m_PhoneNumberIsSet;
}
void UserPersonalInfoPut::unsetPhoneNumber()
{
    m_PhoneNumberIsSet = false;
}

}