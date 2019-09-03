#pragma once

#include "commo.h"
#include "mysql.h"

class MainWd :public WindowImplBase
{
public:
	MainWd(MySQL* mysql = nullptr) :_mysql(mysql)
	{

	}

	void Notify(TNotifyUI& msg);


protected:

	virtual CDuiString GetSkinFolder();

	virtual CDuiString GetSkinFile();

	virtual LPCTSTR GetWindowClassName(void) const;

	void SelectEmployee();

	void DeleteEmployee();

	void InsertEmployee();

private:
	MySQL* _mysql;
};