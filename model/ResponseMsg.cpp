/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 18:30:31
 * @LastEditTime: 2023-11-23 18:11:52
 * @FilePath: /audio_tester_server/model/ResponseMsg.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "ResponseMsg.h"

namespace model {

ResponseMsg::ResponseMsg()
{
    m_Time = 0;
    m_Fail = false;
    // m_Code = 0;
    m_Msg = "";
}

ResponseMsg::~ResponseMsg()
{
}

void ResponseMsg::validate()
{
    // TODO: implement validation
}

void to_json(nlohmann::json& j, const ResponseMsg& o)
{
    j = nlohmann::json();
    j["time"] = o.m_Time;
    j["fail"] = o.m_Fail;
    // j["code"] = o.m_Code;
    j["msg"] = o.m_Msg;
}

void from_json(const nlohmann::json& j, ResponseMsg& o)
{
    j.at("time").get_to(o.m_Time);
    j.at("fail").get_to(o.m_Fail);
    // j.at("code").get_to(o.m_Code);
    j.at("msg").get_to(o.m_Msg);
   
}

int64_t ResponseMsg::getTime() const
{
    return m_Time;
}
void ResponseMsg::setTime(int64_t const value)
{
    m_Time =value;
}
bool ResponseMsg::isFail() const
{
    return m_Fail;
}
void ResponseMsg::setFail(bool const value)
{
    m_Fail = value;
}
// int32_t ResponseMsg::getCode() const
// {
//     return m_Code;
// }
// void ResponseMsg::setCode(int32_t const value)
// {
//     m_Code = value;
// }
std::string ResponseMsg::getMsg() const
{
    return m_Msg;
}
void ResponseMsg::setMsg(std::string const& value)
{
    m_Msg = value;
}

}
