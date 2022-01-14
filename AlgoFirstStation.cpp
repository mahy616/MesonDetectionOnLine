#include "AlgoFirstStation.h"
#include "QTextCodec"
#include "QFileInfo"
#include "QTime"
#include "QCoreApplication"
#include <QDebug>

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
	QString ModelPath = QCoreApplication::applicationDirPath() + "/models/zrise-g1.smartmore";
	std::string model = std::string(gbk_code->fromUnicode(ModelPath).data());

	ResultCode code = module.Init(model, true,0);
	//ResultCode code = smartmore::ResultCode::Success;
	if (code != smartmore::ResultCode::Success)
	{
		errMsg = QString::fromLocal8Bit("工位1模型初始化失败:") + QString::number((int)code);
		return false;
	}
	else if (code == smartmore::ResultCode::Success)
	{
		QString input_image = QCoreApplication::applicationDirPath()+"/data/1input_image.bmp";
		QByteArray ba = input_image.toLocal8Bit();
		char *file = ba.data();
		Mat curImage = imread(file);
		s_AlgoRunData AlgoRunData;
		vector<int>m_RunFirstThreshold;
		vector<int>FirstThreshold;
		Mat RenderImage;
		CAlgoFirstStation::GetInstance()->RunAlog(curImage, RenderImage, m_RunFirstThreshold, FirstThreshold, AlgoRunData);
		qDebug() << "Init RunAlog Success 1";
		return true;

	}
	return true;
}

void CAlgoFirstStation::RunAlog(Mat Image, Mat &RenderImage, vector<int> &m_Firsthreshold , vector<int> &Threshold, s_AlgoRunData &AlgoRunData)
{
	//qDebug() << "station 1,RUN" << endl;
	smartmore::SegmentationRequest req{ Image };
	req.thresholds = m_Firsthreshold;
	smartmore::SegmentationResponse rsp;
	std::vector<cv::Point> center;
	std::vector<float> radius;
	float degree;
	int cls_label;
	QTime time;
	time.start();
	Threshold.clear();
	try
	{
		FirstIndex++;
		smartmore::ResultCode res1 = module.Run(req, rsp, center, radius, degree, cls_label);
		if (res1 != smartmore::ResultCode::Success)
		{
			std::cout << "Position1 Normal run Failure." << std::endl;
			AlgoRunData.bOK = false;
			for (int i = 0; i < 5; ++i)
				Threshold.push_back(1);
			RenderImage = Image;
			return;
		}
		else
		{
			module.Visualize(req, rsp, RenderImage);
		};
	}
	catch (cv::Exception& e)
	{
		qDebug() << "left auto run algo exception:" << e.what();
		printf("left auto run algo exception:%s\n", e.what());
		FirstSaveImage->SaveImage(Image, 1);
		return;
	}
	int AlgoTime = time.elapsed();
	qDebug() << "station 1,algo time:" << AlgoTime;
	for (int i = 0; i < 5; ++i)
		Threshold.push_back(0);
	for (map<int, string>::iterator iter = rsp.names.begin(); iter != rsp.names.end(); iter++)
	{
		Threshold[iter->first] = 1;
	}

	if (AlgoRunData.Type == 2 || AlgoRunData.Type == 3)
	SetFirstLabelData(rsp.mask, RenderImage);
	AlgoRunData.bOK = rsp.code == QCCode::OK;
	int ProcessTime = time.elapsed();
	qDebug() << "station 1,after process time:" << ProcessTime - AlgoTime;
	AlgoRunData.Time = time.elapsed();
}

void CAlgoFirstStation::SetFirstLabelData(Mat Image, Mat & RenderImage)
{
	vector<Mat>Masks(5);
	for (int i = 0; i < Image.rows; i++)
	{
		for (int n = 0; n < Image.cols; n++)
		{
			int index = Image.at<uchar>(i, n);
			if (index < 1 || index>5) continue;
			if (Masks[index].size().height == 0)
				Masks[index] = Mat::zeros(Image.rows, Image.cols, CV_8UC1);
			Masks[index].at<uchar>(i, n) = index;
		}
	}
	for (int i = 0; i < Masks.size(); i++)
	{
		if (Masks[i].size().height == 0)
			continue;

		Mat label, stats, centroids;
		size_t cc_count = cv::connectedComponentsWithStats(Masks[i], label, stats, centroids, 8);
		std::vector<size_t> cc_areas(cc_count);
		for (size_t j = 1; j < cc_count; ++j)
		{
			cc_areas[j] = stats.at<int>(static_cast<int>(j), cv::CC_STAT_AREA);
			int w = stats.at<int>(static_cast<int>(j), cv::CC_STAT_WIDTH);
			int h = stats.at<int>(static_cast<int>(j), cv::CC_STAT_HEIGHT);
			int x = stats.at<int>(static_cast<int>(j), cv::CC_STAT_LEFT);
			int y = stats.at<int>(static_cast<int>(j), cv::CC_STAT_TOP);
			string strData = to_string(cc_areas[j]) + "," + to_string(max(w, h));
			putText(Masks[i], strData, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1, 8);
		}
		Mat MatData = Mat::zeros(Masks[i].rows, Masks[i].cols, CV_8UC3);
		vector<Mat> channels;
		for (int m = 0; m < 3; m++)
		{
			channels.push_back(Masks[i]);
		}
		merge(channels, MatData);
		addWeighted(MatData, 0.7, RenderImage, 0.9, 3, RenderImage, -1);
	}
}
