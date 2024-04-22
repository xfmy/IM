#pragma once
#include <mysqlconnector\mysql_connection.h>
#include <mysqlconnector\mysql_driver.h>
#include <condition_variable>

class CConnectPool
{
public:
    CConnectPool();
    ~CConnectPool();

public:
    //创建一个连接,返回一个Connection
    sql::Connection *CreateConnection();
    //创建连接池实例
    static CConnectPool *GetInstance(const char *pUrl, const char *pDB,
                                     const char *pUserName, const char *pPwd);
    //设置连接池大小
    void SetPoolSize(int nMinSize, int nMaxSize);
    //初始化连接
    bool InitConnection();
    //在连接池中获得一个连接
    sql::Connection *GetConnection();
    //回收数据库连接
    void ReleaseConnection(sql::Connection *conn);
    //销毁连接池,首先要销毁连接池中的连接
    void DestroyPool();
    //销毁一个连接
    void DestroyConnection(sql::Connection *conn);

private:
    //连接池的构造函数
    CConnectPool(const char *pUrl, const char *pDB, const char *pUserName,
                 const char *pPwd);

private:
    int m_nMinSize;
    int m_nMaxSize;

    std::string strUrl;
    std::string strUserName;
    std::string strPwd;
    std::string strDB;

    std::list<sql::Connection *> m_listConn; //连接池容器队列
    std::condition_variable m_variable;
    std::mutex m_mtx;

    static CConnectPool *pConnectPool;
    sql::Driver *driver;
};
