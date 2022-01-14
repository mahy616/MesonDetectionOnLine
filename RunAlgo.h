#pragma once
#include <QThread>
#include "windows.h"
#include <QMutex>
#include "opencv2/opencv.hpp"
#include "QQueue"
#include "AlgoFirstStation.h"
#include "AlgoSecondStation.h"
#include <QVariant>
using namespace std;
using namespace cv;

class CRunAlgo :public QThread
{
	Q_OBJECT
public:
	CRunAlgo(QThread *parent = NULL);
	~CRunAlgo();
	//void RunAlgo(int index, Mat OriginalImage, Mat RenderImage, int Time, bool bok);
private:
	void run();
	bool m_bStop;
	QQueue<Mat>vtOriginalImage;
	QMutex m_Mutex;
	int m_Index;
	int m_Distance;
	int Index;
	vector<int>m_RunFirstThreshold;
	vector<int>m_RunSecondThreshold;
	vector<int>FirstThreshold;
	vector<int>SecondThreshold;
	s_Degree m_DegreeThreshold;

public:
	void StopThread();
	void SetRunFirstThreshold(vector<int>RunFirstThreshold);
	void SetRunSecondThreshold(vector<int>RunSecondThreshold);
	void SetRunDegreeThreshold(s_Degree DegreeThreshold);
	void SetDegree(s_Degree Degree);
	void SetRunStatus(int distance);
signals:
	void SendAlgoImage(int index, Mat OriginalImage, Mat RenderImage, int Time, bool bok);
	void SendLabelType(QVariant);
private slots:
	void ReceivaOriginalImage( Mat OriginalImage, Mat RenderImage, int AlgoIndex);


};