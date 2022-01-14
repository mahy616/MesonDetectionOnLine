#include "CMainWindow.h"
#include <QMessageBox>
#include "PLCManager.h"
#include "QHeaderView"
QStandardItemModel *CMainWindow:: m_LogModel;
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	static QMutex mutex;                   // ����
	mutex.lock();

	QString text;
	switch (type)                         
	{
	case QtDebugMsg:
		text = QString("Debug:");
		break;

	case QtWarningMsg:
		text = QString("Warning:");
		break;

	case QtCriticalMsg:
		text = QString("Critical:");
		break;

	case QtFatalMsg:
		text = QString("Fatal:");
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(QString::fromLocal8Bit(context.file)).arg(context.line);
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ddd");
	QString current_date = QString("(%1)").arg(current_date_time);
	QString message = QString("%1          %2 %3 %4").arg(current_date).arg(text).arg(context_info).arg(msg);
	QString LogPath = QCoreApplication::applicationDirPath();
	LogPath.append("/log");
	QDir dir(LogPath);
	if (!dir.exists(LogPath))
	{
		dir.mkdir(LogPath);
	}
	QString logFile = LogPath + "/" + QDateTime::currentDateTime().toString("yyyy-MM-dd");
	logFile.append(".txt");
	QFile file(logFile);
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream text_stream(&file);
	text_stream << message << "\r\n";
	file.flush();
	file.close();

	mutex.unlock();
}

CMainWindow::CMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qInstallMessageHandler(outputMessage);    //�����־��Ϣ
	InitVariables();
	InitDockWidget();
	InitConnections();
	InitStatusBar();
}

CMainWindow::~CMainWindow()
{
	delete m_Parameter;
	m_Parameter = NULL;
}

void CMainWindow::InitVariables()
{
	qDebug() << "InitVarialbes";
	m_Statistics = new QLabel();
	m_Statistics->setText(QString::fromLocal8Bit("�������:0,�ɹ�:0,�ɹ���:0.00%"));
	m_Statistics->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_Statistics->setFont(QFont("Microsoft YaHei", 25, 75));
	m_Statistics->setStyleSheet("color:blue;");
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addWidget(m_Statistics);
	QLabel *Logo = new QLabel();
	Logo->setFixedWidth(500);
	Logo->setStyleSheet("image: url(:/CMainWindow/Resources/logo.png);");
	ui.mainToolBar->addWidget(Logo);
	ui.mainToolBar->setFont(QFont("Microsoft YaHei", 15, 70));
	m_Parameter = new CParameterSetting();
	m_TotalCount = 0;
	m_SuccessCount = 0;
	m_FirstCount = 0;
	m_SecondCount = 0;
	//��־��������
	m_ListView = new QListView();
	m_LogModel = new QStandardItemModel();
	m_ListView->setModel(m_LogModel);
	QDockWidget *LogDock = new QDockWidget("Log");
	LogDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, LogDock);
	m_ListView->setFont(QFont("΢���ź�", 20));
	LogDock->setWidget(m_ListView);
	ui.action_Stop->setEnabled(false);
	m_bStart = false;
}

void CMainWindow::InitConnections()
{
	qDebug() << "InitConnections";
	connect(ui.action_Start, SIGNAL(triggered()), this, SLOT(StartDetecion()));
	connect(ui.action_Stop, SIGNAL(triggered()), this, SLOT(StopDetecion()));
	connect(ui.action_Setting, SIGNAL(triggered()), this, SLOT(OpenSetting()));
	connect(ui.action_Reset, SIGNAL(triggered()), this, SLOT(ResetStatistics()));
	qRegisterMetaType<Mat>("Mat");
	connect(m_Parameter, SIGNAL(SendAlgoImage(int, Mat, Mat, int, bool)), this, SLOT(ReceiveAlgoImage(int, Mat, Mat, int, bool)));
	connect(m_Parameter, SIGNAL(SendLabelTypeData(QVector<int>)), this, SLOT(ReceiveLabelTypeData(QVector<int>)));
	connect(&m_Timer, SIGNAL(timeout()), this, SLOT(CheckSoftwareLicense()));
	connect(CSerialManager::GetInstance(), SIGNAL(SendClearQueue()), this, SLOT(ReceiveClearQueue()));
	connect(m_Parameter, SIGNAL(SendPlcStatus(QString)), this, SLOT(ReceivePlcStatus(QString)));
}

void CMainWindow::ShowStatistics()
{
	QString Ratio = "0.00%";
	if (m_TotalCount != 0)
	{
		double dRatio = (m_SuccessCount * 0.1 / m_TotalCount)*1000;
		Ratio = QString::number(dRatio, 'f', 2) + "%";
	}
	QString msg = QString::fromLocal8Bit("�������:") + QString::number(m_TotalCount) + QString::fromLocal8Bit(",��Ʒ:");
	msg += QString::number(m_SuccessCount) + QString::fromLocal8Bit(",��Ʒ��:") + Ratio;
	m_Statistics->setText(msg);
}

