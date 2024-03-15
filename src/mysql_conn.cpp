/*** 
 * @Author: chen wei
 * @Date: 2023-10-26 18:29:46
 * @LastEditTime: 2024-03-01 09:27:03
 * @FilePath: /audio_tester/src/mysql_conn.cpp
 * @Description: 
 * @Copyright (c) 2023 by ${chen wei}, All Rights Reserved. 
 */


#include "mysql_conn.h"
#include <glog/logging.h>

MysqlConn::MysqlConn()
{
    m_conn = mysql_init(nullptr);
    
    // 检查 mysql_init 是否成功
    if (m_conn == nullptr) {
        // 错误处理，可以抛出异常或返回错误代码
        throw std::runtime_error("Failed to initialize MySQL connection.");
    }

    if (mysql_set_character_set(m_conn, "utf8mb4") != 0) {
        // 错误处理，可以抛出异常或返回错误代码
        throw std::runtime_error("Failed to set MySQL character set to utf8mb4.");
    }
}

// 析构函数中释放资源
MysqlConn::~MysqlConn() {
    if (m_conn != nullptr) {
        mysql_close(m_conn);
    }
}

bool MysqlConn::connect(std::string user, std::string passwd, std::string dbName, std::string ip, unsigned int port)
{
    if (!m_conn) {
        throw std::runtime_error("MySQL connection not initialized.");
    }
    MYSQL *ptr = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(), 
        dbName.c_str(), port, nullptr, 0);
    return ptr != nullptr;
}

bool MysqlConn::query(std::string sql)
{
    freeResult();
    // 查询数据库数据并在出错时捕获数据库异常
    try
    {
        if(mysql_query(m_conn, sql.c_str())) //执行mysql语句，失败时返回非0值
        {
            
            throw(std::invalid_argument("查询数据库失败：" + std::string(mysql_error(m_conn))));
        }
        m_result = mysql_store_result(m_conn); //储存从数据库查询到的结果
    }
    catch(const std::exception& e)
    {
        LOG(WARNING)<< e.what();
        return false; // 当出现异常时，返回false
    }
    return true;
}

bool MysqlConn::update(const std::string sql)
{
    // 检查数据库连接是否为空
    if (!m_conn)
    {
        LOG(WARNING) << "数据库连接为空!";
        return false;
    }
    // 更新数据库并在出错时捕获数据库异常
    try
    {
        if (mysql_query(m_conn, sql.c_str()))
        {
            throw(std::invalid_argument("执行语句插入/更新/删除失败!请检查数据库或执行语句"));
        }
       
        return true;
        
    }
    catch(const std::exception& e)
    {
        LOG(WARNING)<< e.what();
        return false;
    }
    
}

bool MysqlConn::next()
{
    //遍历结果集，如果结果集为空则没有必要遍历
    if (m_result != nullptr)
    {
        
        m_row = mysql_fetch_row(m_result);
        
        // 判断是否查询到数据
        if (m_row != nullptr)
        {
            return true;
        }
    }
    return false;
}


std::string MysqlConn::value(bool accurate)
{
    int colCount = mysql_num_fields(m_result);
    MYSQL_FIELD *fields = mysql_fetch_fields(m_result);
    nlohmann::json j;
    
    int end = accurate ? colCount : colCount - 2;
    
    for (int k = 0; k < end; k++)
    {
        std::string field = fields[k].name;
        
        // Skip sensitive fields like password
        
        if (m_row == nullptr || m_row[k] == nullptr)
        {
            throw std::runtime_error("Row data is null.");
        }
        
        char *val = m_row[k];
        unsigned long length = mysql_fetch_lengths(m_result)[k];
        
        try
        {
            if(field == "frequency" || field == "environmentNoise")
            {
                j[field] = nlohmann::json::parse(std::string(val, length));
            }
            else
            {
                j[field] = std::string(val, length);
            }
        }
        catch (const nlohmann::json::exception& e)
        {
            // Handle JSON parsing error
            throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
        }
    }
    
    return j.dump();
}

bool MysqlConn::transaction()
{
    if(m_conn == nullptr)
    {
        // throw std::runtime_error("MySQL connection not initialized.");
        LOG(ERROR) << "MySQL connection not initialized.";
        return false;
    }
    return mysql_autocommit(m_conn, false) == 0;
}

