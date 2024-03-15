/*** 
 * @Author: chen wei
 * @Date: 2023-11-07 16:29:19
 * @LastEditTime: 2023-11-15 11:58:58
 * @FilePath: /audio_tester_server/include/Helpers.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */


#ifndef INCLUDE_HELPERS_H
#define  INCLUDE_HELPERS_H

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <map>

namespace helpers {

    class ValidationException : public std::runtime_error
    {
    public:
        explicit ValidationException(const std::string& what)
            : std::runtime_error(what)
        { }
        ~ValidationException() override = default;
    };

    /// <summary>
    /// Validate a string against the full-date definition of RFC 3339, section 5.6.
    /// </summary>
    bool validateRfc3339_date(const std::string& str);

    /// <summary>
    /// Validate a string against the date-time definition of RFC 3339, section 5.6.
    /// </summary>
    bool validateRfc3339_date_time(const std::string& str);

    namespace sfinae_helpers
    {
        struct NoType {};
        template <typename T1, typename T2> NoType operator==(const T1&, const T2&);

        template <typename T1, typename T2> class EqualsOperatorAvailable
        {
        public:
            enum
            {
                value = !std::is_same< decltype(std::declval<T1>() == std::declval<T2>()), NoType >::value
            };
        };
    } // namespace sfinae_helpers


    /// <summary>
    /// Determine if the given vector<T> only has unique elements. T must provide the == operator.
    /// </summary>
    template <typename T>
    bool hasOnlyUniqueItems(const std::vector<T>& vec)
    {
        static_assert(sfinae_helpers::EqualsOperatorAvailable<T, T>::value,
                      "hasOnlyUniqueItems<T> cannot be called, passed template type does not provide == operator.");
        if (vec.size() <= 1)
        {
            return true;
        }
        // Compare every element of vec to every other element of vec.
        // This isn't an elegant way to do this, since it's O(n^2),
        // but it's the best solution working only with the == operator.
        // This could be greatly improved if our models provided a valid hash
        // and/or the < operator
        for (size_t i = 0; i < vec.size() - 1; i++)
        {
            for (size_t j = i + 1; j < vec.size(); j++)
            {
                if (vec[i] == vec[j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    std::string toStringValue(const std::string &value);
    /*** 
     * @brief 转化为string类型数据
     * @param {int32_t} &value
     * @return {string}
     */    
    std::string toStringValue(const int32_t &value);
    /*** 
     * @brief 转化为string类型数据
     * @param {int64_t} &value
     * @return {string}
     */    
    std::string toStringValue(const int64_t &value);
    /*** 
     * @brief 转化为string类型数据
     * @param {bool} &value
     * @return {string}
     */    
    std::string toStringValue(const bool &value);
    /*** 
     * @brief 转化为string类型数据
     * @param {float} &value
     * @return {string}
     */    
    std::string toStringValue(const float &value);
    /*** 
     * @brief 转化为string类型数据
     * @param {double} &value
     * @return {string}
     */    
    std::string toStringValue(const double &value);

    bool fromStringValue(const std::string &inStr, std::string &value);
    bool fromStringValue(const std::string &inStr, int32_t &value);
    bool fromStringValue(const std::string &inStr, int64_t &value);
    bool fromStringValue(const std::string &inStr, bool &value);
    bool fromStringValue(const std::string &inStr, float &value);
    bool fromStringValue(const std::string &inStr, double &value);
    template<typename T>
    bool fromStringValue(const std::vector<std::string> &inStr, std::vector<T> &value){
        try{
            for(auto & item : inStr){
                T itemValue;
                if(fromStringValue(item, itemValue)){
                    value.push_back(itemValue);
                }
            }
        }
        catch(...){
            return false;
        }
        return value.size() > 0;
    }
    template<typename T>
    bool fromStringValue(const std::string &inStr, std::vector<T> &value, char separator = ','){
        std::vector<std::string> inStrings;
        std::istringstream f(inStr);
        std::string s;
        while (std::getline(f, s, separator)) {
            inStrings.push_back(s);
        }
        return fromStringValue(inStrings, value);
    }

}

#endif //INCLUDE_HELPERS_H