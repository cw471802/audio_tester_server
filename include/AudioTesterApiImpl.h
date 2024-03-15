/*** 
 * @Author: chen wei
 * @Date: 2023-11-14 18:34:10
 * @LastEditTime: 2024-03-01 14:26:12
 * @FilePath: /audio_tester/include/AudioTesterApiImpl.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#ifndef INCLUDE_AUDIO_TESTER_API_IMPL_H
#define INCLUDE_AUDIO_TESTER_API_IMPL_H

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <memory>
#include <optional>
#include <glog/logging.h>


#include "mysql_conn.h"
#include "AudioTesterApi.h"
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
#include "ResponseMsg.h"
#include "UpdateSql.h"
#include "CryptoppAes.h"
#include "CheckSuggestionTranslate.h"

#include <utility>
#include <string>
#include <array>
namespace api
{

using namespace model;

class  AudioTesterApiImpl : public api::AudioTesterApi {
public:
    explicit AudioTesterApiImpl(const std::shared_ptr<Pistache::Rest::Router>);
    ~AudioTesterApiImpl() {};
    // bool mysql_conn();

    void user_login_get(const std::optional<std::string> &phoneNumber, const std::optional<std::string> &passwd, 
        Pistache::Http::ResponseWriter &response);
    void doctor_login_get(const std::optional<std::string> &phoneNumber, const std::optional<std::string> &passwd, 
        Pistache::Http::ResponseWriter &response);
    void doctor_doctor_info_put(const std::optional<int32_t> &doctorID, const DoctorInfoPut &doctorInfoPut, 
        Pistache::Http::ResponseWriter &response);
    void doctor_logout_post(const std::optional<int32_t> &doctorID, const std::optional<std::string> &passwd, 
        Pistache::Http::ResponseWriter &response);
    void doctor_personal_info_get(const std::optional<int32_t> &doctorID, Pistache::Http::ResponseWriter &response);
    void doctor_register_post(const DocterRegisterPost &docterRegisterPost, Pistache::Http::ResponseWriter &response);
    void doctor_retrive_passwd_post(const std::optional<std::string> &phoneNumber, const std::optional<std::string> &verificationCode,
        const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response);
    void doctor_passwd_change_put(const std::optional<int32_t> &doctorID, const std::optional<std::string> &passwd, 
        const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response);
    void patients_checklists_info_get(const std::optional<int32_t> &patientID, 
        const std::optional<int32_t> &amount, const std::optional<int32_t> &language, Pistache::Http::ResponseWriter &response);
    void patients_checklists_info_delete(const std::optional<int32_t> &patientID, 
        const std::optional<std::vector<int32_t>> &checkID, Pistache::Http::ResponseWriter &response);
    void patients_checklists_info_post(const PatientChecklistInfoPost &patientChecklistInfoPost, 
        Pistache::Http::ResponseWriter &response);
    void patients_checklists_info_put(const std::optional<int32_t> &patientID, 
        const std::optional<int32_t> &checkID, const PatientChecklistInfoPut &patientChecklistInfoPut, 
        Pistache::Http::ResponseWriter &response);
    void patients_patients_info_delete(const std::optional<int32_t> &doctorID, 
        const std::optional<std::vector<int32_t>> &patientID, Pistache::Http::ResponseWriter &response);
    void patients_patients_info_get(const std::optional<int32_t> &doctorID, const std::optional<int32_t> &amount, 
        Pistache::Http::ResponseWriter &response);
    void patients_patients_info_post(const PatientInfoPost &patientInfoPost, 
        Pistache::Http::ResponseWriter &response);
    void patients_patients_info_put(const std::optional<int32_t> &doctorID, 
        const std::optional<int32_t> &patientID, const PatientInfoPut &patientInfoPut, 
        Pistache::Http::ResponseWriter &response);
    void user_checkinfo_get(const std::optional<int32_t> &userID, const std::optional<int32_t> &amount, 
        const std::optional<int32_t> &language, Pistache::Http::ResponseWriter &response);
    void user_checkinfo_delete(const std::optional<int32_t> &userID, const std::optional<std::vector<int32_t>> &checkID, 
        Pistache::Http::ResponseWriter &response);
    void user_checkinfo_post(const UserCheckinfoPost &userCheckinfoPost, Pistache::Http::ResponseWriter &response);
    void user_logout_post(const std::optional<int32_t> &userID, 
        const std::optional<std::string> &passwd, 
        Pistache::Http::ResponseWriter &response);
    void user_personal_info_get(const std::optional<int32_t> &userID, Pistache::Http::ResponseWriter &response);
    void user_personal_info_put(const std::optional<int32_t> &userID, 
        const UserPersonalInfoPut &userPersonalInfoPut, Pistache::Http::ResponseWriter &response);
    void user_register_post(const UserRegisterPost &userRegisterPost, Pistache::Http::ResponseWriter &response);

    void user_retrieve_passwd_post(const std::optional<std::string> &phoneNumber, const std::optional<std::string> &verificationCode,
        const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response);
    void user_passwd_change_put(const std::optional<int32_t> &userID, const std::optional<std::string> &passwd, 
        const std::optional<std::string> &password, Pistache::Http::ResponseWriter &response);
    void patients_patients_info_name_get(const std::optional<int32_t> &doctorID, const std::optional<std::string> &name, 
        Pistache::Http::ResponseWriter &response);
    
    void patients_patients_info_time_get(const std::optional<int32_t> &doctorID, const std::optional<std::string> &startTime, 
        const std::optional<std::string> &endTime, Pistache::Http::ResponseWriter &response);
    void common_push_info_get(const std::optional<int32_t> &category, 
        const std::optional<int32_t> &language, Pistache::Http::ResponseWriter &response);

    void common_sms_verification_get(std::optional<std::string> &phoneNumber, 
        const std::optional<int32_t> &function, Pistache::Http::ResponseWriter &response);

    void common_update_phone_number_put(const std::optional<int32_t> &category, 
        const std::optional<int32_t>&id, const std::optional<std::string> &phoneNumber,
        Pistache::Http::ResponseWriter &response);
    void common_hearing_trends_get(const std::optional<int32_t> &category, 
        const std::optional<int32_t> &language, const std::optional<std::vector<int32_t>> &checkID,
        Pistache::Http::ResponseWriter &response);
    
};

} // namespace api



#endif // INCLUDE_AUDIO_TESTER_API_IMPL_H