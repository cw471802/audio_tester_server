/*** 
 * @Author: chen wei
 * @Date: 2023-11-20 12:06:25
 * @LastEditTime: 2023-11-20 18:19:59
 * @FilePath: /audio_tester_server/include/DoctorRegisterJudge.h
 * @Description: 判断医生注册申请信息是否符合
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */


#ifndef INCLUDE_DOCTOR_REGISTER_JUDGE_H
#define INCLUDE_DOCTOR_REGISTER_JUDGE_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <glog/logging.h>

class DoctorRegisterJudge
{
private:
    /* data */
public:
    DoctorRegisterJudge(/* args */);
    ~DoctorRegisterJudge();

    static bool InformationJudge(const nlohmann::json &json_array);

};


#endif // INCLUDE_DOCTOR_REGISTER_JUDGE_H