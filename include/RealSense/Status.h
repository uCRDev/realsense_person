/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once

namespace Intel {
    namespace RealSense {
        namespace NSStatus {

            enum Status {
                /* success */
                STATUS_NO_ERROR = 0,      
                /* errors */
                STATUS_FEATURE_UNSUPPORTED = -1,     
                STATUS_PARAM_UNSUPPORTED = -2,     
                STATUS_ITEM_UNAVAILABLE = -3,     
                STATUS_HANDLE_INVALID = -101,   
                STATUS_ALLOC_FAILED = -102,   
                STATUS_DEVICE_FAILED = -201,   
                STATUS_DEVICE_LOST = -202,   
#ifndef STATUS_DEVICE_BUSY
                STATUS_DEVICE_BUSY = -203,   
#endif

                STATUS_EXEC_ABORTED = -301,   
                STATUS_EXEC_INPROGRESS = -302,   
                STATUS_EXEC_TIMEOUT = -303,   
                STATUS_FILE_WRITE_FAILED = -401,   
                STATUS_FILE_READ_FAILED = -402,   
                STATUS_FILE_CLOSE_FAILED = -403,   
                STATUS_DATA_UNAVAILABLE = -501,   
                STATUS_DATA_NOT_INITIALIZED = -502,   
                STATUS_INIT_FAILED = -503,   
                STATUS_STREAM_CONFIG_CHANGED = -601,   
                STATUS_POWER_UID_ALREADY_REGISTERED = -701,
                STATUS_POWER_UID_NOT_REGISTERED = -702,
                STATUS_POWER_ILLEGAL_STATE = -703,
                STATUS_POWER_PROVIDER_NOT_EXISTS = -704,

                STATUS_CAPTURE_CONFIG_ALREADY_SET = -801, 
                STATUS_COORDINATE_SYSTEM_CONFLICT = -802,   
                STATUS_NOT_MATCHING_CALIBRATION = -803,    
                STATUS_ACCELERATION_UNAVAILABLE = -901,     
                STATUS_WRONG_META_DATA_VALUE = -902,        
                /* warnings */
                STATUS_TIME_GAP = 101,   
                STATUS_PARAM_INPLACE = 102,   
                STATUS_DATA_NOT_CHANGED = 103,   
                STATUS_PROCESS_FAILED = 104,   
                STATUS_VALUE_OUT_OF_RANGE = 105,   
                STATUS_DATA_PENDING = 106,    
                /* backward compatibility */
                PXC_STATUS_NO_ERROR = 0,      
                PXC_STATUS_FEATURE_UNSUPPORTED = -1,     
                PXC_STATUS_PARAM_UNSUPPORTED = -2,     
                PXC_STATUS_ITEM_UNAVAILABLE = -3,     
                PXC_STATUS_HANDLE_INVALID = -101,   
                PXC_STATUS_ALLOC_FAILED = -102,   
                PXC_STATUS_DEVICE_FAILED = -201,   
                PXC_STATUS_DEVICE_LOST = -202,   
                PXC_STATUS_DEVICE_BUSY = -203,   
                PXC_STATUS_EXEC_ABORTED = -301,   
                PXC_STATUS_EXEC_INPROGRESS = -302,   
                PXC_STATUS_EXEC_TIMEOUT = -303,   
                PXC_STATUS_FILE_WRITE_FAILED = -401,   
                PXC_STATUS_FILE_READ_FAILED = -402,   
                PXC_STATUS_FILE_CLOSE_FAILED = -403,   
                PXC_STATUS_DATA_UNAVAILABLE = -501,   
                PXC_STATUS_DATA_NOT_INITIALIZED = -502,   
                PXC_STATUS_INIT_FAILED = -503,   
                PXC_STATUS_STREAM_CONFIG_CHANGED = -601,   
                PXC_STATUS_POWER_UID_ALREADY_REGISTERED = -701,
                PXC_STATUS_POWER_UID_NOT_REGISTERED = -702,
                PXC_STATUS_POWER_ILLEGAL_STATE = -703,
                PXC_STATUS_POWER_PROVIDER_NOT_EXISTS = -704,

                PXC_STATUS_CAPTURE_CONFIG_ALREADY_SET = -801, 
                PXC_STATUS_COORDINATE_SYSTEM_CONFLICT = -802,   
                PXC_STATUS_NOT_MATCHING_CALIBRATION = -803,    
                PXC_STATUS_ACCELERATION_UNAVAILABLE = -901,     
                PXC_STATUS_WRONG_META_DATA_VALUE = -902,        
                /* warnings */
                PXC_STATUS_TIME_GAP = 101,   
                PXC_STATUS_PARAM_INPLACE = 102,   
                PXC_STATUS_DATA_NOT_CHANGED = 103,   
                PXC_STATUS_PROCESS_FAILED = 104,   
                PXC_STATUS_VALUE_OUT_OF_RANGE = 105,   
                PXC_STATUS_DATA_PENDING = 106    
             };
        };
        using namespace NSStatus;
    }
}
