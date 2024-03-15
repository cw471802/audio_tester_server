/*** 
 * @Author: chen wei
 * @Date: 2024-01-30 11:33:27
 * @LastEditTime: 2024-01-31 11:25:02
 * @FilePath: /audio_tester_server/include/CheckSuggestionTranslate.h
 * @Description: 对检查信息中的checkSuggestion字段进行翻译
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */


#include <iostream>
#include <random>

#ifndef INCLUDE_CHECK_SUGGESTION_TRANSLATE_H
#define INCLUDE_CHECK_SUGGESTION_TRANSLATE_H
// extern int h_errno;


class CheckSuggestionTranslate
{
public:
    CheckSuggestionTranslate();
    /*** 
     * @brief 将中文字符串翻译成英文字符串
     * @param {string} characters
     * @return {string}
     */    
    std::string  generateEnglish(std::string characters);
    /*** 
     * @brief 根据中文字符串确认严重级别
     * @param {string} characters
     * @return {int}
     */    
    int  generateLevel(std::string characters);
};

#endif // INCLUDE_CHECK_SUGGESTION_TRANSLATE_H