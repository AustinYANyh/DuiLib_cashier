#pragma once

#include "commo.h"

class MainWd :public WindowImplBase
{
public:
	void Notify(TNotifyUI& msg);


protected:

	virtual CDuiString GetSkinFolder();

	virtual CDuiString GetSkinFile();

	virtual LPCTSTR GetWindowClassName(void) const;

	void SelectEmployee();

	void DeleteEmployee();

	void InsertEmployee();
};