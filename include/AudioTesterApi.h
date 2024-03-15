/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 18:37:32
 * @LastEditTime: 2024-03-01 14:25:57
 * @FilePath: /audio_tester/include/AudioTesterApi.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_AUDIO_TESTER_API_H
#define INCLUDE_AUDIO_TESTER_API_H

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/http_headers.h>

#include "DoctorInfoPut.h"
#include "DoctorRegisterPost.h"
#include "PatientInfoPut.h"
#include "PatientInfoPost.h"
#include "PatientChecklistInfoPut.h"
#include "PatientChecklistInfoPost.h"
#include "UserRegisterPost.h"
#include "UserCheckinfoDelete.h"
#include "UserCheckinfoPost.h"
#include "UserPersonalInfoPut.h"
#include "UserPersonalInfoPut.h"
#include <optional>
#include <utility>
#include <string>

namespace api {

using namespace model;

class  AudioTesterApi {
public:
    AudioTesterApi(std::shared_ptr<Pistache::Rest::Router>);
    ~AudioTesterApi(){};
    void init();

    const std::string base = "";

private:
    void setupRoutes();

    void user_login_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void doctor_login_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void doctor_doctor_info_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void doctor_logout_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void doctor_personal_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void doctor_register_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void doctor_retrive_passwd_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void doctor_passwd_change_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_checklists_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_checklists_info_delete_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_checklists_info_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_checklists_info_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_patients_info_delete_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_patients_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_patients_info_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_patients_info_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_patients_info_name_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void patients_patients_info_time_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_checkinfo_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_checkinfo_delete_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_checkinfo_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_logout_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_personal_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_personal_info_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_register_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_retrieve_passwd_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void user_passwd_change_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void common_push_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void common_sms_verification_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void common_update_phone_number_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void common_hearing_trends_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void default_api_default_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    

    std::shared_ptr<Pistache::Rest::Router> router;

     /// <summary>
    /// Helper function to handle unexpected Exceptions during Parameter parsing and validation.
    /// May be overridden to return custom error formats. This is called inside a catch block.
    /// Important: When overriding, do not call `throw ex;`, but instead use `throw;`.
    /// </summary>
    virtual std::pair<Pistache::Http::Code, std::string> handleParsingException(const std::exception& ex) const noexcept;

    /// <summary>
    /// Helper function to handle unexpected Exceptions during processing of the request in handler functions.
    /// May be overridden to return custom error formats. This is called inside a catch block.
    /// Important: When overriding, do not call `throw ex;`, but instead use `throw;`.
    /// </summary>
    virtual std::pair<Pistache::Http::Code, std::string> handleOperationException(const std::exception& ex) const noexcept;
    /// <summary>
    /// 登录
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="phoneNumber"></param>
    /// <param name="passwd"></param>
    virtual void user_login_get(const std::optional<std::string> &phoneNumber, const std::optional<std::string>
        &passwd, Pistache::Http::ResponseWriter &response) = 0;

