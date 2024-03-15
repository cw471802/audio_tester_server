/*** 
 * @Author: chen wei
 * @Date: 2023-11-17 14:54:58
 * @LastEditTime: 2023-12-21 17:29:04
 * @FilePath: /audio_tester_server/include/UpdateSql.h
 * @Description: 提取客户端发送的数据并生成sql语句
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_UPDATE_SQL_H
#define INCLUDE_UPDATE_SQL_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "DoctorInfoPut.h"


class UpdateSql
{
private:
    /* data */
public:
    UpdateSql(/* args */);
    ~UpdateSql();
    /// @brief 生成修改 sql语句
    /// @param json_array 
    /// @return std::string
    static std::string getSqlModify(const nlohmann::json &json_array);
    /// @brief 生成插入 sql语句
    /// @param json_array 
    /// @return std::string
    static std::string getSqlInsert(const nlohmann::json &json_array);
};



#endif // INCLUDE_UPDATE_SQL_H