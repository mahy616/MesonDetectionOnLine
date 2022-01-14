#include "ParameterSetting.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QDateTime"
#include "Config.h"
#include "QClipboard"
#include <QVector>
#include <QVariant>
const QString m_green_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: "
"8px;  border:1px solid black;background:green";
const QString m_grey_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: "
"8px;  border:1px solid black;background:grey";
CParameterSetting::CParameterSetting(QDialog *parent /* = NULL */)
	:QDialog(parent)
{
	ui.setupUi(this);
	m_bConnected = false;
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinimizeButtonHint;
	flags |= Qt::WindowMaximizeButtonHint;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
	InitVariables();
	InitConnections();
	InitCamera();
	LoadConfig();
}

CParameterSetting::~CParameterSetting()
{

	qDebug() << "~CParameterSetting";
	m_FirstCameraInfo.ImageCapture->StopThread();
	m_FirstCameraInfo.ImageCapture->wait(500);
	FirstRunAlgoCapture->StopThread();
	FirstRunAlgoCapture->wait(500);
	if (m_FirstCameraInfo.bOpenCamera)
	{
		CloseDevice(1);
	}

	 m_SecondCameraInfo.ImageCapture->StopThread();
	 m_SecondCameraInfo.ImageCapture->wait(500);
	 SecondRunAlgoCapture->StopThread();
	 SecondRunAlgoCapture->wait(500);
	if (m_SecondCameraInfo.bOpenCamera)
	{
		CloseDevice(2);
	}
	m_SaveImage.StopThread();
	m_SaveImage.wait(1000);
	qDebug() << QString::fromLocal8Bit("线程关闭完成:");
}

void CParameterSetting::InitVariables()
{
	m_FirstCameraInfo.Init();
	FirstRunAlgoCapture = new CRunAlgo;
	
	m_SecondCameraInfo.Init();
	SecondRunAlgoCapture = new CRunAlgo;
	
	ui.pushButton->setEnabled(false);

	QList<QSerialPortInfo> Ports = QSerialPortInfo::availablePorts();
	ui.pushButton->setEnabled(Ports.size() > 0);
	for (int i = 0; i < Ports.size(); ++i)
	{
		ui.comboBox_ComNames->addItem(Ports.at(i).portName());
	}

	m_FirstCameraInfo.ImageCapture->start();
	m_SecondCameraInfo.ImageCapture->start();
	ui.pushButton_OpenFirst->setEnabled(false);
	ui.pushButton_TriggerFirst->setEnabled(false);

	ui.pushButton_OpenSecond->setEnabled(false);
	ui.pushButton_TriggerSecond->setEnabled(false);

	m_FirstGroup = new QButtonGroup();
	m_FirstGroup->addButton(ui.radioButton_FreeFirst, 1);
	m_FirstGroup->addButton(ui.radioButton_ExternalFirst, 2);
	m_FirstGroup->addButton(ui.radioButton_SoftFirst, 3);
	SetButtonGroupEnabled(false, 1);

	m_SecondGroup = new QButtonGroup();
	m_SecondGroup->addButton(ui.radioButton_FreeSecond, 1);
	m_SecondGroup->addButton(ui.radioButton_ExternalSecond, 2);
	m_SecondGroup->addButton(ui.radioButton_SoftSecond, 3);
	SetButtonGroupEnabled(false, 2);


	ui.pushButton_SendOK->setEnabled(false);
	ui.pushButton_SendNG->setEnabled(false);

	ui.pushButton_SaveConfig->setEnabled(false);

	ui.pushButton_LoadNGPath->setEnabled(false);
	ui.pushButton_LoadOKPath->setEnabled(false);

	ui.pushButton_LoadFirstImage->setEnabled(false);
	ui.pushButton_LoadSecondImage->setEnabled(false);

	ui.comboBox_SystemType->addItem(QString::fromLocal8Bit("在线运行"));
	ui.comboBox_SystemType->addItem(QString::fromLocal8Bit("相机调试"));
	ui.comboBox_SystemType->addItem(QString::fromLocal8Bit("在线Debug算法"));
	ui.comboBox_SystemType->addItem(QString::fromLocal8Bit("离线Debug算法"));
	m_FirstCameraInfo.ImageCapture->SetSystemType(RUN_ONLINE);
	m_SecondCameraInfo.ImageCapture->SetSystemType(RUN_ONLINE);
//	QRegExp reg("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
//	ui.lineEdit_IP->setValidator(new QRegExpValidator(reg));
 	QString errMsg;
 	m_bFirstAlgoSuccess = CAlgoFirstStation::GetInstance()->InitAlgo(errMsg);
 	if (!m_bFirstAlgoSuccess)
 	{
 		QMessageBox::information(this, QString::fromLocal8Bit("错误"), errMsg);
 		return;
 	}
	else
	{
		m_FirstOriginalImage.create(4096, 3000, CV_8UC3);
		m_FirstRenderImage.create(4096, 3000, CV_8UC3);
		int Time = 0; 
		bool bOK = true;
		//printf("init success,run first algo once begin\n");
	//	qDebug() << "init success,run first algo once begin";
		//CAlgoFirstStation::GetInstance()->RunAlog(m_FirstOriginalImage, m_FirstRenderImage, bOK, Time);
		//printf("init success,run first algo once end\n");
		//qDebug() << "init success,run first algo once end";
	}
 	m_bSecondAlgoSuccess = CAlgoSecondStation::GetInstance()->InitAlgo(errMsg);
 	if (!m_bSecondAlgoSuccess)
 	{
 		QMessageBox::information(this, QString::fromLocal8Bit("错误"), errMsg);
 		return;
 	}
	else
	{
		m_SecondOriginalImage.create(4096, 3000, CV_8UC3);
		m_SecondRenderImage.create(4096, 3000, CV_8UC3);
		int Time = 0;
		bool bOK = true;
	//	printf("init success,run second algo once begin\n");
		//qDebug() << "init success,run second algo once begin";
		//CAlgoSecondStation::GetInstance()->RunAlog(m_SecondOriginalImage, 7,m_SecondRenderImage, bOK, Time);
		//printf("init success,run first algo once end\n");
		//qDebug() << "init success,run first algo once end";
	}
	FirstRunAlgoCapture->start();
	qDebug() << "init success,run first algo once begin";
	SecondRunAlgoCapture->start();
	qDebug() << "init success,run second algo once begin";
	
	m_SaveImage.start();
	QString MCode = CSoftwareRegister::GetInstance()->GetMachineCode();
	ui.lineEdit_MachineCode->setText(MCode);
	QString LicenseTime = CSoftwareRegister::GetInstance()->GetLicenseTime();
	if (LicenseTime.isEmpty())
	{
		ui.label_RegisterInfo->setText(QString::fromLocal8Bit("未注册"));
	}
	else
	{
		ui.label_RegisterInfo->setText(QString::fromLocal8Bit("到期时间:") + LicenseTime);
	}
	InitFirstThreshold();
	InitSecondThreshold();
	InitDgreeThreshold();
}

e_CheckType CParameterSetting::CheckPermission()
{
	return CSoftwareRegister::GetInstance()->CheckPermission();
}

