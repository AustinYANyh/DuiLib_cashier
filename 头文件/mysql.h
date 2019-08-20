#pragma once

#include <iostream>
#include<WinSock2.h>
#include<mysql.h>
#include<vector>

using namespace std;

class MySQL
{
public:
	MySQL();

	bool ConnectMysql(const char* host, const char* user, const char* password, const char* dbname);

	~MySQL();

	vector<vector<string>> Select(const string& strSQL);

	bool Insert(const string& strSQL);

	bool Delete(const string& strSQL);

	bool Check(const string& strSQL);

	bool Update(const string& strSQL);

private:
	MYSQL* _mySql;
};
