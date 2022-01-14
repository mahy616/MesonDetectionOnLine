#include "PLCManager.h"
#include "windows.h"


CPLCManager *CPLCManager::m_Instace = NULL;

CPLCManager::CPLCManager(QObject *parent)
	:QObject(parent)
{
	m_TcpClient = new QTcpSocket(); 
	m_IP = "";
	m_Port = 0;
	m_bConnected = false;
	m_bInitPLCSuccess = false;
	m_HeartBeat = 3;
	connect(m_TcpClient, SIGNAL(connected()), this, SLOT(TcpConnected()));
	connect(m_TcpClient, SIGNAL(disconnected()), this, SLOT(TcpDisConnected()));
	connect(m_TcpClient, SIGNAL(readyRead()), this, SLOT(ReadPLCData()));
	connect(&m_Timer, SIGNAL(timeout()), this, SLOT(SlotTimeOuter()));
}

CPLCManager::~CPLCManager()
{
	if (m_Timer.isActive())
	{
		m_Timer.stop();
	}
}

CPLCManager *CPLCManager::GetInstance()
{
	if (m_Instace == NULL)
	{
		m_Instace = new CPLCManager();
	}
	return m_Instace;
}

void CPLCManager::TcpConnect(QString ip, quint16 port, int HeartBeat)
{
	printf("connect to server ip:%s,port:%d,heartbeat:%d\n",ip.toStdString().c_str(),port,HeartBeat);
	qDebug() << "TcpConnect ip:" << ip << ",port:" << port << ",heart beat:" << HeartBeat;
	m_Timer.stop();
	m_IP = ip;
	m_Port = port;
	QAbstractSocket::SocketState status = m_TcpClient->state();
	if (status == QAbstractSocket::ConnectedState)
	{
		m_TcpClient->abort();
		Sleep(100);
	}
	m_TcpClient->connectToHost(m_IP, m_Port);
	m_TcpClient->waitForConnected(500);
	m_IP = ip;
	m_Port = port;
	m_HeartBeat = HeartBeat;
	m_Timer.start(m_HeartBeat*1000);
}

#if 0
void CPLCManager::TcpDisconnect()
{
	qDebug() << "TcpDisconnect";
	QAbstractSocket::SocketState status = m_TcpClient->state();
	if (m_bConnected)
	{
		m_TcpClient->disconnectFromHost();
		m_bConnected = false;
		m_TcpClient->waitForDisconnected(1000);	
		m_IP.clear();
		m_Port = 0;
	}
}
#endif

void CPLCManager::WritePLCData(bool bok)
{
	qDebug() << "WritePLCData:" << bok;
	if (m_bInitPLCSuccess)
	{
		if (bok)
		{
			WritePLCOK();
		}
		else
		{
			WritePLCNG();
		}
	}
	else
	{
		printf("PLC did not initialize successfully\n");
		qDebug() << "PLC did not initialize successfully";
	}
}

void CPLCManager::WriteInitCommand()
{
	qDebug() << "WriteInitCommand";
	printf("WriteInitCommand\n");
	if (m_TcpClient->state() == QAbstractSocket::ConnectedState)
	{
		QString InitData = "46 49 4E 53"; //FINS
		InitData += " 00 00 00 0C"; //�������ĳ���0C
		InitData += " 00 00 00 00"; // ��ʼ�������������( �ͻ���->����ˣ�Ҳ����PC��PLC���ͳ�ʼ������) 
		InitData += " 00 00 00 00"; //�������
		InitData += " 00 00 00 " + m_HexLastHost;//��λ������IP�ţ� FE(16����)=254 ��ʾ���Ե�ip:192.168.1.254 ������254
		printf("write init plc command:%s\n", InitData.toStdString().c_str());
		QByteArray arrayHex = QByteArray::fromHex(InitData.toLatin1());
		m_TcpClient->write(arrayHex);
		m_TcpClient->waitForBytesWritten(10);
		m_TcpClient->flush();
		m_TcpClient->waitForReadyRead(10);
	}
	else
	{
		qDebug() << "write init command error:" << m_TcpClient->errorString();
		printf("write init command error:%s\n", m_TcpClient->errorString().toStdString().c_str());
	}
}

