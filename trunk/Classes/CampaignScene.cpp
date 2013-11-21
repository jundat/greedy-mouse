#include "CampaignScene.h"
#include "MenuScene.h"
#include "MainGameScene.h"
#include "CampaignData.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

CCScene* CampaignScene::scene()
{
	CCScene *scene = CCScene::create();
	CampaignScene *layer = CampaignScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool CampaignScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}
	
	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	}

	//touch init...
	isMove = false;

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//content campaign...

	m_sprCampaign = CCSprite::create("seclectReveiw.png");
	m_sprCampaign->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	//map
	loadMap(m_sprCampaign);
	this->addChild(m_sprCampaign, 0);

	//back button...

	CCMenuItemImage* btnBack = CCMenuItemImage::create("buttomMenu.png", "buttomMenuPr.png", this, menu_selector(CampaignScene::back2Menu));
	btnBack->setPosition(ccp(btnBack->getContentSize().width/2 - visibleSize.width/2, btnBack->getContentSize().height/2 - visibleSize.height/2));

	CCMenu* menu = CCMenu::create(btnBack, NULL); //
	this->addChild(menu, 0);

	this->scheduleUpdate();
	return true;
}

CCSprite* CampaignScene::loadMap(CCSprite* sprCampaign)
{
	int len = (sizeof(g_campaignLocations)/sizeof(*g_campaignLocations));
	CCSize size = sprCampaign->getContentSize();

	int currentLevel = DataManager::GetInstance()->GetCurrenLevel();
	currentLevel--;

	for (int i = 0; i < len; ++i)
	{
		if (i < currentLevel)
		{
			int star = DataManager::GetInstance()->GetLevelStar(i+1);
			CCString* _buf = CCString::createWithFormat("%dStar.png", star); //1 sai lầm cực kỳ lớn khi gõ tên "Star" thành "star"

			CCSprite* point = CCSprite::create(_buf->getCString());
			point->setPosition(ccp(g_campaignLocations[i][0], size.height - g_campaignLocations[i][1]));
			sprCampaign->addChild(point, 0, i); //tag = i
		} 
		else if( i == currentLevel) //current level
		{
			CCSprite* point = CCSprite::create("0Star.png");
			point->setPosition(ccp(g_campaignLocations[i][0], size.height - g_campaignLocations[i][1]));
			sprCampaign->addChild(point, 0, i); //tag = i
		}
		else //draw locked level
		{
			CCSprite* point = CCSprite::create("lock.png");
			point->setPosition(ccp(g_campaignLocations[i][0], size.height - g_campaignLocations[i][1]));
			sprCampaign->addChild(point, 0, i); //tag = i
		}
	}
	
	return sprCampaign;
}

bool CampaignScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void CampaignScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	isMove = true;
}

void CampaignScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gốc tọa độ ở góc dưới, bên trái

	CCSprite* point = CCSprite::create("0Star.png");
	int RECT_SIZE = point->getContentSize().width/2 + point->getContentSize().height/2;
	int RECT_SIZE2 = RECT_SIZE/2;

	if(isMove == false)
	{
		int len = (sizeof(g_campaignLocations)/sizeof(*g_campaignLocations));
		
		for (int i = 0; i < len; ++i)
		{
			CCRect rect = CCRect(g_campaignLocations[i][0] - RECT_SIZE2, visibleSize.height - (g_campaignLocations[i][1]) - RECT_SIZE2, RECT_SIZE, RECT_SIZE);
			if(rect.containsPoint(pTouch->getLocation()))
			{
				if(DataManager::GetInstance()->GetCurrenLevel() - 1 >= i)
				{
					if (G_IsPlaySound)
					{
						SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
					}

					gotoplay(i);
					break;
				}
			}
		}
	}

	isMove = false;
}

void CampaignScene::back2Menu( CCObject* pSender )
{
	if (G_IsPlaySound)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
	}

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.3, MenuScene::scene()));
}

void CampaignScene::gotoplay( int level )
{
	CCLOG("[info] Start create MainGameScene");
	CCScene* maingame = MainGameScene::scene(level);
	CCLOG("[info] End create MainGameScene");

	CCScene* transScene = CCTransitionFade::create(0.3, maingame);
	CCDirector::sharedDirector()->replaceScene(transScene);
}
