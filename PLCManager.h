#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QDebug>
#include <QMutex>

class CPLCManager :public QObject
{
	Q_OBJECT
public:
	static CPLCManager *GetInstance();
	void TcpConnect(QString ip, quint16 port,int HeartBeat);
		//�Ͽ�����
	//	void TcpDisconnect();
	bool GetConnectStatus() { return m_bConnected; }
	bool GetPLCInitStatus() { return m_bInitPLCSuccess; }
	void WritePLCData(bool bok);
private:
	//PLCд����
	void WriteInitCommand();
	void WritePLCOK();
	void WritePLCNG();
	void WritePLCHeartbeat();
private:
	CPLCManager(QObject *parent = NULL);
	~CPLCManager();
	static CPLCManager *m_Instace;
	QTcpSocket *m_TcpClient;
	QString m_IP;
	quint16 m_Port;
	//�������ӱ�־
	bool m_bConnected;
	//ŷķ��PLC��ʼ���ɹ���־
	bool m_bInitPLCSuccess;
	QTimer m_Timer;
	int m_HeartBeat;
	QMutex m_Mutex;
	QString m_HexLastHost; //PC��IP��󲿷ֵ�16����
	QString m_HexLastServer; //PLC��IP��󲿷ֵ�16����
private slots:
	void TcpConnected();
	void TcpDisConnected();
	void SlotTimeOuter();
	void ReadPLCData();
signals:
	void SendConnectStatus(bool status);
	void SendPLCMessage(QString msg);
};