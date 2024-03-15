/*** 
 * @Author: chen wei
 * @Date: 2024-01-22 09:03:46
 * @LastEditTime: 2024-01-30 09:18:17
 * @FilePath: /audio_tester_server/utils/SmsVerification.cpp
 * @Description: 
 * @Copyright (c) 2024 by ${Author}, All Rights Reserved. 
 */
#include "SmsVerification.h"

#define SA struct sockaddr
#define MAXLINE 4096
#define MAXSUB  2000
#define MAXPARAM 2048
#define LISTENQ 1024

int basefd;
char *hostname = "106.ihuyi.cn";
char *send_sms_uri = "/webservice/sms.php?method=Submit";

SmsVerification::~SmsVerification()
{
    
}

ssize_t SmsVerification::http_post(char *page, char *poststr)
{
    char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
    ssize_t n;
    snprintf(sendline, MAXSUB,
        "POST %s HTTP/1.0\r\n"
        "Host: %s\r\n"
        "Content-type: application/x-www-form-urlencoded\r\n"
        "Content-length: %zu\r\n\r\n"
        "%s", page, hostname, strlen(poststr), poststr);

    write(basefd, sendline, strlen(sendline));
    while ((n = read(basefd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        // printf("%s", recvline);
    }
    return n;
}

ssize_t SmsVerification::send_sms(char *mobile, char *content)
{
    struct sockaddr_in servaddr;
    char str[50];
    
    #if 0
    //建立socket连接
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr =*(hostname);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    inet_pton(AF_INET, str, &servaddr.sin_addr);
    connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
    #endif
    
    if((basefd= socked_connect(hostname))==-1)
    {
        LOG(ERROR) << ("connect is failed\n");
        return -1;
    }
    // LOG(INFO) << "basefd is = " << basefd;
    char *account;
    account = "C32102492";
    char *password;
    password = "c7f0d12734ab135c1695e6facdf9e703";
    char params[MAXPARAM + 1];
    char *cp = params;
    sprintf(cp,"account=%s&password=%s&mobile=%s&content=%s", account, password, mobile, content);
    return http_post(send_sms_uri, cp);
}

int SmsVerification::socked_connect(char *arg)
{
    struct sockaddr_in their_addr = {0};  
    char buf[1024] = {0};  
    char rbuf[1024] = {0};  
    char pass[128] = {0};  
    struct hostent *host = NULL;   
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        LOG(ERROR) << ("create the sockfd is failed\n");
        return -1;
    }
    
    if((host = gethostbyname(arg))==NULL)  
    {  
        LOG(ERROR) << ("Gethostname error, %s\n");  
        return -1; 
    }  
 
    memset(&their_addr, 0, sizeof(their_addr));  
    their_addr.sin_family = AF_INET;  
    their_addr.sin_port = htons(80);  
    their_addr.sin_addr = *((struct in_addr *)host->h_addr);
    if(connect(sockfd,(struct sockaddr *)&their_addr, sizeof(struct sockaddr)) < 0)  
    {  
        close(sockfd);
        return  -1;
    }  
    // printf ("connect is success\n");
    return sockfd;
}