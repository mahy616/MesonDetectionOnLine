#pragma once
#include "QObject"
#include "QMap"
#include "QSettings"

/*
生成机器码
1、获取硬盘序列号-CPUID-MAC为机器码
2、将机器码Hash加密
3、Hash加密+注册时间
4、将3生成的字符串通过MAP映射，二次加密，机器码生成完毕

生成注册码
1、MAP反映射机器码，解析出Hash加密+当前时间
2、根据当前时间+Lincese时间，推算出软件期限
3、中间注册码=Hash加密+注册时间+到期时间
4、将中间注册码MAP映射，生成最终注册码

软件注册
1、反映射注册码，解析出Hash加密+当前时间+到期时间
2、获取当前机器码Hash加密
3、获取当前系统时间
4、判断注册码Hash加密和当前机器码Hash加密是否一致，不一致无法注册
5、判断(系统时间>注册时间 && 系统时间 <到期时间),否则无法注册，防止提供注册码后修改系统时间

软件运行
1、读取注册码，MAP反映射解析出Hash加密+注册时间+到期时间
2、获取当前系统机器码(Hash)和当前时间
3、判断当前机器码和注册码中的机器码是否一致
4、判断当前时间是否过期
5、软件关闭时，写入最后一次时间
6、再次启动时，判断最后一次时间是否大于当前时间，如果大于，说明系统时间修改，软件无法运行
7、软件半小时检测一次

*/

typedef enum
{
	SOFTWARE_NO_LICENSE,
	CTIME_BIGGER_LTIME,
	SOFTWARE_OVERDUE,
	SOFTWARE_SUCCESS
}e_CheckType;

class CSoftwareRegister :public QObject
{
	Q_OBJECT
public:
	static CSoftwareRegister *GetInstance();
	//获取机器码
	QString GetMachineCode();

	//软件注册
	QString GenRegisterCode(QString MachineCode,int Days);
	bool Register(QString RegisterCode,QString &Time);
	QString GetLicenseTime();
	
	//-3 软件未注册
	//-2 软件过期
	//-1 当前时间小于最后一次时间
	//0 成功
	e_CheckType CheckPermission();
	//软件最后一次运行时间
	void WriteLastTime();
	QString EncryptionCode(QString code);
	QString DecryptionCode(QString code);
private:
	CSoftwareRegister(QObject *parent = NULL);
	~CSoftwareRegister();
	class GarbageCollection
	{
	public:
		~GarbageCollection()
		{
			if (CSoftwareRegister::m_Instance)
			{
				delete CSoftwareRegister::m_Instance;
				CSoftwareRegister::m_Instance = NULL;
			}
		}
	};
private:
	void InitVariables();
	QString GetHashCode();
	QString getWMIC(const QString &cmd);
	//获取CPU ID
	QString GetCPUID();
	//获取主板序列号
	QString GetBaseboardSerial();
	QString GetHashMD5(QString code);
private:
	static CSoftwareRegister *m_Instance;
	static GarbageCollection m_Collection;
	QMap<QChar, QChar> m_EncryptionMap;
	QMap<QChar, QChar> m_DecryptionMap;
};
