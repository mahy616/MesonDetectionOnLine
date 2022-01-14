/*
 * @Descripttion:
 * @version:
 * @Author: max.ma
 * @Date: 2020-11-06 11:49:09
 * @LastEditors: max.ma
 * @LastEditTime: 2020-11-12 17:04:02
 */

#ifndef __ZRISE_VIMO_SEGMENTATION_MODULE_H__
#define __ZRISE_VIMO_SEGMENTATION_MODULE_H__

#include "ISegmentationModule.h"

namespace smartmore
{
    class DLL_API ZriseVimoSegmentationModule : public ISegmentationModule
    {
    public:
        ZriseVimoSegmentationModule();
        ~ZriseVimoSegmentationModule();

        /**
            sdk版本号
            @return sdk版本号字符串
        */
        std::string Version() override;
        /**
            sdk初始化
            @param  input_model_path ：模型路径
            @param  USE_GPU             ：是否使用gpu
            @param  device_id         ：设备id
            @return 返回码 ：0：成功； 其他值：失败
        */
        ResultCode Init(
            const std::string &input_model_path,
            const bool USE_GPU,
            const int device_id) override;

        /**
            sdk处理
            @param  req ：sdk输入参数结构体的引用
            @param  rsp    ：sdk输出结果结构体的引用
            @return 返回码 ：0：成功； 其他值：失败
        */
        ResultCode Run(const SegmentationRequest &req, SegmentationResponse &rsp) override;

		ResultCode Visualize(const SegmentationRequest &req, const SegmentationResponse &rsp, cv::Mat &image) override;

        ResultCode Run(const SegmentationRequest &req, SegmentationResponse &rsp, std::vector<cv::Point> &center,
                       std::vector<float> &radius, float &degree, int &cls_label);

        std::string Meta(MetaType type) override;
    private:
        class Impl;
        std::shared_ptr<Impl> impl_;
    };

} // namespace smartmore

#endif