bool MysqlConn::commit()
{
    if (!m_conn) {
        // 可以选择抛出异常或返回错误值
        return false;
    }
    
    // 提交
    int result = mysql_commit(m_conn);
    if (result != 0) {
        // 处理错误，可以选择抛出异常或返回错误码
        LOG(ERROR) << "Commit failed! ";
        return false;
    }
    return true;
}

bool MysqlConn::callback()
{
    if (!m_conn) {
        LOG(ERROR) << "collback failed! ";
        return false;
    }
    return mysql_rollback(m_conn)==0;
}

void MysqlConn::refreshAliveTime()
{
    m_aliveTime = std::chrono::steady_clock::now();
}

long long MysqlConn::getAliveTime()
{
    std::chrono::nanoseconds res = std::chrono::steady_clock::now() - m_aliveTime;
    std::chrono::milliseconds millsec = std::chrono::duration_cast<std::chrono::milliseconds>(res);
    return millsec.count();
}

void MysqlConn::freeResult()
{
    if (m_result)
    {
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}

bool MysqlConn::executePreparedStatement(const std::string& query, const std::vector<Param>& params) {
    MYSQL_STMT* stmt = mysql_stmt_init(m_conn);
    if (!stmt) {
        LOG(ERROR) << "Failed to initialize statement";
        return false;
    }

    if (mysql_stmt_prepare(stmt, query.c_str(), query.length()) != 0) {
        LOG(ERROR) << "Failed to prepare statement: " << mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        return false;
    }

    std::vector<MYSQL_BIND> bind(params.size());
    memset(bind.data(), 0, sizeof(bind[0]) * params.size());

    for (size_t i = 0; i < params.size(); ++i) {
        bind[i].buffer_type = getMySQLType(params[i].type);
        bind[i].buffer = getBufferPointer(params[i]);
        bind[i].buffer_length = getBufferLength(params[i]);
        bind[i].is_null = 0;
        bind[i].length = nullptr; // For now, this example does not handle NULL values or output parameters.
    }

    if (mysql_stmt_bind_param(stmt, bind.data()) != 0) {
        LOG(ERROR) << "Failed to bind parameters: " << mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        return false;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        LOG(ERROR) << "Failed to execute statement: " << mysql_stmt_error(stmt);
        mysql_stmt_close(stmt);
        return false;
    }

    mysql_stmt_close(stmt);
    return true;
}

enum enum_field_types MysqlConn::getMySQLType(Param::Type type) {
    switch (type) {
        case Param::Type::INT:
            return MYSQL_TYPE_LONG;
        case Param::Type::DOUBLE:
            return MYSQL_TYPE_DOUBLE;
        case Param::Type::STRING:
            return MYSQL_TYPE_STRING;
        case Param::Type::BLOB:
            return MYSQL_TYPE_BLOB;
        default:
            throw std::invalid_argument("Unsupported parameter type");
    }
}

void* MysqlConn::getBufferPointer(const Param& param) {
    switch (param.type) {
        case Param::Type::INT:
            // Remove const qualifier from intValue's address
            return const_cast<void*>(reinterpret_cast<const void*>(&param.value.intValue));
        case Param::Type::DOUBLE:
            // Remove const qualifier from doubleValue's address
            return const_cast<void*>(reinterpret_cast<const void*>(&param.value.doubleValue));
        case Param::Type::STRING:
            // stringValue.ptr is already void*, just remove const qualifier
            return param.value.stringValue.ptr;
        case Param::Type::BLOB:
            // blobValue.ptr is already void*, just remove const qualifier
            return param.value.blobValue.ptr;
        default:
            throw std::invalid_argument("Unsupported parameter type");
    }
}



unsigned long MysqlConn::getBufferLength(const Param& param) {
    switch (param.type) {
        case Param::Type::STRING:
            return param.value.stringValue.size;
        case Param::Type::BLOB:
            return param.value.blobValue.size;
        case Param::Type::INT:
        case Param::Type::DOUBLE:
            // For fixed-size types, MySQL determines the length internally, so 0 is returned.
            return 0;
        default:
            throw std::invalid_argument("Unsupported parameter type");
    }
}
