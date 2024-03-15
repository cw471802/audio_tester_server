
#include "PatientInfoPost.h"
#include "Helpers.h"

namespace model {

PatientInfoPost::PatientInfoPost()
{
    m_DoctorID = 0;
    m_Name = "";
    m_Gender = 0;
    m_GenderIsSet = false;
    m_Age = 0;
    m_AgeIsSet = false;
    m_HospitalizedNumber = "";
    m_HospitalizedNumberIsSet = false;
    m_CheckNumber = "";
    m_CheckNumberIsSet = false;
    m_PhoneNumber = "";
    m_Address = "";
}


void PatientInfoPost::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool PatientInfoPost::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool PatientInfoPost::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "PatientInfoPost" : pathPrefix;

                                
    return success;
}

void to_json(nlohmann::json& j, const PatientInfoPost& o)
{
    j = nlohmann::json();
    j["doctorID"] = o.m_DoctorID;
    j["name"] = o.m_Name;
    if(o.genderIsSet())
        j["gender"] = o.m_Gender;
    if(o.ageIsSet())
        j["age"] = o.m_Age;
    if(o.hospitalizedNumberIsSet())
        j["hospitalizedNumber"] = o.m_HospitalizedNumber;
    if(o.checkNumberIsSet())
        j["checkNumber"] = o.m_CheckNumber;
    j["phoneNumber"] = o.m_PhoneNumber;
    if(o.addressIsSet())
        j["Address"] = o.m_Address;
    j["Address"] = o.m_Address;
}

void from_json(const nlohmann::json& j, PatientInfoPost& o)
{
    j.at("doctorID").get_to(o.m_DoctorID);
    j.at("name").get_to(o.m_Name);
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
    if(j.find("address") != j.end())
    {
        j.at("address").get_to(o.m_Address);
        o.m_AddressIsSet = true;
    } 
    j.at("phoneNumber").get_to(o.m_PhoneNumber);
}

int32_t PatientInfoPost::getDoctorID() const
{
    return m_DoctorID;
}
void PatientInfoPost::setDoctorID(int32_t const value)
{
    m_DoctorID = value;
}

std::string PatientInfoPost::getName() const
{
    return m_Name;
}
void PatientInfoPost::setName(std::string const& value)
{
    m_Name = value;
}
int32_t PatientInfoPost::getGender() const
{
    return m_Gender;
}
void PatientInfoPost::setGender(int32_t const value)
{
    m_Gender = value;
    m_GenderIsSet = true;
}
bool PatientInfoPost::genderIsSet() const
{
    return m_GenderIsSet;
}
void PatientInfoPost::unsetGender()
{
    m_GenderIsSet = false;
}
int32_t PatientInfoPost::getAge() const
{
    return m_Age;
}
void PatientInfoPost::setAge(int32_t const value)
{
    m_Age = value;
    m_AgeIsSet = true;
}
bool PatientInfoPost::ageIsSet() const
{
    return m_AgeIsSet;
}
void PatientInfoPost::unsetAge()
{
    m_AgeIsSet = false;
}
std::string PatientInfoPost::getHospitalizedNumber() const
{
    return m_HospitalizedNumber;
}
void PatientInfoPost::setHospitalizedNumber(std::string const& value)
{
    m_HospitalizedNumber = value;
    m_HospitalizedNumberIsSet = true;
}
bool PatientInfoPost::hospitalizedNumberIsSet() const
{
    return m_HospitalizedNumberIsSet;
}
void PatientInfoPost::unsetHospitalizedNumber()
{
    m_HospitalizedNumberIsSet = false;
}
std::string PatientInfoPost::getCheckNumber() const
{
    return m_CheckNumber;
}
void PatientInfoPost::setCheckNumber(std::string const& value)
{
    m_CheckNumber = value;
    m_CheckNumberIsSet = true;
}
bool PatientInfoPost::checkNumberIsSet() const
{
    return m_CheckNumberIsSet;
}
void PatientInfoPost::unsetCheckNumber()
{
    m_CheckNumberIsSet = false;
}

std::string PatientInfoPost::getAddress() const
{
    return m_Address;
}
void PatientInfoPost::setAddress(std::string const& value)
{
    m_Address = value;
    m_AddressIsSet = true;
}
bool PatientInfoPost::addressIsSet() const
{
    return m_AddressIsSet;
}
void PatientInfoPost::unsetAddress()
{
    m_AddressIsSet = false;
}

std::string PatientInfoPost::getPhoneNumber() const
{
    return m_PhoneNumber;
}
void PatientInfoPost::setPhoneNumber(std::string const& value)
{
    m_PhoneNumber = value;
}

}