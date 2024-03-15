/*** 
 * @Author: chen wei
 * @Date: 2023-11-15 09:12:22
 * @LastEditTime: 2024-03-01 14:27:01
 * @FilePath: /audio_tester/src/AudioTesterApi.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "AudioTesterApi.h"
#include "Helpers.h"
#include "ResponseMsg.h"

namespace api
{

using namespace helpers;
using namespace model;

AudioTesterApi::AudioTesterApi(std::shared_ptr<Pistache::Rest::Router> rtr)
{
    router = rtr;
}

void AudioTesterApi::init() {
    setupRoutes();
}

void AudioTesterApi::setupRoutes() {
    using namespace Pistache::Rest;

    Routes::Get(*router, base + "/user/login", 
        Routes::bind(&AudioTesterApi::user_login_get_handler, this));
    Routes::Get(*router, base + "/doctor/login", 
        Routes::bind(&AudioTesterApi::doctor_login_get_handler, this));
    Routes::Put(*router, base + "/doctor/doctor-info", 
        Routes::bind(&AudioTesterApi::doctor_doctor_info_put_handler, this));
    Routes::Post(*router, base + "/doctor/logout", 
        Routes::bind(&AudioTesterApi::doctor_logout_post_handler, this));
    Routes::Get(*router, base + "/doctor/personal-info", 
        Routes::bind(&AudioTesterApi::doctor_personal_info_get_handler, this));
    Routes::Post(*router, base + "/doctor/register", 
        Routes::bind(&AudioTesterApi::doctor_register_post_handler, this));
    Routes::Post(*router, base + "/doctor/retrive-passwd", 
        Routes::bind(&AudioTesterApi::doctor_retrive_passwd_post_handler, this));
    Routes::Put(*router, base + "/doctor/passwd-change", 
        Routes::bind(&AudioTesterApi::doctor_passwd_change_put_handler, this));
    Routes::Get(*router, base + "/patients/checklists-info", 
        Routes::bind(&AudioTesterApi::patients_checklists_info_get_handler, this));
    Routes::Delete(*router, base + "/patients/checklists-info", 
        Routes::bind(&AudioTesterApi::patients_checklists_info_delete_handler, this));
    Routes::Post(*router, base + "/patients/checklists-info", 
        Routes::bind(&AudioTesterApi::patients_checklists_info_post_handler, this));
    Routes::Put(*router, base + "/patients/checklists-info", 
        Routes::bind(&AudioTesterApi::patients_checklists_info_put_handler, this));
    Routes::Delete(*router, base + "/patients/patients-info", 
        Routes::bind(&AudioTesterApi::patients_patients_info_delete_handler, this));
    Routes::Get(*router, base + "/patients/patients-info", 
        Routes::bind(&AudioTesterApi::patients_patients_info_get_handler, this));
    Routes::Post(*router, base + "/patients/patients-info", 
        Routes::bind(&AudioTesterApi::patients_patients_info_post_handler, this));
    Routes::Put(*router, base + "/patients/patients-info", 
        Routes::bind(&AudioTesterApi::patients_patients_info_put_handler, this));
    Routes::Get(*router, base + "/user/checkinfo", 
        Routes::bind(&AudioTesterApi::user_checkinfo_get_handler, this));
    Routes::Delete(*router, base + "/user/checkinfo", 
        Routes::bind(&AudioTesterApi::user_checkinfo_delete_handler, this));
    Routes::Post(*router, base + "/user/checkinfo", 
        Routes::bind(&AudioTesterApi::user_checkinfo_post_handler, this));
    Routes::Post(*router, base + "/user/logout", 
        Routes::bind(&AudioTesterApi::user_logout_post_handler, this));
    Routes::Get(*router, base + "/user/personal-info", 
        Routes::bind(&AudioTesterApi::user_personal_info_get_handler, this));
    Routes::Put(*router, base + "/user/personal-info", 
        Routes::bind(&AudioTesterApi::user_personal_info_put_handler, this));
    Routes::Post(*router, base + "/user/register/", 
        Routes::bind(&AudioTesterApi::user_register_post_handler, this));
    Routes::Post(*router, base + "/user/retrieve-passwd", 
        Routes::bind(&AudioTesterApi::user_retrieve_passwd_post_handler, this));
    Routes::Put(*router, base + "/user/passwd-change", 
        Routes::bind(&AudioTesterApi::user_passwd_change_put_handler, this));
    Routes::Get(*router, base + "/patients/patients-info/name", 
        Routes::bind(&AudioTesterApi::patients_patients_info_name_get_handler, this));
    Routes::Get(*router, base + "/patients/patients-info/time", 
        Routes::bind(&AudioTesterApi::patients_patients_info_time_get_handler, this));
    Routes::Get(*router, base + "/common/push-info", 
        Routes::bind(&AudioTesterApi::common_push_info_get_handler, this));
    Routes::Get(*router, base + "/common/sms-verification", 
        Routes::bind(&AudioTesterApi::common_sms_verification_get_handler, this));
    Routes::Put(*router, base + "/common/update-phoneNumber", 
        Routes::bind(&AudioTesterApi::common_update_phone_number_put_handler, this));
    Routes::Get(*router, base + "/common/hearing-trends", 
        Routes::bind(&AudioTesterApi::common_hearing_trends_get_handler, this));
    // Default handler, called when a route is not found
    router->addCustomHandler(Routes::bind(&AudioTesterApi::default_api_default_handler, this));
};

std::pair<Pistache::Http::Code, std::string> AudioTesterApi::handleParsingException(const std::exception& ex) const noexcept
{
    try {
        throw;
    } catch (nlohmann::detail::exception &e) {
        return std::make_pair(Pistache::Http::Code::Bad_Request, e.what());


    } catch (helpers::ValidationException &e) {
        return std::make_pair(Pistache::Http::Code::Bad_Request, e.what());
    } catch (std::exception &e) {
        return std::make_pair(Pistache::Http::Code::Internal_Server_Error, e.what());
    }
}

std::pair<Pistache::Http::Code, std::string> AudioTesterApi::handleOperationException(const std::exception& ex) const noexcept
{
    return std::make_pair(Pistache::Http::Code::Internal_Server_Error, ex.what());
}

void AudioTesterApi::user_login_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
        // Getting the query params
        auto phoneNumberQuery = request.query().get("phoneNumber");
        std::optional<std::string> phoneNumber;
        if(phoneNumberQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(phoneNumberQuery.value(), valueQuery_instance)){
                phoneNumber = valueQuery_instance;
            }
        }
        auto passwdQuery = request.query().get("passwd");

        std::optional<std::string> passwd;
        if(passwdQuery.has_value()){
            passwd = passwdQuery.value();
        }
        
        try {
            this->user_login_get(phoneNumber, passwd, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "普通用户登录失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            LOG(WARNING) << "普通用户登录失败： " << errorInfo.second ;
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) 
    {
        LOG(WARNING) << "普通用户登录失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::doctor_login_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
    // Getting the query params
    auto phoneNumberQuery = request.query().get("phoneNumber");
    std::optional<std::string> phoneNumber;
    if(phoneNumberQuery.has_value()){
        std::string valueQuery_instance;
        if(fromStringValue(phoneNumberQuery.value(), valueQuery_instance)){
            phoneNumber = valueQuery_instance;
        }
    }
    auto passwdQuery = request.query().get("passwd");
    std::optional<std::string> passwd;
    if(passwdQuery.has_value()){
        std::string valueQuery_instance;
        if(fromStringValue(passwdQuery.value(), valueQuery_instance)){
            passwd = valueQuery_instance;
        }
    }
    
    try {
        this->doctor_login_get(phoneNumber, passwd, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "医生用户登录失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "医生用户登录失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) 
    {
        LOG(WARNING) << "医生用户登录失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::doctor_doctor_info_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {

    // Getting the body param
    DoctorInfoPut doctorInfoPut;
    
    // Getting the query params
    auto doctorIDQuery = request.query().get("doctorID");
    std::optional<int32_t> doctorID;
    if(doctorIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
            doctorID = valueQuery_instance;
        }
    }
    
    try {
        nlohmann::json::parse(request.body()).get_to(doctorInfoPut);
        doctorInfoPut.validate();
    } catch (std::exception &e) {
        LOG(WARNING) << "医生用户修改个人信息失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    try {
        this->doctor_doctor_info_put(doctorID, doctorInfoPut, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "医生用户修改个人信息失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "医生用户修改个人信息失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) 
    {
        LOG(WARNING) << "医生用户修改个人信息失败： " << e.what() ;
        resMsg.setFail(false);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::doctor_logout_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
        // Getting the query params
        auto doctorIDQuery = request.query().get("doctorID");
        std::optional<int32_t> doctorID;
        if(doctorIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
                doctorID = valueQuery_instance;
            }
        }
        auto passwdQuery = request.query().get("passwd");
        std::optional<std::string> passwd;
        if(passwdQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(passwdQuery.value(), valueQuery_instance)){
                passwd = valueQuery_instance;
            }
        }
        
        try 
        {
            this->doctor_logout_post(doctorID, passwd, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "医生用户注销账号失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "医生用户注销账号失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) 
    {
        LOG(WARNING) << "医生用户注销账号失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::doctor_personal_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
        // Getting the query params
        auto doctorIDQuery = request.query().get("doctorID");
        std::optional<int32_t> doctorID;
        if(doctorIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
                doctorID = valueQuery_instance;
            }
        }
        
        try 
        {
            this->doctor_personal_info_get(doctorID, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "医生用户获取个人信息失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "医生用户获取个人信息失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) {
        LOG(WARNING) << "医生用户获取个人信息失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::doctor_register_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
        // Getting the body param
        DocterRegisterPost docterRegisterPost;
        
        try {
            nlohmann::json::parse(request.body()).get_to(docterRegisterPost);
            docterRegisterPost.validate();
        } catch (std::exception &e) {
            LOG(WARNING) << "医生用户注册账号失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

        try {
            this->doctor_register_post(docterRegisterPost, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "医生用户注册账号失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "医生用户注册账号失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) {
        LOG(WARNING) << "医生用户注册账号失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::doctor_retrive_passwd_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
    // Getting the query params
    auto phoneNumberQuery = request.query().get("phoneNumber");
    std::optional<std::string> phoneNumber;
    if(phoneNumberQuery.has_value()){
        std::string valueQuery_instance;
        if(fromStringValue(phoneNumberQuery.value(), valueQuery_instance)){
            phoneNumber = valueQuery_instance;
        }
    }
    auto verificationCodeQuery = request.query().get("verificationCode");
        std::optional<std::string> verificationCode;
        if(verificationCodeQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(verificationCodeQuery.value(), valueQuery_instance)){
                verificationCode = valueQuery_instance;
            }
        }
    auto passwordQuery = request.query().get("password");
    std::optional<std::string> password;
    if(passwordQuery.has_value()){
        std::string valueQuery_instance;
        if(fromStringValue(passwordQuery.value(), valueQuery_instance)){
            password = valueQuery_instance;
        }
    }
    try {
        this->doctor_retrive_passwd_post(phoneNumber, verificationCode, password, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "医生用户修改密码失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "医生用户修改密码失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) {
        LOG(WARNING) << "医生用户修改密码失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::doctor_passwd_change_put_handler(const Pistache::Rest::Request &request, 
    Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {

        // Getting the query params
        auto doctorIDQuery = request.query().get("doctorID");
        std::optional<int32_t> doctorID;
        if(doctorIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
                doctorID = valueQuery_instance;
            }
        }
        auto passwdQuery = request.query().get("passwd");
        std::optional<std::string> passwd;
        if(passwdQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(passwdQuery.value(), valueQuery_instance)){
                passwd = valueQuery_instance;
            }
        }
        
        auto passwordQuery = request.query().get("password");
        std::optional<std::string> password;
        if(passwordQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(passwordQuery.value(), valueQuery_instance)){
                password = valueQuery_instance;
            }
        }

        try {
            this->doctor_passwd_change_put(doctorID, passwd, password, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "医生用户修改密码失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "医生用户修改密码失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) {
        LOG(WARNING) << "医生用户修改密码失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::patients_checklists_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
    // Getting the query params
    auto patientIDQuery = request.query().get("patientID");
    std::optional<int32_t> patientID;
    if(patientIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(patientIDQuery.value(), valueQuery_instance)){
            patientID = valueQuery_instance;
        }
    }
    auto amountQuery = request.query().get("amount");
    std::optional<int32_t> amount;
    if(amountQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(amountQuery.value(), valueQuery_instance)){
            amount = valueQuery_instance;
        }
    }
    auto languageQuery = request.query().get("language");
    std::optional<int32_t> language;
    if(languageQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(languageQuery.value(), valueQuery_instance)){
            language = valueQuery_instance;
        }
    }
    
    try {
        this->patients_checklists_info_get(patientID, amount, language, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "病人检查信息获取失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "病人检查信息获取失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) {
        LOG(WARNING) << "病人检查信息获取失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::patients_checklists_info_delete_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
    
        // Getting the body param
        std::vector<int32_t> requestBody;
        // Getting the query params
        auto patientIDQuery = request.query().get("patientID");
        std::optional<int32_t> patientID;
        if(patientIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(patientIDQuery.value(), valueQuery_instance)){
                patientID = valueQuery_instance;
            }
        }
        try {
            nlohmann::json::parse(request.body()).get_to(requestBody);
            this->patients_checklists_info_delete(patientID, requestBody, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "病人检查信息删除失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "病人检查信息删除失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }
    } catch (std::exception &e) {
        LOG(WARNING) << "病人检查信息删除失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::patients_checklists_info_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
        // Getting the body param
        PatientChecklistInfoPost patientChecklistInfoPost;
        
        try {
            nlohmann::json::parse(request.body()).get_to(patientChecklistInfoPost);
            patientChecklistInfoPost.validate();
        } catch (std::exception &e) {
            LOG(WARNING) << "病人检查信息添加失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

        try {
            this->patients_checklists_info_post(patientChecklistInfoPost, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "病人检查信息添加失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "病人检查信息添加失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) {
        LOG(WARNING) << "病人检查信息添加失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::patients_checklists_info_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
        // Getting the body param
        
        PatientChecklistInfoPut patientChecklistInfoPut;
        
        // Getting the query params
        auto patientIDQuery = request.query().get("patientID");
        std::optional<int32_t> patientID;
        if(patientIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(patientIDQuery.value(), valueQuery_instance)){
                patientID = valueQuery_instance;
            }
        }
        auto checkIDQuery = request.query().get("checkID");
        std::optional<int32_t> checkID;
        if(checkIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(checkIDQuery.value(), valueQuery_instance)){
                checkID = valueQuery_instance;
            }
        }
        
        try {
            nlohmann::json::parse(request.body()).get_to(patientChecklistInfoPut);
            patientChecklistInfoPut.validate();
        } catch (std::exception &e) {
            LOG(WARNING) << "病人检查信息修改失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

        try {
            this->patients_checklists_info_put(patientID, checkID, patientChecklistInfoPut, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "病人检查信息修改失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "病人检查信息修改失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) 
    {
        LOG(WARNING) << "病人检查信息修改失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::patients_patients_info_delete_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {

        // Getting the body param
        std::vector<int32_t> requestBody;
        // Getting the query params
        auto doctorIDQuery = request.query().get("doctorID");
        std::optional<int32_t> doctorID;
        if(doctorIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
                doctorID = valueQuery_instance;
            }
        }
       
        try {
            nlohmann::json::parse(request.body()).get_to(requestBody);
            this->patients_patients_info_delete(doctorID, requestBody, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "病人个人信息删除失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "病人个人信息删除失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) 
    {
        LOG(WARNING) << "病人个人信息删除失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::patients_patients_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
        // Getting the query params
        auto doctorIDQuery = request.query().get("doctorID");
        std::optional<int32_t> doctorID;
        if(doctorIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
                doctorID = valueQuery_instance;
            }
        }
        auto amountQuery = request.query().get("amount");
        std::optional<int32_t> amount;
        if(amountQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(amountQuery.value(), valueQuery_instance)){
                amount = valueQuery_instance;
            }
        }
        try {
            this->patients_patients_info_get(doctorID, amount, response);
            } catch (Pistache::Http::HttpError &e) {
                LOG(WARNING) << "病人个人信息获取失败： " << e.what() ;
                resMsg.setFail(true);
                resMsg.setMsg(e.what());
                auto  time_now = std::chrono::steady_clock::now();
                resMsg.setTime(time_now.time_since_epoch().count());
                to_json(j, resMsg);
                response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
                return;
            } catch (std::exception &e) {
                LOG(WARNING) << "病人个人信息获取失败： " << e.what() ;
                const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
                resMsg.setFail(true);
                resMsg.setMsg(errorInfo.second);
                auto  time_now = std::chrono::steady_clock::now();
                resMsg.setTime(time_now.time_since_epoch().count());
                to_json(j, resMsg);
                response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
                return;
            }

    } catch (std::exception &e) {
        LOG(WARNING) << "病人个人信息获取失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::patients_patients_info_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {

    // Getting the body param
    
    PatientInfoPost patientInfoPost;
    // Getting the query params
    // auto doctorIDQuery = request.query().get("doctorID");
    // std::optional<int32_t> doctorID;
    // if(doctorIDQuery.has_value()){
    //     int32_t valueQuery_instance;
    //     if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
    //         doctorID = valueQuery_instance;
    //     }
    // }
    
    try {
        nlohmann::json::parse(request.body()).get_to(patientInfoPost);
        patientInfoPost.validate();
    } catch (std::exception &e) {
        LOG(WARNING) << "病人个人信息添加失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    try {
        this->patients_patients_info_post(patientInfoPost, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "病人个人信息添加失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "病人个人信息添加失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) {
        LOG(WARNING) << "病人个人信息添加失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::patients_patients_info_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {

    // Getting the body param
    
    PatientInfoPut patientInfoPut;
    
    // Getting the query params
    auto doctorIDQuery = request.query().get("doctorID");
    std::optional<int32_t> doctorID;
    if(doctorIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
            doctorID = valueQuery_instance;
        }
    }
    auto patientIDQuery = request.query().get("patientID");
    std::optional<int32_t> patientID;
    if(patientIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(patientIDQuery.value(), valueQuery_instance)){
            patientID = valueQuery_instance;
        }
    }
    
    try {
        nlohmann::json::parse(request.body()).get_to(patientInfoPut);
        patientInfoPut.validate();
    } catch (std::exception &e) {
        LOG(WARNING) << "病人个人信息修改失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    try {
        this->patients_patients_info_put(doctorID, patientID, patientInfoPut, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "病人个人信息修改失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "病人个人信息修改失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) {
        LOG(WARNING) << "病人个人信息修改失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::user_checkinfo_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {

    // Getting the query params
    auto userIDQuery = request.query().get("userID");
    std::optional<int32_t> userID;
    if(userIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(userIDQuery.value(), valueQuery_instance)){
            userID = valueQuery_instance;
        }
    }
    auto amountQuery = request.query().get("amount");
    std::optional<int32_t> amount;
    if(amountQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(amountQuery.value(), valueQuery_instance)){
            amount = valueQuery_instance;
        }
    }

    auto languageQuery = request.query().get("language");
    std::optional<int32_t> language;
    if(languageQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(languageQuery.value(), valueQuery_instance)){
            language = valueQuery_instance;
        }
    }
    
    try {
        this->user_checkinfo_get(userID, amount, language, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "普通用户检查信息获取失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户检查信息获取失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户检查信息获取失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::user_checkinfo_delete_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    // Getting the body param
    std::vector<int32_t> requestBody;
    // Getting the query params
    auto userIDQuery = request.query().get("userID");
    std::optional<int32_t> userID;
    if(userIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(userIDQuery.value(), valueQuery_instance)){
            userID = valueQuery_instance;
        }
    }
    
    try {
        nlohmann::json::parse(request.body()).get_to(requestBody);
        this->user_checkinfo_delete(userID, requestBody, response);
    } catch (nlohmann::detail::exception &e) {
        LOG(WARNING) << "普通用户检查信息删除失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户检查信息删除失败： " << e.what() ;
        //send a 500 error
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
        return;
    }
}

void AudioTesterApi::user_checkinfo_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
    // Getting the body param
    
    UserCheckinfoPost userCheckinfoPost;
    
    try {
        nlohmann::json::parse(request.body()).get_to(userCheckinfoPost);
        userCheckinfoPost.validate();
    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户检查信息添加失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    try {
        this->user_checkinfo_post(userCheckinfoPost, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "普通用户检查信息添加失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户检查信息添加失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户检查信息添加失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::user_logout_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
    // Getting the query params
    auto userIDQuery = request.query().get("userID");
    std::optional<int32_t> userID;
    if(userIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(userIDQuery.value(), valueQuery_instance)){
            userID = valueQuery_instance;
        }
    }
    auto passwdQuery = request.query().get("passwd");
    std::optional<std::string> passwd;
    if(passwdQuery.has_value()){
        std::string valueQuery_instance;
        if(fromStringValue(passwdQuery.value(), valueQuery_instance)){
            passwd = valueQuery_instance;
        }
    }
    
    try {
        this->user_logout_post(userID, passwd, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "普通用户注销账户失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户注销账户失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户注销账户失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::user_personal_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {


    // Getting the query params
    auto userIDQuery = request.query().get("userID");
    std::optional<int32_t> userID;
    if(userIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(userIDQuery.value(), valueQuery_instance)){
            userID = valueQuery_instance;
        }
    }
    
    try {
        this->user_personal_info_get(userID, response);
    } catch (Pistache::Http::HttpError &e) {
        LOG(WARNING) << "普通用户个人信息获取失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户个人信息获取失败： " << e.what() ;
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        resMsg.setFail(true);
        resMsg.setMsg(errorInfo.second);
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
        return;
    }

    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户个人信息获取失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::user_personal_info_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
        // Getting the body param
        
        UserPersonalInfoPut userPersonalInfoPut;
        
        // Getting the query params
        auto userIDQuery = request.query().get("userID");
        std::optional<int32_t> userID;
        if(userIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(userIDQuery.value(), valueQuery_instance)){
                userID = valueQuery_instance;
            }
        }
        
        try {
            nlohmann::json::parse(request.body()).get_to(userPersonalInfoPut);
            userPersonalInfoPut.validate();
        } catch (std::exception &e) {
            LOG(WARNING) << "普通用户个人信息修改失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

        try {
            this->user_personal_info_put(userID, userPersonalInfoPut, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "普通用户个人信息修改失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "普通用户个人信息修改失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户个人信息修改失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::user_register_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
        // Getting the body param
        UserRegisterPost userRegisterPost;
        
        try {
            nlohmann::json::parse(request.body()).get_to(userRegisterPost);
            userRegisterPost.validate();
        } catch (std::exception &e) {
            LOG(WARNING) << "普通用户注册账户失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleParsingException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

        try {
            this->user_register_post(userRegisterPost, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "普通用户注册账户失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "普通用户注册账户失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户注册账户失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::user_retrieve_passwd_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {

        // Getting the query params
        auto phoneNumberQuery = request.query().get("phoneNumber");
        std::optional<std::string> phoneNumber;
        if(phoneNumberQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(phoneNumberQuery.value(), valueQuery_instance)){
                phoneNumber = valueQuery_instance;
            }
        }
        auto verificationCodeQuery = request.query().get("verificationCode");
        std::optional<std::string> verificationCode;
        if(verificationCodeQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(verificationCodeQuery.value(), valueQuery_instance)){
                verificationCode = valueQuery_instance;
            }
        }
        auto passwordQuery = request.query().get("password");
        std::optional<std::string> password;
        if(passwordQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(passwordQuery.value(), valueQuery_instance)){
                password = valueQuery_instance;
            }
        }
        try {
            this->user_retrieve_passwd_post(phoneNumber, verificationCode, password, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "普通用户重置密码失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "普通用户重置密码失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户找回密码失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::user_passwd_change_put_handler(const Pistache::Rest::Request &request, 
    Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {

        // Getting the query params
        auto userIDQuery = request.query().get("userID");
        std::optional<int32_t> userID;
        if(userIDQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(userIDQuery.value(), valueQuery_instance)){
                userID = valueQuery_instance;
            }
        }
        
        auto passwdQuery = request.query().get("passwd");
        std::optional<std::string> passwd;
        if(passwdQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(passwdQuery.value(), valueQuery_instance)){
                passwd = valueQuery_instance;
            }
        }
        
        auto passwordQuery = request.query().get("password");
        std::optional<std::string> password;
        if(passwordQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(passwordQuery.value(), valueQuery_instance)){
                password = valueQuery_instance;
            }
        }

        try {
            this->user_passwd_change_put(userID, passwd, password, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "普通用户修改密码失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            LOG(WARNING) << "普通用户修改密码失败： " << e.what() ;
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) {
        LOG(WARNING) << "普通用户修改密码失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::patients_patients_info_name_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    // Getting the query params
    auto nameQuery = request.query().get("name");
    std::optional<std::string> name;
    if(nameQuery.has_value()){
        std::string valueQuery_instance;
        if(fromStringValue(nameQuery.value(), valueQuery_instance)){
            name = valueQuery_instance;
        }
    }
    
    auto doctorIDQuery = request.query().get("doctorID");
    std::optional<int32_t> doctorID;
    if(doctorIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
            doctorID = valueQuery_instance;
        }
    }

    try {
      this->patients_patients_info_name_get(doctorID, name, response);
    } catch (nlohmann::detail::exception &e) {
        LOG(WARNING) << "病人信息按姓名查询失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "病人信息按姓名查询失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
        return;
    }

}

void AudioTesterApi::patients_patients_info_time_get_handler(const Pistache::Rest::Request &request, 
    Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    // Getting the query params
    auto startTimeQuery = request.query().get("startTime");
    std::optional<std::string> startTime;
    if(startTimeQuery.has_value()){
        std::string valueQuery_instance;
        if(fromStringValue(startTimeQuery.value(), valueQuery_instance)){
            startTime = valueQuery_instance;
        }
    }
    auto endTimeQuery = request.query().get("endTime");
    std::optional<std::string> endTime;
    if(endTimeQuery.has_value()){
        std::string valueQuery_instance;
        if(fromStringValue(endTimeQuery.value(), valueQuery_instance)){
            endTime = valueQuery_instance;
        }
    }
    
    auto doctorIDQuery = request.query().get("doctorID");
    std::optional<int32_t> doctorID;
    if(doctorIDQuery.has_value()){
        int32_t valueQuery_instance;
        if(fromStringValue(doctorIDQuery.value(), valueQuery_instance)){
            doctorID = valueQuery_instance;
        }
    }

    try {
      this->patients_patients_info_time_get(doctorID, startTime, endTime, response);
    } catch (nlohmann::detail::exception &e) {
        LOG(WARNING) << "病人信息按创建时间查询失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
        return;
    } catch (std::exception &e) {
        LOG(WARNING) << "病人信息按创建时间查询失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
        return;
    }

}

void AudioTesterApi::common_push_info_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    try {
        // Getting the query params
        auto categoryQuery = request.query().get("category");
        std::optional<int32_t> category;
        if(categoryQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(categoryQuery.value(), valueQuery_instance)){
                category = valueQuery_instance;
            }
        }
        auto languageQuery = request.query().get("language");
        std::optional<int32_t> language;
        if(languageQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(languageQuery.value(), valueQuery_instance)){
                language = valueQuery_instance;
            }
        }

        try {
            this->common_push_info_get(category, language, response);
        } catch (Pistache::Http::HttpError &e) {
            LOG(WARNING) << "用户获取推送信息失败： " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(e.code()), j.dump(), MIME(Text, Plain));
            return;
        } catch (std::exception &e) {
            const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
            LOG(WARNING) << "用户获取推送信息失败： " << errorInfo.second ;
            resMsg.setFail(true);
            resMsg.setMsg(errorInfo.second);
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            nlohmann::json j;
            to_json(j, resMsg);
            response.send(Pistache::Http::Code(errorInfo.first), j.dump(), MIME(Text, Plain));
            return;
        }

    } catch (std::exception &e) 
    {
        LOG(WARNING) << "用户获取推送信息失败： " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::common_sms_verification_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
        // Getting the query params
        auto phoneNumberQuery = request.query().get("phoneNumber");
        std::optional<std::string> phoneNumber;
        if(phoneNumberQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(phoneNumberQuery.value(), valueQuery_instance)){
                phoneNumber = valueQuery_instance;
            }
        }
        auto functionQuery = request.query().get("function");
        std::optional<int32_t> function;
        if(functionQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(functionQuery.value(), valueQuery_instance)){
                function = valueQuery_instance;
            }
        }

        try
        {
            this->common_sms_verification_get(phoneNumber, function, response);
        }
        catch(nlohmann::detail::exception &e)
        {
            LOG(WARNING) << "用户验证码获取失败: " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
            return;
        }
    } catch (std::exception &e) 
    {
        LOG(WARNING) << "用户验证码获取失败: " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }

}

void AudioTesterApi::common_update_phone_number_put_handler(const Pistache::Rest::Request &request, 
    Pistache::Http::ResponseWriter response)
{
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
        // Getting the query params
        auto phoneNumberQuery = request.query().get("phoneNumber");
        std::optional<std::string> phoneNumber;
        if(phoneNumberQuery.has_value()){
            std::string valueQuery_instance;
            if(fromStringValue(phoneNumberQuery.value(), valueQuery_instance)){
                phoneNumber = valueQuery_instance;
            }
        }
        auto idQuery = request.query().get("id");
        std::optional<int32_t> id;
        if(idQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(idQuery.value(), valueQuery_instance)){
                id = valueQuery_instance;
            }
        }
        auto categoryQuery = request.query().get("category");
        std::optional<int32_t> category;
        if(categoryQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(categoryQuery.value(), valueQuery_instance)){
                category = valueQuery_instance;
            }
        }

        try
        {
            this->common_update_phone_number_put(category, id, phoneNumber, response);
        }
        catch(nlohmann::detail::exception &e)
        {
            LOG(WARNING) << "用户手机号码更改失败: " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
            return;
        }
    } catch (std::exception &e) 
    {
        LOG(WARNING) << "用户手机号码更改失败: " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::common_hearing_trends_get_handler(const Pistache::Rest::Request &request, 
    Pistache::Http::ResponseWriter response)
{
    ResponseMsg resMsg;
    nlohmann::json j;
    try {
        // Getting the body param
        std::vector<int32_t> requestBody;
        // Getting the query params
        auto categoryQuery = request.query().get("category");
        std::optional<int32_t> category;
        if(categoryQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(categoryQuery.value(), valueQuery_instance)){
                category = valueQuery_instance;
            }
        }
        auto languageQuery = request.query().get("language");
        std::optional<int32_t> language;
        if(languageQuery.has_value()){
            int32_t valueQuery_instance;
            if(fromStringValue(languageQuery.value(), valueQuery_instance)){
                language = valueQuery_instance;
            }
        }
        try
        {
            nlohmann::json::parse(request.body()).get_to(requestBody);
            this->common_hearing_trends_get(category, language, requestBody, response);
        }
        catch(nlohmann::detail::exception &e)
        {
            LOG(WARNING) << "获取听力趋势失败: " << e.what() ;
            resMsg.setFail(true);
            resMsg.setMsg(e.what());
            auto  time_now = std::chrono::steady_clock::now();
            resMsg.setTime(time_now.time_since_epoch().count());
            to_json(j, resMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
            return;
        }
    } catch (std::exception &e) 
    {
        LOG(WARNING) << "获取听力趋势失败: " << e.what() ;
        resMsg.setFail(true);
        resMsg.setMsg(e.what());
        auto  time_now = std::chrono::steady_clock::now();
        resMsg.setTime(time_now.time_since_epoch().count());
        nlohmann::json j;
        to_json(j, resMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApi::default_api_default_handler(const Pistache::Rest::Request &, Pistache::Http::ResponseWriter response) 
{
    ResponseMsg resMsg;
    nlohmann::json j;
    LOG(WARNING) << "该请求方式不存在！";
    resMsg.setFail(true);
    resMsg.setMsg("The requested method does not exist");
    auto  time_now = std::chrono::steady_clock::now();
    resMsg.setTime(time_now.time_since_epoch().count());
    to_json(j, resMsg);
    response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
}


} // api
