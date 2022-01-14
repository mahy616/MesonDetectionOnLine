#pragma once
#include "ui_ParameterSetting.h"
#include "ImageCapture.h"
#include "QButtonGroup"
#include "SaveImage.h"
#include "SerialManager.h"
#include "SoftwareRegister.h"
#include <vector>
#include "RunAlgo.h"
typedef struct
{
	QString CameraName;
	CMvCamera CameraHandle;
	bool bOpenCamera;
	CImageCapture *ImageCapture;
	void Init()
	{
		CameraName.clear();
		bOpenCamera = false;
		ImageCapture = new CImageCapture();

	}
}s_CameraInfo;

typedef struct
{
	Mat OriginalImage;
	Mat RenderImage;
	bool bok;
}s_StationInfo;

typedef struct
{
	s_StationInfo FirstStation;
	s_StationInfo SecondStation;
}s_SaveImageInfo;



class CParameterSetting :public QDialog
{
	Q_OBJECT
public:
	CParameterSetting(QDialog *parent = NULL);
	~CParameterSetting();
	e_CheckType CheckPermission();
	bool CheckEnv(QString &errMsg);
	void StartDetecion(bool bStart);
	void SaveImage(s_SaveImageInfo ImageInfo);
	void LoadConfig();
	void SendPLCResult(bool bok);
	void SetHeartbeatStatus(bool bSend);
	void GetConnected();
private:
	void InitVariables();
	void InitConnections();
	void InitCamera();
	void SetButtonGroupEnabled(bool enabled, int index);
	bool OpenCamera(MV_CC_DEVICE_INFO device_info, int index);
	bool CloseDevice(int index);
	QImage MattoQImage(Mat image);
	void InitFirstThreshold();
	void InitSecondThreshold();
	void InitDgreeThreshold();
private:
	Ui::DialogSetting ui;
	MV_CC_DEVICE_INFO_LIST m_stDevList;
	//一工位参数
	s_CameraInfo m_FirstCameraInfo;

	QButtonGroup *m_FirstGroup;
	//二工位参数
	s_CameraInfo m_SecondCameraInfo;
	QButtonGroup *m_SecondGroup;
	Mat m_FirstOriginalImage;
	Mat m_FirstRenderImage;
	Mat m_SecondOriginalImage;
	Mat m_SecondRenderImage;
	bool m_bFirstAlgoSuccess;
	bool m_bSecondAlgoSuccess;
	CSaveImage m_SaveImage;
	//QVector<int>m_FirstThreshold;
	vector<int>m_FirstThreshold;
	vector<int>m_SecondThreshold;
	s_Degree m_DegreeThreshold;
	s_AlgoRunData AlgoRunData;

	CRunAlgo *FirstRunAlgoCapture;
	CRunAlgo *SecondRunAlgoCapture;
	bool m_bConnected;
private slots:
	void OpenFirstCamera();
	void OpenSecondCamera();
	void FirstSoftTriggerOnce();
	void SecondSoftTirggerOnce();
	void SwitchFirstCameraStatus(int index, bool checked);
	void SwitchSecondCameraStatus(int index, bool checked);
	void ReceiveConnectStatus(bool bConnected);
	void OpenSerial();
	void SendOKToPLC();
	void SendNGToPLC();
	void SaveConfig();
	void SetSystemType(int index);

	void SetSaveNGChecked(bool checked);
	void SetSaveOKChecked(bool checked);
	void LoadNGPath();
	void LoadOKPath();

	void LoadFirstImage();
	void LoadSecondImage();

	void ShowFristRender(bool checked);
	void ShowSecondRender(bool checked);

	void ReceiveCameraImage(Mat image, int index);
	void ReceivaAlgoImage(int index, Mat OriginalImage, Mat RenderImage, int Time, bool bok);
	void ReceiveLabelTypeData(QVector<int>LabelType);

	void CopyRegisterCode();
	void SoftwareRegister();
	void SetFirstThreshold();
	void SetSecondThreshold();
	void SetDegreeThreshold();
	void ReceiveLabelType(QVariant vRowInfo);
	
signals:
	void SendAlgoImage(int index, Mat OriginalImage, Mat RenderImage, int Time, bool bok);

	void SendLabelTypeData(QVector<int>LabelType);

	void SendPlcStatus(QString style);
	
};
