
#pragma once
#include "ConnectPool.h"
#include <mysqlconnector\cppconn\resultset.h>
#include <mysqlconnector\cppconn\statement.h>
#include <vector>

class CMysqlDataBase
{
public:
    CMysqlDataBase();
    ~CMysqlDataBase();

public:
    static void CreateDataBase();
    //登录数据库
    virtual bool Login(int nMinPoolSize, int nMaxPoolSize);
    //登出数据库
    virtual void Logout();
    //操作数据库
    virtual bool RunSqlExec(const std::string& strsql);
    virtual sql::ResultSet* RunSqlQuery(const std::string strsql);
    virtual bool RunSqlExecTrans(const std::vector<std::string>& vecstrsql);
    //设置数据库信息
    virtual void SetDbSvrInfo(const char* pHost, unsigned short nHostPort,
                              const char* pDbName);
    //设置用户登录信息
    virtual void SetUserLogInfo(const char* pUserName, const char* pPwd);

public:
    static CMysqlDataBase* m_pMysql;

private:
    CConnectPool* m_pConnPool;

    std::string m_strDbName;
    std::string m_strHostIp;
    unsigned short m_nPort;
    std::string m_strUserName;
    std::string m_strPwd;
};
