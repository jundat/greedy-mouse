#include "BoardManager.h"
#include "MainGameScene.h"
#include "DataManager.h"
#include "CampaignScene.h"


void BoardManager::resetBoard(bool isReplay)
{
	CCLOG("[info] Start Reset Board!");
	if(isReplay == false)
	{
		status = STATUS_CHOOSE_START_ITEM;
		curNumMove = START_NUMBER_MOVES;
		curNumStar = 0;
	}
	else
	{
		this->removeAllChildren();

		this->getParent()->getChildByTag(TAG_SHADOW_MANAGER)->removeAllChildren();
		this->getParent()->getChildByTag(TAG_LINE_MANAGER)->removeAllChildren();
		this->getParent()->getChildByTag(TAG_CENTERPOINT_MANAGER)->removeAllChildren();
		this->getParent()->getChildByTag(TAG_STAR_MANAGER)->removeAllChildren();
		initBoard();
		curNumMove = START_NUMBER_MOVES;
		curNumStar = 0;
		status = STATUS_CHOOSE_START_ITEM;

		MainGameScene *a = (MainGameScene *)this->getParent();
		a->updateTextEnergy();
	}
	CCLOG("[info] End Reset Board!");
}

void BoardManager::initBoard()
{
	CCLOG("[info] Start Init Board!");
	ItemData** data = Map::GetInstance()->GetMap(curLevel);

	for (int i = 0; i < Map::MAP_ROW; i++)
	{
		for (int j = 0; j < Map::MAP_COL; j++)
		{
			MapItem *m_mapItem = MapItem::createItem((int)data[i][j].id,data[i][j].col,data[i][j].row,data[i][j].energy,data[i][j].destCol,data[i][j].destRow,data[i][j].keyId,data[i][j].lockId,data[i][j].lockItemId);
			if(m_mapItem)
			{
				this->addChild(m_mapItem, 1, 1);
				
				//////////////////////////////////////////////////////////////////////////
				if(m_mapItem->getId() == Start)
				{
					MainGameScene* mgs = (MainGameScene*) this->getParent();
					CCPoint p = ccp(m_mapItem->getPositionX(), m_mapItem->getPositionY());
					mgs->AddSTARTEff(p);
				}
				else if(m_mapItem->getId() == Finish)
				{
					MainGameScene* mgs = (MainGameScene*) this->getParent();
					CCPoint p = ccp(m_mapItem->getPositionX(), m_mapItem->getPositionY());
					mgs->AddFINISHEff(p);
				}
				//////////////////////////////////////////////////////////////////////////

				if(m_mapItem->getId() == Lock)
				{
					m_mapItem->createInviItem();

				}
			}
		}
	}
	CCLOG("[info] End Init Board!");
}

bool BoardManager::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//CCLog("Touched begin Pos : %f - %f" ,touch->getLocation().x, touch->getLocation().y);
	return true;
}

void BoardManager::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

}

bool BoardManager::isTouchedItemPossible(MapItem *item)
{
	if(status == STATUS_CHOOSE_START_ITEM)
	{
		return true;
	}
	else
		if(lastItemSelected != NULL && status != STATUS_CHOOSE_START_ITEM)
		{
			int deltaRow = abs(item->getRowForIt() - lastItemSelected->getRowForIt());
			int deltaCol = abs(item->getColForIt() - lastItemSelected->getColForIt());


			if(deltaRow == 1 && item->getColForIt() == lastItemSelected->getColForIt() && item->getIsIAvailableForIt() == true)
				return true;
			if(deltaCol == 1 && item->getRowForIt() == lastItemSelected->getRowForIt() && item->getIsIAvailableForIt() == true)
				return true;
		}
		else
			if(item->getIsIAvailableForIt() == false)
				return false;
			else
				if(item->getCurStatus() == sActived)
					return false;

	return false;

}

