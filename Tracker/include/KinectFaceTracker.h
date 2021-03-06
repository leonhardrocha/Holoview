//------------------------------------------------------------------------------
// <copyright file="FTHelper.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#pragma once
#pragma warning(disable:4786)
#include <FaceTrackLib.h>
#include "KinectSensor.h"
#include "ITracker.h"
#include "Callable.h"
#include <vector>
#include <queue>
#include <map>



class TrackerConfig
{
public:	
	TrackerConfig() :
		m_DrawMask(TRUE),
		m_depthType(NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX),
		m_depthRes(NUI_IMAGE_RESOLUTION_320x240),
		m_bNearMode(TRUE),
		m_bFallbackToDefault(TRUE),
		m_bSeatedSkeletonMode(TRUE),
		m_colorType(NUI_IMAGE_TYPE_COLOR),	
		m_colorRes(NUI_IMAGE_RESOLUTION_640x480)
	{}
	BOOL                 m_DrawMask;
	NUI_IMAGE_TYPE       m_depthType;
	NUI_IMAGE_RESOLUTION m_depthRes;
	BOOL                 m_bNearMode;
	BOOL                 m_bFallbackToDefault;
	BOOL                 m_bSeatedSkeletonMode;
	NUI_IMAGE_TYPE       m_colorType;
	NUI_IMAGE_RESOLUTION m_colorRes;
};

class KinectFaceTracker : public Callable
{
public:
	KinectFaceTracker() : m_pKinectSensor(NULL), m_pFaceTracker(NULL), m_pFTResult(NULL), m_colorImage(NULL), m_depthImage(NULL) {};	
    ~KinectFaceTracker();
	HRESULT			Stop();
	HRESULT			GetTrackerResult();
	bool			Start();
	bool			Init();
	void			CheckCameraInput();
	float   		GetPitch()         { return(pitch);}
	IFTResult*		GetResult()        { return(m_pFTResult);}
    IFTImage*		GetColorImage()    { return(m_colorImage);}
    float			GetXCenterFace()   { return(m_XCenterFace);}
    float			GetYCenterFace()   { return(m_YCenterFace);}
    BOOL			IsMaskDraw()	   { return(m_config.m_DrawMask);}
    IFTFaceTracker* GetTracker()       { return(m_pFaceTracker);}
	KinectSensor*   GetSensor()        { return(m_pKinectSensor);}
    BOOL			IsKinectPresent()  { return(IsKinectSensorPresent);}
	void		    SetWindow(HWND hWnd){ m_hWnd = hWnd;}
    HRESULT			GetCameraConfig(FT_CAMERA_CONFIG* cameraConfig);
	IAvatar*		GetAvatar()			{ return m_pKinectSensor != NULL ? m_pKinectSensor->GetEggAvatar() : NULL;};
	float			GetFaceConfidence() { return m_faceConfidence; };
 
	static DWORD WINAPI			FaceTrackingStaticThread(PVOID lpParam);	
	HANDLE						GetThreadId() { return m_hFaceTrackingThread; };		

	
protected:
	KinectSensor*               m_pKinectSensor;
	HANDLE						m_hFaceTrackingThread;	
	IFTFaceTracker*             m_pFaceTracker;
    IFTResult*                  m_pFTResult;
    IFTImage*                   m_colorImage;
    IFTImage*                   m_depthImage;
    FT_VECTOR3D                 m_hint3D[2]; 
	
	float						m_faceConfidence;

	bool						IsKinectSensorPresent;
    float                       m_XCenterFace;
    float                       m_YCenterFace;
	float						pitch, yaw, roll;

	HWND						m_hWnd;
	bool						m_LastTrackSucceeded;
	bool						m_ApplicationIsRunning;
	TrackerConfig				m_config;

    BOOL SubmitFraceTrackingResult(IFTResult* pResult);
    void SetCenterOfImage(IFTResult* pResult);
	DWORD WINAPI FaceTrackingThread();

	
};

