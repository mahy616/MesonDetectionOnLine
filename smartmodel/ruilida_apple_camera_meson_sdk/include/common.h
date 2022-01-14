/*******************************************************************************
 *  FILENAME:      common.h
 *
 *  AUTHORS:       Lin ShuLiang    START DATE: Thursday July 15th 2020
 *
 *  LAST MODIFIED: Thursday, July 31h 2020, 21:00
 *
 *  CONTACT:       shuliang.lin@smartmore.com
*******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

namespace smartmore
{
    enum class ResultCode
    {
        Success = 0,

        NotInited = 10001,
        BadModel = 10101,
        BadInput = 10102,
        NotImage = 10103,
        NotVideo = 10104,

        InternalError = 20001,
        OutOfMemory = 20002,
        CudaError = 20003,

        NoLicense = 30000,
        CallLimited = 30001,
        LicenseExpired = 30002,
        WrongAppName = 30003,
    };
} // namespace smartmore

#endif