void BoardManager::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	MainGameScene *a = (MainGameScene *)this->getParent();

	for(int i = 0 ; i < this->getChildren()->count(); i++)
	{
		MapItem *mapItem = (MapItem *)this->getChildren()->objectAtIndex(i);
		if(mapItem)
		{
			if(mapItem->boundingBox().containsPoint(touch->getLocation()))
			{
				CCLog("Touched Item Pos %d - %d",mapItem->getRow(),mapItem->getCol());

				if(isTouchedItemPossible(mapItem))
				{
					if(mapItem->getCurStatus() == sNormal)
					{

#pragma region Main Logic Game
						switch (status)
						{
						case STATUS_CHOOSE_START_ITEM:
							{
								if(mapItem->getId() == Start)
								{
									if (G_IsPlaySound)
									{
										SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
									}

									MainGameScene *a = (MainGameScene *)this->getParent();
									a->updateTextEnergy();

									lastItemSelected = NULL;

									addNewShadowEffect(mapItem->getPosition());

									mapItem->makeItemActive();

									status = STATUS_PLAYING;

									if(lastItemSelected == NULL)
										lastItemSelected = mapItem;
								}
							}


							break;
						case STATUS_PLAYING:
							{
								//active this item
								addNewShadowEffect(mapItem->getPosition());
								mapItem->makeItemActive();

#pragma region Switch ID item
								//extra processing
								switch (mapItem->getId())
								{
								case None:
									break;

								case Lock:
									if (G_IsPlaySound)
									{
										SimpleAudioEngine::sharedEngine()->playEffect("sfx_goalcomplete.wav");
									}

									addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());
									break;

								case Bridge: //-----------------------------------------------------------------------------------
									{
										//phamtanlong
										curNumMove--;
										curNumMove--;
										//end


										if (G_IsPlaySound)
										{
											SimpleAudioEngine::sharedEngine()->playEffect("sfx_goalcomplete.wav");
										}

										MapItem *nextItem = getItemAtPos(mapItem->getDesRowForIt(),mapItem->getDesColForIt());

										if(nextItem == NULL)
										{
											CCLog("Null next item");
										}


										addNewShadowEffect(nextItem->getPosition());

										addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());

										addNewLineEffect(mapItem->getPosition(),nextItem->getPosition());

										nextItem->makeItemActive();
										lastItemSelected =  nextItem;
										
										if(lastItemSelected->getIDForIt() == Finish)
										{
											if(curNumMove >= 0)
											{
												//Add layer WIN
												MainGameScene* mgs = (MainGameScene*)this->getParent();
												mgs->SetTouchEnable(false);

												status = STATUS_FINISH;
												DataManager::GetInstance()->SetLevelStar(curLevel + 1,curNumStar);
												DataManager::GetInstance()->SetCurrentLevel(curLevel + 2);

												MainGameScene *a = (MainGameScene *)this->getParent();

												a->showCompletedLevel(curLevel,curNumStar);
											}
										}
										else
										{
											status = STATUS_PLAYING;
										}


										//phamtanlong
										if(nextItem != NULL && nextItem->getId() > 0)
										{
											MainGameScene *a = (MainGameScene *)this->getParent();
											switch(nextItem->getId())
											{
											case Energy:
												curNumMove += nextItem->getEnergy();
												a->updateTextEnergy();
												break;

											case Star:
												curNumStar++;
												a->UpdateStar(curNumStar);
												break;

											case Teleport:
												status = STATUS_CHOOSE_START_ITEM;
												CCLog("Touched teleport make choose start item");
												break;
											}
											//break;
										}
										//end

 
 										mapItem = NULL;
 										return;
									}

									break;

								case Energy:
									{
										if (G_IsPlaySound)
										{
											SimpleAudioEngine::sharedEngine()->playEffect("sfx_goalcomplete.wav");
										}

										curNumMove--;
										curNumMove += mapItem->getEnergy();

										MainGameScene *a = (MainGameScene *)this->getParent();
										a->updateTextEnergy();

										addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());
									}
									
									break;

								case Key:
									{

										if (G_IsPlaySound)
										{
											SimpleAudioEngine::sharedEngine()->playEffect("sfx_goalcomplete.wav");
										}

										int keyId = mapItem->getKeyId();
										curNumMove--;
										MainGameScene *a = (MainGameScene *)this->getParent();
										a->updateTextEnergy();

										addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());
										switch (keyId)
										{
										case Red:
											{
												//1. Get all Lock have this keyID
												CCArray *resLockRed = getLockWithKeyID(keyId);
												//2. Active all Lock here
												for (int i = 0 ; i < resLockRed->count();i++)
												{
													MapItem *lock = (MapItem *)resLockRed->objectAtIndex(i);
													if(lock->getLockItemId() != 0)
													{
														lock->setIsInviItemActived(true);
														lock->setVisible(false);
														MapItem *itemInvi = getItemAtPos(lock->getRowForIt(),lock->getColForIt());
														itemInvi->setIsIAvailable(true);
													}
												}
											}
											break;
										case Blue:
											{
												CCArray *resLockBlue = getLockWithKeyID(keyId);
												//2. Active all Lock here
												for (int i = 0 ; i < resLockBlue->count();i++)
												{
													MapItem *lock = (MapItem *)resLockBlue->objectAtIndex(i);
													if(lock->getLockItemId() != 0)
													{
														lock->setIsInviItemActived(true);
														lock->setVisible(false);
														MapItem *itemInvi = getItemAtPos(lock->getRowForIt(),lock->getColForIt());
														itemInvi->setIsIAvailable(true);
													}
												}
											}

											break;
										case Yellow:
											{
												CCArray *resLockYellow = getLockWithKeyID(keyId);
												//2. Active all Lock here
												for (int i = 0 ; i < resLockYellow->count();i++)
												{
													MapItem *lock = (MapItem *)resLockYellow->objectAtIndex(i);
													if(lock->getLockItemId() != 0)
													{
														lock->setIsInviItemActived(true);
														lock->setVisible(false);
														MapItem *itemInvi = getItemAtPos(lock->getRowForIt(),lock->getColForIt());
														itemInvi->setIsIAvailable(true);
													}
												}
											}

											break;
										case Green:
											{
												CCArray *resLockGreen = getLockWithKeyID(keyId);
												//2. Active all Lock here
												for (int i = 0 ; i < resLockGreen->count();i++)
												{
													MapItem *lock = (MapItem *)resLockGreen->objectAtIndex(i);
													if(lock->getLockItemId() != 0)
													{
														lock->setIsInviItemActived(true);
														lock->setVisible(false);
														MapItem *itemInvi = getItemAtPos(lock->getRowForIt(),lock->getColForIt());
														itemInvi->setIsIAvailable(true);
													}
												}
											}

											break;
										}
									}
									break;

								case Normal:
									{
										if (G_IsPlaySound)
										{
											SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
										}

										//Reduce num move;
										curNumMove--;
										MainGameScene *a = (MainGameScene *)this->getParent();
										a->updateTextEnergy();

										addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());
									}
									
									break;

								case Star:
									if(curNumStar >= 0 && curNumStar <=2)
									{
										if (G_IsPlaySound)
										{
											SimpleAudioEngine::sharedEngine()->playEffect("sfx_goalcomplete.wav");
										}

										curNumMove--;
										MainGameScene *a = (MainGameScene *)this->getParent();
										a->updateTextEnergy();
										curNumStar++;

										a->UpdateStar(curNumStar);
										addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());
									}

									break;

								case Start:
									{
										if (G_IsPlaySound)
										{
											SimpleAudioEngine::sharedEngine()->playEffect("sfx_button.wav");
										}
										this->status = STATUS_PLAYING;
										curNumMove--;
										MainGameScene *a = (MainGameScene *)this->getParent();
										a->updateTextEnergy();
										addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());
									}
									
									break;

								case Teleport:
									{
										if (G_IsPlaySound)
										{
											SimpleAudioEngine::sharedEngine()->playEffect("sfx_goalcomplete.wav");
										}

										curNumMove--;
										MainGameScene *a = (MainGameScene *)this->getParent();
										a->updateTextEnergy();
										addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());

										//1. Set status is CHoose_Start_Item => Make player choose next start item
										status = STATUS_CHOOSE_START_ITEM;

										CCLog("Touched teleport make choose start item");
									}

									break;

								case Finish:
									{
										curNumMove--;
										MainGameScene *a = (MainGameScene *)this->getParent();
										a->updateTextEnergy();

										addNewLineEffect(mapItem->getPosition(),lastItemSelected->getPosition());

										//So add WIN here
										if(curNumMove >= 0)
										{

											if (G_IsPlaySound)
											{
												SimpleAudioEngine::sharedEngine()->playEffect("sfx_levelcomplete.wav");
											}

											//Add layer WIN
											status = STATUS_FINISH;
											DataManager::GetInstance()->SetLevelStar(curLevel + 1,curNumStar);
											DataManager::GetInstance()->SetCurrentLevel(curLevel + 2);


											MainGameScene *a = (MainGameScene *)this->getParent();

											a->showCompletedLevel(curLevel,curNumStar);
										}
									}
									break;
								}
