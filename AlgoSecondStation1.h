#pragma once
#include "QObject"
#include "pianwei_location.h"
#include "normal_segmentation.h"

using namespace std;
using namespace cv;
using namespace smartmore;

class CAlgoSecondStation
{
public:
	static CAlgoSecondStation *GetInstance();
	bool InitAlgo(QString &errMsg);
	void RunAlog(Mat Image, int distance, Mat &RenderImage, bool &bOK, int &Time);
private:
	CAlgoSecondStation();
	~CAlgoSecondStation();
	class GarbageCollection
	{
	public:
		~GarbageCollection()
		{
			if (CAlgoSecondStation::m_Instance)
			{
				delete CAlgoSecondStation::m_Instance;
				CAlgoSecondStation::m_Instance = NULL;
			}
		}
	};
private:
	static CAlgoSecondStation *m_Instance;
	static GarbageCollection m_Collection;
	PianweiCircleLocation m_Circle;
	MesonNormalSegmentation m_Segment;
	bool m_bInitCircleSuccess;
	bool m_bInitSegmentSuccess;
};
