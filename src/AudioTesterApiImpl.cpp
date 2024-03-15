/*** 
 * @Author: chen wei
 * @Date: 2023-11-15 14:49:11
 * @LastEditTime: 2024-03-01 16:12:03
 * @FilePath: /audio_tester/src/AudioTesterApiImpl.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include <memory>
#include <glog/logging.h>
#include "AudioTesterApiImpl.h"
#include "mysql_conn.h"
#include "connection_pool.h"
#include "DoctorRegisterJudge.h"
#include "VerificationCodeManager.h"
#include "SmsVerification.h"

#include "HearingHealthAnalyzer.h"
#include "Translator.h"
namespace api {

using namespace model;

AudioTesterApiImpl::AudioTesterApiImpl(std::shared_ptr<Pistache::Rest::Router> rtr)
    : AudioTesterApi(rtr)
{
   
}


void AudioTesterApiImpl::user_login_get(const std::optional<std::string> &phoneNumber, 
    const std::optional<std::string> &passwd, Pistache::Http::ResponseWriter &response) 
{
    // ResponseMsg responseMsg;
    nlohmann::json j_user = nlohmann::json();
    nlohmann::json j_response = nlohmann::json();
    try {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_user = pool->getConnection();

        char sql[1024] = { 0 };
        sprintf(sql, "SELECT userID, password FROM T_USERS WHERE phoneNumber = '%s'", phoneNumber.value().data());
        if (conn_user->query(sql) && conn_user->next()) {
            nlohmann::json passwd_json = nlohmann::json::parse(conn_user->value(true));

            if (strcmp(passwd.value().data(), CryptoppAes::AesDecrypt(passwd_json["password"]).data())==0) {
                j_user["userID"] = passwd_json["userID"];
                j_response["data"] = j_user;
                j_response["fail"] = false;
                j_response["msg"] = "登录成功！";
                j_response["data"]["userID"] = passwd_json["userID"];
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Application, Json));
            } else {
                j_response["fail"] = true;
                j_response["msg"] = "密码错误";
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Unauthorized, j_response.dump(), MIME(Application, Json));
            }
        } else {
            j_response["fail"] = true;
            j_response["msg"] = "未找到该用户";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Not_Found, j_response.dump(), MIME(Application, Json));
        }
    } catch (const std::exception &e) {
        LOG(WARNING) << "Exception: " << e.what();
    }
}

void AudioTesterApiImpl::doctor_login_get(const std::optional<std::string> &phoneNumber, 
    const std::optional<std::string> &passwd, Pistache::Http::ResponseWriter &response) 
{
    // ResponseMsg responseMsg;
    nlohmann::json j_doctor = nlohmann::json();
    nlohmann::json j_response = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_doctor = pool->getConnection();

        char sql[1024] = { 0 };
        sprintf(sql, "SELECT * FROM T_DOCTORS WHERE phoneNumber = '%s'", phoneNumber.value().data());
        // LOG(INFO) << sql;
        // 判断是否成功返回结果
        if (conn_doctor->query(sql)&&conn_doctor->next())
        {
            sprintf(sql, "SELECT doctorID,password FROM T_DOCTORS WHERE phoneNumber = '%s'", phoneNumber.value().data());
            if (conn_doctor->query(sql)&&conn_doctor->next())
            {
                nlohmann::json passwd_json = nlohmann::json::parse(conn_doctor->value(true));
                // 判断查询到的密码是否和用户请求的你们匹配
                if(strcmp(passwd.value().data(), CryptoppAes::AesDecrypt(passwd_json["password"]).data())==0)
                {
                    LOG(INFO) << "医生用户电话号码：" << phoneNumber.value() << " 登录成功";
                    j_doctor["doctorID"] = passwd_json["doctorID"];
                    j_response["data"] = j_doctor;
                    j_response["fail"] = false;
                    j_response["msg"] = "请求成功";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                }
                else{
                    LOG(WARNING) << "医生用户电话号码：" << phoneNumber.value() << " 登录失败（密码错误）";
                    j_response["data"] = j_doctor;
                    j_response["fail"] = true;
                    j_response["msg"] = "密码错误";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Unauthorized, j_response.dump(), MIME(Text, Plain));
                }
            }
            else{
                LOG(WARNING) << "医生用户电话号码：" << phoneNumber.value() << " 查询数据库信息失败";
                j_response["data"] = j_doctor;
                j_response["fail"] = true;
                j_response["msg"] = "查询失败";
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
            }
        }
        else
        {
            LOG(WARNING) << "医生用户电话号码：" << phoneNumber.value() << " 该用户不存在";
            j_response["data"] = j_doctor;
            j_response["fail"] = true;
            j_response["msg"] = "未查询到该用户";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_doctor;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain)); 
    }  
}

void AudioTesterApiImpl::doctor_doctor_info_put(const std::optional<int32_t> &doctorID, 
    const DoctorInfoPut &doctorInfoPut, Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    nlohmann::json j_doctorInfo = doctorInfoPut;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_doctor = pool->getConnection();
        // if (j_doctorInfo.find("phoneNumber") != j_doctorInfo.end())
        // {
        //     std::string phone = j_doctorInfo["phoneNumber"];
        //     char sql[1024] = { 0 };
        //     sprintf(sql, "SELECT * FROM T_DOCTORS WHERE phoneNumber = '%s'", phone.data());
        //     if (conn_doctor->query(sql) & conn_doctor->next())
        //     {
        //         auto  time_now = std::chrono::steady_clock::now();
        //         responseMsg.setTime(time_now.time_since_epoch().count());
        //         responseMsg.setFail(true);
        //         responseMsg.setMsg("该号码已被注册");
        //         nlohmann::json j;
        //         to_json(j, responseMsg);
        //         response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
        //     }
        // }

        char sql[1024] = { 0 };
        sprintf(sql, "SELECT phoneNumber FROM T_DOCTORS WHERE doctorID = %d", doctorID.value());
        
        if(conn_doctor->query(sql)&conn_doctor->next())
        {
            nlohmann::json passwd_json = nlohmann::json::parse(conn_doctor->value(true));
            std::string phone = passwd_json["phoneNumber"];
            
            std::string sql = UpdateSql::getSqlModify(j_doctorInfo);
            sql = "UPDATE T_DOCTORS SET " + sql + " WHERE doctorID = " + std::to_string(doctorID.value());
            if (conn_doctor->update(sql))
            {
                LOG(INFO) << "医生id 为 " << std::to_string(doctorID.value()) << " 电话号码："<< phone << " 的医生用户成功更新了数据";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("更新数据成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
            }
            else{
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                // responseMsg.setCode(409);
                responseMsg.setMsg("更新数据失败");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
            }
            
        }
        else{
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            // responseMsg.setCode(400);
            responseMsg.setMsg("未找到该用户数据");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        LOG(WARNING) <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        // responseMsg.setCode(500);
        responseMsg.setMsg("系统错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::doctor_logout_post(const std::optional<int32_t> &doctorID, 
    const std::optional<std::string> &passwd, Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_doctor = pool->getConnection();

        
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT password, phoneNumber FROM T_DOCTORS WHERE doctorID = %d", doctorID.value());
        // 判断是否有该用户
        if(conn_doctor->query(sql)&conn_doctor->next())
        {
            nlohmann::json passwd_json = nlohmann::json::parse(conn_doctor->value(true));
            std::string phone = passwd_json["phoneNumber"];
            // 判断查询到的密码是否和用户请求的你们匹配
            if(strcmp(passwd.value().data(), CryptoppAes::AesDecrypt(passwd_json["password"]).data())==0)
            {
                sprintf(sql, "DELETE FROM T_DOCTORS WHERE doctorID = %d", doctorID.value());
                if (conn_doctor->update(sql))
                {
                    LOG(INFO) << "医生ID: " << doctorID.value() <<" 的个人数据全部删除成功！";
                    char patient_sql[1024] = { 0 };
                    sprintf(patient_sql, "SELECT patientID FROM T_PATIENTS WHERE doctorID=%d", doctorID.value());
                    if (conn_doctor->query(patient_sql))
                    {
                        // 删除病人检查信息
                        try
                        {
                            while (conn_doctor->next())
                            {
                                nlohmann::json j_patientID = nlohmann::json::parse(conn_doctor->value(true));
                                std::string patientID = j_patientID["patientID"];
                                sprintf(sql, "DELETE FROM T_PATIENT_CHECK WHERE patientID=%d", std::stoi(patientID));
                                if(conn_doctor->update(sql))
                                {
                                    LOG(INFO) << "病人ID: " << patientID <<" 的检测数据全部删除成功！";
                                }
                                else{
                                    break;
                                }
                            }
                        }
                        catch(const std::exception& e)
                        {
                            LOG(WARNING) << "医生ID: " << doctorID.value() <<" 删除病人检查信息失败！";
                            auto  time_now = std::chrono::steady_clock::now();
                            responseMsg.setTime(time_now.time_since_epoch().count());
                            responseMsg.setFail(true);
                            responseMsg.setMsg(e.what());
                            nlohmann::json j;
                            to_json(j, responseMsg);
                            response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
                        }   
                    }
                    else{
                        LOG(WARNING) << "医生ID: " << doctorID.value() <<" 删除病人检查信息失败！";
                        auto  time_now = std::chrono::steady_clock::now();
                        responseMsg.setTime(time_now.time_since_epoch().count());
                        responseMsg.setFail(true);
                        responseMsg.setMsg("执行失败");
                        nlohmann::json j;
                        to_json(j, responseMsg);
                        response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
                    }
                    sprintf(patient_sql, "DELETE FROM T_PATIENTS WHERE doctorID=%d", doctorID.value());
                    if(conn_doctor->update(patient_sql))
                    {
                        LOG(INFO) << "医生用户ID: " << doctorID.value() <<" 的病人信息全部删除成功";
                        LOG(INFO) << "医生用户ID: " << std::to_string(doctorID.value()) <<", 电话号码:"<<phone<< " 注销了账号";
                        auto  time_now = std::chrono::steady_clock::now();
                        responseMsg.setTime(time_now.time_since_epoch().count());
                        responseMsg.setFail(false);
                        responseMsg.setMsg("注销成功");
                        nlohmann::json j;
                        to_json(j, responseMsg);
                        response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                    }    
                }
                else
                {
                    LOG(WARNING) << "医生ID: " << doctorID.value() <<" 删除病人检查信息失败！";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(false);
                    responseMsg.setMsg("执行失败");
                    nlohmann::json j;
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
                }
            }
            else
            {
                LOG(WARNING) << "医生ID: " << doctorID.value() <<" 删除病人检查信息失败！（密码错误）";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("密码错误");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Unauthorized, j.dump(), MIME(Text, Plain));
            }
        }
        else{
            LOG(WARNING) << "医生ID: " << doctorID.value() <<" 该用户不存在！";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("该用户不存在");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("系统错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::doctor_personal_info_get(const std::optional<int32_t> &doctorID, 
    Pistache::Http::ResponseWriter &response) 
{
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_doctor = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_doctor = pool->getConnection();
        
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT name, gender, age, phoneNumber, licenseID, category, IDcard, province \
            FROM T_DOCTORS WHERE doctorID = %d", doctorID.value());
        
        if (conn_doctor->query(sql) & conn_doctor->next())
        {
            j_doctor = nlohmann::json::parse(conn_doctor->value(true));
            LOG(INFO) << "医生用户id: "<< doctorID.value() <<" 电话号码：" << j_doctor["phoneNumber"] << " 个人信息查找成功";

            j_response["data"] = j_doctor;
            j_response["fail"] = false;
            j_response["msg"] = "请求成功";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
        }
        else{
            LOG(INFO) << "医生用户id: "<< doctorID.value()<< " 个人信息查找失败";
            j_response["data"] = j_doctor;
            j_response["fail"] = true;
            j_response["msg"] = "该用户不存在";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Not_Found, j_response.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_doctor;
        // j_response["code"] = 500;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        // to_json(j_response, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::doctor_register_post(const DocterRegisterPost &docterRegisterPost, 
    Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    nlohmann::json j_register = docterRegisterPost;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_doctor = pool->getConnection();

        VerificationCodeManager manager("localhost", 6379, "earchon123");
        bool isCorrect = manager.verifyCode(docterRegisterPost.getPhoneNumber(), docterRegisterPost.getVerificationCode());
        if (!isCorrect)
        {
            LOG(WARNING) << "医生用户号码为：" << docterRegisterPost.getPhoneNumber() << " 的验证码错误";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("手机验证码错误");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Unauthorized, j.dump(), MIME(Text, Plain));
            return ;
        }

        // 判断请求数值中是否包含所有必填项
        std::string licenseID = j_register["licenseID"];
        // 检查电话号码是否已被注册
        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT * FROM T_DOCTORS WHERE phoneNumber = '%s'", docterRegisterPost.getPhoneNumber().data());
       
        if (conn_doctor->query(exist_sql) & conn_doctor->next())
        {
            LOG(WARNING) << "医生用户号码为：" << docterRegisterPost.getPhoneNumber() << " 已被注册";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("该号码已被注册");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
            return ;
        }
        else
        {
            if (licenseID.length() != 15)
            {
                LOG(WARNING) << "医生用户号码为：" << docterRegisterPost.getPhoneNumber() << " 的医师执业证书编号错误";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("医师执业证书编码应为15数字");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
                return ;
            }
            else
            {
                if(DoctorRegisterJudge::InformationJudge(j_register))
                {
                    // 加密后替换成加密后的密码
                    std::string encode_passwd = CryptoppAes::AesEncrypt(docterRegisterPost.getPassword());
                    j_register["password"] = encode_passwd;
                    // 自动提取key和value，并组合
                    std::string sql_value = UpdateSql::getSqlInsert(j_register);
                    char sql[1024] = { 0 };
                    sprintf(sql, "INSERT INTO T_DOCTORS %s", sql_value.data());
                    
                    // 判断是否插入数据
                    if (conn_doctor->update(sql))
                    {
                        LOG(INFO) << "医生用户：" << docterRegisterPost.getPhoneNumber() << " 注册成功";
                        auto  time_now = std::chrono::steady_clock::now();
                        responseMsg.setTime(time_now.time_since_epoch().count());
                        responseMsg.setFail(false);
                        responseMsg.setMsg("注册成功");
                        nlohmann::json j;
                        to_json(j, responseMsg);
                        response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                    }
                    else{
                        LOG(INFO) << "插入语句：" << sql;
                        LOG(WARNING) << "医生用户注册失败！";
                        auto  time_now = std::chrono::steady_clock::now();
                        responseMsg.setTime(time_now.time_since_epoch().count());
                        responseMsg.setFail(true);
                        responseMsg.setMsg("服务器错误");
                        nlohmann::json j;
                        to_json(j, responseMsg);
                        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
                        return ;
                    }
                    
                }
                else{
                    LOG(WARNING) << "医生用户电话号码： "<< docterRegisterPost.getPhoneNumber() << " 的请求数据不符合要求";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(true);
                    // responseMsg.setCode(400);
                    responseMsg.setMsg("请求的数据不符合要求");
                    nlohmann::json j;
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
                    return ;
                }
            }   
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        // responseMsg.setCode(500);
        responseMsg.setMsg("系统错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::doctor_retrive_passwd_post(const std::optional<std::string> &phoneNumber, 
    const std::optional<std::string> &verificationCode, const std::optional<std::string> &password, 
    Pistache::Http::ResponseWriter &response) {
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_doctor = nlohmann::json();
    ResponseMsg responseMsg;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_doctor = pool->getConnection();
        VerificationCodeManager manager("localhost", 6379, "earchon123");
        bool isCorrect = manager.verifyCode(phoneNumber.value(), verificationCode.value());
        if (!isCorrect)
        {
            LOG(WARNING) << "医生用户号码为：" << phoneNumber.value() << " 的验证码错误";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("手机验证码错误");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Unauthorized, j.dump(), MIME(Text, Plain));
            return ;
        }
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT password FROM T_DOCTORS WHERE phoneNumber = '%s'", phoneNumber.value().data());
        if (conn_doctor->query(sql) & conn_doctor->next())
        {
            // 密码加密
            std::string encode_passwd = CryptoppAes::AesEncrypt(password.value());
            char sql[1024] = { 0 };
            sprintf(sql, "UPDATE T_DOCTORS SET password = '%s' WHERE phoneNumber = '%s'", 
                encode_passwd.data(), phoneNumber.value().data());
            // 更新数据库数据
            if(conn_doctor->update(sql))
            {
                LOG(INFO) << "医生用户电话号码为：" << phoneNumber.value() << " 重置密码成功 ";
                j_response["msg"] = "密码重置成功";
                j_response["fail"] = true;
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                return;
            }
            else{
                LOG(WARNING) << "医生用户电话号码为：" << phoneNumber.value() << " 重置密码失败 ";
                j_response["msg"] = "数据库更新失败";
                j_response["fail"] = true;
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Insufficient_Storage, j_response.dump(), MIME(Text, Plain));
                return;
                }
        }
        else
        {
            LOG(INFO) << "电话号码为：" << phoneNumber.value() << " 的医生用户未重置密码，未注册";
            j_response["fail"] = true;
            j_response["msg"] = "该电话号码未注册";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Bad_Request, j_response.dump(), MIME(Text, Plain));
            return;
        }
    }
    catch(const std::exception& e)
    {
        LOG(INFO) << e.what();
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::doctor_passwd_change_put(const std::optional<int32_t> &doctorID, 
    const std::optional<std::string> &passwd, 
    const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response) {
    ResponseMsg responseMsg;
    nlohmann::json j_doctor = nlohmann::json();
    nlohmann::json j;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_doctor = pool->getConnection();
        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT password FROM T_DOCTORS WHERE doctorID = %d", doctorID.value());
        if (conn_doctor->query(exist_sql) & conn_doctor->next())
        {
            j_doctor = nlohmann::json::parse(conn_doctor->value(true));
            // 判断查询到的密码是否和用户请求的你们匹配
            if(strcmp(passwd.value().data(), CryptoppAes::AesDecrypt(j_doctor["password"]).data())==0)
            {
                char sql[1024] = { 0 };
                sprintf(sql, "UPDATE T_DOCTORS SET password= '%s'  WHERE doctorID = %d", 
                    CryptoppAes::AesEncrypt(password.value()).data(), doctorID.value());
                if(conn_doctor->update(sql))
                {
                    LOG(INFO) << "医生用户ID: " << doctorID.value() << " 修改了密码";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(false);
                    responseMsg.setMsg("修改成功");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                }
                else{
                    LOG(WARNING) << "医生用户ID: " << doctorID.value() << " 修改密码失败";
                    auto time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(true);
                    responseMsg.setMsg("数据库数据修改失败");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
                }
            }
            else{
                LOG(WARNING) << "医生用户ID: " << doctorID.value() << " 旧密码错误";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("密码错误");
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Unauthorized, j.dump(), MIME(Text, Plain));
            }
        }
        else
        {
            LOG(WARNING) << "医生用户ID: " << doctorID.value() << " 未找到";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("未找到此医生用户");
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
        }  
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        LOG(WARNING) << "医生用户ID: " << doctorID.value() << " 修改密码错误，系统出错";
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("系统错误");
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::patients_checklists_info_get(const std::optional<int32_t> &patientID, 
const std::optional<int32_t> &amount, const std::optional<int32_t> &language, 
Pistache::Http::ResponseWriter &response) 
{
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_patient = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT * FROM T_PATIENT_CHECK WHERE patientID = %d ORDER BY checkTime DESC LIMIT %d", 
            patientID.value(), amount.value());
        if (conn_patient->query(sql))
        {
            int i = 0;
            CheckSuggestionTranslate suggestionTranslator;
            if (language.value() == 1)
            {
                Translator translator("20240222001970605", "1K5aclpAsqzmVfw_0uky");
                while (conn_patient->next()& i < amount.value())
                {
                    auto j_patient_temp = nlohmann::json::parse(conn_patient->value(false));
                    j_patient_temp["level"] = suggestionTranslator.generateLevel(j_patient_temp["checkSuggestion"]);
                    j_patient_temp["checkSuggestion"] = suggestionTranslator.generateEnglish(j_patient_temp["checkSuggestion"]);
                    j_patient_temp["checkConclusion"] = translator.translate(j_patient_temp["checkConclusion"], "ch", "en");
                    j_patient.push_back(j_patient_temp);
                    i++;
                }
                if (i >0)
                {
                    LOG(INFO) << "病人ID: " << patientID.value() << " 成功查询了数据";
                    j_response["data"] = j_patient;
                    j_response["fail"] = false;
                    j_response["msg"] = "请求成功";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                }
                else
                {
                    j_response["data"] = j_patient;
                    // j_response["code"] = 406;
                    j_response["fail"] = true;
                    j_response["msg"] = "该病人检查信息不存在";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    // to_json(j_response, responseMsg);
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                }   
            }
            else if (language.value() == 0)
            {
                while (conn_patient->next()& i < amount.value())
                {
                    auto j_patient_temp = nlohmann::json::parse(conn_patient->value(false));
                    j_patient_temp["level"] = suggestionTranslator.generateLevel(j_patient_temp["checkSuggestion"]);
                    j_patient.push_back(j_patient_temp);
                    i++;
                }
                if (i >0)
                {
                    LOG(INFO) << "病人ID: " << patientID.value() << " 成功查询了数据";
                    j_response["data"] = j_patient;
                    j_response["fail"] = false;
                    j_response["msg"] = "请求成功";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                }
                else
                {
                    j_response["data"] = j_patient;
                    // j_response["code"] = 406;
                    j_response["fail"] = true;
                    j_response["msg"] = "该病人检查信息不存在";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                }
            }
        }
        else{
            j_response["data"] = j_patient;
            // j_response["code"] = 406;
            j_response["fail"] = true;
            j_response["msg"] = "该病人检查信息不存在";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
           // to_json(j_response, responseMsg);
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_patient;
        // j_response["code"] = 500;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        // to_json(j_response, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::patients_checklists_info_delete(const std::optional<int32_t> &patientID, 
    const std::optional<std::vector<int32_t>> &checkID, Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();

        auto checkArray = checkID.value();
        std::string check_array_str = "";

        // 将检查ID转化为字符串
        for(int i = 0; i < checkArray.size(); i ++ )
        {
            if(i+1 == checkArray.size())
            {
                check_array_str.append(std::to_string(checkArray.at(i)));
            }
            else{
                check_array_str.append(std::to_string(checkArray.at(i)) + ",");
            }
        }

        char sql[1024] = { 0 };
        sprintf(sql, "SELECT * FROM T_PATIENT_CHECK WHERE patientID = %d and checkID in (%s)", 
            patientID.value(), check_array_str.data());
        // 查询是否有检测数据
        if (conn_patient->query(sql) & conn_patient->next())
        {
            sprintf(sql, "DELETE  FROM T_PATIENT_CHECK WHERE patientID = %d and checkID in (%s)", 
                patientID.value(), check_array_str.data());
            // 判断是否成功删除数据
            if(conn_patient->update(sql))
            {
                LOG(INFO) << "用户ID: " << patientID.value() << " 检查ID: " << check_array_str<< " 的检查记录已被删除！";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("删除成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
            }
            else{
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                // responseMsg.setCode(500);
                responseMsg.setMsg("删除数据失败");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
            }
        }
        else
        {
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(false);
            responseMsg.setMsg("未找到要删除的数据");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) << e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(false);
        // responseMsg.setCode(500);
        responseMsg.setMsg("服务器错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::patients_checklists_info_post(const PatientChecklistInfoPost &patientChecklistInfoPost, 
Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    // nlohmann::json j_register = patientChecklistInfoPost;
    nlohmann::json j_frequency;
    nlohmann::json j_EnvironmentNoise;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient= pool->getConnection();

        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT * FROM T_PATIENTS WHERE patientID = %d", patientChecklistInfoPost.getPatientID());
        if (conn_patient->query(exist_sql)& conn_patient->next())
        {
            to_json(j_frequency, patientChecklistInfoPost.getFrequency());
            j_EnvironmentNoise["noise"] = patientChecklistInfoPost.getEnvironmentNoise();
            char sql[1024] = { 0 };
            sprintf(sql, "INSERT INTO T_PATIENT_CHECK (patientID, environmentNoise, checkMode, checkResult,\
            checkSuggestion, checkConclusion, checkTime, frequency) VALUES (%d, '%s', '%s', %f, '%s','%s', '%s', '%s')", 
                patientChecklistInfoPost.getPatientID(), j_EnvironmentNoise.dump().data(),
                patientChecklistInfoPost.getCheckMode().data(), patientChecklistInfoPost.getCheckResult(), 
                patientChecklistInfoPost.getCheckSuggestion().data(), patientChecklistInfoPost.getCheckConclusion().data(),
                patientChecklistInfoPost.getCheckTime().data(), j_frequency.dump().data());
            if(conn_patient->update(sql))
            {
                LOG(INFO) << "病人ID: " << patientChecklistInfoPost.getPatientID() << " 新建了检查信息";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("数据插入成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
            }
            else
            {
                LOG(WARNING) << "病人ID: " << patientChecklistInfoPost.getPatientID() << " 插入数据失败";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("数据插入失败");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
            }
        }
        else{
            LOG(WARNING) << "病人ID: " << patientChecklistInfoPost.getPatientID() << " 不存在";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("病人ID不存在");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        LOG(WARNING) <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("系统错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::patients_checklists_info_put(const std::optional<int32_t> &patientID, 
    const std::optional<int32_t> &checkID, const PatientChecklistInfoPut &patientChecklistInfoPut, 
    Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    nlohmann::json j_patientChecklistInfo = patientChecklistInfoPut;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();
        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT * FROM T_PATIENT_CHECK WHERE patientID = %d and checkID = %d", 
            patientID.value(), checkID.value());
        if(!(conn_patient->query(exist_sql) & conn_patient->next()))
        {
            LOG(WARNING) << "病人id 为 " << patientID.value() << " 检查ID为: "<< checkID.value() << " 的检查数据不存在";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("检查数据不存在");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
        std::string sql = UpdateSql::getSqlModify(j_patientChecklistInfo);
        sql = "UPDATE T_PATIENT_CHECK SET " + sql + " WHERE patientID = " + std::to_string(patientID.value()) + 
            " AND checkID = " + std::to_string(checkID.value());
        if (conn_patient->update(sql))
            {
                LOG(INFO) << "病人id 为 " << patientID.value() << " 检查ID为: "<< checkID.value() << " 成功更新了检查数据";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("更新数据成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
            }
            else{
                LOG(WARNING) << "病人id 为 " << patientID.value() << " 检查ID为: "<< checkID.value() << " 更新检查数据失败";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("更新数据失败");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
            }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) << "病人id 为 " << patientID.value() << " 检查ID为: "<< checkID.value() << e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("更新数据失败");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::patients_patients_info_delete(const std::optional<int32_t> &doctorID, 
    const std::optional<std::vector<int32_t>> &patientID, Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();

        auto patientArray = patientID.value();
        std::string patient_array_str = "";

        // 将检查ID转化为字符串
        for(int i = 0; i < patientArray.size(); i ++ )
        {
            if(i+1 == patientArray.size())
            {
                patient_array_str.append(std::to_string(patientArray.at(i)));
            }
            else{
                patient_array_str.append((std::to_string(patientArray.at(i))) + ",");
            }
        }
       
        char sql[1024] = { 0 };
        char checklist_sql[1024] = {0};
        sprintf(sql, "SELECT * FROM T_PATIENTS WHERE doctorID = %d and patientID in (%s)", 
            doctorID.value(), patient_array_str.data());
        // 查询是否有检测数据
        if (conn_patient->query(sql) & conn_patient->next())
        {
            sprintf(sql, "DELETE  FROM T_PATIENTS WHERE doctorID = %d and patientID in (%s)", 
                doctorID.value(), patient_array_str.data());
            sprintf(checklist_sql, "DELETE  FROM T_PATIENT_CHECK WHERE patientID in (%s)", patient_array_str.data());
            // 判断是否成功删除数据
            if(conn_patient->update(sql)& conn_patient->update(checklist_sql))
            {
                LOG(INFO) << "医生用户ID: " << doctorID.value() << " 病人ID: " << patient_array_str<< " 的检查记录已被删除！";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("删除成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
            }
            else{
                LOG(WARNING) << "删除操作执行失败! " << "医生用户ID: " << doctorID.value();
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                // responseMsg.setCode(500);
                responseMsg.setMsg("删除数据失败");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
            }
        }
        else
        {
            LOG(WARNING) << "未找到要删除的数据, doctorID: " << doctorID.value() << " patientID: " << patient_array_str;
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("未找到要删除的数据");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) << e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(false);
        // responseMsg.setCode(500);
        responseMsg.setMsg("服务器错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::patients_patients_info_get(const std::optional<int32_t> &doctorID, 
    const std::optional<int32_t> &amount, Pistache::Http::ResponseWriter &response) 
{
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_patient = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT * FROM T_PATIENTS WHERE doctorID = %d ORDER BY updatedTime DESC LIMIT %d", 
            doctorID.value(), amount.value());
        if (conn_patient->query(sql))
        {
            // conn_patient->next() 每执行一次就依次取一行数据
            int i = 0;
            while (conn_patient->next() & i < amount.value())
            {
                auto j_patient_info = nlohmann::json::parse(conn_patient->value(true));
                j_patient_info.erase("createdTime");
                j_patient.push_back(j_patient_info);
                // j_patient.push_back(nlohmann::json::parse(conn_patient->value(true)));
                i++;
            }
            if(i==0)
            {
                LOG(INFO) << "医生ID: " << doctorID.value() << " 未查询到数据";
                j_response["data"] = j_patient;
                j_response["fail"] = true;
                j_response["msg"] = "未查询到数据";
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
            }
            else{
                LOG(INFO) << "医生ID: " << doctorID.value() << " 成功查询了数据";
                j_response["data"] = j_patient;
                j_response["fail"] = false;
                j_response["msg"] = "请求成功";
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
            }
        }
        else{
            LOG(WARNING) << "医生ID: " << doctorID.value() << " 查询的病人信息不存在";
            j_response["data"] = j_patient;
            j_response["fail"] = true;
            j_response["msg"] = "数据库查询失败";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_patient;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::patients_patients_info_post(
    const PatientInfoPost &patientInfoPost, Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    nlohmann::json j_patientsInfo = patientInfoPost;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();
 
        std::string sql_string = UpdateSql::getSqlInsert(j_patientsInfo);
        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT * FROM T_DOCTORS WHERE doctorID = %d", patientInfoPost.getDoctorID());
        if (conn_patient->query(exist_sql)&conn_patient->next())
        {
            char sql[1024] = { 0 };
            sprintf(sql, "INSERT INTO T_PATIENTS %s", sql_string.data());
            // LOG(INFO) << sql;
            if(conn_patient->update(sql))
            {
                LOG(INFO) << "医生id 为 " << patientInfoPost.getDoctorID() << " 病人电话号码为："<< patientInfoPost.getPhoneNumber()
                << " 的医生用户成功添加了病人信息";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("添加数据成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                return;
            }
            else{
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("数据添加失败");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
                return;
            }
        }
        else{
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("未找到该医生");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
            return;
        }
    }
    catch(const std::exception& e)
    {
        
        LOG(WARNING) <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        // responseMsg.setCode(500);
        responseMsg.setMsg("系统错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
        return;
    }
}

void AudioTesterApiImpl::patients_patients_info_put(const std::optional<int32_t> &doctorID, 
    const std::optional<int32_t> &patientID, const PatientInfoPut &patientInfoPut, 
    Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    nlohmann::json j_patientInfo = patientInfoPut;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();
        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT * FROM T_PATIENTS WHERE doctorID = %d and patientID = %d", 
            doctorID.value(), patientID.value());
        if(!(conn_patient->query(exist_sql) & conn_patient->next()))
        {
            LOG(WARNING) << "医生id 为 " << doctorID.value() << " 检查ID为: "<< patientID.value() << " 的检查数据不存在";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("检查数据不存在");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
        std::string sql = UpdateSql::getSqlModify(j_patientInfo);
        sql = "UPDATE T_PATIENTS SET " + sql + "WHERE doctorID = " + std::to_string(doctorID.value()) + 
            " AND patientID = " + std::to_string(patientID.value());
        if (conn_patient->update(sql))
        {
            LOG(INFO) << "医生id 为 " << doctorID.value() << " 检查ID为: "<< patientID.value() << " 成功更新了病人信息";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(false);
            responseMsg.setMsg("更新数据成功");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
        }
        else{
            LOG(WARNING) << "医生id 为 " << doctorID.value() << " 检查ID为: "<< patientID.value() << " 更新病人信息失败";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("更新数据失败");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) << "医生id 为 " << doctorID.value() << " 检查ID为: "<< patientID.value() << " 更新病人信息失败";
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("更新数据失败");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_checkinfo_get(const std::optional<int32_t> &userID, 
    const std::optional<int32_t> &amount, const std::optional<int32_t> &language, 
     Pistache::Http::ResponseWriter &response) 
{
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_user = nlohmann::json();
    nlohmann::json j_user_temp = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_user = pool->getConnection();
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT * FROM T_USER_CHECK WHERE userID = %d ORDER BY checkTime DESC LIMIT %d", 
            userID.value(), amount.value());
        if (conn_user->query(sql))
        {
            CheckSuggestionTranslate suggestionTranslator;
            // conn_user->next() 每执行一次就依次取一行数据
            if(language.value()==1)
            {
                Translator translator("20240222001970605", "1K5aclpAsqzmVfw_0uky");
                int i = 0;
                // 将取出的每一行数据依次放入 j_user中
                while (conn_user->next() & i < amount.value())
                {
                    j_user_temp = nlohmann::json::parse(conn_user->value(false));
                    j_user_temp["level"] = suggestionTranslator.generateLevel(j_user_temp["checkSuggestion"]);
                    j_user_temp["checkSuggestion"] = suggestionTranslator.generateEnglish(j_user_temp["checkSuggestion"]);
                    j_user_temp["checkConclusion"] = translator.translate(j_user_temp["checkConclusion"], "ch","en");
                    j_user.push_back(j_user_temp);
                    i++;
                }
                if (i>0)
                {
                    LOG(INFO) << "用户ID: " << userID.value() << " 成功查询了个人检查数据";
                    j_response["data"] = j_user;
                    j_response["fail"] = false;
                    j_response["msg"] = "请求成功";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                    return;
                }
                else{
                    LOG(WARNING) << "用户ID: " << userID.value() << " 查询个人检查数据失败";
                    j_response["data"] = j_user;
                    j_response["fail"] = true;
                    j_response["msg"] = "查询的数据不存在";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                    return;
                }
            }else if (language.value()==0)
            {
                int i = 0;
                // 将取出的每一行数据依次放入 j_user中
                while (conn_user->next() & i < amount.value())
                {
                    j_user_temp = nlohmann::json::parse(conn_user->value(false));
                    j_user_temp["level"] = suggestionTranslator.generateLevel(j_user_temp["checkSuggestion"]);
                    j_user.push_back(j_user_temp);
                    i++;
                }
                if (i>0)
                {
                    LOG(INFO) << "用户ID: " << userID.value() << " 成功查询了个人检查数据";
                    j_response["data"] = j_user;
                    j_response["fail"] = false;
                    j_response["msg"] = "请求成功";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                    return;
                }
                else{
                    LOG(WARNING) << "用户ID: " << userID.value() << " 查询个人检查数据失败";
                    j_response["data"] = j_user;
                    j_response["fail"] = true;
                    j_response["msg"] = "查询的数据不存在";
                    auto  time_now = std::chrono::steady_clock::now();
                    j_response["time"] = time_now.time_since_epoch().count();
                    response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                    return;
                }
            } 
        }
        else{
            LOG(WARNING) << "用户ID: " << userID.value() << " 查询的个人检查数据信息失败";
            j_response["data"] = j_user;
            j_response["fail"] = true;
            j_response["msg"] = "数据库查询失败";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
            return;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_user;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_checkinfo_delete(const std::optional<int32_t> &userID, 
    const std::optional<std::vector<int32_t>> &checkID, Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();

        auto checkArray = checkID.value();
        std::string check_array_str = "";

        // 将检查ID转化为字符串
        for(int i = 0; i < checkArray.size(); i ++ )
        {
            if(i+1 == checkArray.size())
            {
                check_array_str.append(std::to_string(checkArray.at(i)));
            }
            else{
                check_array_str.append(std::to_string(checkArray.at(i)) + ",");
            }
        }

        char sql[1024] = { 0 };
        sprintf(sql, "SELECT * FROM T_USER_CHECK WHERE userID = %d and checkID in (%s)", 
            userID.value(), check_array_str.data());
        // 查询是否有检测数据
        if (conn_patient->query(sql) & conn_patient->next())
        {
            sprintf(sql, "DELETE  FROM T_USER_CHECK WHERE userID = %d and checkID in (%s)", 
                userID.value(), check_array_str.data());
            if(conn_patient->update(sql))
            {
                LOG(INFO) << "用户ID: " << userID.value() << " 检查ID: " << check_array_str<< " 的检查记录已被删除！";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("删除成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
            }
            else{
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("请求错误");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
            }
        }
        else
        {
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("未找到要删除的数据");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) << e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("服务器错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_checkinfo_post(const UserCheckinfoPost &userCheckinfoPost, 
    Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    nlohmann::json j_frequency;
    nlohmann::json j_EnvironmentNoise = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_user= pool->getConnection();

        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT * FROM T_USERS WHERE userID = %d", userCheckinfoPost.getUserID());
        // 判断请求的用户ID是否存在
        if (conn_user->query(exist_sql)& conn_user->next())
        {
            to_json(j_frequency, userCheckinfoPost.getFrequency());
            j_EnvironmentNoise["noise"] = userCheckinfoPost.getEnvironmentNoise();

            char sql[1024] = { 0 };
            sprintf(sql, "INSERT INTO T_USER_CHECK (userID, environmentNoise, checkMode, checkResult,\
            checkSuggestion, checkConclusion, checkTime, frequency) VALUES (%d, '%s', '%s', %f, '%s','%s', '%s', '%s')", 
                userCheckinfoPost.getUserID(), j_EnvironmentNoise.dump().data(),
                userCheckinfoPost.getCheckMode().data(), userCheckinfoPost.getCheckResult(), 
                userCheckinfoPost.getCheckSuggestion().data(), userCheckinfoPost.getCheckConclusion().data(),
                userCheckinfoPost.getCheckTime().data(), j_frequency.dump().data());
            // 判断是否成功将数据插入数据库
            if(conn_user->update(sql))
            {
                LOG(INFO) << "普通用户ID: " << userCheckinfoPost.getUserID() << " 新建了检查信息";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("数据插入成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
            }
            else
            {
                LOG(WARNING) << "普通用户ID: " << userCheckinfoPost.getUserID() << " 插入检查数据失败";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("数据插入失败");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
            }
        }
        else{
            LOG(WARNING) << "普通用户ID: " << userCheckinfoPost.getUserID() << " 不存在";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            
            responseMsg.setMsg("未找到该普通用户ID");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("系统错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_logout_post(const std::optional<int32_t> &userID, 
    const std::optional<std::string> &passwd, Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_user = pool->getConnection();
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT password, phoneNumber FROM T_USERS WHERE userID = %d", userID.value());
        // 判断是否有该用户
        if(conn_user->query(sql)&conn_user->next())
        {
            // LOG(INFO) << conn_user->value(true);
            nlohmann::json user_json = nlohmann::json::parse(conn_user->value(true));
            std::string phone = user_json["phoneNumber"];
            // 判断查询到的密码是否和用户请求的你们匹配
            if(strcmp(passwd.value().data(), CryptoppAes::AesDecrypt(user_json["password"]).data())==0)
            {
                sprintf(sql, "DELETE FROM T_USERS WHERE userID = %d", userID.value());
                // 删除用户个人信息
                if (conn_user->update(sql))
                {
                    sprintf(sql, "SELECT checkID FROM T_USER_CHECK WHERE userID = %d", userID.value());
                    if(conn_user->query(sql))
                    {
                        // 删除用户检查信息
                        try
                        {
                            while (conn_user->next())
                            {
                                LOG(INFO) << "查询到该用户检查数据";
                                nlohmann::json j_checkID = nlohmann::json::parse(conn_user->value(true));
                                std::string checkID = j_checkID["checkID"];
                                sprintf(sql, "DELETE FROM T_USER_CHECK WHERE checkID=%d", std::stoi(checkID));
                                if(conn_user->update(sql))
                                {
                                    LOG(INFO) << "检查ID: " << checkID <<" 的检测数据全部删除成功！";
                                }
                                else{
                                    LOG(WARNING) << "检查ID: " << checkID <<" 的检测数据删除失败！";
                                    auto  time_now = std::chrono::steady_clock::now();
                                    responseMsg.setTime(time_now.time_since_epoch().count());
                                    responseMsg.setFail(false);
                                    responseMsg.setMsg("用户检查数据删除失败");
                                    nlohmann::json j;
                                    to_json(j, responseMsg);
                                    response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
                                    return;
                                }
                            }
                        }
                        catch(const std::exception& e)
                        {
                            auto  time_now = std::chrono::steady_clock::now();
                            responseMsg.setTime(time_now.time_since_epoch().count());
                            responseMsg.setFail(true);
                            responseMsg.setMsg(e.what());
                            nlohmann::json j;
                            to_json(j, responseMsg);
                            response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
                            return;
                        }   
                    }
                    LOG(INFO) << "普通用户ID: " << std::to_string(userID.value()) <<", 电话号码:"<< phone << " 注销了账号";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(false);
                    responseMsg.setMsg("注销成功");
                    nlohmann::json j;
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                    return;                                
                }
                else
                {
                    LOG(INFO) << "请求的普通用户ID: " << std::to_string(userID.value()) <<", 电话号码:"
                        << phone << " 注销账号失败";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(true);
                    responseMsg.setMsg("执行失败");
                    nlohmann::json j;
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
                    return;
                }
            }
            else
            {
                LOG(INFO) << "普通用户ID: " <<userID.value() <<", 电话号码:"<< phone << " 密码错误";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("密码错误");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Unauthorized, j.dump(), MIME(Text, Plain));
            }
        }
        else{
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("该用户不存在");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("系统错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_personal_info_get(const std::optional<int32_t> &userID, 
    Pistache::Http::ResponseWriter &response) 
{
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_user = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_user = pool->getConnection();
        
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT name, gender, age, phoneNumber FROM T_USERS WHERE userID = %d", userID.value());
        
        if (conn_user->query(sql) & conn_user->next())
        {
            j_user = nlohmann::json::parse(conn_user->value(true));
            LOG(INFO) << "普通用户id: "<<  userID.value() <<" 电话号码：" << j_user["phoneNumber"] << " 个人信息查找成功";

            j_response["data"] = j_user;
            j_response["fail"] = false;
            j_response["msg"] = "请求成功";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));

        }
        else{
            LOG(INFO) << "普通用户id: "<< userID.value() << " 不存在";
            j_response["data"] = j_user;
            j_response["fail"] = true;
            j_response["msg"] = "该用户数据不存在";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Not_Found, j_response.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_user;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_personal_info_put(const std::optional<int32_t> &userID, 
    const UserPersonalInfoPut &userPersonalInfoPut, Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    nlohmann::json j_userInfo = userPersonalInfoPut;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_user = pool->getConnection();
        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT * FROM T_USERS WHERE userID = %d ", userID.value());
        if(!(conn_user->query(exist_sql) & conn_user->next()))
        {
            LOG(INFO) << "普通用户id 为 " << userID.value() << " 的个人数据不存在";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("用户不存在");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
        }
        std::string sql = UpdateSql::getSqlModify(j_userInfo);
        sql = "UPDATE T_USERS SET " + sql + " WHERE userID = " + std::to_string(userID.value()) ;
       
        if (conn_user->update(sql))
        {
            LOG(INFO) << "普通用户id 为 " << userID.value() << " 成功更新了个人数据";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(false);
            responseMsg.setMsg("更新数据成功");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
        }
        else{
            LOG(WARNING) << "普通用户id 为 " << userID.value() << " 更新个人数据失败";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("更新数据失败");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
        }

    }
    catch(const std::exception& e)
    {
        LOG(WARNING) << "普通用户id 为 " << userID.value() << " 更新个人数据失败";
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("更新数据失败");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_register_post(const UserRegisterPost &userRegisterPost, 
    Pistache::Http::ResponseWriter &response) 
{
    ResponseMsg responseMsg;
    nlohmann::json j_register = userRegisterPost;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_doctor = pool->getConnection();

        VerificationCodeManager manager("localhost", 6379, "earchon123");
        bool isCorrect = manager.verifyCode(userRegisterPost.getPhoneNumber(), userRegisterPost.getVerificationCode());
        if (!isCorrect)
        {
            LOG(INFO) << "普通用户手机号码："<< userRegisterPost.getPhoneNumber() << " 验证码错误";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("验证码错误");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
            return;
        }

        // 检查电话号码是否已被注册
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT * FROM T_USERS WHERE phoneNumber = '%s'", userRegisterPost.getPhoneNumber().data());
        
        if (conn_doctor->query(sql) & conn_doctor->next())
        {
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("该号码已被注册");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
        }
        else
        {
            // 加密后替换成加密后的密码
            std::string encode_passwd = CryptoppAes::AesEncrypt(userRegisterPost.getPassword());
            j_register["password"] = encode_passwd;
            std::string sql_value = UpdateSql::getSqlInsert(j_register);
            LOG(INFO) << "SQL语句: " << sql_value;
            // 生成数据库执行语句
            char update_sql[1024] = { 0 };
            sprintf(update_sql, "INSERT INTO T_USERS %s", sql_value.data());
            if (conn_doctor->update(update_sql))
            {
                LOG(INFO) << "普通用户电话号码：" << userRegisterPost.getPhoneNumber() << " 注册成功";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(false);
                responseMsg.setMsg("注册成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
            }
            else{
                LOG(INFO) << "普通用户电话号码：" << userRegisterPost.getPhoneNumber() << " 注册时发生了服务器错误";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("未成功更新数据库");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
            }
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        // responseMsg.setCode(500);
        responseMsg.setMsg("系统错误");
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_retrieve_passwd_post(const std::optional<std::string> &phoneNumber, 
    const std::optional<std::string> &verificationCode, const std::optional<std::string> &password, 
    Pistache::Http::ResponseWriter &response) {
    ResponseMsg responseMsg;
    nlohmann::json j_user = nlohmann::json();
    nlohmann::json j_response;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_user = pool->getConnection();
        VerificationCodeManager manager("localhost", 6379, "earchon123");
        bool isCorrect = manager.verifyCode(phoneNumber.value(), verificationCode.value());
        if (!isCorrect)
        {
            LOG(WARNING) << "普通用户号码为：" << phoneNumber.value() << " 的验证码错误";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("手机验证码错误");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Unauthorized, j.dump(), MIME(Text, Plain));
            return ;
        }
        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT * FROM T_USERS WHERE phoneNumber = %s", phoneNumber.value().data());
        // 查询是否有该电话号码
        if (conn_user->query(exist_sql) & conn_user->next())
        {
            std::string encode_passwd = CryptoppAes::AesEncrypt(password.value());
            char sql[1024] = { 0 };
            sprintf(sql, "UPDATE T_USERS SET password = '%s' WHERE phoneNumber = '%s'", 
                encode_passwd.data(), phoneNumber.value().data());
            // 更新数据库数据
            if(conn_user->update(sql))
            {
                LOG(INFO) << "普通用户号码为：" << phoneNumber.value() << " 重置密码成功";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("重置密码成功");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                return ;
            }
            else{
                LOG(WARNING) << "普通用户电话号码为：" << phoneNumber.value() << " 重置密码失败 ";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("数据更新失败");
                nlohmann::json j;
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
                return;
                }
        }
        else{
            LOG(WARNING) << "普通用户电话号码为：" << phoneNumber.value() << " 重置密码失败 ";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("未查询到该用户");
            nlohmann::json j;
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
            return;
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) << "普通用户电话号码为：" << phoneNumber.value() << " 找回密码失败 " <<  e.what();
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg(e.what());
        nlohmann::json j;
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::user_passwd_change_put(const std::optional<int32_t> &userID,
    const std::optional<std::string> &passwd, 
    const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response) {
    ResponseMsg responseMsg;
    nlohmann::json j_user = nlohmann::json();
    nlohmann::json j;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_user = pool->getConnection();
        char exist_sql[1024] = { 0 };
        sprintf(exist_sql, "SELECT password FROM T_USERS WHERE userID = %d", userID.value());
        if (conn_user->query(exist_sql) & conn_user->next())
        {
            j_user = nlohmann::json::parse(conn_user->value(true));
            // 判断查询到的密码是否和用户请求的密码匹配
            if(strcmp(passwd.value().data(), CryptoppAes::AesDecrypt(j_user["password"]).data())==0)
            {
                char sql[1024] = { 0 };
                sprintf(sql, "UPDATE T_USERS SET password='%s' WHERE userID = %d", 
                    CryptoppAes::AesEncrypt(password.value()).data(), userID.value());
                if(conn_user->update(sql))
                {
                    LOG(INFO) << "普通用户ID: " << userID.value() << " 修改了密码";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(false);
                    responseMsg.setMsg("修改成功");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                }
                else{
                    LOG(WARNING) << "普通用户ID: " << userID.value() << " 修改密码失败";
                    auto time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(true);
                    responseMsg.setMsg("数据库数据修改失败");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
                }
            }
            else{
                LOG(WARNING) << "普通用户ID: " << userID.value() << " 旧密码错误";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("密码错误");
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Unauthorized, j.dump(), MIME(Text, Plain));
            }
        }
        else
        {
            LOG(WARNING) << "普通用户ID: " << userID.value() << " 未找到";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("未找到此普通用户");
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
        }  
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        LOG(WARNING) << "普通用户ID: " << userID.value() << " 修改密码错误，系统出错";
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("系统错误");
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::patients_patients_info_name_get(const std::optional<int32_t> &doctorID, 
    const std::optional<std::string> &name, 
        Pistache::Http::ResponseWriter &response)
{
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_patient = nlohmann::json();

    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();
        std::string vague_name = "%" + name.value() + "%";
        // LOG(INFO) << name.value();
        // char sql[1024] = { 0 };
        // sprintf(sql, "SELECT * FROM T_PATIENTS WHERE doctorID = %d and name like %'%s'%", 
        //     doctorID.value(), name.value().data());
        std::string sql = "SELECT * FROM T_PATIENTS WHERE doctorID =" + 
            std::to_string(doctorID.value()) + " and name like '" + vague_name + "'";
        LOG(INFO) << sql;
        // 查询符合条件的数据
        if (conn_patient->query(sql) & conn_patient->next())
        {
            // conn_patient->next() 每执行一次就依次取一行数据
            j_patient.push_back(nlohmann::json::parse(conn_patient->value(false)));
            while (conn_patient->next())
            {
                j_patient.push_back(nlohmann::json::parse(conn_patient->value(false)));
            }
            
            LOG(INFO) << "医生ID: " << doctorID.value() << " 成功查询了数据";
            j_response["data"] = j_patient;
            j_response["fail"] = false;
            j_response["msg"] = "请求成功";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));

        }
        else{
            LOG(WARNING) << "医生ID: " << doctorID.value() << "查询的病人信息不存在";
            j_response["data"] = j_patient;
            j_response["fail"] = true;
            j_response["msg"] = "没有符合该条件的病人";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_patient;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}
    
void AudioTesterApiImpl::patients_patients_info_time_get(const std::optional<int32_t> &doctorID, 
    const std::optional<std::string> &startTime, 
    const std::optional<std::string> &endTime, Pistache::Http::ResponseWriter &response)
{
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_patient = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();
        
        char sql[1024] = { 0 };
        sprintf(sql, "SELECT * FROM T_PATIENTS WHERE doctorID = %d and createdTime BETWEEN '%s' AND '%s'", 
            doctorID.value(), startTime.value().data(), endTime.value().data());
        
        // 查询符合条件的数据
        if (conn_patient->query(sql) & conn_patient->next())
        {
            // conn_patient->next() 每执行一次就依次取一行数据
            j_patient.push_back(nlohmann::json::parse(conn_patient->value(false)));
            while (conn_patient->next())
            {
                j_patient.push_back(nlohmann::json::parse(conn_patient->value(false)));
            }
            
            LOG(INFO) << "医生ID: " << doctorID.value() << " 成功查询了数据";
            j_response["data"] = j_patient;
            j_response["fail"] = false;
            j_response["msg"] = "请求成功";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
        }
        else{
            LOG(WARNING) << "医生ID: " << doctorID.value() << "查询的病人信息不存在";
            j_response["data"] = j_patient;
            j_response["fail"] = true;
            j_response["msg"] = "没有符合该条件的病人";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
        }
    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_patient;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}


void AudioTesterApiImpl::common_push_info_get(const std::optional<int32_t> &category, 
    const std::optional<int32_t> &language, Pistache::Http::ResponseWriter &response)
{
    nlohmann::json j_response = nlohmann::json();
    nlohmann::json j_common = nlohmann::json();
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_common = pool->getConnection();
        
        char sql[1024] = { 0 };
        if(category.value() == 0)
        {
            if (language.value() == 0)
            {
                sprintf(sql, "SELECT chineseInfo FROM T_PUSHINFO WHERE userCategory = 'user'");
            }
            else if (language.value() == 1)
            {
                sprintf(sql, "SELECT englishInfo FROM T_PUSHINFO WHERE userCategory = 'user'");
            }
            else{
                LOG(WARNING) << "语言参数错误";
            }
        }
        else if(category.value() == 1)
        {
            if (language.value() == 0)
            {
                sprintf(sql, "SELECT chineseInfo FROM T_PUSHINFO WHERE userCategory = 'doctor'");
            }
            else if (language.value() == 1)
            {
                sprintf(sql, "SELECT englishInfo FROM T_PUSHINFO WHERE userCategory = 'doctor'");
            }
            else{
                LOG(WARNING) << "语言参数错误";
            }
        }
        else{
            LOG(WARNING) << "获取推送信息失败";
            j_response["data"] = j_common;
            j_response["fail"] = true;
            j_response["msg"] = "category 参数请求数据不符合要求";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Bad_Request, j_response.dump(), MIME(Text, Plain));
            return;
        }
        // 查询符合条件的数据
        if (conn_common->query(sql) & conn_common->next())
        {
            j_common = nlohmann::json::parse(conn_common->value(true));
            
            LOG(INFO) << "推送信息获取成功！";
            j_response["data"] = j_common;
            j_response["fail"] = false;
            j_response["msg"] = "请求成功";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
        }
        else{
            LOG(WARNING) << "获取推送信息失败，未查询到相关数据";
            j_response["data"] = j_common;
            j_response["fail"] = true;
            j_response["msg"] = "请求数据不存在";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Not_Found, j_response.dump(), MIME(Text, Plain));
        }

    }
    catch(const std::exception& e)
    {
        LOG(WARNING) <<  e.what();
        j_response["data"] = j_common;
        j_response["fail"] = true;
        j_response["msg"] = "系统错误";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::common_sms_verification_get( std::optional<std::string> &phoneNumber, 
    const std::optional<int32_t> &function, Pistache::Http::ResponseWriter &response)
{
    nlohmann::json j_response = nlohmann::json();
    std::string VerificationCode;
    try
    {
        // 获取线程池连接
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_patient = pool->getConnection();
        // 获取六位数验证码和短信发送的初始化
        // VerificationCodeGenerator generator;  
        VerificationCodeManager codeManager("localhost", 6379, "earchon123");
        SmsVerification sms;
        VerificationCode = codeManager.generateAndSaveCode(phoneNumber.value());
        if (VerificationCode == "Daily limit reached") {
            LOG(WARNING) << "验证码发送失败，当日发送次数已达上限";
            j_response["fail"] = true;
            j_response["msg"] = "验证码发送失败，当日发送次数已达上限";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));      
            return;   
        }
        char message[1024] = { 0 };
        switch (function.value())
        {
        case 1:
            sprintf(message, "尊敬的客户, 您正在进行医听的注册，本次验证码：%s, 切勿将验证码泄露给他人, 本条验证码有效期5分钟。",
             VerificationCode.data());
            break;
        case 2:
            sprintf(message, "尊敬的客户, 您正在进行医听的更换手机号码的操作，本次验证码：%s, 切勿将验证码泄露给他人, 本条验证码有效期5分钟。",
             VerificationCode.data());
            break;
        default:
            sprintf(message, "您的验证码是：%s。请不要把验证码泄露给其他人。", VerificationCode.data());
            break;
        }

    
        try
        {
            // 发送短信
            // LOG(INFO) << message;
            sms.send_sms(phoneNumber.value().data(), message);
        }
        catch(const std::exception& e)
        {
            LOG(WARNING) << "验证码发送失败";
            j_response["fail"] = true;
            j_response["msg"] = "验证码发送失败";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
        }
        
        LOG(INFO) << "验证码获取并发送成功";
        j_response["fail"] = false;
        j_response["msg"] = "验证码获取并发送成功";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        LOG(WARNING) << "验证码发送失败";
        j_response["fail"] = true;
        j_response["msg"] = "验证码发送失败";
        auto  time_now = std::chrono::steady_clock::now();
        j_response["time"] = time_now.time_since_epoch().count();
        response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::common_update_phone_number_put(const std::optional<int32_t> &category, 
    const std::optional<int32_t> &id, const std::optional<std::string> &phoneNumber, 
    Pistache::Http::ResponseWriter &response)
{
    ResponseMsg responseMsg;
    nlohmann::json j_common = nlohmann::json();
    nlohmann::json j;
    try
    {
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
        std::shared_ptr<MysqlConn> conn_common = pool->getConnection();
        char exist_sql[1024] = { 0 };
        char sql[1024] = { 0 };
        if (category==0)
        {
            sprintf(exist_sql, "SELECT phoneNumber FROM T_USERS WHERE userID = %d", id.value());
            if (conn_common->query(exist_sql) & conn_common->next())
            {
                j_common = nlohmann::json::parse(conn_common->value(true));
                std::string phone = j_common["phoneNumber"];
                if (strcmp(phoneNumber.value().data(), phone.data())==0)
                {
                    LOG(WARNING) << "普通用户ID: " << id.value() << " 新电话号码与原电话号码相同";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(true);
                    responseMsg.setMsg("号码重复");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
                    return;
                }
                sprintf(sql, "UPDATE T_USERS SET phoneNumber='%s' WHERE userID = %d", phoneNumber.value().data(), id.value());
                if(conn_common->update(sql))
                {
                    LOG(INFO) << "普通用户ID: " << id.value() << " 修改了电话号码";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(false);
                    responseMsg.setMsg("修改成功");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                    return;
                }
                else
                {
                    LOG(WARNING) << "普通用户ID: " << id.value() << " 修改电话号码时服务器出错";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(true);
                    responseMsg.setMsg("服务器数据未成功更新");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
                }
            }
            else{
                LOG(WARNING) << "普通用户ID: " << id.value() << " 未到该用户数据";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("未找到该数据");
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
            }
        }
        else if (category ==1)
        {
            sprintf(exist_sql, "SELECT phoneNumber FROM T_DOCTORS WHERE doctorID = %d", id.value());
            if (conn_common->query(exist_sql) & conn_common->next())
            {
                j_common = nlohmann::json::parse(conn_common->value(true));
                std::string phone = j_common["phoneNumber"];
                if (strcmp(phoneNumber.value().data(), phone.data())==0)
                {
                    LOG(WARNING) << "医生用户ID: " << id.value() << " 新电话号码与原电话号码相同";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(true);
                    responseMsg.setMsg("号码重复");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
                    return;
                }
                sprintf(sql, "UPDATE T_DOCTORS SET phoneNumber='%s' WHERE doctorID = %d", phoneNumber.value().data(), id.value());
                if(conn_common->update(sql))
                {
                    LOG(INFO) << "医生用户ID: " << id.value() << " 修改了电话号码";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(false);
                    responseMsg.setMsg("修改成功");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Ok, j.dump(), MIME(Text, Plain));
                    return;
                }
                else
                {
                    LOG(WARNING) << "医生用户ID: " << id.value() << " 修改电话号码时服务器出错";
                    auto  time_now = std::chrono::steady_clock::now();
                    responseMsg.setTime(time_now.time_since_epoch().count());
                    responseMsg.setFail(true);
                    responseMsg.setMsg("服务器数据未成功更新");
                    to_json(j, responseMsg);
                    response.send(Pistache::Http::Code::Insufficient_Storage, j.dump(), MIME(Text, Plain));
                    return;
                }
            }
            else
            {
                LOG(WARNING) << "医生用户ID: " << id.value() << " 未到该用户数据";
                auto  time_now = std::chrono::steady_clock::now();
                responseMsg.setTime(time_now.time_since_epoch().count());
                responseMsg.setFail(true);
                responseMsg.setMsg("未找到该数据");
                to_json(j, responseMsg);
                response.send(Pistache::Http::Code::Not_Found, j.dump(), MIME(Text, Plain));
                return;
            }   
        }
        else{
            LOG(WARNING) << "用户ID: " << id.value() << " 修改手机号出错";
            auto  time_now = std::chrono::steady_clock::now();
            responseMsg.setTime(time_now.time_since_epoch().count());
            responseMsg.setFail(true);
            responseMsg.setMsg("category 字段超出范围");
            to_json(j, responseMsg);
            response.send(Pistache::Http::Code::Bad_Request, j.dump(), MIME(Text, Plain));
            return;
        }
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        LOG(WARNING) << "用户ID: " << id.value() << " 修改手机号出错";
        auto  time_now = std::chrono::steady_clock::now();
        responseMsg.setTime(time_now.time_since_epoch().count());
        responseMsg.setFail(true);
        responseMsg.setMsg("服务器错误");
        to_json(j, responseMsg);
        response.send(Pistache::Http::Code::Internal_Server_Error, j.dump(), MIME(Text, Plain));
    }
}

void AudioTesterApiImpl::common_hearing_trends_get(const std::optional<int32_t>& category,
    const std::optional<int32_t> &language, const std::optional<std::vector<int32_t>> &checkID, 
    Pistache::Http::ResponseWriter &response)
    {
        nlohmann::json j_response = nlohmann::json();
        nlohmann::json j_common = nlohmann::json();
        nlohmann::json j_conclusion = nlohmann::json();
        try
        {
            ConnectionPool* pool = ConnectionPool::getConnectionPool();
            std::shared_ptr<MysqlConn> conn_common = pool->getConnection();
            auto checkArray = checkID.value();
            std::string check_array_str = "";

            // 将检查ID转化为字符串
            for(int i = 0; i < checkArray.size(); i ++ )
            {
                if(i+1 == checkArray.size())
                {
                    check_array_str.append(std::to_string(checkArray.at(i)));
                }
                else{
                    check_array_str.append((std::to_string(checkArray.at(i))) + ",");
                }
            }
        
            char sql[1024] = { 0 };
            
            if(category.value() == 1)
            {
                sprintf(sql, "SELECT * FROM T_PATIENT_CHECK WHERE checkID in (%s)",  check_array_str.data());
            }
            else if(category.value() == 0)
            {
                sprintf(sql, "SELECT * FROM T_USER_CHECK WHERE checkID in (%s)",  check_array_str.data());
            }
            if(conn_common->query(sql))
            {
                std::vector<float> resultArray;
                while(conn_common->next())
                {
                    j_common = nlohmann::json::parse(conn_common->value(false));
                    auto checkResult = j_common["checkResult"];
                    resultArray.push_back(std::stof(checkResult.get<std::string>()));
                }
                HearingHealthAnalyzer hearingTrends;
                hearingTrends.addTestData(resultArray);
                std::string trend_str = hearingTrends.analyzeTrend();
                // 去掉空格
                trend_str.erase(std::remove(trend_str.begin(), trend_str.end(), ' '), trend_str.end());
                if(trend_str.length() > 0 && language.value() == 1)
                {
                    Translator translator("20240222001970605", "1K5aclpAsqzmVfw_0uky");
                    trend_str = translator.translate(trend_str, "ch", "en");
                    j_conclusion["checkConclusion"] = trend_str;
                }
                else
                {
                    j_conclusion["checkConclusion"] = trend_str;
                }
                LOG(INFO) << "听力测试趋势分析结论获取成功";
                j_response["data"] = j_conclusion;
                j_response["fail"] = false;
                j_response["msg"] = "听力测试趋势分析结论获取成功";
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Ok, j_response.dump(), MIME(Text, Plain));
                return;
            }
            else
            {
                LOG(WARNING) << "查询失败";
                j_response["data"] = j_conclusion;
                j_response["fail"] = true;
                j_response["msg"] = "查询失败";
                auto  time_now = std::chrono::steady_clock::now();
                j_response["time"] = time_now.time_since_epoch().count();
                response.send(Pistache::Http::Code::Not_Found, j_response.dump(), MIME(Text, Plain));
                return;
            }
        }
        catch(const std::exception& e)
        {
            LOG(WARNING) << e.what() << " 听力测试趋势分析结论获取出错";
            j_response["data"] = j_conclusion;
            j_response["fail"] = true;
            j_response["msg"] = "查询失败";
            auto  time_now = std::chrono::steady_clock::now();
            j_response["time"] = time_now.time_since_epoch().count();
            response.send(Pistache::Http::Code::Internal_Server_Error, j_response.dump(), MIME(Text, Plain));
            return;
        }
        
    }

}