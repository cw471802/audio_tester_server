/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 16:58:38
 * @LastEditTime: 2023-11-08 18:43:07
 * @FilePath: /audio_tester_server/include/UserCheckinfoDelete.h
 * @Description: 删除普通用户检查信息的客户端数据请求处理
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_USER_CHECKINFO_DELETE_H
#define INCLUDE_USER_CHECKINFO_DELETE_H

#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 普通用户个人信息删除传入数据
/// </summary>
class  UserCheckinfoDelete
{
public:
    UserCheckinfoDelete();
    virtual ~UserCheckinfoDelete();

    void validate();

    /////////////////////////////////////////////
    /// Inline_object_6 members

    /// <summary>
    /// 用户序号
    /// </summary>
    int32_t getUserID() const;
    void setUserID(int32_t const value);
    /// <summary>
    /// 检查序号
    /// </summary>
    int32_t getCheckID() const;
    void setCheckID(int32_t const value);

    friend void to_json(nlohmann::json& j, const UserCheckinfoDelete& o);
    friend void from_json(const nlohmann::json& j, UserCheckinfoDelete& o);
protected:
    int32_t m_UserID;

    int32_t m_CheckID;

};

}

#endif // INCLUDE_USER_CHECKINFO_DELETE_H