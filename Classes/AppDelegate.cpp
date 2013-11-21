
#include "AppDelegate.h"

#include <vector>
#include <string>

#include "Global.h"

#include "MainGameScene.h"
#include "AppMacros.h"
#include "SplashScene.h"
#include "DataManager.h"
#include "CampaignScene.h"
#include "MenuScene.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
using namespace std;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setViewName("Greedy Mouse");

#ifdef WIN32
	eglView->setFrameSize(1280, 768);
	eglView->setFrameZoomFactor(0.9);
#endif
	
	pDirector->setOpenGLView(eglView);
	pDirector->setDisplayStats(false);
	pDirector->setAnimationInterval(1.0 / 60);

	eglView->setDesignResolutionSize(1280, 768, kResolutionExactFit);

	//////////////////////////////////////////////////////////////////////////

	// set searching path
	vector<string> searchPath;
	searchPath.push_back("assets");
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);


	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgSong.wav");


	//----------------------------- INIT MAP ---------------------------------
	if(DataManager::GetInstance()->GetCurrenLevel() == 0)
	{
		DataManager::GetInstance()->SetCurrentLevel(1);
	}


	// create a scene. it's an autorelease object
	CCScene *pScene = SplashScene::scene();

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->startAnimation();
}
