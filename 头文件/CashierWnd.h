#pragma once

#include "commo.h"
#include "mysql.h"

class CashierWnd:public WindowImplBase
{
public:
	CashierWnd(MySQL* mysql) :_mysql(mysql)
	{

	}

public:
	void Notify(TNotifyUI& msg);

protected:

	virtual CDuiString GetSkinFolder();

	virtual CDuiString GetSkinFile();

	virtual LPCTSTR GetWindowClassName(void) const;

	void SelectGood();

	void AddGoodCount();

	void SubGoodCount();

	void InsertGood();

	void Commit();

	void Cancel();

private:
	MySQL* _mysql;
};

