/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 14:47:11
 * @LastEditTime: 2023-12-06 11:08:56
 * @FilePath: /audio_tester_server/model/PatientInfoPut.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "PatientInfoPut.h"
#include "Helpers.h"

namespace model {

PatientInfoPut::PatientInfoPut()
{
    m_Name = "";
    m_NameIsSet = false;
    m_Gender = 0;
    m_GenderIsSet = false;
    m_Age = 0;
    m_AgeIsSet = false;
    m_HospitalizedNumber = "";
    m_HospitalizedNumberIsSet = false;
    m_CheckNumber = "";
    m_CheckNumberIsSet = false;
    m_PhoneNumber = "";
    m_PhoneNumberIsSet = false;
    m_Address = "";
    m_AddressIsSet = false;
    
}


void PatientInfoPut::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool PatientInfoPut::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool PatientInfoPut::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "PatientInfoPut" : pathPrefix;                        
    return success;
}

void to_json(nlohmann::json& j, const PatientInfoPut& o)
{
    j = nlohmann::json();
    if(o.nameIsSet())
        j["name"] = o.m_Name;
    if(o.genderIsSet())
        j["gender"] = o.m_Gender;
    if(o.ageIsSet())
        j["age"] = o.m_Age;
    if(o.hospitalizedNumberIsSet())
        j["hospitalizedNumber"] = o.m_HospitalizedNumber;
    if(o.checkNumberIsSet())
        j["checkNumber"] = o.m_CheckNumber;
    if(o.phoneNumberIsSet())
        j["phoneNumber"] = o.m_PhoneNumber;
    if(o.addressIsSet())
        j["address"] = o.m_Address;
}

void from_json(const nlohmann::json& j, PatientInfoPut& o)
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
    if(j.find("hospitalizedNumber") != j.end())
    {
        j.at("hospitalizedNumber").get_to(o.m_HospitalizedNumber);
        o.m_HospitalizedNumberIsSet = true;
    } 
    if(j.find("checkNumber") != j.end())
    {
        j.at("checkNumber").get_to(o.m_CheckNumber);
        o.m_CheckNumberIsSet = true;
    } 
    if(j.find("phoneNumber") != j.end())
    {
        j.at("phoneNumber").get_to(o.m_PhoneNumber);
        o.m_PhoneNumberIsSet = true;
    } 
    if(j.find("address") != j.end())
    {
        j.at("address").get_to(o.m_Address);
        o.m_AddressIsSet = true;
    } 
}

std::string PatientInfoPut::getName() const
{
    return m_Name;
}
void PatientInfoPut::setName(std::string const& value)
{
    m_Name = value;
    m_NameIsSet = true;
}
bool PatientInfoPut::nameIsSet() const
{
    return m_NameIsSet;
}
void PatientInfoPut::unsetName()
{
    m_NameIsSet = false;
}
int32_t PatientInfoPut::getGender() const
{
    return m_Gender;
}
void PatientInfoPut::setGender(int32_t const value)
{
    m_Gender = value;
    m_GenderIsSet = true;
}
bool PatientInfoPut::genderIsSet() const
{
    return m_GenderIsSet;
}
void PatientInfoPut::unsetGender()
{
    m_GenderIsSet = false;
}
int32_t PatientInfoPut::getAge() const
{
    return m_Age;
}
void PatientInfoPut::setAge(int32_t const value)
{
    m_Age = value;
    m_AgeIsSet = true;
}
bool PatientInfoPut::ageIsSet() const
{
    return m_AgeIsSet;
}
void PatientInfoPut::unsetAge()
{
    m_AgeIsSet = false;
}
std::string PatientInfoPut::getHospitalizedNumber() const
{
    return m_HospitalizedNumber;
}
void PatientInfoPut::setHospitalizedNumber(std::string const& value)
{
    m_HospitalizedNumber = value;
    m_HospitalizedNumberIsSet = true;
}
bool PatientInfoPut::hospitalizedNumberIsSet() const
{
    return m_HospitalizedNumberIsSet;
}
void PatientInfoPut::unsetHospitalizedNumber()
{
    m_HospitalizedNumberIsSet = false;
}
std::string PatientInfoPut::getCheckNumber() const
{
    return m_CheckNumber;
}
void PatientInfoPut::setCheckNumber(std::string const& value)
{
    m_CheckNumber = value;
    m_CheckNumberIsSet = true;
}
bool PatientInfoPut::checkNumberIsSet() const
{
    return m_CheckNumberIsSet;
}
void PatientInfoPut::unsetCheckNumber()
{
    m_CheckNumberIsSet = false;
}
std::string PatientInfoPut::getPhoneNumber() const
{
    return m_PhoneNumber;
}
void PatientInfoPut::setPhoneNumber(std::string const& value)
{
    m_PhoneNumber = value;
    m_PhoneNumberIsSet = true;
}
bool PatientInfoPut::phoneNumberIsSet() const
{
    return m_PhoneNumberIsSet;
}
void PatientInfoPut::unsetPhoneNumber()
{
    m_PhoneNumberIsSet = false;
}

std::string PatientInfoPut::getAddress() const
{
    return m_Address;
}
void PatientInfoPut::setAddress(std::string const& value)
{
    m_Address = value;
    m_AddressIsSet = true;
}
bool PatientInfoPut::addressIsSet() const
{
    return m_AddressIsSet;
}
void PatientInfoPut::unsetAddress()
{
    m_AddressIsSet = false;
}


}