void CPLCManager::WritePLCOK()
{
	qDebug() << "WritePLCOK";
	printf("WritePLCOK\n");
	if (m_TcpClient->state() == QAbstractSocket::ConnectedState)
	{
		QString WriteCommand = "46 49 4E 53"; //FINS
		WriteCommand += " 00 00 00 1C"; //д��1C:28*2���ֽ�
		WriteCommand += " 00 00 00 02"; //�����룬��������
		WriteCommand += " 00 00 00 00"; //�������
		WriteCommand += " 80 00 02 00 ";  //80 ��ʾ ICF;  00��ʾRSV 02��ʾGCT, 00��ʾPLC�����
		WriteCommand += m_HexLastServer + " 00 00 " + m_HexLastHost; //PLC��ip��󲿷֣�00--plc��Ԫ�� 00--pc����� PC��IP��󲿷�
		WriteCommand += " 00 FF 01 02";  //00--pc��Ԫ�� FF--SID  01-- MRC���� 02--GCT����(����0102��ʾд)
		WriteCommand += " 80"; //CIO - 80��DM - 82��WR - B1
		WriteCommand += " 01 F4 00 00 01"; //01 F4 ��ַ500,00 �׵�ַ��00 01 д�볤��
		WriteCommand += " 00 01"; //д��1
		printf("write plc ok command:%s\n", WriteCommand.toStdString().c_str());
		QByteArray arrayHex = QByteArray::fromHex(WriteCommand.toLatin1());
		m_TcpClient->write(arrayHex);
		m_TcpClient->waitForBytesWritten(10);
		m_TcpClient->flush();
		m_TcpClient->waitForReadyRead(10);
	}
	else
	{
		qDebug() << "write plc ok error:" << m_TcpClient->errorString();
		printf("write plc ok error :%s\n", m_TcpClient->errorString().toStdString().c_str());
	}
}

void CPLCManager::WritePLCNG()
{
	qDebug() << "WritePLCNG";
	printf("WritePLCNG\n");
	if (m_TcpClient->state() == QAbstractSocket::ConnectedState)
	{
		QString WriteCommand = "46 49 4E 53"; //FINS
		WriteCommand += " 00 00 00 1C"; //д��1C:28*2���ֽ�
		WriteCommand += " 00 00 00 02"; //�����룬��������
		WriteCommand += " 00 00 00 00"; //�������
		WriteCommand += " 80 00 02 00 ";  //80 ��ʾ ICF;  00��ʾRSV 02��ʾGCT, 00��ʾPLC�����
		WriteCommand += m_HexLastServer + " 00 00 " + m_HexLastHost; //PLC��ip��󲿷֣�00--plc��Ԫ�� 00--pc����� PC��IP��󲿷�
		WriteCommand += " 00 FF 01 02";  //00--pc��Ԫ�� FF--SID  01-- MRC���� 02--GCT����(����0102��ʾд)
		WriteCommand += " 80"; //CIO - 80��DM - 82��WR - B1
		WriteCommand += " 01 F4 00 00 01"; //01 F4 ��ַ500,00 �׵�ַ��00 01 д�볤��
		WriteCommand += " 00 02"; //д��2
		printf("write plc ng command:%s\n", WriteCommand.toStdString().c_str());
		QByteArray arrayHex = QByteArray::fromHex(WriteCommand.toLatin1());
		m_TcpClient->write(arrayHex);
		m_TcpClient->waitForBytesWritten(10);
		m_TcpClient->flush();
		m_TcpClient->waitForReadyRead(10);
	}
	else
	{
		qDebug() << "write plc ok error:" << m_TcpClient->errorString();
		printf("write plc ok error :%s\n", m_TcpClient->errorString().toStdString().c_str());
	}
}