bool CParameterSetting::CheckEnv(QString &errMsg)
{
	if (!m_FirstCameraInfo.bOpenCamera)
	{
		errMsg = QString::fromLocal8Bit("工位1相机未打开");
		return false;
	}
	if (!m_SecondCameraInfo.bOpenCamera)
	{
		errMsg = QString::fromLocal8Bit("工位2相机未打开");
		return false;
	}
	if (!m_bFirstAlgoSuccess)
	{
		errMsg = QString::fromLocal8Bit("工位1算法初始化失败");
		return false;
	}
	if (!m_bSecondAlgoSuccess)
	{
		errMsg = QString::fromLocal8Bit("工位2算法初始化失败");
		return false;
	}

	if (!CSerialManager::GetInstance()->GetConnectStatus())
	{
		errMsg = QString::fromLocal8Bit("PLC未连接");
		return false;
	}
	return true;
}

void CParameterSetting::StartDetecion(bool bStart)
{
	if (bStart)
	{
		m_FirstCameraInfo.ImageCapture->SetSystemType(RUN_ONLINE);
		m_SecondCameraInfo.ImageCapture->SetSystemType(RUN_ONLINE);
	}
	else
	{
		SetSystemType(ui.comboBox_SystemType->currentIndex());
	}
	int distance = ui.spinBox_Distance->value();
	m_FirstCameraInfo.ImageCapture->SetRunStatus(bStart, distance);
	m_SecondCameraInfo.ImageCapture->SetRunStatus(bStart, distance);
	FirstRunAlgoCapture->SetRunStatus(distance);
	SecondRunAlgoCapture->SetRunStatus(distance);
	FirstRunAlgoCapture->SetRunFirstThreshold(m_FirstThreshold);
	SecondRunAlgoCapture->SetRunSecondThreshold(m_SecondThreshold);
	FirstRunAlgoCapture->SetDegree(m_DegreeThreshold);
	SecondRunAlgoCapture->SetDegree(m_DegreeThreshold);
	CSerialManager::GetInstance()->OpenHeart(bStart);
	
}

void CParameterSetting::SetButtonGroupEnabled(bool enabled,int index)
{
	if (index == 1)
	{
		ui.radioButton_FreeFirst->setEnabled(enabled);
		ui.radioButton_ExternalFirst->setEnabled(enabled);
		ui.radioButton_SoftFirst->setEnabled(enabled);
	}
	else if (index == 2)
	{
		//ui.spinBox_Distance->setEnabled(enabled);
		ui.radioButton_FreeSecond->setEnabled(enabled);
		ui.radioButton_ExternalSecond->setEnabled(enabled);
		ui.radioButton_SoftSecond->setEnabled(enabled);
	}
}

void CParameterSetting::InitConnections()
{
	connect(m_FirstGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(SwitchFirstCameraStatus(int, bool)));
	connect(m_SecondGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(SwitchSecondCameraStatus(int, bool)));
	qRegisterMetaType<Mat>("Mat");
	connect(m_FirstCameraInfo.ImageCapture, SIGNAL(SendCameraImage(Mat,int)), this, SLOT(ReceiveCameraImage(Mat,int)));
	connect(m_SecondCameraInfo.ImageCapture, SIGNAL(SendCameraImage(Mat, int)), this, SLOT(ReceiveCameraImage(Mat, int)));

	//ReceivaAlgoImage
	connect(FirstRunAlgoCapture, SIGNAL(SendAlgoImage(int, Mat, Mat, int, bool)), this, SLOT(ReceivaAlgoImage(int, Mat , Mat, int, bool)));
	connect(SecondRunAlgoCapture, SIGNAL(SendAlgoImage(int, Mat, Mat, int, bool)), this, SLOT(ReceivaAlgoImage(int, Mat, Mat, int, bool)));

	//connect(m_FirstCameraInfo.ImageCapture, SIGNAL(SendLabelTypeData(QString)), this, SLOT(ReceiveLabelTypeData(vector<int>)));
	//connect(m_SecondCameraInfo.ImageCapture, SIGNAL(SendLabelTypeData(QString)), this, SLOT(ReceiveLabelTypeData(vector<int>)));

	connect(FirstRunAlgoCapture, SIGNAL(SendLabelType(QVariant)), this, SLOT(ReceiveLabelType(QVariant)), Qt::QueuedConnection);
	connect(SecondRunAlgoCapture, SIGNAL(SendLabelType(QVariant)), this, SLOT(ReceiveLabelType(QVariant)), Qt::QueuedConnection);

	connect(CSerialManager::GetInstance(), SIGNAL(SendConnectStatus(bool)), this, SLOT(ReceiveConnectStatus(bool)));


	connect(m_FirstCameraInfo.ImageCapture, SIGNAL(SendOriginalImage(Mat, Mat,int)), FirstRunAlgoCapture, SLOT(ReceivaOriginalImage( Mat, Mat,int)));
	connect(m_SecondCameraInfo.ImageCapture, SIGNAL(SendOriginalImage(Mat, Mat,int)), SecondRunAlgoCapture, SLOT(ReceivaOriginalImage( Mat, Mat,int)));
}

void CParameterSetting::InitCamera()
{
	qDebug() << "InitCameraInfos";
	printf("InitCameraInfos\n");
	memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE, &m_stDevList);
	if (MV_OK != nRet)
	{
		qDebug() << QString::fromLocal8Bit("枚举相机失败:") << nRet;
		printf("枚举相机失败\n");
		return;
	}
	ui.pushButton_OpenFirst->setEnabled(m_stDevList.nDeviceNum > 0);
	ui.pushButton_OpenSecond->setEnabled(m_stDevList.nDeviceNum > 0);
	for (int i = 0; i < m_stDevList.nDeviceNum; ++i)
	{
		MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
		char strUserName[256] = { 0 };
		sprintf_s(strUserName, "%s-%s_%s", pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName, pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
			pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
		QString UserName = QString::fromLocal8Bit(strUserName);
		ui.comboBox_First->addItem(UserName);
		ui.comboBox_Second->addItem(UserName);
		qDebug() << "CameraName;" << strUserName;
		printf("Find Camera:%s\n",strUserName);
	}
}

