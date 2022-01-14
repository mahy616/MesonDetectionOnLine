#ifndef SMORESDK_PIANWEI_LOCATION_H
#define SMORESDK_PIANWEI_LOCATION_H

#ifdef MESON_LOCATION_EXPORTS
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
    * 结构体 - 圆
    *   x       ：圆心横坐标
    *   y       : 圆心纵坐标
    *   radius  ：半径
    */
    struct DLL_API Circle
    {
        int x{ 0 };
        int y{ 0 };
        float radius{ 0 };
        Circle(int _x = 0, int _y = 0, float _radius = 0) : x(_x), y(_y), radius(_radius) {}
    };

    /*
    * sdk 输入结构体
    *   inputImage ： 输入图片
    */
    struct DLL_API circleRequest
    {
        cv::Mat inputImage;
    };

    /*
    * sdk 输出结构体
    *   inner_circle : 内圆
    *   outer_circle ：外圆
    *   colorMap     ：渲染图
    */
    struct DLL_API circleResponse
    {
        Circle inner_circle;
        Circle outer_circle;
        cv::Mat colorMap;
    };

    class DLL_API PianweiCircleLocation
    {
    public:
        PianweiCircleLocation();
        ~PianweiCircleLocation();

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
        ResultCode Run(const circleRequest& req, circleResponse& rsp);

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

#endif //SMORESDK_PIANWEI_LOCATION_H
