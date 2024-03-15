/*** 
 * @Author: chen wei
 * @Date: 2023-10-27 14:48:03
 * @LastEditTime: 2024-03-01 09:40:45
 * @FilePath: /audio_tester/src/connection_pool.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${Author}, All Rights Reserved. 
 */

#include "connection_pool.h"
#include <glog/logging.h>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <thread>
#include <string>
#include <filesystem>

ConnectionPool* ConnectionPool::getConnectionPool()
{
    static ConnectionPool pool;
    return &pool;
}

bool ConnectionPool::parseJson()
{
    try{
        // std::string homeDir;
        // const char *homeEnv = getenv("HOME");
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::string filepath =  currentPath.parent_path().generic_string() + "/config/dbConfig.json";
      
        std::ifstream ifs(filepath);
        if (!ifs.is_open()) {
            LOG(ERROR) << "无法打开数据库配置文件";
            return false;
        }
        Json::Reader rd;
        Json::Value root;
        rd.parse(ifs, root);
        if (root.isObject())
        {
            m_ip = root["ip"].asString();
            
            m_user = root["user"].asString();
            
            m_port = root["port"].asInt();
            
            m_passwd = root["passwd"].asString();
            
            m_dbName = root["dbName"].asString();
            
            m_minSize = root["minSize"].asInt();
            
            m_maxSize = root["maxSize"].asInt();
            
            m_maxIdleTime = root["maxIdleTime"].asInt();
           
            m_timeout = root["timeout"].asInt();
            
            return true;
        }
        throw("读取数据库配置文件JSON失败!");
    }
    catch(const char *str)
    {
        LOG(ERROR) << str;
    }
    return false;
}

void ConnectionPool::produceConnection()
{
    while(true)
    {
        // uniuqe模版类，mutex互斥锁类型 locker对象管理
        std::unique_lock<std::mutex> locker(m_mutexQ);
        // 判断连接池中连接数是否
        while(m_connectionQ.size() >= m_minSize)
        {
            // 阻塞条件变量
            m_cond.wait(locker);
        }
        addConnection();
        m_cond.notify_all();  // 唤醒生产者
    }
}

void ConnectionPool::recycleConnection()
{
    // 根据创建时间来回收连接
    while(true)
    {
        // 休息一段时间，每隔一秒钟进行一次检查
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // 加锁
        std::lock_guard<std::mutex> locker(m_mutexQ);
        while(m_connectionQ.size() > m_minSize)
        {
            // 先进后出
            MysqlConn *conn = m_connectionQ.front();
           
            if(conn->getAliveTime()>= m_maxIdleTime)
            {
                m_connectionQ.pop();
                delete conn;
            }
            else
            {
                break;
            }
        }
    }
}


void ConnectionPool::addConnection()
{
    MysqlConn *conn = new MysqlConn;
    conn->connect(m_user, m_passwd, m_dbName, m_ip, m_port); // 实例化数据库连接对象
    conn->refreshAliveTime();  // 记录生成的数据库连接的时间戳
    m_connectionQ.push(conn);  // 将数据库连接添加到队列
}


std::shared_ptr<MysqlConn> ConnectionPool::getConnection()
{
    std::unique_lock<std::mutex> locker(m_mutexQ);
    // 数据库连接队列为空的时候，阻塞连接
    while (m_connectionQ.empty())
    {
        if(std::cv_status::timeout == m_cond.wait_for(locker, std::chrono::milliseconds(m_timeout)))
        {
            if(m_connectionQ.empty())
            {
                //return nullptr;
                continue;
            }
        }
    }
    std::shared_ptr<MysqlConn> connptr(m_connectionQ.front(), [this](MysqlConn* conn){
        std::lock_guard<std::mutex> locker(m_mutexQ);
        conn->refreshAliveTime();
        m_connectionQ.push(conn);
    });
    m_connectionQ.pop();
    m_cond.notify_all();
    return connptr;
}


ConnectionPool::ConnectionPool()
{
    //加载配置文件
    if(!parseJson())
    {
        return ;
    };
    for (int i = 0; i<m_minSize; ++i)
    {
         //如果队列总数小于最大数量
        if (m_connectionQ.size() < m_maxSize)
        {
            addConnection();
        }
        //当连接总数大于允许连接的最大数量
        else
        {
            LOG(WARNING) << "当前连接数量已超过允许连接的总数";
            break;
        }
        
    }
    // 创建两个线程，一个控制数据库连接的生成，一个控制数据库连接的销毁
    std::thread producer(&ConnectionPool::produceConnection, this);
    std::thread recycler(&ConnectionPool::recycleConnection, this);
    // 子线程和主线程分离
    producer.detach();
    recycler.detach();
}

ConnectionPool::~ConnectionPool()
{
    std::lock_guard<std::mutex> locker(m_mutexQ);
    while (!m_connectionQ.empty())
    {
        MysqlConn* conn = m_connectionQ.front();
        m_connectionQ.pop();
        delete conn;
    }
    
}

