/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 16:52:01
 * @LastEditTime: 2023-12-08 18:07:56
 * @FilePath: /audio_tester_server/model/DoctorInfoPut.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "DoctorInfoPut.h"
#include "Helpers.h"

namespace model {

DoctorInfoPut::DoctorInfoPut()
{
    m_Name = "";
    m_NameIsSet = false;
    m_LicenseID = "";
    m_LicenseIDIsSet = false;
    m_Gender = 0;
    m_GenderIsSet = false;
    m_Age = 0;
    m_AgeIsSet = false;
    m_PhoneNumber = "";
    m_PhoneNumberIsSet = false;
    m_IDcard = "";
    m_IDcardIsSet = false;
    m_Province = "";
    m_ProvinceIsSet = false;
    m_Category = "";
    m_CategoryIsSet = false;
    
}

DoctorInfoPut::~DoctorInfoPut()
{
}

void DoctorInfoPut::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool DoctorInfoPut::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool DoctorInfoPut::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "DoctorInfoPut" : pathPrefix;                      
    return success;
}

void to_json(nlohmann::json& j, const DoctorInfoPut& o)
{
    j = nlohmann::json();
    if(o.nameIsSet())
        j["name"] = o.m_Name;
    if(o.licenseIDIsSet())
        j["licenseID"] = o.m_LicenseID;
    if(o.genderIsSet())
        j["gender"] = o.m_Gender;
    if(o.ageIsSet())
        j["age"] = o.m_Age;
    
    if(o.phoneNumberIsSet())
        j["phoneNumber"] = o.m_PhoneNumber;
    if(o.iDcardIsSet())
        j["IDcard"] = o.m_IDcard;
    if(o.provinceIsSet())
        j["province"] = o.m_Province;
    if(o.categoryIsSet())
        j["category"] = o.m_Category;
}

void from_json(const nlohmann::json& j, DoctorInfoPut& o)
{
    if(j.find("name") != j.end())
    {
        j.at("name").get_to(o.m_Name);
        o.m_NameIsSet = true;
    } 
    if(j.find("licenseID") != j.end())
    {
        j.at("licenseID").get_to(o.m_LicenseID);
        o.m_LicenseIDIsSet = true;
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
    if(j.find("IDcard") != j.end())
    {
        j.at("IDcard").get_to(o.m_IDcard);
        o.m_IDcardIsSet = true;
    } 
    if(j.find("province") != j.end())
    {
        j.at("province").get_to(o.m_Province);
        o.m_ProvinceIsSet = true;
    } 
    if(j.find("category") != j.end())
    {
        j.at("category").get_to(o.m_Category);
        o.m_CategoryIsSet = true;
    } 
}

std::string DoctorInfoPut::getName() const
{
    return m_Name;
}
void DoctorInfoPut::setName(std::string const& value)
{
    m_Name = value;
    m_NameIsSet = true;
}
bool DoctorInfoPut::nameIsSet() const
{
    return m_NameIsSet;
}
void DoctorInfoPut::unsetName()
{
    m_NameIsSet = false;
}
std::string DoctorInfoPut::getLicenseID() const
{
    return m_LicenseID;
}
void DoctorInfoPut::setLicenseID(std::string const& value)
{
    m_LicenseID = value;
    m_LicenseIDIsSet = true;
}
bool DoctorInfoPut::licenseIDIsSet() const
{
    return m_LicenseIDIsSet;
}
void DoctorInfoPut::unsetLicenseID()
{
    m_LicenseIDIsSet = false;
}
int32_t DoctorInfoPut::getGender() const
{
    return m_Gender;
}
void DoctorInfoPut::setGender(int32_t const value)
{
    m_Gender = value;
    m_GenderIsSet = true;
}
bool DoctorInfoPut::genderIsSet() const
{
    return m_GenderIsSet;
}
void DoctorInfoPut::unsetGender()
{
    m_GenderIsSet = false;
}
int32_t DoctorInfoPut::getAge() const
{
    return m_Age;
}
void DoctorInfoPut::setAge(int32_t const value)
{
    m_Age = value;
    m_AgeIsSet = true;
}
bool DoctorInfoPut::ageIsSet() const
{
    return m_AgeIsSet;
}
void DoctorInfoPut::unsetAge()
{
    m_AgeIsSet = false;
}

std::string DoctorInfoPut::getPhoneNumber() const
{
    return m_PhoneNumber;
}
void DoctorInfoPut::setPhoneNumber(std::string const& value)
{
    m_PhoneNumber = value;
    m_PhoneNumberIsSet = true;
}
bool DoctorInfoPut::phoneNumberIsSet() const
{
    return m_PhoneNumberIsSet;
}
void DoctorInfoPut::unsetPhoneNumber()
{
    m_PhoneNumberIsSet = false;
}
std::string DoctorInfoPut::getIDcard() const
{
    return m_IDcard;
}
void DoctorInfoPut::setIDcard(std::string const& value)
{
    m_IDcard = value;
    m_IDcardIsSet = true;
}
bool DoctorInfoPut::iDcardIsSet() const
{
    return m_IDcardIsSet;
}
void DoctorInfoPut::unsetIDcard()
{
    m_IDcardIsSet = false;
}
std::string DoctorInfoPut::getProvince() const
{
    return m_Province;
}
void DoctorInfoPut::setProvince(std::string const& value)
{
    m_Province = value;
    m_ProvinceIsSet = true;
}
bool DoctorInfoPut::provinceIsSet() const
{
    return m_ProvinceIsSet;
}
void DoctorInfoPut::unsetProvince()
{
    m_ProvinceIsSet = false;
}
std::string DoctorInfoPut::getCategory() const
{
    return m_Category;
}
void DoctorInfoPut::setCategory(std::string const& value)
{
    m_Category = value;
    m_CategoryIsSet = true;
}
bool DoctorInfoPut::categoryIsSet() const
{
    return m_CategoryIsSet;
}
void DoctorInfoPut::unsetCategory()
{
    m_CategoryIsSet = false;
}

}