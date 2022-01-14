#include "AlgoFirstStation.h"
#include "QTextCodec"
#include "QFileInfo"
#include "QTime"
#include "QCoreApplication"

CAlgoFirstStation *CAlgoFirstStation::m_Instance = NULL;
CAlgoFirstStation::GarbageCollection CAlgoFirstStation::m_Collection;

CAlgoFirstStation::CAlgoFirstStation()
{
}

CAlgoFirstStation::~CAlgoFirstStation()
{
}

CAlgoFirstStation *CAlgoFirstStation::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CAlgoFirstStation();
	}
	return m_Instance;
}

bool CAlgoFirstStation::InitAlgo(QString &errMsg)
{
	QTextCodec *gbk_code = QTextCodec::codecForName("GBK");
	QString ModelPath = QCoreApplication::applicationDirPath() + "/models/HIGH_LIGHT_E62.smartmore";
	QString JasonPath = QCoreApplication::applicationDirPath() + "/models/high_light_model.json";
	std::string model = std::string(gbk_code->fromUnicode(ModelPath).data());
	std::string json = std::string(gbk_code->fromUnicode(JasonPath).data());

	ResultCode code = m_Segment.Init(model, json, 1, 0, spdlog::level::trace);
	if (code != smartmore::ResultCode::Success)
	{
		errMsg = QString::fromLocal8Bit("工位1初始化High模型失败:") + QString::number((int)code);
		return false;
	}
	else if (code == smartmore::ResultCode::Success)
	{
		return true;
	}
	return true;
}

void CAlgoFirstStation::RunAlog(Mat Image,Mat &RenderImage,bool &bOK,int &Time)
{
	smartmore::MesonHighlightSegRequest segReq = { Image };
	smartmore::MesonHighlightSegResponse segRsp;
	QTime time;
	time.start();
	smartmore::ResultCode segRet = m_Segment.Run(segReq, segRsp);
	if (segRet != smartmore::ResultCode::Success)
	{
		std::cout << "Position1 Normal run Failure." << std::endl;
	}
	Time = time.elapsed();
	bOK = segRsp.isOK;
	if (!bOK)
	{
		m_Segment.drawDebugGraph(segRsp.colorMap);
	}
	RenderImage = segRsp.colorMap;
}