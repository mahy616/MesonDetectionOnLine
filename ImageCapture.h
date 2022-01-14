#pragma once
#include <QThread>
#include "windows.h"
#include <QMutex>
#include "MvCamera.h"
#include "opencv2/opencv.hpp"
#include "qdebug.h"
#include "AlgoFirstStation.h"
#include "AlgoSecondStation.h"
#include <QVector>
#include <QMetaType>
#include <QVariant>
Q_DECLARE_METATYPE(QVector<int>);
#define DEBUG_FLAG

using namespace std;
using namespace cv;

typedef enum
{
	RUN_ONLINE,  //�������У����㷨��ͳ�ƽ����PLCͨѶ
	CAMEREA_TEST, //������ԣ���ʾ���ͼ�񣬲����㷨
	ONLINE_ALGO_TEST, //���߲����㷨�������ͼ�����㷨����ʾ���
	OFFLINE_ALGO_TEST //��������ͼ�����㷨����ʾ���
}s_SystemType;

class CImageCapture :public QThread
{
	Q_OBJECT
public:
	CImageCapture(QThread *parent = NULL);
	~CImageCapture();
	bool SetCameraHandle(CMvCamera &camera,int index); 
	void SetCameraStatus(bool bOpen);
	//void SetDegree(s_Degree Degree);
	void SetSystemType(s_SystemType type);
	void SetRunStatus(bool bStart, int distance= 7);
	void StopThread();
	//void SetRunFirstThreshold(vector<int>RunFirstThreshold);
	//void SetRunSecondThreshold(vector<int>RunSecondThreshold);
	//void SetRunDegreeThreshold(s_Degree DegreeThreshold);
private:
	CMvCamera m_MvCamera;
	QMutex m_Mutex;
	bool m_bStop;
	bool m_bOpen;
	bool m_bStartRun;
	int m_Index;
	s_SystemType m_Type;
	int m_Distance;
	unsigned char*  m_pGrabBuf;
	unsigned int nDataSize;
	vector<int>m_RunFirstThreshold;
	vector<int>m_RunSecondThreshold;
	vector<int>FirstThreshold;
	vector<int>SecondThreshold;
	s_Degree m_DegreeThreshold;
	//s_AlgoRunData FirstAlgoRunData;
private:
	void run();
	Mat Convert2Mat(MV_FRAME_OUT_INFO_EX* pstImageInfo, unsigned char * pData);
signals:
	void SendCameraImage(Mat image, int index);
	void SendAlgoImage(int index, Mat OriginalImage, Mat RenderImage, int Time, bool bok);
	void SendLabelTypeData(QVector<int>LabelType);
	void SendLabelType(QVariant);
	void SendOriginalImage(Mat OriginalImage, Mat RenderImage,int index);
};
