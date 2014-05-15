#include "stdafx.h"
#include "AssetWindow.h"

AssetWindow::AssetWindow() : ToeInStereoView()
{
}

void AssetWindow::ResetWindow()
{
	windowWidth = width();
	windowHeight = height();
	windowOffsetX = 0;
	windowOffsetY = 0;
}

void AssetWindow::initialize()
{
	ResetWindow();
	SetupWindow();
	ResetView();
	SetupView();
	SetupScene();
	renderer.Initialize();
	SetRenderer((BaseAssetRenderer&) renderer);
	tracker.SetTrackerCallback(AssetWindow::TrackerUpdateStatic, this, NULL);
}

void AssetWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
	RenderStereoView();
}


void AssetWindow::RenderScene()
{
	renderer.Render();
}

void AssetWindow::TrackerUpdateStatic(void* lpParam, void* args)
{
	AssetWindow* pThis = reinterpret_cast<AssetWindow*>(lpParam);
	auto results = pThis->tracker.GetTrackingResults();
	pThis->render();
}

void AssetWindow::resizeWindow()
{
	ResetWindow();
	ResetView();
	SetupScene();
}

//void AssetWindow::exposeEvent(QExposeEvent *event)
//{
//    Q_UNUSED(event);
//
//    if (isExposed())
//	{
//		//TrackerUpdateStatic(this);
//        renderNow();
//	}
//}