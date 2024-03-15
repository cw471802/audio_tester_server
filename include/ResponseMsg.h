/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 18:22:17
 * @LastEditTime: 2023-11-23 18:04:50
 * @FilePath: /audio_tester_server/include/ResponseMsg.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */
#ifndef INCLUDE_RESPONSE_MSG_H
#define INCLUDE_RESPONSE_MSG_H


#include <string>
#include <nlohmann/json.hpp>
#include <glog/logging.h>
namespace model {

/// <summary>
/// 
/// </summary>
class  ResponseMsg
{
public:
    ResponseMsg();
    virtual ~ResponseMsg();

    void validate();

    
    int64_t getTime() const;
    void setTime(int64_t const value);
    /// <summary>
    /// 
    /// </summary>
    bool isFail() const;
    void setFail(bool const value);
    /// <summary>
    /// 
    /// </summary>
    // int32_t getCode() const;
    // void setCode(int32_t const value);
    /// <summary>
    /// 
    /// </summary>
    std::string getMsg() const;
    void setMsg(std::string const& value);


    friend void to_json(nlohmann::json& j, const ResponseMsg& o);
    friend void from_json(const nlohmann::json& j, ResponseMsg& o);
protected:
    int64_t m_Time;

    bool m_Fail;

    // int32_t m_Code;

    std::string m_Msg;

};

}


#endif // INCLUDE_RESPONSE_MSG_H