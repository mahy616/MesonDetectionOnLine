#include "SoftwareRegister.h"
#include "QProcess"
#include "QCryptographicHash"
#include "qdatetime.h"
#include "QDebug"


CSoftwareRegister *CSoftwareRegister::m_Instance = NULL;
CSoftwareRegister::GarbageCollection CSoftwareRegister::m_Collection;

//[0-9,A-Z,-,:]-[A-J,:,K-Z,-,0-9]
const QString Encryption = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-:";
const QString Decryption = "ABCDEFG:HIJKLMNOPQRSTUVWXYZ-0123456789";
const QString RegisterDir = "HKEY_LOCAL_MACHINE\\SOFTWARE\\SMARTMORE";
const QString RegisterKey = "Register";

CSoftwareRegister::CSoftwareRegister(QObject *parent /* = NULL */)
	:QObject(parent)
{
	InitVariables();
}

CSoftwareRegister::~CSoftwareRegister()
{

}

CSoftwareRegister *CSoftwareRegister::GetInstance() 
{
	if (m_Instance == NULL)
	{
		m_Instance = new CSoftwareRegister();
	}
	return m_Instance;
}

void CSoftwareRegister::InitVariables()
{
	qDebug() << "InitVariables";
	for (int i = 0; i < Encryption.length(); ++i)
	{
		m_EncryptionMap.insert(Encryption.at(i), Decryption.at(i));
		m_DecryptionMap.insert(Decryption.at(i), Encryption.at(i));
	}
}

QString CSoftwareRegister::EncryptionCode(QString code)
{
	qDebug() << "EncryptionCode";
	QString EncrypCode;
	for (int i = 0; i < code.length(); ++i)
	{
		QChar c = code.at(i);
		QMap<QChar, QChar>::iterator it = m_EncryptionMap.find(c);
		if (it != m_EncryptionMap.end())
		{
			QChar fc = it.value();
			EncrypCode += fc;
		}
	}
	return EncrypCode;
}

QString CSoftwareRegister::DecryptionCode(QString code)
{
	qDebug() << "DecryptionCode";
	QString DecrypCode;
	for (int i = 0; i < code.length(); ++i)
	{
		QChar c = code.at(i);
		QMap<QChar, QChar>::iterator it = m_DecryptionMap.find(c);
		if (it != m_DecryptionMap.end())
		{
			QChar fc = it.value();
			DecrypCode += fc;
		}
	}
	return DecrypCode;
}

QString CSoftwareRegister::GetMachineCode()
{
	qDebug() << "GetMachineCode";
	QString HashCode = GetHashCode();
	QString CurrentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	QString code = HashCode + "-" + CurrentTime;
	qDebug() << "hash code:" << code;
	return EncryptionCode(code);
}

QString CSoftwareRegister::GenRegisterCode(QString MachineCode, int Days)
{
	qDebug() << "GenRegisterCode";
	//解密
	QString DCode = DecryptionCode(MachineCode);
	//机器码获取时间
	QString MTime = DCode.right(10);
	QDateTime DateTime = QDateTime::fromString(MTime, "yyyy-MM-dd");
	//计算license时间
	QDateTime LicenseTime = DateTime.addDays(Days);
	QString strLTime = LicenseTime.toString("yyyy-MM-dd");
	//注册码=License时间-机器码-机器码时间
	QString RegisterString = strLTime + "-" + DCode;
	//两次加密
	QString EncryCode = EncryptionCode(RegisterString);
	RegisterString = EncryptionCode(EncryCode);
	return RegisterString;
}

bool CSoftwareRegister::Register(QString RegisterCode, QString &Time)
{
	qDebug() << "Register";
	//两次解密
	QString FirstDecode = DecryptionCode(RegisterCode);
	QString SecondDecode = DecryptionCode(FirstDecode);
	QString MachineCode = GetMachineCode();
	QString DecryMCode = DecryptionCode(MachineCode);

	QString OriginalMCode = DecryMCode.left(DecryMCode.length() - 11);
	QString RegisterMachineCode = SecondDecode.left(SecondDecode.length() - 11);
	RegisterMachineCode = RegisterMachineCode.right(RegisterMachineCode.length() - 11);
	if (OriginalMCode != RegisterMachineCode)
	{
		qDebug() << "current Machine code != register Machine code";
		return false;
	}
	//当前时间
	QDateTime CurrentTime = QDateTime::currentDateTime();
	//注册码中机器码时间
	QString strMachineTime = SecondDecode.right(10);
	QDateTime MachineTime = QDateTime::fromString(strMachineTime, "yyyy-MM-dd");
	//注册码中到期时间
	QString strRegisterTime = SecondDecode.left(10);
	Time = strRegisterTime;
	QDateTime RegisterTime = QDateTime::fromString(strRegisterTime, "yyyy-MM-dd");
	//如果当前时间不在机器码时间和到期时间之间，返回注册失败
	if (CurrentTime < MachineTime || CurrentTime > RegisterTime)
	{
		qDebug() << "current time is not between Machine time and Register time";
		qDebug() << "curretn time:" << CurrentTime.toString("yyyy-MM-dd");
		qDebug() << "Machine time:" << strMachineTime;
		qDebug() << "Register time:" << strRegisterTime;
		return false;
	}
	//写注册表
	//HKEY_LOCAL_MACHINE\SOFTWARE
	QString strCurrentTime = CurrentTime.toString("yyyy-MM-dd-hh");
	SecondDecode = SecondDecode + "-" + strCurrentTime;
	QString RCode = EncryptionCode(SecondDecode);
	RCode = EncryptionCode(RCode);
	QSettings settings(RegisterDir, QSettings::NativeFormat);
	settings.setValue(RegisterKey, RCode);
	return true;
}

