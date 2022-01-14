#ifndef __NORMAL_SEGMENTATION_H__
#define __NORMAL_SEGMENTATION_H__

#ifdef MESON_NORMAL_SEGMENTATION_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include <opencv2/opencv.hpp>
#include <vector>
#include <spdlog/spdlog.h>
#include "common.h"

namespace smartmore
{
    /* 
    * SDK 输入
    *   outerCenterX : 外援圆心的横坐标
    *   outerCenterY : 外圆圆心的纵坐标
    *   outerRadius  : 外圆半径
    *   inputImage   : 输入图片
    */
    struct DLL_API MesonNormalSegRequest
    {
        int outerCenterX = 0;
        int outerCenterY = 0;
        int outerRadius  = 0;
        cv::Mat inputImage;
    };

    /*
    * SDK 输出
    *   isOK     : 是否 OK
    *   colorMap : 渲染结果
    */
    struct DLL_API MesonNormalSegResponse
    {
        bool isOK;
        cv::Mat colorMap;
    };

    class DLL_API MesonNormalSegmentation
    {
    public:
        MesonNormalSegmentation();
        ~MesonNormalSegmentation();

        /*
        * SDK 初始化
        *   inputModelPath : 输入模型路径
        *   jsonConfigPath ：json 配置文件路径
        *   USE_GPU        ：是否使用 GPU 推理
        *   deviceID       : 设备 ID
        *   logLevel       ：log 级别
        */
        ResultCode Init(
            const std::string& inputModelPath,
            const std::string& jsonConfigPath,
            const bool USE_GPU,
            const int deviceId,
            spdlog::level::level_enum logLevel = spdlog::level::info);

        /*
        * SDK 运行
        *   req : 推理输入
        *   rsp : 推理输出
        */
        ResultCode Run(const MesonNormalSegRequest& req, MesonNormalSegResponse& rsp);

        /*
        * 绘制 ColorMap
        *   img : 输入图片
        */
        void drawDebugGraph(cv::Mat& img);

    private:
        class Impl;
        std::shared_ptr<Impl> impl_;
    };
}

#endif // __NORMAL_SEGMENTATION_H__
