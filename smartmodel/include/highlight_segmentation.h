#ifndef __HIGH_LIGHT_SEGMENTATION__
#define __HIGH_LIGHT_SEGMENTATION__

#ifdef MESON_HIGH_LIGHT_SEGMENTATION_EXPORTS
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
    *   inputImage   : 输入图片
    */
    struct DLL_API MesonHighlightSegRequest
    {
        cv::Mat inputImage;
    };

    /*
    * SDK 输出
    *   isOK     : 是否 OK
    *   colorMap : 渲染结果
    */
    struct DLL_API MesonHighlightSegResponse
    {
        bool isOK;
        cv::Mat colorMap;
    };

    class DLL_API MesonHighlightSegmentation
    {
    public:
        MesonHighlightSegmentation();
        ~MesonHighlightSegmentation();

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
        ResultCode Run(const MesonHighlightSegRequest& req, MesonHighlightSegResponse& rsp);

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

#endif // __HIGH_LIGHT_SEGMENTATION__