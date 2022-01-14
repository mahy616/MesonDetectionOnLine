#pragma once
#include "QObject"
#include "highlight_segmentation.h"

using namespace std;
using namespace cv;
using namespace smartmore;

class CAlgoFirstStation
{
public:
	static CAlgoFirstStation *GetInstance();
	bool InitAlgo(QString &errMsg);
	void RunAlog(Mat Image, Mat &RenderImage, bool &bOK, int &Time);
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
	MesonHighlightSegmentation m_Segment;
	bool m_bInitSegmentSuccess;
};
