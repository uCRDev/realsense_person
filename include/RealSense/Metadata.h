/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Base.h"

namespace Intel {
    namespace RealSense {

        class Metadata :public Base {
        public:
            PXC_CUID_OVERWRITE(0x62398423);

            virtual int32_t PXCAPI QueryUID(void) = 0;

            virtual int32_t PXCAPI QueryMetadata(int32_t idx) = 0;

            virtual Status PXCAPI DetachMetadata(int32_t id) = 0;
 
            virtual Status PXCAPI AttachBuffer(int32_t id, uint8_t *buffer, int32_t size) = 0;

            virtual int32_t PXCAPI QueryBufferSize(int32_t id) = 0;

            virtual Status PXCAPI QueryBuffer(int32_t id, uint8_t *buffer, int32_t size) = 0;

            virtual Status PXCAPI AttachSerializable(int32_t id, Base *instance) = 0;

            virtual Status PXCAPI CreateSerializable(int32_t id, int32_t cuid, void **instance) = 0;

            template <class T> Status __inline CreateSerializable(int32_t id, T **instance) {
                return CreateSerializable(id, T::CUID, (void**)instance);
            }
        };
    }
}