QString CSoftwareRegister::GetLicenseTime()
{
	qDebug() << "GetLicenseTime";
	QSettings settings(RegisterDir, QSettings::NativeFormat);
	QString RegisterCode = settings.value(RegisterKey).toString();
	if (RegisterCode.isEmpty())
	{
		return "";
	}

	QString OriginalCode = DecryptionCode(RegisterCode);
	OriginalCode = DecryptionCode(OriginalCode);
	return OriginalCode.left(10);
}

e_CheckType CSoftwareRegister::CheckPermission()
{
	qDebug() << "CheckPermission";
	QSettings settings(RegisterDir, QSettings::NativeFormat);
	QString RegisterCode = settings.value(RegisterKey).toString();
	if (RegisterCode.isEmpty())
	{
		return SOFTWARE_NO_LICENSE;
	}

	QString OriginalCode = DecryptionCode(RegisterCode);
	OriginalCode = DecryptionCode(OriginalCode);
	qDebug() << "original code:" << OriginalCode;
	QString strLicensetTime = OriginalCode.left(10);
	qDebug() << "license time:" << strLicensetTime;
	QDateTime LicenseTime = QDateTime::fromString(strLicensetTime, "yyyy-MM-dd");

	QString strLastTime = OriginalCode.right(13);
	qDebug() << "last time:" << strLastTime;
	QDateTime LastTime = QDateTime::fromString(strLastTime, "yyyy-MM-dd-hh");

	QDateTime CurrentTime = QDateTime::currentDateTime();
	if (LastTime > CurrentTime)
	{
		qDebug() << "current time < last time";
		return CTIME_BIGGER_LTIME;
	}
	if (CurrentTime > LicenseTime)
	{
		qDebug() << "current time > license time";
		return SOFTWARE_OVERDUE;
	}
	return SOFTWARE_SUCCESS;
}

QString CSoftwareRegister::GetHashCode()
{
	qDebug() << "GetHashCode";
	QString cpuid = GetCPUID();
	QString serial = GetBaseboardSerial();
	QString code = cpuid + serial;
	qDebug() << "original:" << code;
	return GetHashMD5(code);
}

QString CSoftwareRegister::getWMIC(const QString &cmd)
{
	qDebug() << "getWMIC:" << cmd;
	QProcess p;
	p.start(cmd);
	p.waitForFinished();
	QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
	QStringList list = cmd.split(" ");
	result = result.remove(list.last(), Qt::CaseInsensitive);
	result = result.replace("\r", "");
	result = result.replace("\n", "");
	result = result.simplified();
	return result;
}

QString CSoftwareRegister::GetCPUID()
{
	return getWMIC("wmic cpu get processorid");
}

QString CSoftwareRegister::GetBaseboardSerial()
{
	QString serial = getWMIC("wmic baseboard get serialnumber");
	QString NewSerial = serial.replace("/", "-");
	NewSerial = NewSerial.left(NewSerial.length() - 1);
	return NewSerial;
}

QString CSoftwareRegister::GetHashMD5(QString code)
{
	qDebug() << "GetHashMD5";
	QString md5;
	QByteArray ba, bb;
	QCryptographicHash md(QCryptographicHash::Md5);
	ba.append(code);
	md.addData(ba);
	bb = md.result();
	md5.append(bb.toHex());
	return md5.toUpper();
}

void CSoftwareRegister::WriteLastTime()
{
	qDebug() << "WriteLastTime";
	QSettings settings(RegisterDir, QSettings::NativeFormat);
	QString RegisterCode = settings.value(RegisterKey).toString();
	RegisterCode = DecryptionCode(RegisterCode);
	RegisterCode = DecryptionCode(RegisterCode);
	RegisterCode = RegisterCode.left(RegisterCode.length() - 13);
	QString CurrentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh");
	RegisterCode = RegisterCode + CurrentTime;
	RegisterCode = EncryptionCode(RegisterCode);
	RegisterCode = EncryptionCode(RegisterCode);
	settings.setValue(RegisterKey, RegisterCode);
}