/*** 
 * @Author: chen wei
 * @Date: 2023-11-07 17:15:45
 * @LastEditTime: 2024-02-28 11:48:39
 * @FilePath: /audio_tester/model/DoctorRegisterPost.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "DoctorRegisterPost.h"
#include "Helpers.h"
namespace model {

DocterRegisterPost::DocterRegisterPost()
{
    m_PhoneNumber = "";
    m_LicenseID = "";
    m_Name = "";
    m_VerificationCode = "";
    m_Password = "";
    m_IDcard = "";
    m_Province = "";
    m_Category = "";
    m_Age = 0;
    m_Gender = 2;
    
}

DocterRegisterPost::~DocterRegisterPost()
{
}

void DocterRegisterPost::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool DocterRegisterPost::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool DocterRegisterPost::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "DocterRegisterPost" : pathPrefix;            
    return success;
}

void to_json(nlohmann::json& j, const DocterRegisterPost& o)
{
    j = nlohmann::json();
    j["phoneNumber"] = o.m_PhoneNumber;
    j["verificationCode"] = o.m_VerificationCode;
    j["licenseID"] = o.m_LicenseID;
    if(o.ageIsSet())
        j["age"] = o.m_Age;
    if(o.genderIsSet())
        j["gender"] = o.m_Gender;
    // if(o.nameIsSet())
    j["name"] = o.m_Name;
    j["password"] = o.m_Password;
    j["IDcard"] = o.m_IDcard;
    j["province"] = o.m_Province;
    j["category"] = o.m_Category;
}

void from_json(const nlohmann::json& j, DocterRegisterPost& o)
{
    j.at("phoneNumber").get_to(o.m_PhoneNumber);
    j.at("verificationCode").get_to(o.m_VerificationCode);
    j.at("licenseID").get_to(o.m_LicenseID);

    j.at("name").get_to(o.m_Name);
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
    j.at("password").get_to(o.m_Password);
    j.at("IDcard").get_to(o.m_IDcard);
    j.at("province").get_to(o.m_Province);
    j.at("category").get_to(o.m_Category);
}

std::string DocterRegisterPost::getPhoneNumber() const
{
    return m_PhoneNumber;
}
void DocterRegisterPost::setPhoneNumber(std::string const& value)
{
    m_PhoneNumber = value;
}

std::string DocterRegisterPost::getVerificationCode() const
{
    return m_VerificationCode;
}
void DocterRegisterPost::setVerificationCode(std::string const& value)
{
    m_VerificationCode = value;
}
std::string DocterRegisterPost::getLicenseID() const
{
    return m_LicenseID;
}
void DocterRegisterPost::setLicenseID(std::string const& value)
{
    m_LicenseID = value;
}
std::string DocterRegisterPost::getName() const
{
    return m_Name;
}
void DocterRegisterPost::setName(std::string const& value)
{
    m_Name = value;
}
// bool DocterRegisterPost::nameIsSet() const
// {
//     return m_NameIsSet;
// }
// void DocterRegisterPost::unsetName()
// {
//     m_NameIsSet = false;
// }

int32_t DocterRegisterPost::getAge() const
{
    return m_Age;
}
void DocterRegisterPost::setAge(int32_t const& value)
{
    m_Age = value;
    m_AgeIsSet = true;
}
bool DocterRegisterPost::ageIsSet() const
{
    return m_AgeIsSet;
}
void DocterRegisterPost::unsetAge()
{
    m_AgeIsSet = false;
}

int32_t DocterRegisterPost::getGender() const
{
    return m_Gender;
}
void DocterRegisterPost::setGender(int32_t const& value)
{
    m_Gender = value;
    m_GenderIsSet = true;
}
bool DocterRegisterPost::genderIsSet() const
{
    return m_GenderIsSet;
}
void DocterRegisterPost::unsetGender()
{
    m_GenderIsSet = false;
}

std::string DocterRegisterPost::getPassword() const
{
    return m_Password;
}
void DocterRegisterPost::setPassword(std::string const& value)
{
    m_Password = value;
}
std::string DocterRegisterPost::getIDcard() const
{
    return m_IDcard;
}
void DocterRegisterPost::setIDcard(std::string const& value)
{
    m_IDcard = value;
}
std::string DocterRegisterPost::getProvince() const
{
    return m_Province;
}
void DocterRegisterPost::setProvince(std::string const& value)
{
    m_Province = value;
}
std::string DocterRegisterPost::getCategory() const
{
    return m_Category;
}
void DocterRegisterPost::setCategory(std::string const& value)
{
    m_Category = value;
}

}