/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not  be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/

#pragma once
#include "RealSense/PersonTracking/PersonTrackingData.h"
#include "RealSense/PersonTracking/PersonTrackingModule.h"

namespace Intel {
    namespace RealSense {

        namespace PersonTracking {
            class PersonTrackingConfiguration : public Base
            {
            public:
                /* Constants */
                PXC_CUID_OVERWRITE(PXC_UID('P', 'O', 'T', 'C'));

                enum TrackingStrategyType
                {
                    STRATEGY_APPEARANCE_TIME,
                    STRATEGY_CLOSEST_TO_FARTHEST,
                    STRATEGY_FARTHEST_TO_CLOSEST,
                    STRATEGY_LEFT_TO_RIGHT,
                    STRATEGY_RIGHT_TO_LEFT
                };

                 class TrackingConfiguration
                {
                public:
                    enum TrackingMode
                    {
                        TRACKING_MODE_FOLLOWING, 
                        TRACKING_MODE_INTERACTIVE, 
                        TRACKING_MODE_SINGLE_PERSON  
                    };
                    enum DetectionMode
                    {
                        AUTO,               
                        MANUAL_CLOSE_RANGE, 
                        MANUAL_MID_RANGE,   
                        MANUAL_FAR_RANGE,   
                        MANUAL_ALL          
                    };

                    virtual ~TrackingConfiguration() {}

                    virtual void PXCAPI Enable() = 0;

                    virtual void PXCAPI Disable() = 0;

                    virtual bool32_t PXCAPI IsEnabled() = 0;

                    virtual void PXCAPI EnableSegmentation() = 0;

                    virtual void PXCAPI DisableSegmentation() = 0;

                    virtual bool32_t PXCAPI IsSegmentationEnabled() = 0;
 
                    virtual void PXCAPI EnableBlob() = 0;

                    virtual void PXCAPI DisableBlob() = 0;
 
                    virtual bool32_t PXCAPI IsBlobEnabled() = 0;
#ifdef PT_MW_DEV
                    virtual void PXCAPI EnablePersonOrientation() = 0;

                    virtual void PXCAPI DisablePersonOrientation() = 0;

                    virtual bool32_t PXCAPI IsPersonOrientationEnabled() = 0;
#endif

                    virtual void PXCAPI EnableHeadBoundingBox() = 0;

                    virtual void PXCAPI DisableHeadBoundingBox() = 0;

                    virtual bool32_t PXCAPI IsHeadBoundingBoxEnabled() = 0;

                    virtual void PXCAPI SetMaxTrackedPersons(int32_t maxTrackedPersons) = 0;

                    virtual int32_t PXCAPI GetMaxTrackedPersons() const = 0;

                    virtual void PXCAPI SetTrackingMode(TrackingMode mode) = 0;
 
                    virtual TrackingMode PXCAPI GetTrackingMode() = 0;

                    virtual void PXCAPI SetDetectionMode(DetectionMode mode) = 0;

                    virtual DetectionMode PXCAPI GetDetectionMode() = 0;
                    virtual void PXCAPI EnableDetectionFromFar() = 0;

                    virtual void PXCAPI DisableDetectionFromFar() = 0;
                };

                class SkeletonJointsConfiguration
                {
                public:
                    enum SkeletonMode
                    {
                        AREA_UPPER_BODY, //This includes all joints of the upper body.
                        AREA_UPPER_BODY_ROUGH, //This includes only 4 points: head, chest, and hands.
                        AREA_FULL_BODY_ROUGH, // Not in use
                        AREA_FULL_BODY
                    };

                    virtual ~SkeletonJointsConfiguration() {}

                    virtual void PXCAPI Enable() = 0;

                    virtual void PXCAPI Disable() = 0;

                    virtual bool32_t PXCAPI IsEnabled() = 0;

                    virtual void PXCAPI SetMaxTrackedPersons(int32_t maxTrackedPersons) = 0;
 
                    virtual void PXCAPI  SetTrackingArea(SkeletonMode area) = 0;
                };

                class PersonLyingConfiguration
                {
                public:
                    enum DetectionState
                    {
                        SEARCH_CANDIDATES_STATE,
                        CLASSIFICATION_STATE
                    };

                    virtual void PXCAPI Enable() = 0;

                    virtual void PXCAPI Disable() = 0;

                    virtual bool32_t PXCAPI IsEnabled() = 0;

                    virtual void PXCAPI SetMaxTrackedPersons(int32_t maxTrackedPersons) = 0;

                    virtual void PXCAPI SetDetectionState(DetectionState state) = 0;
 
                    virtual DetectionState PXCAPI GetDetectionState() = 0;
                };

                class PoseConfiguration
                {
                public:
                    virtual ~PoseConfiguration() {}

                    virtual void PXCAPI Enable() = 0;

