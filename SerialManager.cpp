#include "SerialManager.h"
#include "windows.h"
#include "qdebug.h"
#include <iostream>

CSerialManager *CSerialManager::m_Instance = NULL;

CSerialManager::CSerialManager(QSerialPort *parent /* = NULL */)
	:QSerialPort(parent)
{
	m_bConnected = false;
	m_bStart = false;
	m_HeartbeatForPlc = false;
	qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError");
	connect(&m_SerialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handleSerialError(QSerialPort::SerialPortError)));
	connect(&m_SerialPort, SIGNAL(readyRead()), this, SLOT(handle_data()), Qt::DirectConnection); //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号
	connect(&m_HeartTimer, SIGNAL(timeout()), this, SLOT(SendPLCHeartbeat()));
	connect(&m_HeartTimerForPlc, SIGNAL(timeout()), this, SLOT(GetPLCHeartbeat()));
}

CSerialManager::~CSerialManager()
{
	if (m_bConnected)
	{
		m_SerialPort.close();
		m_SerialPort.clear();
	}
}

CSerialManager *CSerialManager::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CSerialManager();
	}
	return m_Instance;
}

void CSerialManager::InitSerial(QString comName, int Heartbeat)
{
	m_Heartbeat = Heartbeat;
	m_SerialPort.setPortName(comName);
	m_SerialPort.setBaudRate(QSerialPort::Baud9600);
	m_SerialPort.setDataBits(QSerialPort::Data7);
	m_SerialPort.setStopBits(QSerialPort::TwoStop);
	m_SerialPort.setParity(QSerialPort::EvenParity);
	m_SerialPort.setFlowControl(QSerialPort::NoFlowControl);
	if (m_SerialPort.open(QSerialPort::ReadWrite))
	{
		qDebug() << "InitSerial Success:" ;
	}
	else 
	{
		qDebug() << "InitSerial Error:";
		//m_SerialPort.clearError();
	}
}

void CSerialManager::OpenHeart(bool Heartbeat)
{
	m_bStart = Heartbeat;
	if (m_bConnected&&m_bStart)
	{
		m_HeartTimer.isActive();
	    m_HeartTimer.start(m_Heartbeat * 1000);
		m_HeartTimerForPlc.isActive();
		m_HeartTimerForPlc.start(m_Heartbeat * 5000);
	}
	else
	{
		m_HeartTimer.stop();
		m_HeartTimerForPlc.stop();
	}
}

void CSerialManager::handleSerialError(QSerialPort::SerialPortError error)
{
	if (m_SerialPort.isOpen())
	{
		m_bConnected = false;
		emit SendConnectStatus(m_bConnected);
		m_SerialPort.close();
		m_HeartTimer.stop();
		return;
	}
	m_bConnected = error == QSerialPort::NoError;
	emit SendConnectStatus(m_bConnected);
//	if (m_bConnected&&m_bStart)
//	{
//		if (m_HeartTimer.isActive())
//		{
//			m_HeartTimer.stop();
//		}
//		m_HeartTimer.start(m_Heartbeat * 1000);
//	}
}

void CSerialManager::handle_data()
{
	//Sleep(100);
	
	QByteArray ba = m_SerialPort.readAll();
	
	if (ba == "@")
	{
		QstrData == "@";
		s_SerialReceiveData.Init();
		//printf("receive plc data Init:%s\n", ba.data());
	}
	if (s_SerialReceiveData.recstatu == 1)
	{
		QstrData = QstrData + ba;
	}
	if (ba == "*")
	{
		s_SerialReceiveData.Clear();
		QString str = ba.data();
		str = str.trimmed();
		//printf("receive plc data frameQstrData:%s\n", QstrData.data());
		//qDebug() << "receive plc data frameQstrData" << QstrData.data();
		//emit SendBarScannerString(str);
		GetPLCdata(QstrData);
		QstrData = "";
	}
	m_HeartbeatForPlc = true;
	/*if (ba.size() > 0)
	{
		QString str = ba.data();
		str = str.trimmed();
		printf("receive plc data byte:%s\n", ba.data());
		//emit SendBarScannerString(str);
		//GetPLCdata(str);
	}*/
}

void CSerialManager::SendPLCHeartbeat()
{
	WritePLCHeartbeat();
	ReadPLCClearData();
}

void CSerialManager::GetPLCHeartbeat()
{
	if (m_HeartbeatForPlc)
	{
		m_HeartbeatForPlc = false;
		emit SendConnectStatus(true);
	}
	else
	{
		emit SendConnectStatus(false);
	}
}

//void CSerialManager::ReceiveStartSignal()
//{
//	m_bStart = 1;
//}

void CSerialManager::WritePLCData(bool bok)
{
	qDebug() << "CSerialManager:" << bok;
	if (bok)
	{
		WritePLCOK();
	}
	else
	{
		WritePLCNG();
	}
}

void CSerialManager::WritePLCOK()
{
	//D501 д 1 
	QString data = "@00FA00000000001028201F500000100010C*\r";
	//printf("Write PLC OK:%s\n", data.toStdString().c_str());
	//qDebug() << "Write PLC OK:" << data;
	QByteArray arrayAsc = data.toLatin1();
	m_SerialPort.write(arrayAsc);
}

void CSerialManager::WritePLCNG()
{
	//D501 д 2 
	QString data = "@00FA00000000001028201F500000100020F*\r";
	//printf("Write PLC NG:%s\n", data.toStdString().c_str());
	//qDebug() << "Write PLC NG:" << data;
	QByteArray arrayAsc = data.toLatin1();
	m_SerialPort.write(arrayAsc);
}

void CSerialManager::WritePLCHeartbeat()
{
	//D500 д 1
	QString data = "@00FA00000000001028201F400000100010D*\r";
	//printf("Write PLC Heartbeat:%s\n", data.toStdString().c_str());
	QByteArray arrayAsc = data.toLatin1();
	m_SerialPort.write(arrayAsc);
}

void CSerialManager::ReadPLCClearData()
{
	//D550 д 1
	QString data = "@00FA00000000001018202260000017A*\r";
	//printf("Read PLC Clear:%s\n", data.toStdString().c_str());
	QByteArray arrayAsc = data.toLatin1();
	m_SerialPort.write(arrayAsc);
}

void CSerialManager::GetPLCdata(QByteArray QstrValue)
{
	 //QString strValue = QstrValue;
	if ((QstrValue.contains("0101"))&& (QstrValue.size()<40))            //寄存器D550
	{
		//QString strState = strValue.mid(34,4);
		//QString strState1 = strValue.mid(30, 4);
		int numb= QstrValue.count("01");
		//printf("Read PLC Clear numb:%d\n", numb);
		if (3 == numb)
		{
			printf("Read PLC Clear Over:%s\n", QstrValue);
			qDebug() << "Write PLC OK:" << QstrValue.toStdString().c_str();
			Sleep(100);
			emit SendClearQueue();
		}
	}

}