void CMainWindow::InitDockWidget()
{
	//��λһ
	QFont font("΢���ź�", 12);
	m_FirstDefectTypeTab.setSelectionBehavior(QAbstractItemView::SelectRows);                                                   //����ѡ����Ϊʱÿ��ѡ��һ��
	m_FirstDefectTypeTab.setEditTriggers(QAbstractItemView::NoEditTriggers);                                                    //���ò��ɱ༭
	m_FirstDefectTypeTab.horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
	m_FirstDefectTypeTab.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_FirstDefectTypeTab.horizontalHeader()->setFont(font);                                                                     //��������
	m_FirstDefectTypeTab.horizontalHeader()->setHighlightSections(false);                                                       //��ȡ����
	m_FirstDefectTypeTab.verticalHeader()->setHidden(true);
	m_FirstDefectTypeTab.horizontalHeader()->setStyleSheet("QHeaderView::section{color:rgb(255,255,255);background:rgb(41,136,41);}"); //����ѡ�б���ɫ
	m_FirstDefectTypeTab.setColumnCount(2);
	m_FirstDefectTypeTab.setRowCount(4);
	// 	m_BoxTab.horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	// 	m_BoxTab.horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	QStringList Firstheader;
	Firstheader << QString::fromLocal8Bit("  ȱ������  ") << QString::fromLocal8Bit("  OK/NG  ");
	m_FirstDefectTypeTab.setHorizontalHeaderLabels(Firstheader);                                                                     //���ñ�ͷ����

	QDockWidget *FirstResult = new QDockWidget(QString::fromLocal8Bit("��λһ"));
	FirstResult->setMinimumWidth(200);
	FirstResult->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, FirstResult);
	FirstResult->setWidget(&m_FirstDefectTypeTab);
	
	m_FirstDefectTypeTab.setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("�н�")));
	m_FirstDefectTypeTab.setItem(1, 0, new QTableWidgetItem(QString::fromLocal8Bit("����")));
	m_FirstDefectTypeTab.setItem(2, 0, new QTableWidgetItem(QString::fromLocal8Bit("��ѹ��")));
	m_FirstDefectTypeTab.setItem(3, 0, new QTableWidgetItem(QString::fromLocal8Bit("����")));


	//��λ��
	m_SecondDefectTypeTab.setSelectionBehavior(QAbstractItemView::SelectRows);                                                   //����ѡ����Ϊʱÿ��ѡ��һ��
	m_SecondDefectTypeTab.setEditTriggers(QAbstractItemView::NoEditTriggers);                                                    //���ò��ɱ༭
	m_SecondDefectTypeTab.horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
	m_SecondDefectTypeTab.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_SecondDefectTypeTab.horizontalHeader()->setFont(font);                                                                     //��������
	m_SecondDefectTypeTab.horizontalHeader()->setHighlightSections(false);                                                       //��ȡ����
	m_SecondDefectTypeTab.verticalHeader()->setHidden(true);
	m_SecondDefectTypeTab.horizontalHeader()->setStyleSheet("QHeaderView::section{color:rgb(255,255,255);background:rgb(41,136,41);}"); //����ѡ�б���ɫ
	m_SecondDefectTypeTab.setColumnCount(2);
	m_SecondDefectTypeTab.setRowCount(12);
	// 	m_BoxTab.horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	// 	m_BoxTab.horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	QStringList Secondheader;
	Secondheader << QString::fromLocal8Bit("  ȱ������  ") << QString::fromLocal8Bit("  OK/NG  ");
	m_SecondDefectTypeTab.setHorizontalHeaderLabels(Secondheader);                                                                     //���ñ�ͷ����

	QDockWidget *SecondResult = new QDockWidget(QString::fromLocal8Bit("��λ��"));
	SecondResult->setMinimumWidth(200);
	SecondResult->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, SecondResult);
	SecondResult->setWidget(&m_SecondDefectTypeTab);
	m_SecondDefectTypeTab.setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("ȱ��")));
	m_SecondDefectTypeTab.setItem(1, 0, new QTableWidgetItem(QString::fromLocal8Bit("ë˿")));
	m_SecondDefectTypeTab.setItem(2, 0, new QTableWidgetItem(QString::fromLocal8Bit("����")));
	m_SecondDefectTypeTab.setItem(3, 0, new QTableWidgetItem(QString::fromLocal8Bit("����")));
	m_SecondDefectTypeTab.setItem(4, 0, new QTableWidgetItem(QString::fromLocal8Bit("ѹ��")));
	m_SecondDefectTypeTab.setItem(5, 0, new QTableWidgetItem(QString::fromLocal8Bit("ˮ�ڳ�")));
	m_SecondDefectTypeTab.setItem(6, 0, new QTableWidgetItem(QString::fromLocal8Bit("����")));
	m_SecondDefectTypeTab.setItem(7, 0, new QTableWidgetItem(QString::fromLocal8Bit("��ѹ��")));
	m_SecondDefectTypeTab.setItem(8, 0, new QTableWidgetItem(QString::fromLocal8Bit("�Ͻ���")));
	m_SecondDefectTypeTab.setItem(9, 0, new QTableWidgetItem(QString::fromLocal8Bit("�Ƕ�")));
	m_SecondDefectTypeTab.setItem(10, 0, new QTableWidgetItem(QString::fromLocal8Bit("ƫλ")));
	m_SecondDefectTypeTab.setItem(11, 0, new QTableWidgetItem(QString::fromLocal8Bit("������")));
}

