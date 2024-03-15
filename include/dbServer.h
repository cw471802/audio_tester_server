/*** 
 * @Author: chen wei
 * @Date: 2023-11-02 17:24:32
 * @LastEditTime: 2023-11-03 09:32:28
 * @FilePath: /audio_tester_server/include/dbServer.h
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */



#include <iostream>
#include <memory>

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/mime.h>
#include <pistache/net.h>
#include <pistache/router.h>

#include <glog/logging.h>
#include "mysql_conn.h"
#include "connection_pool.h"
#include <jsoncpp/json/json.h>

class DBServer
{
private:
    /*** 
     * @brief 配置服务器路由
     * @return {*}
     */    
    void configureRoutes();

    using Request = Pistache::Rest::Request;
    using Response = Pistache::Http::ResponseWriter;
    void getData(const Request &request, Response response);
    void deleteData(const Request &request, Response response);
    void updateData(const Request &request, Response response);
    void createData(const Request &request, Response response);

    uint16_t m_portNum;
    unsigned int m_numThreads;
    Pistache::Address m_address;
    std::shared_ptr<Pistache::Http::Endpoint> m_endPoint;
    Pistache::Rest::Router m_router;

    
public:
    DBServer(uint16_t portNum = 8000, unsigned int numThreads = std::thread::hardware_concurrency());
    ~DBServer();
};


DBServer::~DBServer()
{
}