                    virtual void PXCAPI Disable() = 0;

                    virtual bool32_t PXCAPI IsEnabled() = 0;

                    virtual void PXCAPI SetMaxTrackedPersons(int32_t maxTrackedPersons) = 0;
                };

                class RecognitionConfiguration
                {
                public:
                    enum RecognitionAsyncPolicy
                    {
                        /*
                         * Recognizing a person based on multiple frames.
                        * Improves accuracy but takes longer time to return.
                         * Recommended in cases of head pose and tough light environments
                        */
                        //MultipleFrames,
 
                        SingleFrame 
                    };

                    enum RecognitionPolicy
                    {
                        Standard, 
                        /*
                        * Little to no false positives.
                        * Suitable for login use-case. Might take longer to recognize a person.
                       */
                         //Strict,
                    };

                    class RecognitionDatabase
                    {
                    public:
                        virtual ~RecognitionDatabase() {}
                        virtual int32_t PXCAPI GetNumberOfRegisteredUsers() = 0; //

                        virtual bool32_t PXCAPI Exists(int32_t recognitionId) = 0;

                        virtual void PXCAPI RemoveDescriptor(int32_t recognitionId, int32_t descriptorId) = 0;

                        virtual void PXCAPI RemoveEntry(int32_t recognitionId) = 0; //unregister

                        virtual void PXCAPI Clear() = 0;
 
                        virtual void PXCAPI GetRegisteredUsersIds(int32_t* outIds, int32_t userAllocatedOutIdsSize, int32_t* numIdsWritten) = 0;
 
                        virtual int PXCAPI GetNumberOfUserDescriptors(int recognitionId) = 0;

                        virtual bool PXCAPI GetUserDescriptorIds(int recognitionId, int* outDescriptorIds) = 0;
                    };

                    class RecognitionDatabaseUtilities
                    {
                    public:
                        virtual ~RecognitionDatabaseUtilities() {}

                        /* Creation / Destruction */
                        //virtual RecognitionDatabase* CreateDatabase() = 0;
                       //virtual DestoryDatabase(RecognitionDatabase* database) = 0;

                       /* Merge */
                        //virtual bool MergeDatabases(RecognitionDatabase* firstDatabase, RecognitionDatabase* secondDatabase, RecognitionDatabase* MergedDatabase);
 
                        /* Memory */

                        virtual int32_t PXCAPI GetDatabaseMemorySize(RecognitionDatabase* database) = 0;

                        virtual bool32_t PXCAPI DeserializeDatabase(RecognitionDatabase* database, unsigned char* buffer, int32_t bufferSize) = 0;

                        virtual bool32_t PXCAPI SerializeDatabase(RecognitionDatabase* database, unsigned char* outBuffer, int32_t inAllocatedBufferSize, int32_t* outWrittenBufferSize) = 0;

                        /* FileSystem */
                        //virtual bool32_t PXCAPI LoadDatabaseFromFile(RecognitionDatabase* database, const char* dbFilePath) = 0;
                       //virtual bool32_t PXCAPI SaveDatabaseToFile(RecognitionDatabase* database, const char* dbFilePath) = 0;
                    };

                    virtual ~RecognitionConfiguration() {}

                    virtual void PXCAPI Enable() = 0;

                    virtual void PXCAPI Disable() = 0;

                    virtual bool32_t PXCAPI IsEnabled() = 0;
 
                    virtual RecognitionPolicy PXCAPI QueryPolicy() = 0;

                    virtual bool32_t PXCAPI SetPolicy(RecognitionPolicy recognitionPolicy) = 0;

                    virtual RecognitionAsyncPolicy PXCAPI QueryAsyncPolicy() = 0;

                    virtual bool32_t PXCAPI SetAsyncPolicy(RecognitionAsyncPolicy asyncRecognitionPolicy) = 0;
 
                    virtual RecognitionDatabase* PXCAPI QueryDatabase() = 0;
                    //virtual void SetDatabase(IDatabase* database) = 0; // Goes along with create/destroy

                    virtual RecognitionDatabaseUtilities* PXCAPI QueryDatabaseUtilities() = 0;
                };

                class GesturesConfiguration
                {
                public:
                    virtual ~GesturesConfiguration() {}

                    virtual void PXCAPI Enable() = 0;

                    virtual void PXCAPI Disable() = 0;

                    virtual bool32_t PXCAPI IsEnabled() = 0;

                    virtual void PXCAPI SetMaxTrackedPersons(int32_t maxTrackedPersons) = 0;

                    virtual void PXCAPI EnableGesture(GestureType gestureType) = 0;

                    virtual void PXCAPI EnableAllGestures() = 0;

                    virtual void PXCAPI DisableGesture(GestureType gestureType) = 0;

                    virtual void PXCAPI DisableAllGestures() = 0;
                };

