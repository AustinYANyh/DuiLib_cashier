#include "commo.h"
#include "mysql.h"

class LoginWind :public WindowImplBase
{
public:
	LoginWind(MySQL* mysql = nullptr) :_mysql(mysql)
	{

	}

	void Notify(TNotifyUI& msg);

	void Login();

protected:

	virtual CDuiString GetSkinFolder();

	virtual CDuiString GetSkinFile();

	virtual LPCTSTR GetWindowClassName(void) const;

private:
	MySQL* _mysql;
};