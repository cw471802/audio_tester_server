/*** 
 * @Author: chen wei
 * @Date: 2023-10-26 09:10:32
 * @LastEditTime: 2024-02-19 14:10:40
 * @FilePath: /audio_tester/include/mysql_conn.h
 * @Description: 
 * @Copyright (c) 2023 by ${chen wei}, All Rights Reserved. 
 */


#ifndef INCLUDE_MYSQL_CONN_H
#define INCLUDE_MYSQL_CONN_H

#include <iostream>
#include <ctime>
#include <chrono>
#include <mysql/mysql.h>
#include <stdexcept>
#include <memory>
#include <nlohmann/json.hpp>


class MysqlConn
{
public:
    MysqlConn();
    ~MysqlConn();
    /**
     * @brief 连接mysql数据库
     * @param {string} user 用户名
     * @param {string} passwd  密码
     * @param {string} dbName 数据库
     * @param {string} ip  数据库ip地址 
     * @param {unsigned short} port  数据库访问端口
     * @return {*}
     */   
    bool connect(std::string user, std::string passwd, std::string dbName, std::string ip, unsigned int port);
    /*** 
     * @brief  更新数据库，包含 delete、insert、update
     * @param {string} sql sql 语句
     * @return {bool}
     */       
    bool update(std::string sql);
    /**
     * @brief  插入新的数据
     * @param {string} sql sql语句
     * @return {*}
     */    
    bool query(std::string sql);
    /**
     * @brief 遍历查询得到的结果集
     * @return {*}
     */    
    bool next();
    /**
     * @brief 获取结果中的字段值
     * @param {bool} accurate true:返回最后两行，false:不返回最后两行
     * @return {std::string}
     */    
    std::string value(bool accurate);
    /**
     * @brief  事务操作
     * @return {std::string} 返回获取的字段值
     */    
    bool transaction();
    /**
     * @brief  提交事务
     * @return {*}
     */    
    bool commit();
    /*** 
     * @brief 事务回滚
     * @return {*}
     */    
    bool callback();

    /*** 
     * @brief 刷新起始的空闲时间点
     * @return {*}
     */    
    void refreshAliveTime();
    /*** 
     * @brief 计算连续存活的总时长
     * @return {*}
     */    
    long long getAliveTime();

    struct Param {
        enum class Type { INT, DOUBLE, STRING, BLOB } type;
        union Value {
            int intValue;
            double doubleValue;
            struct { char* ptr; unsigned long size; } stringValue;
            struct { void* ptr; unsigned long size; } blobValue;
        } value;
    };

    /*** 
     * @brief 参数化要执行的sql语句，以确保数据安全
     * @param {string&} query
     * @return {*}
     */    
    bool executePreparedStatement(const std::string& query, const std::vector<Param>& params);
private:
    /*** 
     * @brief 释放结果内存
     * @return {*}
     */    
    void freeResult();
    
    MYSQL *m_conn = nullptr;
    MYSQL_RES *m_result = nullptr;
    MYSQL_ROW m_row = nullptr;
    MYSQL_FIELD *fields = nullptr;
    std::chrono::steady_clock::time_point m_aliveTime;  // 连接数据库线程的存活时间

    /*** 
     * @brief 根据给定的参数类型，获取对应的mysql类型
     * @param {Type} type 参数类型
     * @return {*}
     */    
    enum enum_field_types getMySQLType(Param::Type type);
    /*** 
     * @brief 根据给定的参数类型，获取对应的缓冲区指针
     * @param {Param&} param 参数对象
     * @return {void*} 缓冲区指针
     */    
    void* getBufferPointer(const Param& param);
    /*** 
     * @brief 根据给定的参数类型，获取对应的缓冲区长度。
     * @param {Param&} param 参数对象
     * @return {unsigned long} 缓冲区长度
     */    
    unsigned long getBufferLength(const Param& param);
};

#endif //INCLUDE_MYSQL_CONN_H