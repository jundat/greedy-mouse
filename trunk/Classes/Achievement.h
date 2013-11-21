// #ifndef __ACHIEVEMENT__
// #define __ACHIEVEMENT__
// #include <vector>
// #include "cocos2d.h"
// USING_NS_CC;
// using namespace std;
// 
// #define ACHI_STEP_1			1
// #define ACHI_STAR_3			2
// #define ACHI_LEVEL_1		3
// #define ACHI_STEP_100		4
// #define ACHI_STAR_10		5
// #define ACHI_STEP_1000		6
// #define ACHI_STAR_20		7
// #define ACHI_STAR_40		8
// 
// // class Achievement_Data
// // {
// // 	public:
// // 		int Star;
// // 		int Step;
// // 		int Level;
// // 		int CurrentAchievement;
// // 		int NameAchi;
// // 	Achievement_Data(void);
// // 	Achievement_Data(int _star,int _step, int _level, int _CurrentAchievement, int _name);
// // };
// 
// class Achievement
// {
// private:
// 	Achievement(void);
// 	static Achievement *_instance;
// public:
// 	~Achievement(void);
// 	static Achievement* GetInstance();
// 	
// 	static CCSprite* CreateAchievementSprite(int _type);
// 	CCSprite* DoAchievement();
// 	//vector<Achievement_Data*> m_listAchievement;
// 	vector<int> m_listCompleteAchievement;
// 
// 	int m_achieStar;
// 	int	m_achieStep;
// 	int	m_achieLevel;
// 
// 	void SetStar(int _star);
// 	void SetStep(int _step);
// 	void SetLevel(int _level);
// 
// 	int GetStar();
// 	int GetStep();
// 	int GetLevel();
// 
// 	bool isAchievement(int _index);
// 	void GetCompleteAchievement();
// 	bool isNotContain(int _indexAchievement);
// 
// };
// #endif
