/*** 
 * @Author: chen wei
 * @Date: 2023-10-26 09:10:32
 * @LastEditTime: 2023-10-30 17:12:21
 * @FilePath: /audio_tester_server/include/connection_pool.h
 * @Description: the pool setting of mysql databse
 * @Copyright (c) 2023 by ${chen wei}, All Rights Reserved. 
 */

#ifndef INCLUDE_CONNECTION_POOL_H
#define INCLUDE_CONNECTION_POOL_H

#include <iostream>
#include <queue>
#include <mutex>
#include <ctime>
#include <chrono>
#include <condition_variable>
#include "mysql_conn.h"

class ConnectionPool
{
public:
    static ConnectionPool*getConnectionPool();
    ConnectionPool(const ConnectionPool & obj) = delete;
    ConnectionPool & operator=(const ConnectionPool & obj) = delete;
    /*** 
     * @brief 获取数据库线程池中的连接 
     * @return {*}
     */    
    std::shared_ptr<MysqlConn> getConnection();
    ~ConnectionPool();
private:
    ConnectionPool();
    /*** 
     * @brief 解析json数据文件并赋值
     * @return {*}
     */    
    bool parseJson();
    /*** 
     * @brief 生产数据库连接
     * @return {*}
     */    
    void produceConnection();
    /*** 
     * @brief 销毁数据库连接
     * @return {*}
     */    
    void recycleConnection();
    /*** 
     * @brief 添加数据库连接
     * @return {*}
     */    
    void addConnection();
    std::string m_ip;
    std::string m_user;
    std::string m_passwd;
    std::string m_dbName;
    unsigned short m_port;
    int m_minSize;          // 线程最小连接数
    int m_maxSize;          // 线程最大连接数
    int m_timeout;          //超时时间
    int m_maxIdleTime;      // 最大空闲时间
    std::queue<MysqlConn*> m_connectionQ; //连接池线程
    std::mutex m_mutexQ;  //线程互斥锁
    std::condition_variable m_cond;  // 线程调节条件变量
};


#endif //INCLUDE_CONNECTION_POOL_H