    virtual void doctor_login_get(const std::optional<std::string> &phoneNumber, const std::optional<std::string>
        &passwd, Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 修改医生信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="doctorID"></param>
    /// <param name="inlineObject9"> (optional)</param>
    virtual void doctor_doctor_info_put(const std::optional<int32_t> &doctorID, const DoctorInfoPut &doctorInfoPut, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 医生用户注销
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="doctorID"></param>
    /// <param name="passwd"></param>
    virtual void doctor_logout_post(const std::optional<int32_t> &doctorID, const std::optional<std::string> &passwd, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 获取医生用户基本信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="doctorID"></param>
    virtual void doctor_personal_info_get(const std::optional<int32_t> &doctorID, Pistache::Http::ResponseWriter 
        &response) = 0;

    /// <summary>
    /// 医生用户注册
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="inlineObject1"> (optional)</param>
    virtual void doctor_register_post(const DocterRegisterPost &docterRegisterPostObject, 
        Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 找回密码
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="phoneNumber"></param>
    virtual void doctor_retrive_passwd_post(const std::optional<std::string> &phoneNumber, const std::optional<std::string> &verificationCode,
        const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 医生用户修改密码
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="doctorID"></param> 医生ID
    /// <param name="passwd"></param> 旧密码
    /// <param name="password"></param> 新密码
    virtual void doctor_passwd_change_put(const std::optional<int32_t> &doctorID, 
        const std::optional<std::string> &passwd, 
        const std::optional<std::string> &password,
        Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 获取病人检查信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="patientID"></param>
    /// <param name="checkID"></param>
    virtual void patients_checklists_info_get(const std::optional<int32_t> &patientID, 
        const std::optional<int32_t> &checkID, const std::optional<int32_t> &language, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 删除病人检查记录
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="patientID"></param>
    /// <param name="checkID"></param>
    virtual void patients_checklists_info_delete(const std::optional<int32_t> &patientID, 
        const std::optional<std::vector<int32_t>> &checkID, Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 添加病人检查记录
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="inlineObject8"> (optional)</param>
    virtual void patients_checklists_info_post(const PatientChecklistInfoPost &patientChecklistInfoPost, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 修改病人检查记录
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="patientID"></param>
    /// <param name="checkID"></param>
    /// <param name="inlineObject7"> (optional)</param>
    virtual void patients_checklists_info_put(const std::optional<int32_t> &patientID, 
        const std::optional<int32_t> &checkID, const PatientChecklistInfoPut &patientChecklistInfoPut, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 删除病人信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="doctosrID"></param>
    /// <param name="patientID"></param>
    virtual void patients_patients_info_delete(const std::optional<int32_t> &doctorID, 
        const std::optional<std::vector<int32_t>> &patientID, Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 根据最新修改时间获取医生名下的病人
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="doctorID">医生用户的ID (optional, default to 0)</param>
    virtual void patients_patients_info_get(const std::optional<int32_t> &doctorID, const std::optional<int32_t> &amount,
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 添加病人信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="inlineObject4"> (optional)</param>
    virtual void patients_patients_info_post(const PatientInfoPost &patientInfoPost, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 修改病人信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="doctorID"> (optional, default to 0)</param>
    /// <param name="patientID"> (optional, default to 0)</param>
    /// <param name="inlineObject3"> (optional)</param>
    virtual void patients_patients_info_put(const std::optional<int32_t> &doctorID, 
        const std::optional<int32_t> &patientID, const PatientInfoPut &patientInfoPut, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 获取普通用户检查历史
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userID">普通用户的用户ID</param>
    /// <param name="amount">查找检查记录的数量</param>
    /// <param name="language">返回结果的语言</param>

    virtual void user_checkinfo_get(const std::optional<int32_t> &userID, const std::optional<int32_t> &amount,
        const std::optional<int32_t> &language, Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 用户删除检查记录
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="inlineObject6"> (optional)</param>
    virtual void user_checkinfo_delete(const std::optional<int32_t> &userID, const std::optional<std::vector<int32_t>> &checkID,
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 用户添加检查记录
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="inlineObject5"> (optional)</param>
    virtual void user_checkinfo_post(const UserCheckinfoPost &userCheckinfoPost, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 普通用户注销
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userID">用户ID</param>
    /// <param name="passwd">密码</param>
    virtual void user_logout_post(const std::optional<int32_t> &userID, 
        const std::optional<std::string> &passwd, Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 获取用户基本信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userID">普通用户的用户ID</param>
    virtual void user_personal_info_get(const std::optional<int32_t> &userID, 
        Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 修改用户信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userID">用户序列号 (optional, default to 0)</param>
    /// <param name="inlineObject2"> (optional)</param>
    virtual void user_personal_info_put(const std::optional<int32_t> &userID, 
        const UserPersonalInfoPut &userPersonalInfoPut, Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 普通用户注册
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="inlineObject"> (optional)</param>
    virtual void user_register_post(const UserRegisterPost &userRegisterPost, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 找回密码
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="phoneNumber"></param>
    virtual void user_retrieve_passwd_post(const std::optional<std::string> &phoneNumber, const std::optional<std::string> &verificationCode,
        const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 普通用户修改密码
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userID"></param> 普通用户ID
    /// <param name="passwd"></param> 旧密码
    /// <param name="password"></param> 新密码
    virtual void user_passwd_change_put(const std::optional<int32_t> &userID, const std::optional<std::string> &passwd, 
        const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 获取病人信息，根据姓名
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="doctorID"></param> 医生ID
    /// <param name="name"></param> 病人姓名
    virtual void patients_patients_info_name_get(const std::optional<int32_t> &doctorID, const std::optional<std::string> &name, 
        Pistache::Http::ResponseWriter &response) = 0;
    
    /// <summary>
    /// 获取病人信息，根据创建时间
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="startTime"></param>
    /// <param name="endTime"></param>
    virtual void patients_patients_info_time_get(const std::optional<int32_t> &doctorID, 
        const std::optional<std::string> &startTime, 
        const std::optional<std::string> &endTime, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 获取推送信息
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userCategory"></param> 用户类别
    virtual void common_push_info_get(const std::optional<int32_t> &category, 
        const std::optional<int32_t> &language, Pistache::Http::ResponseWriter &response) = 0;

    /// <summary>
    /// 发送短信验证消息，并获取验证码
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userCategory"></param> 用户类别
    /// <param name="function"></param> 短信验证类型
    virtual void common_sms_verification_get(std::optional<std::string> &phoneNumber, 
        const std::optional<int32_t> &function, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 更改手机号码
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userCategory"></param> 用户类别
    /// <param name="ID"></param> 用户id
    /// <param name="phoneNumber"></param> 新的手机号码
    virtual void common_update_phone_number_put(const std::optional<int32_t> &category, 
        const std::optional<int32_t> &id, const std::optional<std::string> &phoneNumber,
        Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 更改手机号码
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    /// <param name="userCategory"></param> 用户类别
    /// <param name="ID"></param> 用户id
    /// <param name="phoneNumber"></param> 新的手机号码
    virtual void common_hearing_trends_get(const std::optional<int32_t> &category, 
        const std::optional<int32_t> &language, const std::optional<std::vector<int32_t>> &checkID,
        Pistache::Http::ResponseWriter &response) = 0;
};

} // namespace api

#endif // INCLUDE_AUDIO_TESTER_API_H