/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include <stdint.h>

namespace Intel {
    namespace RealSense {

        typedef int32_t bool32_t;

        struct RectI32 {
            int32_t x, y, w, h;
        };

        struct RectF32 {
            float x, y, w, h;
        };

        struct SizeI32 {
            int32_t width, height;
        };

        struct Size3DF32 {
            float width, height, depth;
        };

        struct PointF32 {
            float x, y;
        };

        struct PointI32 {
            int32_t x, y;
        };

        struct RangeF32 {
            float min, max;
        };
 
        struct Point3DF32 {
            float x, y, z;
        };
 
        struct Point4DF32 {
            float x, y, z, w;
        };

       struct Box3DF32 {
            Point3DF32 centerOffset, dimension;
        };

#define PXC_UID(X1,X2,X3,X4) ((int32_t)(((unsigned int)(X4)<<24)+((unsigned int)(X3)<<16)+((unsigned int)(X2)<<8)+(unsigned int)(X1)))

#define PXC_DEFINE_CONST(Y,X) enum {Y=X}
 
#define PXC_DEFINE_UID(Y,X1,X2,X3,X4) enum {Y=PXC_UID(X1,X2,X3,X4)}

#if defined(_WIN32) || defined(_WIN64)
#define PXC_DEPRECATED(_MSG) __declspec(deprecated(_MSG))
#else
#define PXC_DEPRECATED(_MSG)
#endif
    }
}