bool CParameterSetting::OpenCamera(MV_CC_DEVICE_INFO device_info,int index)
{
	qDebug() << "OpenCamera:"<<index;
	printf("open camere:%d\n",index);
	if (index == 1)
	{
		int nRet = m_FirstCameraInfo.CameraHandle.Open(&device_info);
		if (nRet != MV_OK)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("打开一工位相机失败:") + QString::number(nRet));
			return false;
		}
		else
		{
			unsigned int PackSize = 0;
			int nRet = m_FirstCameraInfo.CameraHandle.GetOptimalPacketSize(&PackSize);
			if (nRet == MV_OK)
			{
				m_FirstCameraInfo.CameraHandle.SetIntValue("GevSCPSPacketSize", PackSize);
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), "First Camera GevSCPSPacketSize Error:" + QString::number(nRet));
				return false;
			}
			nRet = m_FirstCameraInfo.CameraHandle.StartGrabbing();
			if (nRet != MV_OK)
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), "First Camera Start grabbing Error:" + QString::number(nRet));
				return false;
			}
			m_FirstCameraInfo.CameraHandle.SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);
			m_FirstCameraInfo.CameraHandle.SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_LINE0);
		}
	}
	else if (index == 2)
	{
		int nRet = m_SecondCameraInfo.CameraHandle.Open(&device_info);
		if (nRet != MV_OK)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("打开二工位相机失败:") + QString::number(nRet));
			return false;
		}
		else
		{
			unsigned int PackSize = 0;
			int nRet = m_SecondCameraInfo.CameraHandle.GetOptimalPacketSize(&PackSize);
			if (nRet == MV_OK)
			{
				m_SecondCameraInfo.CameraHandle.SetIntValue("GevSCPSPacketSize", PackSize);
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), "Second Camera GevSCPSPacketSize Error:" + QString::number(nRet));
				return false;
			}
			nRet = m_SecondCameraInfo.CameraHandle.StartGrabbing();
			if (nRet != MV_OK)
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), "Second Camera Start grabbing Error:" + QString::number(nRet));
				return false;
			}
			m_SecondCameraInfo.CameraHandle.SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);
			m_SecondCameraInfo.CameraHandle.SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_LINE0);
		}
	}
	return true;
}

bool CParameterSetting::CloseDevice(int index)
{
	qDebug() << "CloseDevice:" << index;
	printf("CloseDevice:%d\n", index);
	if (index == 1)
	{
		if (m_FirstCameraInfo.bOpenCamera)
		{
			qDebug() << "Close First Camera";
			printf("Close First Camera\n");
			m_FirstCameraInfo.ImageCapture->SetCameraStatus(false);
			int nRet = m_FirstCameraInfo.CameraHandle.StopGrabbing();
			if (nRet != MV_OK)
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), "Frist Camera StopGrabbing failed:" + QString::number(nRet));
				return false;
			}
			nRet = m_FirstCameraInfo.CameraHandle.Close();
			if (nRet == MV_OK)
			{
				m_FirstCameraInfo.bOpenCamera = false;
				return true;
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), "close first device failed:" + QString::number(nRet));
				return false;
			}
		}
	}
	else if (index == 2)
	{
		if (m_SecondCameraInfo.bOpenCamera)
		{
			qDebug() << "Close Second Camera";
			printf("Close Second Camera\n");
			m_SecondCameraInfo.ImageCapture->SetCameraStatus(false);
			int nRet = m_SecondCameraInfo.CameraHandle.StopGrabbing();
			if (nRet != MV_OK)
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), "Second Camera StopGrabbing failed:" + QString::number(nRet));
				return false;
			}
			nRet = m_SecondCameraInfo.CameraHandle.Close();
			if (nRet == MV_OK)
			{
				m_SecondCameraInfo.bOpenCamera = false;
				return true;
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), "close second device failed:" + QString::number(nRet));
				return false;
			}
		}
	}
	return true;
}


void CParameterSetting::OpenFirstCamera()
{
	qDebug() << "open first camera";
	printf("open first camera\n");
	QString name = ui.comboBox_First->currentText();
	int index = ui.comboBox_First->currentIndex();
	if (m_FirstCameraInfo.bOpenCamera)
	{
		bool rv = CloseDevice(1);
		if (!rv)
		{	
			return;
		}
		ui.pushButton_OpenFirst->setText(QString::fromLocal8Bit("打开相机"));
		SetButtonGroupEnabled(false, 1);
		ui.pushButton_SaveConfig->setEnabled(false);
		ui.pushButton_TriggerFirst->setEnabled(false);
		m_FirstCameraInfo.bOpenCamera = false;
		m_FirstCameraInfo.CameraName.clear();
	}
	else
	{
		if (name == m_SecondCameraInfo.CameraName)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("相机已被占用"));
			return;
		}
		else if (index <= m_stDevList.nDeviceNum)
		{
			QString errMsg;
			m_FirstCameraInfo.bOpenCamera = OpenCamera(*m_stDevList.pDeviceInfo[index],1);
			if (!m_FirstCameraInfo.bOpenCamera)
			{
				return;
			}
			m_FirstCameraInfo.ImageCapture->SetCameraHandle(m_FirstCameraInfo.CameraHandle,1);
			m_FirstCameraInfo.ImageCapture->SetCameraStatus(true);
			m_FirstCameraInfo.CameraName = name;
			SetButtonGroupEnabled(true, 1);
			ui.pushButton_SaveConfig->setEnabled(m_SecondCameraInfo.bOpenCamera);
			ui.radioButton_FreeFirst->setChecked(false);
			ui.radioButton_ExternalFirst->setChecked(true);
			ui.radioButton_SoftFirst->setChecked(false);
			ui.pushButton_TriggerFirst->setEnabled(false);
			ui.pushButton_OpenFirst->setText(QString::fromLocal8Bit("关闭相机"));
		}
	}
}

void CParameterSetting::OpenSecondCamera()
{
	qDebug() << "open second camera";
	printf("open second camera\n");
	QString name = ui.comboBox_Second->currentText();
	int index = ui.comboBox_Second->currentIndex();
	if (m_SecondCameraInfo.bOpenCamera)
	{
		bool rv = CloseDevice(2);
		if (!rv)
		{
			return;
		}
		ui.pushButton_OpenSecond->setText(QString::fromLocal8Bit("打开相机"));
		SetButtonGroupEnabled(false, 2);
		ui.pushButton_SaveConfig->setEnabled(false);
		ui.pushButton_TriggerSecond->setEnabled(false);
		m_SecondCameraInfo.bOpenCamera = false;
		m_SecondCameraInfo.CameraName.clear();
	}
	else
	{
		if (name == m_FirstCameraInfo.CameraName)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("相机已被占用"));
			return;
		}
		else if (index <= m_stDevList.nDeviceNum)
		{
			QString errMsg;
			m_SecondCameraInfo.bOpenCamera = OpenCamera(*m_stDevList.pDeviceInfo[index],2);
			if (!m_SecondCameraInfo.bOpenCamera)
			{
				return;
			}
			m_SecondCameraInfo.ImageCapture->SetCameraHandle(m_SecondCameraInfo.CameraHandle,2);
			m_SecondCameraInfo.ImageCapture->SetCameraStatus(true);
			m_SecondCameraInfo.CameraName = name;
			SetButtonGroupEnabled(true, 2);
			ui.pushButton_SaveConfig->setEnabled(m_FirstCameraInfo.bOpenCamera);
			ui.radioButton_FreeSecond->setChecked(false);
			ui.radioButton_ExternalSecond->setChecked(true);
			ui.radioButton_SoftSecond->setChecked(false);
			ui.pushButton_TriggerSecond->setEnabled(false);
			ui.pushButton_OpenSecond->setText(QString::fromLocal8Bit("关闭相机"));
		}
	}
}

void CParameterSetting::FirstSoftTriggerOnce()
{
	qDebug() << "FirstSoftTriggerOnce";
	printf("FirstSoftTriggerOnce\n");
	m_FirstCameraInfo.CameraHandle.CommandExecute("TriggerSoftware");
}