void CPLCManager::WritePLCHeartbeat()
{
	qDebug() << "WritePLCHeartbeat";
	printf("WritePLCHeartbeat\n");
	if (m_TcpClient->state() == QAbstractSocket::ConnectedState)
	{
		QString WriteCommand = "46 49 4E 53"; //FINS
		WriteCommand += " 00 00 00 1C"; //д��1C:28*2���ֽ�
		WriteCommand += " 00 00 00 02"; //�����룬��������
		WriteCommand += " 00 00 00 00"; //�������
		WriteCommand += " 80 00 02 00 ";  //80 ��ʾ ICF;  00��ʾRSV 02��ʾGCT, 00��ʾPLC�����
		WriteCommand += m_HexLastServer + " 00 00 " + m_HexLastHost; //PLC��ip��󲿷֣�00--plc��Ԫ�� 00--pc����� PC��IP��󲿷�
		WriteCommand += " 00 FF 01 02";  //00--pc��Ԫ�� FF--SID  01-- MRC���� 02--GCT����(����0102��ʾд)
		WriteCommand += " 80"; //CIO - 80��DM - 82��WR - B1
		WriteCommand += " 01 F4 00 00 01"; //01 F4 ��ַ500,00 �׵�ַ��00 01 д�볤��
		WriteCommand += " 00 00"; //д��2
		printf("write plc heartbeat command:%s\n", WriteCommand.toStdString().c_str());
		QByteArray arrayHex = QByteArray::fromHex(WriteCommand.toLatin1());
		m_TcpClient->write(arrayHex);
		m_TcpClient->waitForBytesWritten(10);
		m_TcpClient->flush();
		m_TcpClient->waitForReadyRead(10);
	}
	else
	{
		qDebug() << "write plc ok error:" << m_TcpClient->errorString();
		printf("write plc ok error :%s\n", m_TcpClient->errorString().toStdString().c_str());
	}
}

void CPLCManager::TcpConnected()
{
	qDebug() << "TcpConnected";
	m_Mutex.lock();
	m_bConnected = true;
	//��ȡPLC��PC��IP���һ���ֵ�16����
	QString HostAddress = m_TcpClient->localAddress().toString();
	int pos = HostAddress.lastIndexOf(".");
	QString LastHost = HostAddress.right(HostAddress.length() - pos - 1);
	pos = m_IP.lastIndexOf(".");
	QString LastServer = m_IP.right(m_IP.length() - pos - 1);
	m_HexLastHost = QString::number(LastHost.toInt(), 16).toUpper();
	m_HexLastServer = QString::number(LastServer.toInt(), 16).toUpper();
	WriteInitCommand();
	m_Mutex.unlock();
	emit SendConnectStatus(true);
}

void CPLCManager::TcpDisConnected()
{
	qDebug() << "TcpDisConnected";
	m_Mutex.lock();
	m_bConnected = false;
	m_Mutex.unlock();
	emit SendConnectStatus(false);
}

void CPLCManager::ReadPLCData()
{
	if (m_TcpClient->state() == QAbstractSocket::ConnectedState)
	{
		QByteArray ba = m_TcpClient->readAll();
		if (ba.size() > 0)
		{
			QString data = ba.toHex().toUpper();
			printf("receive plc data:%s\n",data.toStdString().c_str());
			qDebug() << "receive plc data:" << data;
			//46 49 4E 53    --  ͷ˵��,�����ASCII����FINS
			//00 00 00 10    --  �������ĳ���10(16����)= 16��
			//00 00 00 01    --  ��ʼ�������������ظ�( �����->�ͻ���) 
			//00 00 00 00    --  �������
			//00 00 00 FE    --  ��λ������IP�ţ� FE(16����)=254 ��ʾ���Ե�ip:192.168.1.254 ������254��
			QString InitResponse = "46494E53000000100000000100000000000000"+m_HexLastHost;

			//46 49 4E 53   --ͷ˵��, �����ASCII����FINS
			//00 00 00 16   --����
			//00 00 00 02    ----�����룬��������
			//00 00 00 00      --�������
			//C0 00 02 00   --�ظ�
			//FD 00 00 FE  --  FD--��ip��󲿷֣�00--plc��Ԫ�� 00--pc����� FE--PC��IP��󲿷�
			//00 FF 01 02      -- 00--pc��Ԫ�� FF--SID  01--MRC���� 02--GCT����
			//00 00               --��ʾд��������
			QString WriteResponse = "46494E53000000160000000200000000C0000200" + m_HexLastServer + "0000" + m_HexLastHost + "00FF01020000";
			if (data == InitResponse)
			{
				//PLC������
				m_bInitPLCSuccess = true;
				printf("init plc success\n");
				emit SendPLCMessage("init plc success");
			}
			else if (data == WriteResponse)
			{
				printf("write plc success\n");
				emit SendPLCMessage("write plc success");
			}
		}
	}
}

void CPLCManager::SlotTimeOuter()
{
	if (!m_bConnected)
	{
		if (!m_IP.isEmpty())
		{
			//����
			qDebug() << "reconnect ip:" << m_IP << ",port:" << m_Port;
			m_TcpClient->connectToHost(m_IP, m_Port);
			m_bConnected = m_TcpClient->waitForConnected(50);
		}
	}
 	else
 	{
		WritePLCHeartbeat();
 	}
}