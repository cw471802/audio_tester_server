/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 17:07:31
 * @LastEditTime: 2023-12-06 12:02:56
 * @FilePath: /audio_tester_server/include/ResponseFrequency.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_RESPONSE_FREQUENCY_H
#define INCLUDE_RESPONSE_FREQUENCY_H

#include <nlohmann/json.hpp>
#include <PureToneFrequency.h>
namespace model {

/// <summary>
/// 返回的查询结果中纯音频率所对应的值
/// </summary>
class  ResponseFrequency
{
public:
    ResponseFrequency();
    virtual ~ResponseFrequency() = default;

    /// <summary>
    /// Validate the current data in the model. Throws a ValidationException on failure.
    /// </summary>
    bool validate() const;

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

    PureToneFrequency getL() const;
    void setL(PureToneFrequency const& value);
    /// <summary>
    /// 
    /// </summary>
    PureToneFrequency getR() const;
    void setR(PureToneFrequency const& value);

    friend void to_json(nlohmann::json& j, const ResponseFrequency& o);
    friend void from_json(const nlohmann::json& j, ResponseFrequency& o);
protected:
    PureToneFrequency m_L;
    PureToneFrequency m_R;

};

}


#endif // INCLUDE_RESPONSE_FREQUENCY_H