                class ExpressionsConfiguration
                {
                public:
                    virtual ~ExpressionsConfiguration()
                    {}

                   virtual void PXCAPI Enable() = 0;

                   virtual void PXCAPI Disable() = 0;

                   virtual bool32_t PXCAPI IsEnabled() = 0;

                   virtual void PXCAPI SetMaxTrackedPeople(int32_t maxTrackedPeople) = 0;

                   virtual void PXCAPI EnableAllExpressions() = 0;

                   virtual void PXCAPI DisableAllExpressions() = 0;

                   virtual Status PXCAPI EnableExpression(PersonExpressionsEnum expression) = 0;

                   virtual void PXCAPI DisableExpression(PersonExpressionsEnum expression) = 0;

                   virtual bool32_t PXCAPI IsExpressionEnabled(PersonExpressionsEnum expression) = 0;
                };

                class PersonFaceConfiguration
                {
                public:
                   virtual ~PersonFaceConfiguration() {}

                    virtual void PXCAPI EnableHeadPose() = 0;

                    virtual void PXCAPI DisableHeadPose() = 0;

                    virtual bool32_t PXCAPI IsHeadPoseEnabled() const = 0;

                    virtual void PXCAPI EnableFaceLandmarks() = 0;

                    virtual void PXCAPI DisableFaceLandmarks() = 0;

                    virtual bool32_t PXCAPI IsFaceLandmarksEnabled() const = 0;

                    virtual void PXCAPI EnableGaze() = 0;

                    virtual void PXCAPI DisableGaze() = 0;

                    virtual bool32_t PXCAPI IsGazeEnabled() const = 0;
#ifdef PT_MW_DEV

                        virtual ExpressionsConfiguration* PXCAPI QueryExpressions() = 0;
#endif
                };

                virtual TrackingConfiguration* PXCAPI QueryTracking() = 0;
                virtual SkeletonJointsConfiguration* PXCAPI QuerySkeletonJoints() = 0;
#ifdef PT_MW_DEV

            virtual PoseConfiguration* PXCAPI QueryPose() = 0;
#endif

                virtual RecognitionConfiguration* PXCAPI QueryRecognition() = 0;

                virtual GesturesConfiguration* PXCAPI QueryGestures() = 0;
#ifdef PT_MW_DEV

            virtual PersonLyingConfiguration* PXCAPI QueryPersonLying() = 0;
#endif
 
                virtual PersonFaceConfiguration* QueryFace() = 0;

                enum TrackingAngles
                {
                    TRACKING_ANGLES_FRONTAL = 0,
                    TRACKING_ANGLES_PROFILE,
                    TRACKING_ANGLES_ALL
                };

                virtual void PXCAPI SetTrackedAngles(TrackingAngles angles) = 0;


                /* Event Handlers */

                class AlertHandler {
                public:
                    virtual void PXCAPI OnFiredAlert(const AlertData & alertData) = 0;
                };
#ifdef PT_MW_DEV
               /* Tracking Configuration */

            virtual Status PXCAPI ResetTracking() = 0;

           /* Alerts Configuration */

            virtual Status PXCAPI EnableAlert(AlertType alertEvent) = 0;

            virtual Status PXCAPI EnableAllAlerts(void) = 0;
 
            virtual bool32_t PXCAPI IsAlertEnabled(AlertType alertEvent) const = 0;

            virtual Status PXCAPI DisableAlert(AlertType alertEvent) = 0;

            virtual Status PXCAPI DisableAllAlerts(void) = 0;

            virtual Status PXCAPI SubscribeAlert(AlertHandler *alertHandler) = 0;

            virtual Status PXCAPI UnsubscribeAlert(AlertHandler *alertHandler) = 0;
#endif
            };
 
            typedef PersonTrackingConfiguration::TrackingStrategyType TrackingStrategyType;
            typedef PersonTrackingConfiguration::TrackingConfiguration TrackingConfiguration;
            typedef PersonTrackingConfiguration::TrackingConfiguration::TrackingMode TrackingMode;
            typedef PersonTrackingConfiguration::SkeletonJointsConfiguration SkeletonJointsConfiguration;
            typedef PersonTrackingConfiguration::SkeletonJointsConfiguration::SkeletonMode SkeletonMode;
            typedef PersonTrackingConfiguration::PoseConfiguration PoseConfiguration;
            typedef PersonTrackingConfiguration::RecognitionConfiguration RecognitionConfiguration;
            typedef PersonTrackingConfiguration::GesturesConfiguration GesturesConfiguration;
            typedef PersonTrackingConfiguration::ExpressionsConfiguration ExpressionsConfiguration;
            typedef PersonTrackingConfiguration::TrackingAngles TrackingAngles;
            typedef PersonTrackingConfiguration::PersonFaceConfiguration PersonFaceConfiguration;
        }
    }