void CMainWindow::InitStatusBar()
{
	qDebug() << "InitStatusBar";
	ui.statusBar->setStyleSheet("QStatusBar::item{ border: 0px }");
	m_PLC.setStyleSheet("min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: "
		"8px;  border:1px solid black;background:grey");
	ui.statusBar->addWidget(&m_PLC);
	QLabel *label = new QLabel(QString::fromLocal8Bit("PLC:"));
	ui.statusBar->addWidget(label);
	m_Parameter->GetConnected();
}

void CMainWindow::StartDetecion()
{
#ifndef DEBUG_FLAG

	qDebug() << "StartDecode";
	e_CheckType Type = m_Parameter->CheckPermission();
	if (Type == SOFTWARE_NO_LICENSE)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���δע�ᣬ����ϵ������Ա����ע����"));
		return;
	}
	else if (Type == CTIME_BIGGER_LTIME)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����޷���������ǰʱ��С���ϴ�������е�ʱ��"));
		return;
	}
	else if (Type == SOFTWARE_OVERDUE)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����ѹ��ڣ�����ϵ������Ա����"));
		return;
	}
	else
	{
		m_Timer.start(1800000);
	}
	QString errMsg;
	bool rv = m_Parameter->CheckEnv(errMsg);
	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), errMsg);
		return;
	}
	rv = CPLCManager::GetInstance()->GetConnectStatus();
	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("δ����PLC"));
		return;
	}
	rv = CPLCManager::GetInstance()->GetPLCInitStatus();
	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("PLCδ��ʼ���ɹ�"));
		return;
	}
#endif
	ui.action_Start->setEnabled(false);
	ui.action_Stop->setEnabled(true);
	ui.action_Setting->setEnabled(false);
	m_Parameter->StartDetecion(true);
	m_bStart = true;
	qDebug() << "StartDetecion:" << 1;
}

void CMainWindow::StopDetecion()
{
	ui.action_Start->setEnabled(true);
	ui.action_Stop->setEnabled(false);
	ui.action_Setting->setEnabled(true);
	m_Parameter->StartDetecion(false);
	m_FirstStation.clear();
	m_bStart = false;
}

void CMainWindow::OpenSetting()
{
	m_Parameter->exec();
}

void CMainWindow::ResetStatistics()
{
	m_TotalCount = 0;
	m_SuccessCount = 0;
	m_FirstCount = 0;
	m_SecondCount = 0;
	ShowStatistics();
}

void CMainWindow::ShowLog(QString log)
{
	int rows = m_LogModel->rowCount();
	if (rows > 1000)
	{
		m_LogModel->removeRows(0, rows);
	}
	m_LogModel->insertRow(0, new QStandardItem(log));
}

void CMainWindow::ReceivePLCMessage(QString msg)
{
//	qDebug() << "ReceiveMessage:" << msg;
//	printf("CMainWindow::ReceiveMessage%s\n", msg.toStdString().c_str());
	ShowLog(msg);
}

void CMainWindow::ReceiveLabelTypeData(QVector<int> LabelType)
{
	if (LabelType.size() < 7)
	{
		for (int i = 1; i < LabelType.size(); i++)
		{
			if (LabelType[i] == 1)
			{
				m_FirstDefectTypeTab.setItem(i - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("NG")));
			}
			else
			{
				m_FirstDefectTypeTab.setItem(i - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("OK")));

			}
		}
	}
	else
	{
		for (int i = 1; i < LabelType.size(); i++)
		{
			if (LabelType[i] == 1)
			{
				m_SecondDefectTypeTab.setItem(i - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("NG")));
			}
			else
			{
				m_SecondDefectTypeTab.setItem(i - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("OK")));
			}
		}
	}

}


