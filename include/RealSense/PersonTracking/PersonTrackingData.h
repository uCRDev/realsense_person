/*******************************************************************************
 
 INTEL CORPORATION PROPRIETARY INFORMATION
 This software is supplied under the terms of a license agreement or nondisclosure
 agreement with Intel Corporation and may not be copied or disclosed except in
 accordance with the terms of that agreement
 Copyright(c) 2013-2017 Intel Corporation. All Rights Reserved.
 
 *******************************************************************************/
 #pragma once
 #include "RealSense/Image.h"
 #include "RealSense/PersonTracking/PersonTrackingModule.h"
 #include <cstdint>
 
 namespace Intel {
     namespace RealSense {
         namespace PersonTracking {
 
             class PersonTrackingData : public Base
             {
             public:
                 /* Constants */
                 PXC_CUID_OVERWRITE(PXC_UID('P', 'O', 'T', 'D'));
 
                 enum AlertType {
                     ALERT_PERSON_DETECTED = 0x0001,         
                             ALERT_PERSON_NOT_DETECTED = 0x0002,     
                             ALERT_PERSON_OCCLUDED = 0X0004,         
                             ALERT_PERSON_TOO_CLOSE = 0X0008,        
                             ALERT_PERSON_TOO_FAR = 0X0010           
                 };
 
                 enum AccessOrderType {
                     ACCESS_ORDER_BY_INDEX = 0            
 #ifdef PT_MW_DEV
                     , ACCESS_ORDER_BY_TIME               
                     , ACCESS_ORDER_NEAR_TO_FAR           
                     , ACCESS_ORDER_LEFT_TO_RIGHT         
 #endif
                 };
 
                 enum TrackingState
                 {
                     TRACKING_STATE_TRACKING = 0,        
                             TRACKING_STATE_DETECTING            
                 };
 
                 /* Data Structures */
 
                 struct AlertData
                 {
                     AlertType    label;                  
                     int32_t      personId;               
                     int64_t      timeStamp;              
                     int32_t      frameNumber;            
                 };
 
                 struct PoseEulerAngles
                 {
                     float yaw;
                     float pitch;
                     float roll;
                     int32_t reserved[10];
                 };
 
                 struct BoundingBox2D
                 {
                     RectI32 rect; 
                     int32_t confidence; 
                 };
 
                 struct PointInfo
                 {
                     Point3DF32 point; 
                     int32_t confidence; 
                 };
 
                 struct PointCombined
                 {
                     PointInfo image; 
                     PointInfo world; 
                     int32_t reserved[10];
                 };
 
                 /* Interfaces */
 
                 class ObjectProposal
                 {
                 public:
                     struct ProposedObject
                     {
                         BoundingBox2D boundingBox; 
                         Point3DF32 centerMass; 
                     };
 
                     virtual int32_t PXCAPI QueryNumberOfObjects(void) const = 0;
 
                     virtual ProposedObject PXCAPI QueryObject(int32_t index) const = 0;
                 };
 
                 class PersonLying
                 {
                 public:
                     enum ClassificationResult
                     {
                         CLASSIFIED = 0,
                         NEED_DIFFERENT_VIEW_POINT,
                         NOT_CLASSIFIED
                     };
 
                     virtual int32_t PXCAPI QueryNumberOfCandidates(void) = 0;
 
                     virtual PointCombined PXCAPI QueryCandidatePosition(int32_t index) = 0;
 
                     virtual BoundingBox2D PXCAPI QueryCandidate2DBoundingBox(int32_t index) = 0;
 
                     virtual ClassificationResult PXCAPI QueryCandidateClassificationResult(int32_t index) = 0;
 
                     virtual int32_t PXCAPI QueryCandidateClassificationConfidence(int32_t index) = 0;
 
                     virtual float PXCAPI QueryCandidateEigenValue(int32_t index, int32_t eigIndex) = 0;
 
                     virtual Point3DF32 PXCAPI QueryCandidateEigenVector(int32_t index, int32_t eigIndex) = 0;
                 };
 
                 class PersonPose
                 {
                 public:
                     enum PositionState
                     {
                         POSITION_LYING_DOWN = 0,         
                                 POSITION_SITTING,                
                                 POSITION_STANDING                
                         //POSITION_CROUCHING,
                         //POSITION_JUMPING
                     };
 
                     struct PositionInfo
                     {
                         PositionState position;
                         int32_t confidence;
                     };
 
                     struct LeanInfo
                     {
                         PoseEulerAngles leanData;
                         int32_t confidence;
                     };
 
                     virtual PositionInfo PXCAPI QueryPositionState() = 0;
 #ifdef PT_MW_DEV
 
                     virtual bool32_t PXCAPI QueryLeanData(LeanInfo& leanInfo) = 0;
 #endif
                 };
 
                 class PersonRecognition
                 {
                 public:
                     enum RecognitionStatus
                     {
                         RecognitionPassedPersonRecognized = 0,
                         RecognitionPassedPersonNotRecognized,
                         RecognitionFailed,
                         RecognitionFailedFaceNotDetected,
                         RecognitionFailedFaceNotClear,
                         RecognitionFailedPersonTooFar,
                         RecognitionFailedPersonTooClose,
                         RecognitionFailedFaceAmbiguity
                     };
 
                     enum RegistrationStatus
                     {
                         RegistrationSuccessful = 0,
                         RegistrationFailed = 1,
                         RegistrationFailedAlreadyRegistered,
                         RegistrationFailedFaceNotDetected,
                         RegistrationFailedFaceNotClear,
                         RegistrationFailedPersonTooFar,
                         RegistrationFailedPersonTooClose
                     };
 
                     class RecognizerScoreData
                     {
                     public:
                         virtual float PXCAPI QuerySimilarityScoreById(int userId) = 0;
                     };
 
                     struct RecognizerData
                     {
                         int trackingId; 
                         int recognitionId; 
                         float similarityScore; 
                         RecognizerScoreData* scoreData; 
                     };
 
                     class RegistrationHandler
                     {
                     public:
                         virtual ~RegistrationHandler() {}
                         virtual void OnAsyncRegistrationEnded(int32_t recognitionId, int32_t trackingId, int32_t descriptorId, RegistrationStatus status) = 0;
                     };
 
                     class ReinforceRegistrationHandler
                     {
                     public:
                         virtual ~ReinforceRegistrationHandler() {}
                         virtual void OnAsyncReinforceRegisterationEnded(int32_t trackingId, int32_t descriptorId, RegistrationStatus status) = 0;
                     };
 
                     class RecognitionHandler
                     {
                     public:
                         virtual ~RecognitionHandler() {}
                         virtual void OnAsyncRecognitionEnded(RecognizerData* recognizerData, RecognitionStatus status) = 0;
                     };
 
                     virtual RegistrationStatus PXCAPI RegisterUser(int32_t* outputRecognitionId, int32_t* outTrackingId, int32_t* outDescriptorId) = 0;
 
                     virtual bool32_t PXCAPI RegisterUserAsync(RegistrationHandler* callback) = 0;
 
                     virtual RegistrationStatus PXCAPI ReinforceUserRegistration(int32_t recognitionId, int32_t* outTrackingId, int32_t* outDescriptorId) = 0;
 
                     virtual bool32_t PXCAPI ReinforceUserRegistartionAsync(int32_t recognitionId, ReinforceRegistrationHandler* callback) = 0;
 
                     virtual RecognitionStatus PXCAPI RecognizeUser(RecognizerData* result) = 0;
 
                     virtual bool32_t PXCAPI RecognizeUserAsync(RecognitionHandler* callback) = 0;
                 };
 
                 class RecognitionModuleData
                 {
                 public:
                     enum RecognizeAllStatus
                     {
                         RecognizeAllPassed = 0,
                         RecognizeAllUserAllocatedArrayIsSmallerThanExpected,
                         RecognizeAllInternalError,
                     };
 
                     struct RecognizerDataWithStatus
                     {
                         int trackingId;  
                         int recognitionId; 
                         float similarityScore; 
                         PersonRecognition::RecognitionStatus status;    
                     };
 
                     class RecognizeAllHandler
                     {
                     public:
                         virtual ~RecognizeAllHandler() {}
                         virtual void OnAsyncRecognitionEnded(RecognizerDataWithStatus* resultsArray, int32_t numberOfResultsWritten) = 0;
                     };
 
                     virtual RecognizeAllStatus PXCAPI RecognizeAll(RecognizerDataWithStatus* resultsArray, int32_t resultsArraySize, int32_t* numberOfResultsWritten) = 0;
 
                     virtual bool32_t PXCAPI RecognizeAllAsync(RecognizeAllHandler* callback) = 0;
 
                     virtual int PXCAPI QueryNumberOfOngoingAsyncRequests() = 0;
                 };
 
                 class PersonGestures
                 {
                 public:
                     enum GestureType
                     {
                         Pointing,
                         Wave
                     };
                     enum WaveType
                     {
                         WAVE_NOT_DETECTED = -1,   
                         WAVE_LEFT_LA = 1,         
                         WAVE_RIGHT_LA = 2,        
                         WAVE_LEFT_RA = 3,         
                         WAVE_RIGHT_RA = 4         
                     };
 
 
                     struct PointingData2D
                     {
                         PointF32 origin; 
                         PointF32 direction; 
                     };
 
                     struct PointingData3D
                     {
                         Point3DF32 origin; 
                         Point3DF32 direction; 
                     };
 
                     struct PointingInfo
                     {
                         PointingData3D worldPointingData; 
                         PointingData2D colorPointingData; 
                         int64_t gestureStartTimeStamp;    
                         int confidence; 
                     };
 
                     virtual PointingInfo QueryPointingInfo() = 0;
 
                     virtual bool IsPointing() = 0;
 
                     virtual WaveType QueryWaveGesture() = 0;
                     };
 
                 class PersonExpressions
                 {
                 public:
                     enum PersonExpressionsEnum
                     {
                         NEUTRAL = 0,
                         HAPPINESS = 1,
                         SADNESS = 2,
                         SURPRISE = 3,
                         FEAR = 4,
                         ANGER = 5,
                         DISGUST = 6,
                         CONTEMPT = 7,
                         MOUTH_OPEN = 8
                     };
 
                     struct PersonExpressionsResult
                     {
                         int32_t confidence;
                         int32_t reserved[10];
                     };
 
                     virtual bool32_t PXCAPI QueryExpression(PersonExpressionsEnum expression, PersonExpressionsResult* expressionResult) const = 0;
                 };
 
                 class PersonJoints
                 {
                 public:
                     enum JointType
                     {
                         JOINT_ANKLE_LEFT,
                         JOINT_ANKLE_RIGHT,
                         JOINT_ELBOW_LEFT,
                         JOINT_ELBOW_RIGHT,
                         JOINT_FOOT_LEFT,
                         JOINT_FOOT_RIGHT,
                         JOINT_HAND_LEFT,
                         JOINT_HAND_RIGHT,
                         JOINT_HAND_TIP_LEFT,
                         JOINT_HAND_TIP_RIGHT,
                         JOINT_HEAD,
                         JOINT_HIP_LEFT,
                         JOINT_HIP_RIGHT,
                         JOINT_KNEE_LEFT,
                         JOINT_KNEE_RIGHT,
                         JOINT_NECK,
                         JOINT_SHOULDER_LEFT,
                         JOINT_SHOULDER_RIGHT,
                         JOINT_SPINE_BASE,
                         JOINT_SPINE_MID,
                         JOINT_SPINE_SHOULDER,
                         JOINT_THUMB_LEFT,
                         JOINT_THUMB_RIGHT,
                         JOINT_WRIST_LEFT,
                         JOINT_WRIST_RIGHT
                     };
 
                     struct SkeletonPoint
                     {
                         JointType jointType; 
                         int32_t confidenceImage; 
                         int32_t confidenceWorld; 
                         Point3DF32 world; 
                         PointF32   image; 
                         int32_t reserved[10];
                     };
 
                     struct Bone
                     {
                         JointType startJoint; 
                         JointType endJoint; 
                         PoseEulerAngles orientation; 
                         int32_t orientationConfidence; 
                         int32_t reserved[10];
                     };
 
                     virtual int32_t PXCAPI QueryNumJoints() = 0;
 
                     virtual bool32_t PXCAPI QueryJoints(SkeletonPoint* joints) = 0;
 
 #ifdef PT_MW_DEV
 
                     virtual int32_t PXCAPI QueryNumBones() = 0;
 
                     virtual bool32_t PXCAPI QueryBones(Bone* bones) = 0;
 #endif
                 };
 
                 class PersonTracking
                 {
                 public:
                     struct BoundingBox3D
                     {
                         Box3DF32 box;
                         int32_t confidence;
                     };
 
                     struct SpeedInfo
                     {
                         Point3DF32 direction;
                         float magnitude;
                     };
 
                     enum PersonOrientation
                     {
                         ORIENTATION_FRONTAL = 0,        
                                 ORIENTATION_45_DEGREE_RIGHT,    
                                 ORIENTATION_45_DEGREE_LEFT,     
                                 ORIENTATION_PROFILE_RIGHT,      
                                 ORIENTATION_PROFILE_LEFT,       
                                 ORIENTATION_REAR                
                     };
 
                     struct OrientationInfo
                     {
                         PersonOrientation orientation;
                         int32_t confidence;
                     };
 
                     enum class DetectionSource : std::int8_t
                     {
                         NOT_SPECIFIED,      
                         FACE,               
                         HEAD_SHOULDERS,     
                         UPPER_BODY,         
                         FULL_BODY,          
                         LOWER_BODY,         
                         HEAD_LESS,          
                         TORSO,              
                     };
 
                     enum class RelativeDistance : std::int8_t
                     {
                         NOT_SPECIFIED, 
                         IN_RANGE, 
                         RELATIVE_NEAR, 
                         RELATIVE_FAR 
                     };
 
                     struct ApproximateDistance
                     {
                         float distance; 
                         RelativeDistance relative; 
                     };
 
                     virtual int32_t PXCAPI QueryId() const = 0;
 
                     virtual BoundingBox2D PXCAPI Query2DBoundingBox() const = 0;
 
                     virtual Image* PXCAPI QuerySegmentationImage() = 0;
 
                     virtual PointCombined PXCAPI QueryCenterMass() = 0;
 
                     virtual ApproximateDistance PXCAPI QueryRelativeLocation() const = 0;
 
                     virtual BoundingBox2D PXCAPI QueryHeadBoundingBox() const = 0;
 
                     virtual Image* PXCAPI QueryBlobMask() = 0;
 #ifdef PT_MW_DEV
 
                     virtual OrientationInfo PXCAPI QueryPersonOrientation() = 0;
 #endif
 
                     virtual DetectionSource PXCAPI QueryDetectionSource() const = 0;
 
 #ifdef PT_MW_DEV
 
                     virtual BoundingBox3D PXCAPI Query3DBoundingBox() const = 0;
 
                     virtual bool32_t PXCAPI QuerySpeed(SpeedInfo& speed) const = 0;
 
                     virtual int32_t PXCAPI Query3DBlobPixelCount() const = 0;
 
                     virtual Status PXCAPI Query3DBlob(Point3DF32* blob) const = 0;
 
                     virtual float PXCAPI QueryHeight() const = 0;
 
                     virtual int32_t PXCAPI QueryContourSize() const = 0;
 
                     virtual Status PXCAPI QueryContourPoints(PointI32* contour) = 0;
 #endif
                 };
 
                 class PersonFace
                 {
                 public:
                     struct LandmarksLocation
                     {
                         Point3DF32 image; 
                         Point3DF32 world; 
                     };
 
                     struct LandmarksInfo
                     {
                         LandmarksLocation* landmarks; 
                         int32_t confidence; 
                         int numLandmarks; 
                     };
 
                     enum class FaceGaze
                     {
                         NOT_SPECIFIED,
                         FRONTAL,
                         LEFT,
                         LEFT_45,
                         RIGHT,
                         RIGHT_45
                     };
 
                     struct FaceGazeInfo
                     {
                         FaceGaze gaze; 
                         int32_t confidence; 
                     };
 
                     virtual int32_t PXCAPI QueryNumLandmarks() = 0;
 
                     virtual LandmarksInfo* PXCAPI QueryLandmarks() = 0;
 
                     virtual bool32_t PXCAPI QueryHeadPose(PoseEulerAngles& pose) const = 0;
 
                     virtual FaceGazeInfo PXCAPI QueryGaze() const = 0;
 #ifdef PT_MW_DEV
 
                     virtual PersonExpressions* PXCAPI QueryExpressions() = 0;
 #endif
                 };
 
                 class Person
                 {
                 public:
                     virtual PersonTracking* PXCAPI QueryTracking() = 0;
 
                     virtual PersonRecognition* PXCAPI QueryRecognition() = 0;
 
                     virtual PersonJoints* PXCAPI QuerySkeletonJoints() = 0;
 
                     virtual PersonGestures* PXCAPI QueryGestures() = 0;
 
                     virtual PersonFace* PXCAPI QueryFace() = 0;
 
 #ifdef PT_MW_DEV
 
                     virtual PersonPose* PXCAPI QueryPose() = 0;
 #endif
                 };
 
             public:
                 /* General */
 
                 /* Person Outputs */
 
                 virtual int32_t PXCAPI QueryNumberOfPeople(void) = 0;
 
                 virtual Person* PXCAPI QueryPersonData(AccessOrderType accessOrder, int32_t index) = 0;
 
                 virtual Person* PXCAPI QueryPersonDataById(int32_t personID) = 0;
 
                 virtual void PXCAPI StartTracking(int32_t personID) = 0;
 
                 virtual void PXCAPI StopTracking(int32_t personID) = 0;
 
                 virtual TrackingState PXCAPI GetTrackingState() = 0;
 
                 virtual void PXCAPI ResetTracking(void) = 0;
 
                 virtual RecognitionModuleData* PXCAPI QueryRecognitionModuleData() = 0;
 #ifdef PT_MW_DEV
 
                 virtual PersonLying* PXCAPI QueryPersonLying(void) = 0;
 
                 virtual ObjectProposal* PXCAPI QueryObjectProposal(void) = 0;
 
                 virtual void PXCAPI SetDetectionClassifierForNextFrame(PersonTracking::DetectionSource classifier) = 0;
 
 
                 /* Alerts Outputs */
 
                 virtual int32_t PXCAPI QueryFiredAlertsNumber(void) const = 0;
 
                 virtual Status PXCAPI QueryFiredAlertData(int32_t index, AlertData & alertData) const = 0;
 
                 virtual bool32_t PXCAPI IsAlertFired(AlertType alertEvent, AlertData & alertData) const = 0;
 #endif
             };
 
             typedef PersonTrackingData::AlertType AlertType;
             typedef PersonTrackingData::AccessOrderType AccessOrderType;
             typedef PersonTrackingData::TrackingState TrackingState;
             typedef PersonTrackingData::AlertData AlertData;
             typedef PersonTrackingData::PoseEulerAngles PoseEulerAngles;
             typedef PersonTrackingData::BoundingBox2D BoundingBox2D;
             typedef PersonTrackingData::PersonPose PersonPose;
             typedef PersonTrackingData::PersonPose::PositionState PositionState;
             typedef PersonTrackingData::PersonPose::PositionInfo PositionInfo;
             typedef PersonTrackingData::PersonPose::LeanInfo LeanInfo;
             typedef PersonTrackingData::PersonRecognition PersonRecognition;
             typedef PersonTrackingData::RecognitionModuleData RecognitionModuleData;
             typedef PersonTrackingData::PersonGestures PersonGestures;
             typedef PersonTrackingData::PersonGestures::GestureType GestureType;
             typedef PersonTrackingData::PersonGestures::PointingData2D PointingData2D;
             typedef PersonTrackingData::PersonGestures::PointingData3D PointingData3D;
             typedef PersonTrackingData::PersonGestures::PointingInfo PointingInfo;
             typedef PersonTrackingData::PersonExpressions PersonExpressions;
             typedef PersonTrackingData::PersonExpressions::PersonExpressionsEnum PersonExpressionsEnum;
             typedef PersonTrackingData::PersonExpressions::PersonExpressionsResult PersonExpressionsResult;
             typedef PersonTrackingData::PersonJoints PersonJoints;
             typedef PersonTrackingData::PersonJoints::JointType JointType;
             typedef PersonTrackingData::PersonJoints::SkeletonPoint SkeletonPoint;
             typedef PersonTrackingData::PersonJoints::Bone Bone;
             typedef PersonTrackingData::PersonTracking PersonTracking;
             typedef PersonTrackingData::PersonTracking::BoundingBox3D BoundingBox3D;
             typedef PersonTrackingData::PersonTracking::SpeedInfo SpeedInfo;
             typedef PersonTrackingData::PointInfo PointInfo;
             typedef PersonTrackingData::PointCombined PointCombined;
             typedef PersonTrackingData::PersonTracking::OrientationInfo OrientationInfo;
             typedef PersonTrackingData::Person Person;
             typedef PersonTrackingData::PersonRecognition::RecognitionStatus RecognitionStatus;
             typedef PersonTrackingData::PersonRecognition::RecognizerData RecognizerData;
             typedef PersonTrackingData::PersonRecognition::RecognizerScoreData RecognizerScoreData;
             typedef PersonTrackingData::PersonRecognition::RegistrationStatus RegistrationStatus;
             typedef PersonTrackingData::RecognitionModuleData::RecognizerDataWithStatus RecognizerDataWithStatus;
             typedef PersonTrackingData::RecognitionModuleData::RecognizeAllStatus RecognizeAllStatus;
         }
     }
 }
