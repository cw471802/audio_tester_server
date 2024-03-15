/*** 
 * @Author: chen wei
 * @Date: 2023-10-25 11:09:19
 * @LastEditTime: 2024-02-18 16:05:38
 * @FilePath: /audio_tester_server/main.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include <iostream>
#include <memory>
#include <glog/logging.h>

#include "pistache/endpoint.h"
#include "pistache/http.h"
#include "pistache/router.h"
#include "mysql_conn.h"
#include "connection_pool.h"
#include <jsoncpp/json/json.h>
#include "AudioTesterApiImpl.h"

#ifdef __linux__
#include <vector>
#include <signal.h>
#include <unistd.h>
#endif
#define PISTACHE_SERVER_THREADS     2
#define PISTACHE_SERVER_MAX_REQUEST_SIZE 16384
#define PISTACHE_SERVER_MAX_RESPONSE_SIZE 16384

static Pistache::Http::Endpoint *httpEndpoint;
#ifdef __linux__
static void sigHandler [[noreturn]] (int sig){
    switch(sig){
        case SIGINT:
        case SIGQUIT:
        case SIGTERM:
        case SIGHUP:
        default:
            httpEndpoint->shutdown();
            break;
    }
    exit(0);
}

static void setUpUnixSignals(std::vector<int> quitSignals) {
    sigset_t blocking_mask;
    sigemptyset(&blocking_mask);
    for (auto sig : quitSignals)
        sigaddset(&blocking_mask, sig);

    struct sigaction sa;
    sa.sa_handler = sigHandler;
    sa.sa_mask    = blocking_mask;
    sa.sa_flags   = 0;

    for (auto sig : quitSignals)
        sigaction(sig, &sa, nullptr);
}
#endif

using namespace api;

int main(int argc,char* argv[]){
    google::InitGoogleLogging("audio_tester");
    google::SetLogDestination(google::GLOG_INFO, "../log");
    FLAGS_colorlogtostderr = true; 
    FLAGS_alsologtostderr = true;
    LOG(INFO) << "Hello,GLOG!";
    // query();
    #ifdef __linux__
    std::vector<int> sigs{SIGQUIT, SIGINT, SIGTERM, SIGHUP};
    setUpUnixSignals(sigs);
    #endif
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9090));

    httpEndpoint = new Pistache::Http::Endpoint((addr));
    auto router = std::make_shared<Pistache::Rest::Router>();


    auto opts = Pistache::Http::Endpoint::options().threads(PISTACHE_SERVER_THREADS);
    opts.flags(Pistache::Tcp::Options::ReuseAddr);
    opts.maxRequestSize(PISTACHE_SERVER_MAX_REQUEST_SIZE);
    opts.maxResponseSize(PISTACHE_SERVER_MAX_RESPONSE_SIZE);
    httpEndpoint->init(opts);

    AudioTesterApiImpl DefaultApiserver(router);
    DefaultApiserver.init();

    httpEndpoint->setHandler(router->handler());
    httpEndpoint->serve();

    httpEndpoint->shutdown();

    google::ShutdownGoogleLogging();
    return 0; 
}


