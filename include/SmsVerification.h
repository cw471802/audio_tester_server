/*** 
 * @Author: chen wei
 * @Date: 2024-01-19 15:57:44
 * @LastEditTime: 2024-01-22 16:22:56
 * @FilePath: /audio_tester_server/include/SmsVerification.h
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */

#include <string>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#include <glog/logging.h>

#ifndef INCLUDE_SMS_VERIFICATION_H
#define INCLUDE_SMS_VERIFICATION_H
// extern int h_errno;


class SmsVerification
{
public:
    
    virtual ~SmsVerification();
    /*** 
     * @brief 发送 http 请求
     * @param {char} *page 
     * @param {char} *poststr
     * @return {*}
     */    
    ssize_t http_post(char *page, char *poststr);
    /*** 
     * @brief 发送短信
     * @param {char} *account APIID
     * @param {char} *password APIKEY
     * @param {char} *mobile 电话号码
     * @param {char} *content 要发送的短信内容
     * @return {*}
     */    
    ssize_t send_sms(char *mobile, char *content);

    int socked_connect(char *arg);
    
};

#endif // INCLUDE_SMS_VERIFICATION_H