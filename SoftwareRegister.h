#pragma once
#include "QObject"
#include "QMap"
#include "QSettings"

/*
���ɻ�����
1����ȡӲ�����к�-CPUID-MACΪ������
2����������Hash����
3��Hash����+ע��ʱ��
4����3���ɵ��ַ���ͨ��MAPӳ�䣬���μ��ܣ��������������

����ע����
1��MAP��ӳ������룬������Hash����+��ǰʱ��
2�����ݵ�ǰʱ��+Linceseʱ�䣬������������
3���м�ע����=Hash����+ע��ʱ��+����ʱ��
4�����м�ע����MAPӳ�䣬��������ע����

���ע��
1����ӳ��ע���룬������Hash����+��ǰʱ��+����ʱ��
2����ȡ��ǰ������Hash����
3����ȡ��ǰϵͳʱ��
4���ж�ע����Hash���ܺ͵�ǰ������Hash�����Ƿ�һ�£���һ���޷�ע��
5���ж�(ϵͳʱ��>ע��ʱ�� && ϵͳʱ�� <����ʱ��),�����޷�ע�ᣬ��ֹ�ṩע������޸�ϵͳʱ��

�������
1����ȡע���룬MAP��ӳ�������Hash����+ע��ʱ��+����ʱ��
2����ȡ��ǰϵͳ������(Hash)�͵�ǰʱ��
3���жϵ�ǰ�������ע�����еĻ������Ƿ�һ��
4���жϵ�ǰʱ���Ƿ����
5������ر�ʱ��д�����һ��ʱ��
6���ٴ�����ʱ���ж����һ��ʱ���Ƿ���ڵ�ǰʱ�䣬������ڣ�˵��ϵͳʱ���޸ģ�����޷�����
7�������Сʱ���һ��

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
	//��ȡ������
	QString GetMachineCode();

	//���ע��
	QString GenRegisterCode(QString MachineCode,int Days);
	bool Register(QString RegisterCode,QString &Time);
	QString GetLicenseTime();
	
	//-3 ���δע��
	//-2 �������
	//-1 ��ǰʱ��С�����һ��ʱ��
	//0 �ɹ�
	e_CheckType CheckPermission();
	//������һ������ʱ��
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
	//��ȡCPU ID
	QString GetCPUID();
	//��ȡ�������к�
	QString GetBaseboardSerial();
	QString GetHashMD5(QString code);
private:
	static CSoftwareRegister *m_Instance;
	static GarbageCollection m_Collection;
	QMap<QChar, QChar> m_EncryptionMap;
	QMap<QChar, QChar> m_DecryptionMap;
};
