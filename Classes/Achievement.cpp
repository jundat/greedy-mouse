// #include "Achievement.h"
// 
// 
// Achievement_Data::Achievement_Data(void)
// {
// 	Star = 0;
// 	Step = 0;
// 	Level = 0;
// }
// 
// Achievement_Data::Achievement_Data(int _star,int _step, int _level,int _CurrentAchievement, int _name)
// {
// 	Star = _star;
// 	Step = _step;
// 	Level = _level;
// 	CurrentAchievement = _CurrentAchievement;
// 	NameAchi = _name;
// }
// 
// Achievement* Achievement::_instance = 0;
// 
// Achievement* Achievement::GetInstance()
// {
// 	if(Achievement::_instance == 0)
// 	{
// 		_instance = new Achievement();
// 	}
// 	return _instance;
// }
// 
// 
// Achievement::Achievement()
// {
// 	m_achieStar = CCUserDefault::sharedUserDefault()->getIntegerForKey("ACHIEVEMENT_STAR");
// 	m_achieStep = CCUserDefault::sharedUserDefault()->getIntegerForKey("ACHIEVEMENT_STEP");
// 	m_achieLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("ACHIEVEMENT_LEVEL");
// 	m_achieStep = 0;
// 	// 1 Star, 2 step, 3 Level
// 	m_listAchievement.push_back(new Achievement_Data(0,1,0,1, ACHI_STEP_1));
// 	m_listAchievement.push_back(new Achievement_Data(3,0,0,2, ACHI_STAR_3));
// 	m_listAchievement.push_back(new Achievement_Data(0,0,1,3, ACHI_LEVEL_1));
// 	m_listAchievement.push_back(new Achievement_Data(0,100,0,4, ACHI_STEP_100));
// 	m_listAchievement.push_back(new Achievement_Data(10,0,0,5, ACHI_STAR_10));
// 	m_listAchievement.push_back(new Achievement_Data(0,1000,0,6, ACHI_STEP_1000));
// 	m_listAchievement.push_back(new Achievement_Data(20,0,0,7, ACHI_STAR_20));
// 	m_listAchievement.push_back(new Achievement_Data(40,0,0,8, ACHI_STAR_40));
// 	GetCompleteAchievement();
// }
// 
// 
// 
// Achievement::~Achievement(void)
// {
// }
// 
// int Achievement::GetStar()
// {
// 	return m_achieStar;
// }
// 
// int Achievement::GetStep()
// {
// 	return m_achieStep;
// }
// 
// int Achievement::GetLevel()
// {
// 	return m_achieLevel;
// }
// 
// void Achievement::SetStep(int _step)
// {
// 	m_achieStep = _step;
// 	//CCUserDefault::sharedUserDefault()->setIntegerForKey("ACHIEVEMENT_STEP", m_achieStep);
// }
// 
// void Achievement::SetLevel(int _level)
// {
// 	m_achieLevel = _level;
// 	//CCUserDefault::sharedUserDefault()->setIntegerForKey("ACHIEVEMENT_LEVEL", m_achieLevel);
// }
// 
// void Achievement::SetStar(int _star)
// {
// 	m_achieStar = _star;
// 	//CCUserDefault::sharedUserDefault()->setIntegerForKey("ACHIEVEMENT_STAR", m_achieStar);
// }
// 
// bool Achievement::isAchievement(int _index)
// {
// 	if(m_listAchievement[_index]->Level <= m_achieLevel && m_listAchievement[_index]->Star <= m_achieStar && m_listAchievement[_index]->Step <= m_achieStep)
// 		return true;
// 	return false;
// }
// 
// void Achievement::GetCompleteAchievement()
// {
// 	//m_listCompleteAchievement.clear();
// 	int size = m_listAchievement.size();
// 	for(int i = 0;i < size; i++)
// 	{
// 		if(isAchievement(i) && (isNotContain(m_listAchievement[i]->CurrentAchievement)))
// 		{
// 			m_listCompleteAchievement.push_back(m_listAchievement[i]->CurrentAchievement);
// 			int a = 0;
// 			a++;
// 		}
// 	}
// }
// 
// CCSprite* Achievement::DoAchievement()
// {
// 	int size = m_listAchievement.size();
// 	for(int i = 0;i < size; i++)
// 	{
// 		if(isAchievement(i))
// 		{
// 			if(isNotContain(m_listAchievement[i]->CurrentAchievement))
// 			{
// 				CCSprite* newSprite = Achievement::CreateAchievementSprite(m_listAchievement[i]->NameAchi);
// 				m_listCompleteAchievement.push_back(m_listAchievement[i]->CurrentAchievement);
// 				//GetCompleteAchievement();
// 				return newSprite;
// 			}
// 		}
// 	}
// 	return NULL;
// }
// 
// bool Achievement::isNotContain(int _index)
// {
// 	int size = m_listCompleteAchievement.size();
// 	for(int i = 0;i < size;i++)
// 	{
// 		if(m_listCompleteAchievement[i] == _index)
// 		{
// 			return false;
// 		}
// 	}
// 	return true;
// }
// 
// 
// CCSprite* Achievement::CreateAchievementSprite(int _type)
// {
// 	CCSprite *newSprite = new CCSprite();
// 	newSprite->initWithFile("/achi/achi.png");
// 	CCSprite *d = new CCSprite();
// 	//int a = 0;
// 	switch (_type)
// 	{
// 		/*	Step_1,
// 		Step_3,
// 		Level_1,
// 		Step_100,
// 		Star_10,
// 		Step_1000,
// 		Star_20,
// 		Star_40*/
// 		//d->initWithFile("AchiPopup_01.png");
// 		//newSprite->addChild(d);
// 		
// 	case ACHI_STEP_1:
// 		d->initWithFile("01.png");
// 		
// 		newSprite->addChild(d);
// 		break;
// 	case ACHI_STAR_3:
// 		d->initWithFile("02.png");
// 		
// 		newSprite->addChild(d);
// 		break;
// 	case ACHI_LEVEL_1:
// 		d->initWithFile("03.png");
// 		newSprite->addChild(d);
// 		break;
// 	case ACHI_STEP_100:
// 		d->initWithFile("04.png");
// 		newSprite->addChild(d);
// 		break;
// 	case ACHI_STAR_10:
// 		d->initWithFile("05.png");
// 		newSprite->addChild(d);
// 		break;
// 	case ACHI_STEP_1000:
// 		d->initWithFile("06.png");
// 		newSprite->addChild(d);
// 		break;
// 	case ACHI_STAR_20:
// 		d->initWithFile("07.png");
// 		newSprite->addChild(d);
// 		break;
// 	case ACHI_STAR_40:
// 		d->initWithFile("08.png");
// 		newSprite->addChild(d);
// 		break;
// 	default:
// 		return NULL;
// 		break;
// 	}
// 	d->setPosition(ccp(450,60));
// 	return newSprite;
// }