void CParameterSetting::SecondSoftTirggerOnce()
{
	qDebug() << "SecondSoftTirggerOnce";
	printf("SecondSoftTirggerOnce\n");
	m_SecondCameraInfo.CameraHandle.CommandExecute("TriggerSoftware");
}

void CParameterSetting::SwitchFirstCameraStatus(int index, bool checked)
{
	qDebug() << "SwitchFirstCameraStatus:" << index;
	printf("SwitchFirstCameraStatus:%d\n",index);
	if (checked)
	{
		ui.pushButton_TriggerFirst->setEnabled(false);
		switch (index)
		{
		case 1:
			m_FirstCameraInfo.CameraHandle.SetEnumValue("TriggerMode", MV_TRIGGER_MODE_OFF);
			break;
		case 2:
			m_FirstCameraInfo.CameraHandle.SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);
			m_FirstCameraInfo.CameraHandle.SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_LINE0);
			break;
		case 3:
			m_FirstCameraInfo.CameraHandle.SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);
			m_FirstCameraInfo.CameraHandle.SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
			ui.pushButton_TriggerFirst->setEnabled(true);
			break;
		}
	}
}

void CParameterSetting::SwitchSecondCameraStatus(int index, bool checked)
{
	qDebug() << "SwitchSecondCameraStatus:" << index;
	printf("SwitchSecondCameraStatus:%d\n", index);
	if (checked)
	{
		ui.pushButton_TriggerSecond->setEnabled(false);
		switch (index)
		{
		case 1:
			m_SecondCameraInfo.CameraHandle.SetEnumValue("TriggerMode", MV_TRIGGER_MODE_OFF);
			break;
		case 2:
			m_SecondCameraInfo.CameraHandle.SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);
			m_SecondCameraInfo.CameraHandle.SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_LINE0);
			break;
		case 3:
			m_SecondCameraInfo.CameraHandle.SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);
			m_SecondCameraInfo.CameraHandle.SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
			ui.pushButton_TriggerSecond->setEnabled(true);
			break;
		}
	}
}

void CParameterSetting::ReceiveConnectStatus(bool bConnected)
{
	QString style;
	m_bConnected = bConnected;
	if (bConnected)
	{
		style = "background-color: rgb(0, 170, 0);";
		ui.pushButton->setText(QString::fromLocal8Bit("关闭"));
		emit SendPlcStatus(m_green_SheetStyle);
	}
	else
	{
		style = "background-color: rgb(170, 0, 0);";
		ui.pushButton->setText(QString::fromLocal8Bit("打开"));
		emit SendPlcStatus(m_grey_SheetStyle);
	}
	ui.pushButton_SendOK->setEnabled(bConnected);
	ui.pushButton_SendNG->setEnabled(bConnected);
	ui.label_Status->setStyleSheet(style);
}

void CParameterSetting::OpenSerial()
{
	QString ComName = ui.comboBox_ComNames->currentText();
	int Heartbeat = ui.spinBox_Heartbeat->value();
	CSerialManager::GetInstance()->InitSerial(ComName, Heartbeat);
}

void CParameterSetting::SendOKToPLC()
{
	CSerialManager::GetInstance()->WritePLCData(true);
}

void CParameterSetting::SendNGToPLC()
{
	CSerialManager::GetInstance()->WritePLCData(false);
}

void CParameterSetting::SaveConfig()
{
	QString IniPath = QCoreApplication::applicationDirPath() + "/parameter_cfg.ini";
	CConfig *cfg = new CConfig(IniPath);
	if (m_FirstCameraInfo.bOpenCamera)
	{
		cfg->Write(CAMERA_SECTION, FIRST_CAMERA_NAME, m_FirstCameraInfo.CameraName);
	}
	if (m_SecondCameraInfo.bOpenCamera)
	{
		cfg->Write(CAMERA_SECTION, SECOND_CAMERA_NAME, m_SecondCameraInfo.CameraName);
	}
	int Distance = ui.spinBox_Distance->value();
	cfg->Write(CAMERA_SECTION, DISTANCE, Distance);

	bool bchecked = ui.checkBox_SaveNG->isChecked();
	cfg->Write(DATA_SECTION, SAVE_NG, bchecked);
	QString NGPath = ui.lineEdit_NGPath->text();
	if (bchecked && !NGPath.isEmpty())
	{
		cfg->Write(DATA_SECTION, NG_PATH, NGPath);
	}
	bchecked = ui.checkBox_SaveOK->isChecked();
	cfg->Write(DATA_SECTION, SAVE_OK, bchecked);
	QString OKPath = ui.lineEdit_OKPath->text();
	if (bchecked && !OKPath.isEmpty())
	{
		cfg->Write(DATA_SECTION, OK_PATH, OKPath);
	}

	bool bconnected = CSerialManager::GetInstance()->GetConnectStatus();
	cfg->Write(COMMUNICATION_SECTOIN, COM_STATUS, bconnected);
	if (bconnected)
	{
		QString Name = ui.comboBox_ComNames->currentText();
		int heartbeat = ui.spinBox_Heartbeat->value();
		cfg->Write(COMMUNICATION_SECTOIN, SERIAL_NAME, Name);
		cfg->Write(COMMUNICATION_SECTOIN, HEARTBEAT, heartbeat);
	}
	cfg->Write(FIRST_THRESHOLD, FIRST_AREA_THRESHOLD1, ui.spinBox_Area_canjiao->value());
	cfg->Write(FIRST_THRESHOLD, FIRST_AREA_THRESHOLD2, ui.spinBox_Area_huashang->value());
	cfg->Write(FIRST_THRESHOLD, FIRST_AREA_THRESHOLD3, ui.spinBox_Area_yajiaoshang->value());
	cfg->Write(FIRST_THRESHOLD, FIRST_AREA_THRESHOLD4, ui.spinBox_Area_zangwu->value());
	cfg->Write(FIRST_THRESHOLD, FIRST_WH_THRESHOLD6, ui.spinBox_Wh_canjiao->value());
	cfg->Write(FIRST_THRESHOLD, FIRST_WH_THRESHOLD7, ui.spinBox_Wh_huashang->value());
	cfg->Write(FIRST_THRESHOLD, FIRST_WH_THRESHOLD8, ui.spinBox_Wh_yajiaoshang->value());
	cfg->Write(FIRST_THRESHOLD, FIRST_WH_THRESHOLD9, ui.spinBox_Wh_zangwu->value());

	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD1, ui.spinBox_Area_quejijao->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD2, ui.spinBox_Area_maosi->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD3, ui.spinBox_Area_yiwu->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD4, ui.spinBox_Area_zangwu_2->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD5, ui.spinBox_Area_yashang->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD6, ui.spinBox_Area_shuikouchang->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD7, ui.spinBox_Area_qipao->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD8, ui.spinBox_Area_yajiaoshang_2->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD9, ui.spinBox_Area_duanjiezi->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD11, ui.spinBox_Wh_quejijao->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD12, ui.spinBox_Wh_maosi->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD13, ui.spinBox_Wh_yiwu->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD14, ui.spinBox_Wh_zangwu_2->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD15, ui.spinBox_Wh_yashang->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD16, ui.spinBox_Wh_shuikouchang->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD17, ui.spinBox_Wh_qipao->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD18, ui.spinBox_Wh_yajiaoshang_2->value());
	cfg->Write(SECOND_THRESHOLD, SECOND_WH_THRESHOLD19, ui.spinBox_Wh_duanjiezi->value());

	cfg->Write(DEGREE_THRESHOLD, DEGREE_Add, ui.spinBox_AddDegreeThreshold->value());
	cfg->Write(DEGREE_THRESHOLD, DEGREE_Sub, ui.spinBox_SubDegreeThreshold->value());



	delete cfg;
	cfg = NULL;
}

