#pragma once
#include "QObject"
#include "zrise_vimo_segmentation_module.h"

using namespace std;
using namespace cv;
using namespace smartmore;

typedef struct
{
	float AddDegree;
	float SubDegree;
}s_Degree;


typedef struct
{
	int Distance;
	bool bOK;
	int Time;
	int Type;
}s_AlgoRunData;

class CAlgoSecondStation
{
public:
	static CAlgoSecondStation *GetInstance();
	bool InitAlgo(QString &errMsg);
	void RunAlog(Mat Image, Mat &RenderImage,vector<int> &m_SecondThreshold, s_Degree Degree, vector<int> &SecondThreshold, s_AlgoRunData &AlgoRunData);
	void SetSecondLabelData(Mat Image, Mat &RenderImage);
	void SaveImage(Mat Image,int Index);
	int SecondIndex = 0;

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
	smartmore::ZriseVimoSegmentationModule module;
};
