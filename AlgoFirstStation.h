#pragma once
#include "QObject"
#include "zrise_vimo_segmentation_module.h"
#include "AlgoSecondStation.h"
using namespace std;
using namespace cv;
using namespace smartmore;

class CAlgoFirstStation
{
public:
	static CAlgoFirstStation *GetInstance();
	bool InitAlgo(QString &errMsg);
	void RunAlog(Mat Image, Mat &RenderImage, vector<int> &m_Firsthreshold, vector<int> &Threshold, s_AlgoRunData &AlgoRunData);
	void SetFirstLabelData(Mat Image, Mat &RenderImage);
private:
	CAlgoFirstStation();
	~CAlgoFirstStation();
	class GarbageCollection
	{
	public:
		~GarbageCollection()
		{
			if (CAlgoFirstStation::m_Instance)
			{
				delete CAlgoFirstStation::m_Instance;
				CAlgoFirstStation::m_Instance = NULL;
			}
		}
	};
private:
	static CAlgoFirstStation *m_Instance;
	static GarbageCollection m_Collection;
	smartmore::ZriseVimoSegmentationModule module;
	bool m_bInitSegmentSuccess;
public:
	int FirstIndex = 0;
	CAlgoSecondStation *FirstSaveImage;
};
