/*** 
 * @Author: chen wei
 * @Date: 2023-11-17 15:09:21
 * @LastEditTime: 2024-02-28 12:25:57
 * @FilePath: /audio_tester/utils/UpdateSql.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "UpdateSql.h"


std::string UpdateSql::getSqlModify(const nlohmann::json &json_array)
{
    std::string sql = "";
    for (const auto& element : json_array.items()) 
    {
        if (sql.empty())
        {
            sql = sql + element.key() + " = " + element.value().dump();
        }
        else{
            sql = sql + ","+ element.key() + " = " + element.value().dump();
        }
    }
    
    return sql;
}


std::string UpdateSql::getSqlInsert(const nlohmann::json &json_array)
{
    std::string keys = "";
    std::string values = "";

    for (const auto& element : json_array.items()) 
    {
        if (element.key() == "verificationCode")
        {
            continue;
        }
        if (keys.empty())
        {
            keys = element.key() + keys;
            values = element.value().dump() + values;
        }
        else{
            keys =keys + "," + element.key();
            values = values + "," + element.value().dump();
        }
    }
    auto sql = "(" + keys + ") VALUES (" + values +")";
    return sql;
}