void CParameterSetting::LoadConfig()
{
	QString IniPath = QCoreApplication::applicationDirPath() + "/parameter_cfg.ini";
	QFileInfo info;
	if (info.exists(IniPath))
	{
		CConfig *cfg = new CConfig(IniPath);
		QString FirstCameraName = cfg->GetString(CAMERA_SECTION, FIRST_CAMERA_NAME);
		qDebug() << "load config first camera name:" << FirstCameraName;
		printf("load config first camera name:%s\n", FirstCameraName.toStdString().c_str());
		if (!FirstCameraName.isEmpty())
		{
			int index = ui.comboBox_First->findText(FirstCameraName);
			qDebug() << "first camera comboBox index:" << index;
			printf("first camera comboBox index:%d\n", index);
			if (index != -1)
			{
				ui.comboBox_First->setCurrentIndex(index);
				OpenFirstCamera();
			}
		}

		QString SecondCameraName = cfg->GetString(CAMERA_SECTION, SECOND_CAMERA_NAME);
		qDebug() << "load config second camera name:" << SecondCameraName;
		printf("load config second camera name:%s\n", SecondCameraName.toStdString().c_str());
		if (!SecondCameraName.isEmpty())
		{
			int index = ui.comboBox_Second->findText(SecondCameraName);
			qDebug() << "second camera comboBox index:" << index;
			printf("second camera comboBox index:%d\n", index);
			if (index != -1)
			{
				ui.comboBox_Second->setCurrentIndex(index);
				OpenSecondCamera();
			}
		}

		int Distance = cfg->GetInt(CAMERA_SECTION, DISTANCE);
		qDebug() << "load config distance:" << Distance;
		printf("load config distance:%d\n", Distance);
		ui.spinBox_Distance->setValue(Distance);

		bool rv = cfg->GetBool(COMMUNICATION_SECTOIN, COM_STATUS);
		qDebug() << "load config plc connected:" << rv;
		printf("load config plc connected:%d\n", Distance);
		if (rv)
		{
			QString ComName = cfg->GetString(COMMUNICATION_SECTOIN, SERIAL_NAME);
			qDebug() << "load config com name:" << ComName;
			printf("load config com name:%s\n", ComName.toStdString().c_str());
			int heartbeat = cfg->GetInt(COMMUNICATION_SECTOIN, HEARTBEAT);
			qDebug() << "load config heartbeat:" << heartbeat;
			printf("load config heartbeat:%d\n", heartbeat);
			ui.spinBox_Heartbeat->setValue(heartbeat);
			int index = ui.comboBox_ComNames->findText(ComName);
			if (index != -1)
			{
				ui.comboBox_ComNames->setCurrentText(ComName);
				OpenSerial();
			}
		}

		bool bSaveNG = cfg->GetBool(DATA_SECTION, SAVE_NG);
		qDebug() << "load config save ng:" << bSaveNG;
		printf("load config save ng:%d\n", bSaveNG);
		ui.checkBox_SaveNG->setChecked(bSaveNG);
		ui.pushButton_LoadNGPath->setEnabled(bSaveNG);
		if (bSaveNG)
		{
			QString NGPath = cfg->GetString(DATA_SECTION, NG_PATH);
			qDebug() << "load config save ng path:" << NGPath;
			printf("load config save ng path:%s\n", NGPath.toStdString().c_str());
			if (!NGPath.isEmpty())
			{
				ui.lineEdit_NGPath->setText(NGPath);
			}
		}

		bool bSaveOK = cfg->GetBool(DATA_SECTION, SAVE_OK);
		qDebug() << "load config save ok:" << bSaveOK;
		printf("load config save ok:%d\n", bSaveOK);
		ui.checkBox_SaveOK->setChecked(bSaveOK);
		ui.pushButton_LoadOKPath->setEnabled(bSaveOK);
		if (bSaveOK)
		{
			QString OKPath = cfg->GetString(DATA_SECTION, OK_PATH);
			qDebug() << "load config save ok path:" << OKPath;
			printf("load config save ok path:%s\n", OKPath.toStdString().c_str());
			if (!OKPath.isEmpty())
			{
				ui.lineEdit_OKPath->setText(OKPath);
			}
		}
		ui.spinBox_Area_canjiao->setValue(cfg->GetInt(FIRST_THRESHOLD, FIRST_AREA_THRESHOLD1));
		ui.spinBox_Area_huashang->setValue(cfg->GetInt(FIRST_THRESHOLD, FIRST_AREA_THRESHOLD2));
		ui.spinBox_Area_yajiaoshang->setValue(cfg->GetInt(FIRST_THRESHOLD, FIRST_AREA_THRESHOLD3));
		ui.spinBox_Area_zangwu->setValue(cfg->GetInt(FIRST_THRESHOLD, FIRST_AREA_THRESHOLD4));
		ui.spinBox_Wh_canjiao->setValue(cfg->GetInt(FIRST_THRESHOLD, FIRST_WH_THRESHOLD6));
		ui.spinBox_Wh_huashang->setValue(cfg->GetInt(FIRST_THRESHOLD, FIRST_WH_THRESHOLD7));
		ui.spinBox_Wh_yajiaoshang->setValue(cfg->GetInt(FIRST_THRESHOLD, FIRST_WH_THRESHOLD8));
		ui.spinBox_Wh_zangwu->setValue(cfg->GetInt(FIRST_THRESHOLD, FIRST_WH_THRESHOLD9));

		ui.spinBox_Area_quejijao->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD1));
		ui.spinBox_Area_maosi->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD2));
		ui.spinBox_Area_yiwu->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD3));
		ui.spinBox_Area_zangwu_2->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD4));
		ui.spinBox_Area_yashang->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD5));
		ui.spinBox_Area_shuikouchang->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD6));
		ui.spinBox_Area_qipao->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD7));
		ui.spinBox_Area_yajiaoshang_2->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD8));
		ui.spinBox_Area_duanjiezi->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_AREA_THRESHOLD9));
		ui.spinBox_Wh_quejijao->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD11));
		ui.spinBox_Wh_maosi->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD12));
		ui.spinBox_Wh_yiwu->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD13));
		ui.spinBox_Wh_zangwu_2->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD14));
		ui.spinBox_Wh_yashang->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD15));
		ui.spinBox_Wh_shuikouchang->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD16));
		ui.spinBox_Wh_qipao->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD17));
		ui.spinBox_Wh_yajiaoshang_2->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD18));
		ui.spinBox_Wh_duanjiezi->setValue(cfg->GetInt(SECOND_THRESHOLD, SECOND_WH_THRESHOLD19));

		ui.spinBox_AddDegreeThreshold->setValue(cfg->GetInt(DEGREE_THRESHOLD, DEGREE_Add));
		ui.spinBox_SubDegreeThreshold->setValue(cfg->GetInt(DEGREE_THRESHOLD, DEGREE_Sub));
	

	}
	else
	{
		qDebug() << IniPath << ",is not exist";
		printf("%s,is not exist\n",IniPath.toStdString().c_str());
	}

}

