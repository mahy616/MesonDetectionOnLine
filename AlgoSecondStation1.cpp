#include "AlgoSecondStation.h"
#include "QTextCodec"
#include "QFileInfo"
#include "QTime"
#include "QCoreApplication"

CAlgoSecondStation *CAlgoSecondStation::m_Instance = NULL;
CAlgoSecondStation::GarbageCollection CAlgoSecondStation::m_Collection;

CAlgoSecondStation::CAlgoSecondStation()
{
}

CAlgoSecondStation::~CAlgoSecondStation()
{
}

CAlgoSecondStation *CAlgoSecondStation::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CAlgoSecondStation();
	}
	return m_Instance;
}

bool CAlgoSecondStation::InitAlgo(QString &errMsg)
{
	QTextCodec *gbk_code = QTextCodec::codecForName("GBK");
	QString CircleModel = QCoreApplication::applicationDirPath() + "/models/NORMAL_C06.smartmore";
	QString CricleJson = QCoreApplication::applicationDirPath() + "/models/normal_model.json";
	std::string modelpath = std::string(gbk_code->fromUnicode(CircleModel).data());
	std::string jsonpath = std::string(gbk_code->fromUnicode(CricleJson).data());

	ResultCode code = m_Circle.Init(modelpath, jsonpath, 1, 0, spdlog::level::trace);
	if (code != smartmore::ResultCode::Success)
	{
		errMsg = QString::fromLocal8Bit("工位2初始化偏位模型失败:") + QString::number((int)code);
		return false;
	}

	QString SegmentModel = QCoreApplication::applicationDirPath() + "/models/NORMAL_E51.smartmore";
	modelpath = std::string(gbk_code->fromUnicode(SegmentModel).data());

	code = m_Segment.Init(modelpath, jsonpath, 1, 0, spdlog::level::trace);
	if (code != smartmore::ResultCode::Success)
	{
		errMsg = QString::fromLocal8Bit("工位2初始化Normal模型失败:") + QString::number((int)code);
		return false;
	}
	else if (code == smartmore::ResultCode::Success)
	{
		return true;
	}
	return true;
}

void CAlgoSecondStation::RunAlog(Mat Image, int distance, Mat &RenderImage, bool &bOK, int &Time)
{
	bool bAllOK = true;
	int iDistance = distance;
	smartmore::circleRequest circleReq = { Image };
	smartmore::circleResponse circleRsp;
	QTime time;
	time.start();
	smartmore::ResultCode circleRet = m_Circle.Run(circleReq, circleRsp);
	if (circleRet != smartmore::ResultCode::Success)
	{
		bAllOK = false;
		std::cout << "Position1 Circle run Failure." << std::endl;
	}

	if (circleRsp.outer_circle.radius == 0)
	{
		bAllOK &= false;
		cv::putText(circleRsp.colorMap, "can't find outer circle", cv::Point(Image.cols / 2, 30),
			cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 255, 0), 3);
	}
	else if (circleRsp.inner_circle.radius == 0)
	{
		bAllOK &= false;
		cv::putText(circleRsp.colorMap, "can't find inner circle", cv::Point(Image.cols / 2, 70),
			cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 255, 0), 3);
	}

	int dis = sqrt(pow(circleRsp.outer_circle.x - circleRsp.inner_circle.x, 2)
		+ pow(circleRsp.outer_circle.y - circleRsp.inner_circle.y, 2));
	if (dis > iDistance)
	{
		bAllOK &= false;
	}
	smartmore::MesonNormalSegRequest segReq = { circleRsp.outer_circle.x, circleRsp.outer_circle.y, (int)circleRsp.outer_circle.radius, Image };
	smartmore::MesonNormalSegResponse segRsp;
	smartmore::ResultCode segRet = m_Segment.Run(segReq, segRsp);
	if (segRet != smartmore::ResultCode::Success)
	{
		std::cout << "Position1 Normal run Failure." << std::endl;
	}
	m_Circle.drawDebugGraph(circleRsp.colorMap);
	m_Segment.drawDebugGraph(circleRsp.colorMap);
	RenderImage = circleRsp.colorMap;
	bOK = segRsp.isOK &= bAllOK;
	Time = time.elapsed();
}