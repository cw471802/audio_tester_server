/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 18:17:21
 * @LastEditTime: 2023-12-06 14:24:05
 * @FilePath: /audio_tester_server/model/ResponseChecklistData.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "ResponseChecklistData.h"
#include "Helpers.h"
namespace model {

ResponseChecklistData::ResponseChecklistData()
{
    m_Time = 0;
    m_Fail = false;
    m_Msg = "";

}

void ResponseChecklistData::validate() const
{
    std::stringstream msg;
    if (!validate(msg))
    {
        throw helpers::ValidationException(msg.str());
    }
}

bool ResponseChecklistData::validate(std::stringstream& msg) const
{
    return validate(msg, "");
}

bool ResponseChecklistData::validate(std::stringstream& msg, const std::string& pathPrefix) const
{
    bool success = true;
    const std::string _pathPrefix = pathPrefix.empty() ? "ResponseChecklistData" : pathPrefix;        
    return success;
}

void to_json(nlohmann::json& j, const ResponseChecklistData& o)
{
    j = nlohmann::json();
    j["data"] = o.m_Data;
    j["time"] = o.m_Time;
    j["fail"] = o.m_Fail;
    j["msg"] = o.m_Msg;

}

void from_json(const nlohmann::json& j, ResponseChecklistData& o)
{
    j.at("data").get_to(o.m_Data);
    j.at("time").get_to(o.m_Time);
    j.at("fail").get_to(o.m_Fail);
    j.at("msg").get_to(o.m_Msg);
}

std::vector<ResponseCheckData>& ResponseChecklistData::getData()
{
    return m_Data;
}
void ResponseChecklistData::setData(std::vector<ResponseCheckData> const& value)
{
    m_Data = value;
}

int32_t ResponseChecklistData::getTime() const
{
    return m_Time;
}
void ResponseChecklistData::setTime(int32_t const value)
{
    m_Time = value;
}
bool ResponseChecklistData::isFail() const
{
    return m_Fail;
}
void ResponseChecklistData::setFail(bool const value)
{
    m_Fail = value;
}

std::string ResponseChecklistData::getMsg() const
{
    return m_Msg;
}
void ResponseChecklistData::setMsg(std::string const& value)
{
    m_Msg = value;
}

}