void CParameterSetting::SetSystemType(int index)
{
	ui.pushButton_LoadFirstImage->setEnabled(false);
	ui.pushButton_LoadSecondImage->setEnabled(false);
	s_SystemType type;
	if (index == 0)
	{
		type = RUN_ONLINE;
	}
	else if (index == 1)
	{
		type = CAMEREA_TEST;
	}
	else if (index == 2)
	{
		type = ONLINE_ALGO_TEST;
	}
	else if (index == 3)
	{
		type = OFFLINE_ALGO_TEST;
		ui.pushButton_LoadFirstImage->setEnabled(true);
		ui.pushButton_LoadSecondImage->setEnabled(true);
	}
	m_FirstCameraInfo.ImageCapture->SetSystemType(type);
	m_SecondCameraInfo.ImageCapture->SetSystemType(type);
}

void CParameterSetting::SetSaveNGChecked(bool checked)
{
	ui.pushButton_LoadNGPath->setEnabled(checked);
}

void CParameterSetting::SetSaveOKChecked(bool checked)
{
	ui.pushButton_LoadOKPath->setEnabled(checked);
}

void CParameterSetting::LoadNGPath()
{
	QString path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("NG图像保存路径"));
	if (path.isEmpty())
	{
		return;
	}
	ui.lineEdit_NGPath->setText(path);
	qDebug() << "browse first save ng path:" << path;
}

void CParameterSetting::LoadOKPath()
{
	QString path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("OK图像保存路径"));
	if (path.isEmpty())
	{
		return;
	}
	ui.lineEdit_OKPath->setText(path);
	qDebug() << "browse first save ok path:" << path;
}

void CParameterSetting::LoadFirstImage()
{
	if (m_bFirstAlgoSuccess)
	{	
		QString imagePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("图像文件"), "", "*.bmp;*.jpg;*.png;;All Files(*)");
		if (imagePath.isEmpty())
		{
			return;
		}
		qDebug() << "load first image:" << imagePath;
		QByteArray ba = imagePath.toLocal8Bit();
		char *file = ba.data();
		m_FirstOriginalImage = imread(file);
		s_AlgoRunData FirstAlgoRunData;
		FirstAlgoRunData.Time = 0;
		FirstAlgoRunData.bOK = true;
		AlgoRunData.Type = 3;
		vector<int>Threshold;
		m_FirstRenderImage.create(m_FirstOriginalImage.rows, m_FirstOriginalImage.cols, m_FirstOriginalImage.type());
		CAlgoFirstStation::GetInstance()->RunAlog(m_FirstOriginalImage, m_FirstRenderImage, m_FirstThreshold, Threshold,AlgoRunData);
		QVector<int> qVec = QVector<int>::fromStdVector(Threshold);

		emit SendLabelTypeData(qVec);
		QImage qImage;
		if (ui.checkBox_RenderFirst->isChecked())
		{
			qImage = MattoQImage(m_FirstRenderImage);
		}
		else
		{
			qImage = MattoQImage(m_FirstOriginalImage);
		}
		QString style;
		if (AlgoRunData.bOK)
		{
			style = "image: url(:/CMainWindow/Resources/OK.svg);";
		}
		else
		{
			style = "image: url(:/CMainWindow/Resources/NG.svg);";
		}
		ui.label_FirstTime->setText(QString::fromLocal8Bit("耗时:") + QString::number(AlgoRunData.Time) + "ms");
		ui.label_FirstResult->setStyleSheet(style);
		ui.label_FirstImage->SetImage(qImage);
	}
	else
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("工位1算法模型未初始化成功"));
	}
}

void CParameterSetting::LoadSecondImage()
{
	if (m_bSecondAlgoSuccess)
	{
		QString imagePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("图像文件"), "", "*.bmp;*.jpg;*.png;;All Files(*)");
		if (imagePath.isEmpty())
		{
			return;
		}
		qDebug() << "load second image:" << imagePath;
		QByteArray ba = imagePath.toLocal8Bit();
		char *file = ba.data();
		m_SecondOriginalImage = imread(file);
		s_AlgoRunData AlgoRunData;
		AlgoRunData.Time = 0;
		AlgoRunData.bOK = true;
		AlgoRunData.Type = 3;
		vector<int>SecondTreshold;
		AlgoRunData.Distance = ui.spinBox_Distance->value();
		m_SecondRenderImage.create(m_SecondOriginalImage.rows, m_SecondOriginalImage.cols, m_SecondOriginalImage.type());
		CAlgoSecondStation::GetInstance()->RunAlog(m_SecondOriginalImage, m_SecondRenderImage,m_SecondThreshold, m_DegreeThreshold, SecondTreshold, AlgoRunData);
		QVector<int> qVec = QVector<int>::fromStdVector(SecondTreshold);

		emit SendLabelTypeData(qVec);
		QImage qImage;
		if (ui.checkBox_RenderSecond->isChecked())
		{
			qImage = MattoQImage(m_SecondRenderImage);
		}
		else
		{
			qImage = MattoQImage(m_SecondOriginalImage);
		}
		QString style;
		if (AlgoRunData.bOK)
		{
			style = "image: url(:/CMainWindow/Resources/OK.svg);";
		}
		else
		{
			style = "image: url(:/CMainWindow/Resources/NG.svg);";
		}
		ui.label_SecondTime->setText(QString::fromLocal8Bit("耗时:") + QString::number(AlgoRunData.Time) + "ms");
		ui.label_SecondResult->setStyleSheet(style);
		ui.label_SecondImage->SetImage(qImage);
	}
	else
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("工位2算法模型未初始化成功"));
	}
}

QImage CParameterSetting::MattoQImage(Mat image)
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

void CParameterSetting::InitFirstThreshold()
{
	m_FirstThreshold.push_back(0);
	m_FirstThreshold.push_back(ui.spinBox_Area_huashang->value());
	m_FirstThreshold.push_back(ui.spinBox_Area_canjiao->value());
	m_FirstThreshold.push_back(ui.spinBox_Area_zangwu->value());
	m_FirstThreshold.push_back(ui.spinBox_Area_yajiaoshang->value());
	m_FirstThreshold.push_back(0);
	m_FirstThreshold.push_back(ui.spinBox_Wh_huashang->value());
	m_FirstThreshold.push_back(ui.spinBox_Wh_canjiao->value());
	m_FirstThreshold.push_back(ui.spinBox_Wh_zangwu->value());
	m_FirstThreshold.push_back(ui.spinBox_Wh_yajiaoshang->value());
}