#pragma endregion


								if(lastItemSelected == NULL)
									lastItemSelected = mapItem;
								else
								{
									if(mapItem != NULL)
										curItemSelected = mapItem;

									///AD effffect

									lastItemSelected = curItemSelected;
									curItemSelected = NULL;

								}
								break;
							}

						}


						if(curNumMove == 0 && status == STATUS_PLAYING)
						{
							//LOSEEEEEEEEEEEEEEEEEEEEEEEEEEE HERE
							//Add layer WIN

							if (G_IsPlaySound)
							{
								SimpleAudioEngine::sharedEngine()->playEffect("sfx_gameover.wav");
							}
							status = STATUS_FINISH;

							MainGameScene *a = (MainGameScene *)this->getParent();

							a->showFailedLevel();
						}

#pragma endregion
					}
				}
				return;
			}
		}

	}
} 

void BoardManager::touchDelegateRetain()
{
	this->retain();
}

void BoardManager::touchDelegateRelease()
{
	this->release();
}

void BoardManager::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	//CCSprite::onEnter();
}

void BoardManager::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	//CCSprite::onExit();
}    

CCArray* BoardManager::getLockWithKeyID(int key)
{
	CCArray *res = new CCArray();
	for(int i = 0 ; i < this->getChildren()->count(); i++)
	{
		MapItem *item = (MapItem *)this->getChildren()->objectAtIndex(i);
		if(item->getIDForIt() == Lock)
		{
			if(item->getLockId() == key)
			{
				res->addObject(item);
			}
		}


	}

	return res;

}

