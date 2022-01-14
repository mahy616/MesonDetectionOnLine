#include "RunAlgo.h"
#include <QDebug>


CRunAlgo::CRunAlgo(QThread *parent)
	:QThread(parent)
{
	m_bStop = false;
	//CAlgoFirstStation::GetInstance()->RunAlog(curImage, RenderImage, m_RunFirstThreshold, FirstThreshold, AlgoRunData);
}

CRunAlgo::~CRunAlgo()
{

}


void CRunAlgo::run()
{
	while (!m_bStop)
	{
		if (vtOriginalImage.size() == 0)
		{
			Sleep(10);
		}
		s_AlgoRunData AlgoRunData;
		AlgoRunData.Time = 0;
		AlgoRunData.bOK = true;
		AlgoRunData.Distance = m_Distance;
		AlgoRunData.Type = 0;
		Mat RenderImage;
		Mat curImage;
		m_Index = Index;
		if (vtOriginalImage.size() > 0)
		{
			m_Mutex.lock();
			curImage = vtOriginalImage.dequeue();
			m_Mutex.unlock();
		}
		else
		{
			continue;
		}
	
		if (m_Index == 1)
		{
			CAlgoFirstStation::GetInstance()->RunAlog(curImage, RenderImage, m_RunFirstThreshold, FirstThreshold, AlgoRunData);
			qDebug() << "RunAlog Success 1";
			QVariant DataVar;
			QVector<int> qVec = QVector<int>::fromStdVector(FirstThreshold);
			DataVar.setValue(qVec);
			emit SendLabelType(DataVar);
			FirstThreshold.clear();
		}
		else if(m_Index == 2)
		{
			CAlgoSecondStation::GetInstance()->RunAlog(curImage, RenderImage, m_RunSecondThreshold, m_DegreeThreshold, SecondThreshold, AlgoRunData);
			qDebug() << "RunAlog Success 2";
			QVariant DataVar;
			QVector<int> qVec = QVector<int>::fromStdVector(SecondThreshold);
			DataVar.setValue(qVec);
			emit SendLabelType(DataVar);
			SecondThreshold.clear();
		}

		emit SendAlgoImage(m_Index, curImage, RenderImage, AlgoRunData.Time, AlgoRunData.bOK);
	
		Mat Render;
		//emit SendPorcessResult(ImageInfo.Image, Render, ImageInfo.ImageID);
	}
}

void CRunAlgo::StopThread()
{
	m_Mutex.lock();
	m_bStop = true;
	m_Mutex.unlock();
}

void CRunAlgo::SetRunFirstThreshold(vector<int> RunFirstThreshold)
{
	m_Mutex.lock();
	m_RunFirstThreshold = RunFirstThreshold;
	m_Mutex.unlock();
}

void CRunAlgo::SetRunSecondThreshold(vector<int> RunSecondThreshold)
{
	m_Mutex.lock();
	m_RunSecondThreshold = RunSecondThreshold;
	m_Mutex.unlock();
}

void CRunAlgo::SetRunDegreeThreshold(s_Degree DegreeThreshold)
{
	m_Mutex.lock();
	m_DegreeThreshold = DegreeThreshold;
	m_Mutex.unlock();
}

void CRunAlgo::SetDegree(s_Degree Degree)
{
	m_Mutex.lock();
	m_DegreeThreshold = Degree;
	m_Mutex.unlock();
}

void CRunAlgo::SetRunStatus(int distance)
{
	m_Mutex.lock();
	m_Distance = distance;
	m_Mutex.unlock();
}

void CRunAlgo::ReceivaOriginalImage( Mat OriginalImage, Mat RenderImage,int AlgoIndex)
{
	m_Mutex.lock();
	Index = AlgoIndex;
	vtOriginalImage.push_back(OriginalImage);
	m_Mutex.unlock();
}
