/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 18:26:57
 * @LastEditTime: 2023-11-08 18:28:33
 * @FilePath: /audio_tester_server/model/UserCheckinfoDelete.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "UserCheckinfoDelete.h"

namespace model {

UserCheckinfoDelete::UserCheckinfoDelete()
{
    m_UserID = 0;
    m_CheckID = 0;
    
}

UserCheckinfoDelete::~UserCheckinfoDelete()
{
}

void UserCheckinfoDelete::validate()
{
    // TODO: implement validation
}

void to_json(nlohmann::json& j, const UserCheckinfoDelete& o)
{
    j = nlohmann::json();
    j["userID"] = o.m_UserID;
    j["checkID"] = o.m_CheckID;
}

void from_json(const nlohmann::json& j, UserCheckinfoDelete& o)
{
    j.at("userID").get_to(o.m_UserID);
    j.at("checkID").get_to(o.m_CheckID);
}

int32_t UserCheckinfoDelete::getUserID() const
{
    return m_UserID;
}
void UserCheckinfoDelete::setUserID(int32_t const value)
{
    m_UserID = value;
}
int32_t UserCheckinfoDelete::getCheckID() const
{
    return m_CheckID;
}
void UserCheckinfoDelete::setCheckID(int32_t const value)
{
    m_CheckID = value;
}

}