MapItem* BoardManager::getItemAtPos(int row,int col)
{
	if(row < 0 || row > 7)
		return NULL;
	if(col < 0 || col > 10)
		return NULL;

	for(int i = 0 ; i < this->getChildren()->count(); i++)
	{
		MapItem *item = (MapItem *)this->getChildren()->objectAtIndex(i);

		if(item->getColForIt() == col && item->getRowForIt() == row)
		{
			return item;
			break;
		}
	}
	return NULL;
}

void BoardManager::addNewLineEffect(CCPoint pos1,CCPoint pos2)
{
	if(status == STATUS_PLAYING || status == STATUS_CHOOSE_START_ITEM)
	{
		//Create Line beetween 2 Item
		Line *newLine = Line::createLine(pos1,pos2);
		this->getParent()->getChildByTag(TAG_LINE_MANAGER)->addChild(newLine);

		//Create center point 1
		CCSprite *sprCenterPoint = new CCSprite();
		sprCenterPoint->initWithFile("centerpoint.png");
		sprCenterPoint->setPosition(pos1);
		this->getParent()->getChildByTag(TAG_CENTERPOINT_MANAGER)->addChild(sprCenterPoint);

		CCSprite *sprCenterPoint2 = new CCSprite();
		sprCenterPoint2->initWithFile("centerpoint.png");
		sprCenterPoint2->setPosition(pos2);
		this->getParent()->getChildByTag(TAG_CENTERPOINT_MANAGER)->addChild(sprCenterPoint2);
	}
}

void BoardManager::addNewShadowEffect(CCPoint pos)
{
	CCSprite *shadowSpr = new CCSprite();
	shadowSpr->initWithFile("actived.png");
	shadowSpr->setPosition(pos);
	this->getParent()->getChildByTag(TAG_SHADOW_MANAGER)->addChild(shadowSpr);
}

bool BoardManager::isLimitStep(int row,int col)
{
	CCPoint left = ccp(row,col -1);
	CCPoint right = ccp(row,col + 1);
	CCPoint down  = ccp(row - 1, col);
	CCPoint up = ccp(row + 1,col);

	if(getItemAtPos(left.x,left.y) == NULL && getItemAtPos(right.x,right.y) == NULL &&
			getItemAtPos(up.x,up.y) == NULL && getItemAtPos(down.x,down.y) == NULL)
	{

		return true;
	}

	return false;
}

CCScene* BoardManager::scene()
{
	CCScene *scene = CCScene::create();
	BoardManager *layer = BoardManager::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool BoardManager::init()
{
	if( !CCLayer::init())
	{
		return false;
	}

	return true;
}

void BoardManager::setLevel( int level )
{
	this->curLevel = level;
}
