#include "AlgoSecondStation.h"
#include "QTextCodec"
#include "QFileInfo"
#include "QTime"
#include "QCoreApplication"
#include <QDebug>
#include <omp.h>
#include <qdir.h>
#include <QMessageBox>
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
	QString Model = QCoreApplication::applicationDirPath() + "/models/zrise-g2.smartmore";
	std::string modelpath = std::string(gbk_code->fromUnicode(Model).data());

	ResultCode code = module.Init(modelpath,true, 0);
	if (code != smartmore::ResultCode::Success)
	{
		errMsg = QString::fromLocal8Bit("工位2模型初始化失败:") + QString::number((int)code);
		return false;
	}
	else if (code == smartmore::ResultCode::Success)
	{
		QString input_image = QCoreApplication::applicationDirPath() + "/data/2input_image.bmp";
		QByteArray ba = input_image.toLocal8Bit();
		char *file = ba.data();
		Mat curImage = imread(file);
		s_AlgoRunData AlgoRunData;
		vector<int>m_RunSecondThreshold;
		vector<int>FirstThreshold;
		Mat RenderImage;
		s_Degree m_DegreeThreshold;
		CAlgoSecondStation::GetInstance()->RunAlog(curImage, RenderImage, m_RunSecondThreshold, m_DegreeThreshold, FirstThreshold, AlgoRunData);
		qDebug() << "Init RunAlog Success 2";
		return true;
	}
	return true;
}

void CAlgoSecondStation::RunAlog(Mat Image, Mat &RenderImage, vector<int> &m_SecondThreshold, s_Degree Degree, vector<int> &SecondThreshold, s_AlgoRunData &AlgoRunData)
{
	//qDebug() << "station 2,RUN" <<endl;
	smartmore::SegmentationRequest req{ Image };
	smartmore::SegmentationResponse rsp;
	std::vector<cv::Point> center ;
	std::vector<float> radius ;
	req.thresholds = m_SecondThreshold;
	QTime time;
	float degree;
	string strData;
	int cls_label;
	bool OpenDegree=false;
	SecondThreshold.clear();
	time.start();
	try
	{
		SecondIndex++;
		smartmore::ResultCode res1 = module.Run(req, rsp, center, radius, degree, cls_label);
		if (res1 != smartmore::ResultCode::Success)
		{
			std::cout << "Position1 Normal run Failure." << std::endl;
			AlgoRunData.bOK = false;
			for (int i = 0; i < 13; ++i)
				SecondThreshold.push_back(1);
			RenderImage = Image;
			return;
		}
		else
		{
			module.Visualize(req, rsp, RenderImage);
		}
	}
	catch (cv::Exception& e)
	{
		qDebug() << "left auto run algo exception:" << e.what();
		printf("left auto run algo exception:%s\n", e.what());
		SaveImage(Image,2);
		return;
	}
	int AlgoTime = time.elapsed();
	qDebug() << "station 2,Algo time:" << AlgoTime;
	for (int i = 0; i < 10; ++i)
		SecondThreshold.push_back(0);


	for (map<int, string>::iterator iter = rsp.names.begin(); iter != rsp.names.end(); iter++)
	{
		SecondThreshold[iter->first] = 1;
	}
	if (Degree.AddDegree == Degree.SubDegree)
		OpenDegree = true;
	bool DegreeShold = (degree > Degree.SubDegree&&degree < Degree.AddDegree)|| OpenDegree;
	if (DegreeShold)
	{
		SecondThreshold.push_back(0);
	}
	else
	{
		SecondThreshold.push_back(1);
	}
	AlgoRunData.bOK = (((rsp.code == QCCode::OK)&& DegreeShold)&& cls_label==0);
	if(AlgoRunData.Type==2|| AlgoRunData.Type == 3)
	SetSecondLabelData(rsp.mask, RenderImage);

	if (center.size() != 2)
	{
		QByteArray ba("find circle number = ");
		ba.append(QString::number(center.size()));
		cv::putText(RenderImage, ba.data(), cv::Point(Image.cols / 2, 30),
			cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 255, 0), 3);
		AlgoRunData.bOK = false;
	}
	else
	{
		cv::Point P1 = center.at(0);
		cv::Point P2 = center.at(1);
		int dis = sqrt(pow(P1.x - P2.x, 2)
			+ pow(P1.y - P2.y, 2));
		if (dis > AlgoRunData.Distance)
		{
			AlgoRunData.bOK = false;
			SecondThreshold.push_back(1);
			
			strData="NG,"+ to_string(dis);
		}
		else
		{
			strData = "OK," + to_string(dis);
			SecondThreshold.push_back(0);
		}
		if (cls_label == 0)
		{
			SecondThreshold.push_back(0);
		}
		else
		{
			SecondThreshold.push_back(1);
		}
		putText(RenderImage, strData, Point(100, 2800), FONT_HERSHEY_TRIPLEX, 3, Scalar(255, 255, 255), 3, 8);

	}
	int ProcessTime = time.elapsed();
	qDebug() << "station 2,after process time:" << ProcessTime - AlgoTime;
	AlgoRunData.Time = time.elapsed();

}

void CAlgoSecondStation::SetSecondLabelData(Mat Image, Mat &RenderImage)
{
	vector<Mat> Masks(10);
	for (int i = 0; i < Image.rows; i++)
	{
		for (int n = 0; n < Image.cols; n++)
		{
			int index = Image.at<uchar>(i, n);
			if (index < 1 || index>10) continue;
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

void CAlgoSecondStation::SaveImage(Mat Image, int Index)
{
	QString CurTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz");
		QString NGPath = QCoreApplication::applicationDirPath();
		QString OriginalImageName;
		if (NGPath.isEmpty())
		{
			//qDebug() << " exception path is empty";
			return;
		}
		QString CurPath = NGPath + "/" + CurTime;
		QDir dir;
		if (!dir.exists(CurPath))
		{
			dir.mkpath(CurPath);
		}
		if (Index==2)
		{
			 OriginalImageName = CurPath + "/2_O.bmp";

		}
		if (Index == 1)
		{
			OriginalImageName = CurPath + "/1_O.bmp";
	
		}
	//	qDebug() << " exception iamgeName:" << OriginalImageName;
		QByteArray ba = OriginalImageName.toLocal8Bit();
		char *file = ba.data();
		try
		{
			bool rv = imwrite(file, Image);
			if (rv)
			{
			//	qDebug() << "save image success:" << file;
			}
		}
		catch (cv::Exception& e)
		{
			const char* err_msg = e.what();
			//qDebug() << "save image failed:" << file;
		}
}

