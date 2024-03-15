/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 17:54:36
 * @LastEditTime: 2023-12-06 14:23:15
 * @FilePath: /audio_tester_server/include/ResponseChecklistData.h
 * @Description: 获取检查表数据的返回值的内联函数
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_RESPONSE_CHECKLIST_DATA_H
#define INCLUDE_RESPONSE_CHECKLIST_DATA_H

#include "ResponseCheckData.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace model {

/// <summary>
/// 获取多个检查结果的数据
/// </summary>
class  ResponseChecklistData
{
public:
    ResponseChecklistData();
    virtual ~ResponseChecklistData()= default;

    /// <summary>
    /// Validate the current data in the model. Throws a ValidationException on failure.
    /// </summary>
    void validate() const;

    /// <summary>
    /// Validate the current data in the model. Returns false on error and writes an error
    /// message into the given stringstream.
    /// </summary>
    bool validate(std::stringstream& msg) const;

    /// <summary>
    /// Helper overload for validate. Used when one model stores another model and calls it's validate.
    /// Not meant to be called outside that case.
    /// </summary>
    bool validate(std::stringstream& msg, const std::string& pathPrefix) const;

    /*** 
     * @brief 获取检查数据
     * @return {std::vector}
     */    
    std::vector<ResponseCheckData>& getData();
    void setData(std::vector<ResponseCheckData> const& value);
    /*** 
     * @brief 返回数据时间
     * @return {*}
     */    
    int32_t getTime() const;
    void setTime(int32_t const value);
    /*** 
     * @brief 是否成功获取数据
     * @return {bool}
     */   
    bool isFail() const;
    void setFail(bool const value);
    
    /*** 
     * @brief 返回的提示信息
     * @return {*}
     */    
    std::string getMsg() const;
    void setMsg(std::string const& value);
    /*** 
     * @brief 是否成功返回
     * @return {*}
     */    
    

    friend void to_json(nlohmann::json& j, const ResponseChecklistData& o);
    friend void from_json(const nlohmann::json& j, ResponseChecklistData& o);
protected:
    std::vector<ResponseCheckData> m_Data;

    int32_t m_Time;

    bool m_Fail;

    std::string m_Msg;

};

}

#endif  // INCLUDE_RESPONSE_MSG_H