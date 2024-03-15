/*** 
 * @Author: chen wei
 * @Date: 2023-11-23 16:51:21
 * @LastEditTime: 2024-03-01 09:34:40
 * @FilePath: /audio_tester/include/PureToneFrequency.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_PURE_TONE_FREQUENCY_H
#define INCLUDE_PURE_TONE_FREQUENCY_H
#include <nlohmann/json.hpp>

namespace model {

/*** 
 * @brief 用户进行听觉筛查时的纯音频率，分别有1000，2000，3000，4000，6000，8000，125，250，500，1000几种频率
 * @return {}
 */
class  PureToneFrequency
{
public:
    PureToneFrequency();
    virtual ~PureToneFrequency()=default;

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

    /////////////////////////////////////////////
    /// PureToneFrequency members

    /// <summary>
    /// 
    /// </summary>
    float get125() const;
    void set125(float const value);
    bool t125IsSet() const;
    void unset_125();
    /// <summary>
    /// 
    /// </summary>
    float get250() const;
    void set250(float const value);
    bool t250IsSet() const;
    void unset_250();
    /// <summary>
    /// 
    /// </summary>
    float get500() const;
    void set500(float const value);
   
    /// <summary>
    /// 
    /// </summary>
    float get4000() const;
    void set4000(float const value);
    /// <summary>
    /// 
    /// </summary>
    float get6000() const;
    void set6000(float const value);
    bool t6000IsSet() const;
    void unset_6000();
    /// <summary>
    /// 
    /// </summary>
    float get8000() const;
    void set8000(float const value);
    bool t8000IsSet() const;
    void unset_8000();
    /// <summary>
    /// 
    /// </summary>
    float get1000s() const;
    void set1000s(float const value);
    /// <summary>
    /// 
    /// </summary>
    float get2000() const;
    void set2000(float const value);
    /// <summary>
    /// 
    /// </summary>
    float get1000e() const;
    void set1000e(float const value);

    friend void to_json(nlohmann::json& j, const PureToneFrequency& o);
    friend void from_json(const nlohmann::json& j, PureToneFrequency& o);
protected:
    float m_125;
    bool m_125IsSet;
    float m_250;
    bool m_250IsSet;
    float m_500;

    float m_4000;

    float m_6000;
    bool m_6000IsSet;
    float m_8000;
    bool m_8000IsSet;
    float m_1000s;

    float m_2000;

    float m_1000e;

};

}

#endif // INCLUDE_PURE_TONE_FREQUENCY_H