/*** 
 * @Author: chen wei
 * @Date: 2023-11-08 15:56:17
 * @LastEditTime: 2023-12-05 14:10:21
 * @FilePath: /audio_tester_server/include/CheckinfoFrequency.h
 * @Description: 听力筛查中纯音频率数据内联函数
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_CHECKINFO_FREQUENCY_H
#define INCLUDE_CHECKINFO_FREQUENCY_H

#include <nlohmann/json.hpp>
#include "PureToneFrequency.h"

namespace model {

/*** 
 * @brief 听力检测表中储存的双耳检测数据
 * @return {*}
 */
class  CheckinfoFrequency
{
public:
    CheckinfoFrequency();
    virtual ~CheckinfoFrequency();

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

    friend void to_json(nlohmann::json& j, const CheckinfoFrequency& o);
    friend void from_json(const nlohmann::json& j, CheckinfoFrequency& o);
protected:
    PureToneFrequency m_L;
    PureToneFrequency m_R;
};

}

#endif // INCLUDE_CHECKINFO_FREQUENCY_H