void CMainWindow::CheckSoftwareLicense()
{
	e_CheckType Type = m_Parameter->CheckPermission();
	qDebug() << "CheckSoftwareLicense:" << Type;
	if (Type == SOFTWARE_NO_LICENSE)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���δע�ᣬ����ϵ������Ա����ע����"));
		return;
	}
	else if (Type == CTIME_BIGGER_LTIME)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����޷���������ǰʱ��С���ϴ�������е�ʱ��"));
		return;
	}
	else if (Type == SOFTWARE_OVERDUE)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����ѹ��ڣ�����ϵ������Ա����"));
		return;
	}
	if (Type != SOFTWARE_SUCCESS)
	{
		StopDetecion();
		m_bStart = false;
		m_Timer.stop();
	}
}

void CMainWindow::ReceiveClearQueue()
{
	StopDetecion();
	ResetStatistics();
	StartDetecion();
	QString Msg="Station 1 has been initialized";
	ShowLog(Msg);
}

void CMainWindow::ReceivePlcStatus(QString style)
{
	m_PLC.setStyleSheet(style);
}

QImage CMainWindow::MattoQImage(Mat image)
{
	switch (image.type())
	{
	case CV_8UC1:
	{
		QImage img((const unsigned char *)(image.data), image.cols, image.rows, image.cols, QImage::Format_Grayscale8);
		return img;
	}
	break;
	case CV_8UC3:
	{
		QImage img((const unsigned char *)(image.data), image.cols, image.rows, image.cols * 3, QImage::Format_RGB888);
		return img.rgbSwapped();
	}
	break;
	default:
	{
		QImage img;
		return img;
	}
	break;
	}
}

int SendPLCCount = 0;

void CMainWindow::ReceiveAlgoImage(int index, Mat OriginalImage, Mat RenderImage, int Time, bool bok)
{
	if (!m_bStart)
	{
		return;
	}
	s_StationInfo StationInfo;
	//cout << "��λ��" << index << "���" << m_FirstCount << endl;
	//cout << "��λ��" << index << "���" << m_SecondCount << endl;
	QString Msg = "Receive algo image: index = " + QString::number(index) + ",result = " + QString::number(bok);
	ShowLog(Msg);
	if (index == 1)
	{
		StationInfo.OriginalImage = OriginalImage;// .clone();
		StationInfo.RenderImage = RenderImage;// .clone();
		StationInfo.bok = bok;
		if (m_FirstStation.size() > 500)
		{
			StopDetecion();
			QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("һ��λ���ϴ���50��,���ٴ���һ��λ����"));
			return;
		}
		m_Mutex.lock();
		m_FirstStation.push_back(StationInfo);
		m_Mutex.unlock();

	}
	else if (index == 2)
	{
		if (m_FirstStation.size() == 0)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("һ��λ������Ϊ��"));
			return;
		}
		m_Mutex.lock();
		StationInfo = m_FirstStation.dequeue();
		m_Mutex.unlock();
		bool a = bok & StationInfo.bok;
		qDebug() << "Main Send PLC Count:" << SendPLCCount++ << " Result;" <<a;
		m_Parameter->SendPLCResult(bok & StationInfo.bok);
	}

	QString strTime = QString::fromLocal8Bit("��ʱ:") + QString::number(Time) + "ms";
	QString strIndex = QString::fromLocal8Bit("���:");
	QString style;
	QImage qimage = MattoQImage(RenderImage);
	if (bok)
	{
		style = "image: url(:/CMainWindow/Resources/OK.svg);";
	}
	else
	{
		style = "image: url(:/CMainWindow/Resources/NG.svg);";
	}
	if (index == 1)
	{
		m_FirstCount++;
		strIndex += QString::number(m_FirstCount);
		ui.label_FirstTime->setText(strTime);
		ui.label_FirstIndex->setText(strIndex);
		ui.label_FirstResult->setStyleSheet(style);
		ui.label_FirstImage->SetImage(qimage);
	}
	else if (index == 2)
	{
		m_SecondCount++;
		strIndex += QString::number(m_SecondCount);
		ui.label_SecondTime->setText(strTime);
		ui.label_SecondIndex->setText(strIndex);
		ui.label_SecondResult->setStyleSheet(style);
		m_TotalCount++;
		if (StationInfo.bok&bok)
		{
			m_SuccessCount++;
		}
		ui.label_SecondImage->SetImage(qimage);
		ShowStatistics();
		s_SaveImageInfo SaveInfo;
		SaveInfo.FirstStation = StationInfo;
		StationInfo.OriginalImage = OriginalImage;
		StationInfo.RenderImage = RenderImage;
		StationInfo.bok = bok;
		SaveInfo.SecondStation = StationInfo;
		//����ͼ��
		m_Parameter->SaveImage(SaveInfo);
	}
}