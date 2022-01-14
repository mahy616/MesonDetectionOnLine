#pragma once
#include "QtSerialPort/QSerialPort"
#include "QSerialPortInfo"
#include "qtimer.h"

typedef struct
{
	bool recstatu;
	int ccnt;
	int packerflag ;
	QString strData;
	void Init()
	{
		recstatu = 1;
		ccnt = 0;
		 packerflag = 0;
		 strData="@";
	}
	void Clear()
	{
		recstatu = 0;
		//ccnt = 1;
		packerflag = 1;
		//vtData.clear();
	}
}s_SerialReceive;
class CSerialManager :public QSerialPort
{
	Q_OBJECT
public:
	static CSerialManager *GetInstance();
	void InitSerial(QString comName, int Heartbeat);
	void OpenHeart(bool Heartbeat);
	bool GetConnectStatus() { return m_bConnected; }
	void WritePLCData(bool bok);
private:
	CSerialManager(QSerialPort *parent = NULL);
	~CSerialManager();
	static CSerialManager *m_Instance;
	QSerialPort m_SerialPort;
	bool m_bConnected;
	int m_Heartbeat;
	bool m_bStart;
	bool m_HeartbeatForPlc;
	QTimer m_HeartTimer;
	QTimer m_HeartTimerForPlc;
	s_SerialReceive s_SerialReceiveData;
	QByteArray QstrData;
	//PLCд����
	void WritePLCOK();
	void WritePLCNG();
	void WritePLCHeartbeat();
	void ReadPLCClearData();
	void GetPLCdata(QByteArray QstrValue); //��ȡ��ȡ��PLC�Ĵ�������ֵ 

private slots:
	void handleSerialError(QSerialPort::SerialPortError error);
	void handle_data();
	void SendPLCHeartbeat();
	void GetPLCHeartbeat();
signals:
	void SendConnectStatus(bool bConnected);
	void SendClearQueue();
};
