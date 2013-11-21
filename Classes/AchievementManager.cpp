// #include "AchievementManager.h"
// 
// 
// AchievementManager::AchievementManager(void)
// {
// }
// 
// 
// AchievementManager::~AchievementManager(void)
// {
// }
// 
// void AchievementManager::update( float dt )
// {
// 	CCSprite* newSprite = Achievement::GetInstance()->DoAchievement();
// 
// 	if(newSprite != NULL)
// 	{
// 		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
// 		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
// 		//newSprite->setPosition(ccp(visibleSize.width + origin.x + newSprite->getContentSize().width/2, visibleSize.height/2 + origin.y));
// 		newSprite->setPosition(ccp(visibleSize.width/2 + origin.x,visibleSize.height + newSprite->getContentSize().height/2));
// 
// 		CCSequence* seq = CCSequence::create(
// 			//CCMoveTo::create(3.0f, ccp(-newSprite->getContentSize().width/2,visibleSize.height/2 + origin.y)),
// 			CCMoveTo::create(2.0f, ccp(visibleSize.width/2 + origin.x,-newSprite->getContentSize().height/2)),
// 			CCCallFuncN::create(this, callfuncN_selector(AchievementManager::RemoveSomething)),
// 			NULL
// 			);
// 
// 		newSprite->runAction(seq);
// 
// 		this->addChild(newSprite);
// 	}
// }
// 
// void AchievementManager::RemoveSomething( CCNode* pSender )
// {
// 	this->removeChild(pSender);
// }
// 
// void AchievementManager::SetStar( int _star )
// {
// 	Achievement::GetInstance()->SetStar(_star);
// }
// 
// void AchievementManager::SetStep( int _step )
// {
// 	Achievement::GetInstance()->SetStep(_step);
// }
// 
// void AchievementManager::SetLevel( int _level )
// {
// 	Achievement::GetInstance()->SetLevel(_level);
// }
// 
