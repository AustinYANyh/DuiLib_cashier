#include "commo.h"
#include "mysql.h"

class LoginWind :public WindowImplBase
{
public:

	void Notify(TNotifyUI& msg);

	MySQL* m_MySQL;

	void Login();

protected:

	virtual CDuiString GetSkinFolder();

	virtual CDuiString GetSkinFile();

	virtual LPCTSTR GetWindowClassName(void) const;
};