#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CMainWindow.h"
#include "QLabel"
#include "ParameterSetting.h"
#include "QQueue"
#include <qdir.h>
#include <QDateTime>
#include <QTextStream>
#include <QMutex>
#include <QDockWidget>
#include <QListView>
#include <QStandardItemModel>
#include "QTimer"
#include "qtablewidget.h"


class CMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CMainWindow(QWidget *parent = Q_NULLPTR);
	~CMainWindow();
	static void ShowLog(QString log);
private:
	void InitVariables();
	void InitConnections();
	void ShowStatistics();
	void InitDockWidget();
	void InitStatusBar();
	QImage MattoQImage(Mat image);

private:
	Ui::CMainWindowClass ui;
	QLabel *m_Statistics;
	CParameterSetting *m_Parameter;
	int m_TotalCount;
	int m_SuccessCount;
	QQueue<s_StationInfo> m_FirstStation;
	QMutex m_Mutex;
	int m_FirstCount;
	int m_SecondCount;
	QListView *m_ListView;
	static QStandardItemModel *m_LogModel;
	//static QStandardItemModel m_LogMode2;
	bool m_bStart;
	QTimer m_Timer;
	QTableWidget m_FirstDefectTypeTab;
	QTableWidget m_SecondDefectTypeTab;
	QTableWidget m_DegreeDefectTypeTab;

	//×´Ì¬À¸
	QLabel m_PLC;
private slots:
	void StartDetecion();
	void StopDetecion();
	void OpenSetting();
	void ResetStatistics();
	void ReceiveAlgoImage(int index, Mat OriginalImage, Mat RenderImage, int Time, bool bok);
	void ReceivePLCMessage(QString msg);
	void ReceiveLabelTypeData(QVector<int> LabelType);
	void CheckSoftwareLicense();
	void ReceiveClearQueue();
	void ReceivePlcStatus(QString style);
};