void CParameterSetting::InitSecondThreshold()
{
	m_SecondThreshold.push_back(0);
	m_SecondThreshold.push_back(ui.spinBox_Area_quejijao->value());
	m_SecondThreshold.push_back(ui.spinBox_Area_maosi->value());
	m_SecondThreshold.push_back(ui.spinBox_Area_yiwu->value());
	m_SecondThreshold.push_back(ui.spinBox_Area_zangwu_2->value());
	m_SecondThreshold.push_back(ui.spinBox_Area_yashang->value());
	m_SecondThreshold.push_back(ui.spinBox_Area_shuikouchang->value());
	m_SecondThreshold.push_back(ui.spinBox_Area_qipao->value());
	m_SecondThreshold.push_back(ui.spinBox_Area_yajiaoshang_2->value());
	m_SecondThreshold.push_back(ui.spinBox_Area_duanjiezi->value());
	m_SecondThreshold.push_back(0);
	m_SecondThreshold.push_back(ui.spinBox_Wh_quejijao->value());
	m_SecondThreshold.push_back(ui.spinBox_Wh_maosi->value());
	m_SecondThreshold.push_back(ui.spinBox_Wh_yiwu->value());
	m_SecondThreshold.push_back(ui.spinBox_Wh_zangwu_2->value());
	m_SecondThreshold.push_back(ui.spinBox_Wh_yashang->value());
	m_SecondThreshold.push_back(ui.spinBox_Wh_shuikouchang->value());
	m_SecondThreshold.push_back(ui.spinBox_Wh_qipao->value());
	m_SecondThreshold.push_back(ui.spinBox_Wh_yajiaoshang_2->value());
	m_SecondThreshold.push_back(ui.spinBox_Wh_duanjiezi->value());
}

void CParameterSetting::InitDgreeThreshold()
{
	m_DegreeThreshold.AddDegree = ui.spinBox_AddDegreeThreshold->value();
	m_DegreeThreshold.SubDegree = ui.spinBox_SubDegreeThreshold->value();

}

void CParameterSetting::ReceiveCameraImage(Mat image, int index)
{
	QImage qimage = MattoQImage(image);
	if (index == 1)
	{
		ui.label_FirstImage->SetImage(qimage);
	}
	else if (index == 2)
	{
		ui.label_SecondImage->SetImage(qimage);
	}
}

void CParameterSetting::ShowFristRender(bool checked)
{
	QImage qimage;
	if (checked)
	{
		qimage = MattoQImage(m_FirstRenderImage);
	}
	else
	{
		qimage = MattoQImage(m_FirstOriginalImage);
	}
	ui.label_FirstImage->SetImage(qimage);
}

void CParameterSetting::ShowSecondRender(bool checked)
{
	QImage qimage;
	if (checked)
	{
		qimage = MattoQImage(m_SecondRenderImage);
	}
	else
	{
		qimage = MattoQImage(m_SecondOriginalImage);
	}
	ui.label_SecondImage->SetImage(qimage);
}

void CParameterSetting::ReceivaAlgoImage(int index, Mat OriginalImage, Mat RenderImage, int Time, bool bok)
{
	int type = ui.comboBox_SystemType->currentIndex();
	if (type == ONLINE_ALGO_TEST)
	{
		if (index == 1)
		{
			m_FirstOriginalImage = OriginalImage;//.clone();
			m_FirstRenderImage = RenderImage;//.clone();
			bool checked = ui.checkBox_RenderFirst->isChecked();
			QImage qimage;
			QString style;
			if (checked)
			{
				qimage = MattoQImage(m_FirstRenderImage);
			}
			else
			{
				qimage = MattoQImage(m_FirstOriginalImage);
			}
			if (bok)
			{
				style = "image: url(:/CMainWindow/Resources/OK.svg);";
			}
			else
			{
				style = "image: url(:/CMainWindow/Resources/NG.svg);";
			}
			ui.label_FirstTime->setText(QString::fromLocal8Bit("耗时:") + QString::number(Time) + "ms");
			ui.label_FirstResult->setStyleSheet(style);
			ui.label_FirstImage->SetImage(qimage);
		}
		else if (index == 2)
		{
			m_SecondOriginalImage = OriginalImage;//.clone();
			m_SecondRenderImage = RenderImage;// .clone();
			bool checked = ui.checkBox_RenderSecond->isChecked();
			QImage qimage;
			QString style;
			if (checked)
			{
				qimage = MattoQImage(m_SecondRenderImage);
			}
			else
			{
				qimage = MattoQImage(m_SecondOriginalImage);
			}
			if (bok)
			{
				style = "image: url(:/CMainWindow/Resources/OK.svg);";
			}
			else
			{
				style = "image: url(:/CMainWindow/Resources/NG.svg);";
			}
			ui.label_SecondTime->setText(QString::fromLocal8Bit("耗时:") + QString::number(Time) + "ms");
			ui.label_SecondResult->setStyleSheet(style);
			ui.label_SecondImage->SetImage(qimage);
		}
	}
	else if (type == RUN_ONLINE)
	{
		emit SendAlgoImage(index, OriginalImage, RenderImage, Time, bok);
	}
}

void CParameterSetting::ReceiveLabelTypeData(QVector<int> LabelType)
{
	//QVector<int>vRow = LabelType.value<QVector<int>>();
	//emit SendLabelTypeData(LabelType);
}

void CParameterSetting::CopyRegisterCode()
{
	QString MachineCode = ui.lineEdit_MachineCode->text();
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(MachineCode);
}

void CParameterSetting::SoftwareRegister()
{
	QString RegisterCode = ui.lineEdit_RegisterCode->text();
	if (RegisterCode.isEmpty())
	{
		QMessageBox::information(this, "hints", "registration code is empty");
		return;
	}
	QString LicenseTime;
	bool rv = CSoftwareRegister::GetInstance()->Register(RegisterCode, LicenseTime);
	if (rv)
	{
		ui.label_RegisterInfo->setText(QString::fromLocal8Bit("到期时间:") + LicenseTime);
	}
	else
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("注册失败"));
		return;
	}
}

void CParameterSetting::SetFirstThreshold()
{

	QString m_ObjectName = sender()->objectName();	
	if (m_ObjectName == "spinBox_Area_canjiao")
	{
		m_FirstThreshold[1] = ui.spinBox_Area_canjiao->value();
	}
	else if (m_ObjectName == "spinBox_Area_huashang")
	{
		m_FirstThreshold[2] = ui.spinBox_Area_huashang->value();
	}
	else if (m_ObjectName == "spinBox_Area_yajiaoshang")
	{
		m_FirstThreshold[3] = ui.spinBox_Area_yajiaoshang->value();
	}
	else if (m_ObjectName == "spinBox_Area_zangwu")
	{
		m_FirstThreshold[4] = ui.spinBox_Area_zangwu->value();
	}
	else if (m_ObjectName == "spinBox_Wh_canjiao")
	{
		m_FirstThreshold[6] = ui.spinBox_Wh_canjiao->value();
	}
	else if (m_ObjectName == "spinBox_Wh_huashang")
	{
		m_FirstThreshold[7] = ui.spinBox_Wh_huashang->value();
	}
	else if (m_ObjectName == "spinBox_Wh_yajiaoshang")
	{
		m_FirstThreshold[8] = ui.spinBox_Wh_yajiaoshang->value();
	}
	else if (m_ObjectName == "spinBox_Wh_zangwu")
	{
		m_FirstThreshold[9] = ui.spinBox_Wh_zangwu->value();
	}
	else
	{
		qDebug() << "spinBox Error";
	}

}

