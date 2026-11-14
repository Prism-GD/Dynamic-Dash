#pragma once
#include "cocos2d.h"
class LoadingScene { public: static cocos2d::Scene* createScene(); };
class MainMenuScene { public: static cocos2d::Scene* createScene(); };
class LevelSelectScene { public: static cocos2d::Scene* createScene(); };
class GameplayScene : public cocos2d::Scene {
public: static cocos2d::Scene* createScene(); bool init() override; CREATE_FUNC(GameplayScene);
private:
 void update(float dt) override; void jump(); void finish(bool won);
 cocos2d::DrawNode* world_=nullptr; cocos2d::Label* progress_=nullptr; cocos2d::Label* message_=nullptr;
 cocos2d::Vec2 player_; float velocity_=0, distance_=0; bool grounded_=true, ended_=false;
};