void CParameterSetting::SetSecondThreshold()
{
	QString m_ObjectName = sender()->objectName();
	if (m_ObjectName == "spinBox_Area_quejijao")
	{
		m_SecondThreshold[1] = ui.spinBox_Area_quejijao->value();
	}
	else if (m_ObjectName == "spinBox_Area_maosi")
	{
		m_SecondThreshold[2] = ui.spinBox_Area_maosi->value();
	}
	else if (m_ObjectName == "spinBox_Area_yiwu")
	{
		m_SecondThreshold[3] = ui.spinBox_Area_yiwu->value();
	}
	else if (m_ObjectName == "spinBox_Area_zangwu_2")
	{
		m_SecondThreshold[4] = ui.spinBox_Area_zangwu_2->value();
	}
	else if (m_ObjectName == "spinBox_Area_yashang")
	{
		m_SecondThreshold[5] = ui.spinBox_Area_yashang->value();
	}
	else if (m_ObjectName == "spinBox_Area_shuikouchang")
	{
		m_SecondThreshold[6] = ui.spinBox_Area_shuikouchang->value();
	}
	else if (m_ObjectName == "spinBox_Area_qipao")
	{
		m_SecondThreshold[7] = ui.spinBox_Area_qipao->value();
	}
	else if (m_ObjectName == "spinBox_Area_yajiaoshang_2")
	{
		m_SecondThreshold[8] = ui.spinBox_Area_yajiaoshang_2->value();
	}
	else if (m_ObjectName == "spinBox_Area_duanjiezi")
	{
		m_SecondThreshold[9] = ui.spinBox_Area_duanjiezi->value();
	}
	else if (m_ObjectName == "spinBox_Wh_quejijao")
	{
		m_SecondThreshold[11] = ui.spinBox_Wh_quejijao->value();
	}
	else if (m_ObjectName == "spinBox_Wh_maosi")
	{
		m_SecondThreshold[12] = ui.spinBox_Wh_maosi->value();
	}
	else if (m_ObjectName == "spinBox_Wh_yiwu")
	{
		m_SecondThreshold[13] = ui.spinBox_Wh_yiwu->value();
	}
	else if (m_ObjectName == "spinBox_Wh_zangwu_2")
	{
		m_SecondThreshold[14] = ui.spinBox_Wh_zangwu_2->value();
	}
	else if (m_ObjectName == "spinBox_Wh_yashang")
	{
		m_SecondThreshold[15] = ui.spinBox_Wh_yashang->value();
	}
	else if (m_ObjectName == "spinBox_Wh_shuikouchang")
	{
		m_SecondThreshold[16] = ui.spinBox_Wh_shuikouchang->value();
	}
	else if (m_ObjectName == "spinBox_Wh_qipao")
	{
		m_SecondThreshold[17] = ui.spinBox_Wh_qipao->value();
	}
	else if (m_ObjectName == "spinBox_Wh_yajiaoshang_2")
	{
		m_SecondThreshold[18] = ui.spinBox_Wh_yajiaoshang_2->value();
	}
	else if (m_ObjectName == "spinBox_Wh_duanjiezi")
	{
		m_SecondThreshold[19] = ui.spinBox_Wh_duanjiezi->value();
	}
	else
	{
		qDebug() << "spinBox Error";
	}
}

void CParameterSetting::SetDegreeThreshold()
{
	QString m_ObjectName = sender()->objectName();
	if (m_ObjectName == "spinBox_AddDegreeThreshold")
	{
		m_DegreeThreshold.AddDegree = ui.spinBox_AddDegreeThreshold->value();
	}
	else if (m_ObjectName == "spinBox_SubDegreeThreshold")
	{
		m_DegreeThreshold.SubDegree = ui.spinBox_SubDegreeThreshold->value();
	}
	else
	{
		qDebug() << "spinBox Error";
	}

}

void CParameterSetting::ReceiveLabelType(QVariant vRowInfo)
{
	QVector<int>vRow = vRowInfo.value<QVector<int>>();
	emit SendLabelTypeData(vRow);
}

void CParameterSetting::SaveImage(s_SaveImageInfo ImageInfo)
{
	QString CurTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz");
	if (ui.checkBox_SaveNG->isChecked())
	{
		QString NGPath = ui.lineEdit_NGPath->text();
		if (NGPath.isEmpty())
		{
			qDebug() << "NG path is empty";
			return;
		}
		QString CurPath = NGPath + "/" + CurTime;
		QDir dir;
		if (!dir.exists(CurPath))
		{
			dir.mkpath(CurPath);
		}
		if (!ImageInfo.FirstStation.bok)
		{
			QString OriginalImageName = CurPath + "/1_O.bmp";
			//QString RenderImageName = CurPath + "/1_R.jpg";
			m_SaveImage.SaveImage(OriginalImageName, ImageInfo.FirstStation.OriginalImage);
			//m_SaveImage.SaveImage(RenderImageName, ImageInfo.FirstStation.RenderImage);
		}
		if (!ImageInfo.SecondStation.bok)
		{
			QString OriginalImageName = CurPath + "/2_O.bmp";
			//QString RenderImageName = CurPath + "/2_R.jpg";
			m_SaveImage.SaveImage(OriginalImageName, ImageInfo.SecondStation.OriginalImage);
			//m_SaveImage.SaveImage(RenderImageName, ImageInfo.SecondStation.RenderImage);
		}
	}

	if (ui.checkBox_SaveOK->isChecked())
	{
		QString OKPath = ui.lineEdit_OKPath->text();
		if (OKPath.isEmpty())
		{
			qDebug() << "OK path is empty";
			return;
		}
		QString CurPath = OKPath + "/" + CurTime;
		QDir dir;
		if (!dir.exists(CurPath))
		{
			dir.mkpath(CurPath);
		}
		if (ImageInfo.FirstStation.bok)
		{
			QString ImageName = CurPath + "/1_O.jpg";
			m_SaveImage.SaveImage(ImageName, ImageInfo.FirstStation.OriginalImage);
		}
		if (ImageInfo.SecondStation.bok)
		{
			QString ImageName = CurPath + "/2_O.jpg";
			m_SaveImage.SaveImage(ImageName, ImageInfo.SecondStation.OriginalImage);
		}
	}
}

void CParameterSetting::SendPLCResult(bool bok)
{
	qDebug() << "CParameterSetting:" << bok;
	if (CSerialManager::GetInstance()->GetConnectStatus())
	{
		CSerialManager::GetInstance()->WritePLCData(bok);
	}
}

void CParameterSetting::SetHeartbeatStatus(bool bSend)
{

}

void CParameterSetting::GetConnected()
{
	if (m_bConnected)
	{
		emit SendPlcStatus(m_green_SheetStyle);
	}
	else
	{
		emit SendPlcStatus(m_grey_SheetStyle);
	}

}
