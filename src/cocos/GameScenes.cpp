#include "GameScenes.h"
#include <algorithm>
#include <array>
#include <string>
USING_NS_CC;
namespace {
const Color4B BG(10,14,34,255), CYAN(35,235,255,255), PURPLE(160,75,255,255), WHITE(245,248,255,255);
constexpr float GROUND=105.0f;
void background(Scene* s){s->addChild(LayerColor::create(BG),-10);}
Label* label(const std::string& t,float n,Vec2 p,Color4B c=WHITE){auto l=Label::createWithSystemFont(t,"Arial",n);l->setTextColor(c);l->setPosition(p);return l;}
MenuItemLabel* button(const std::string& t,float n,Vec2 p,const ccMenuCallback& cb){auto i=MenuItemLabel::create(label(t,n,Vec2::ZERO,CYAN),cb);i->setPosition(p);return i;}
}
Scene* LoadingScene::createScene(){
 auto s=Scene::create();background(s);auto z=Director::getInstance()->getVisibleSize();
 s->addChild(label("DYNAMIC DASH",44,{z.width/2,z.height/2+38},CYAN));
 s->addChild(label("Preparing game...",20,{z.width/2,z.height/2-28}));
 auto bar=DrawNode::create();Vec2 c(z.width/2,z.height/2-65);
 bar->drawSolidRect(c-Vec2(180,5),c+Vec2(180,5),Color4F(.18f,.2f,.3f,1));
 bar->drawSolidRect(c-Vec2(180,5),c+Vec2(180,5),Color4F(.1f,.9f,1,1));s->addChild(bar);
 s->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([]{Director::getInstance()->replaceScene(TransitionFade::create(.25f,MainMenuScene::createScene()));}),nullptr));return s;
}
Scene* MainMenuScene::createScene(){
 auto s=Scene::create();background(s);auto z=Director::getInstance()->getVisibleSize();
 s->addChild(label("DYNAMIC DASH",58,{z.width/2,z.height*.69f},CYAN));
 s->addChild(label("RHYTHM  •  JUMP  •  REPEAT",18,{z.width/2,z.height*.57f},PURPLE));
 auto play=button("PLAY",34,{z.width/2,z.height*.36f},[](Ref*){Director::getInstance()->replaceScene(TransitionFade::create(.2f,LevelSelectScene::createScene()));});
 auto m=Menu::create(play,nullptr);m->setPosition(Vec2::ZERO);s->addChild(m);
 s->addChild(label("1.0.0-ALPHA.1  •  EARLY TEST BUILD",14,{z.width/2,28},Color4B(145,155,185,255)));return s;
}
Scene* LevelSelectScene::createScene(){
 auto s=Scene::create();background(s);auto z=Director::getInstance()->getVisibleSize();
 s->addChild(label("SELECT LEVEL",42,{z.width/2,z.height*.78f},CYAN));
 auto d=DrawNode::create();Vec2 c(z.width/2,z.height*.48f);
 d->drawSolidRect(c-Vec2(205,65),c+Vec2(205,65),Color4F(.08f,.12f,.25f,1));
 d->drawRect(c-Vec2(205,65),c+Vec2(205,65),Color4F(.12f,.85f,1,1),3);s->addChild(d);
 s->addChild(label("1",28,c+Vec2(-155,0),PURPLE));s->addChild(label("FIRST STEPS",28,c+Vec2(15,13)));
 s->addChild(label("EASY  •  OFFICIAL LEVEL",15,c+Vec2(15,-22),CYAN));
 auto play=button("PLAY LEVEL",26,{z.width/2,z.height*.22f},[](Ref*){Director::getInstance()->replaceScene(TransitionFade::create(.2f,GameplayScene::createScene()));});
 auto back=button("BACK",20,{65,38},[](Ref*){Director::getInstance()->replaceScene(MainMenuScene::createScene());});
 auto m=Menu::create(play,back,nullptr);m->setPosition(Vec2::ZERO);s->addChild(m);return s;
}
Scene* GameplayScene::createScene(){return GameplayScene::create();}
bool GameplayScene::init(){
 if(!Scene::init())return false;background(this);auto z=Director::getInstance()->getVisibleSize();
 world_=DrawNode::create();addChild(world_);player_=Vec2(150,GROUND+22);
 progress_=label("0%",20,{z.width-65,z.height-38},CYAN);addChild(progress_);
 addChild(label("FIRST STEPS",18,{100,z.height-38}));
 message_=label("TAP TO JUMP",18,{z.width/2,z.height-38},PURPLE);addChild(message_);
 auto t=EventListenerTouchOneByOne::create();t->onTouchBegan=[](Touch*,Event*){return true;};
 t->onTouchEnded=[this](Touch*,Event*){if(!ended_)jump();};_eventDispatcher->addEventListenerWithSceneGraphPriority(t,this);
 scheduleUpdate();return true;
}
void GameplayScene::jump(){if(grounded_){velocity_=650;grounded_=false;message_->setString("NICE!");}}
void GameplayScene::update(float dt){
 if(ended_)return;dt=std::min(dt,1.0f/30.0f);distance_+=270*dt;velocity_-=1750*dt;player_.y+=velocity_*dt;
 if(player_.y<=GROUND+22){player_.y=GROUND+22;velocity_=0;grounded_=true;}
 world_->clear();auto z=Director::getInstance()->getVisibleSize();
 world_->drawSolidRect({0,GROUND-8},{z.width,GROUND},Color4F(.08f,.12f,.24f,1));
 world_->drawSegment({0,GROUND},{z.width,GROUND},3,Color4F(.1f,.85f,1,1));
 Rect p(player_.x-19,player_.y-19,38,38);
 world_->drawSolidRect(player_-Vec2(22,22),player_+Vec2(22,22),Color4F(.1f,.9f,1,1));
 const std::array<float,7> obs{{430,690,980,1210,1490,1740,1940}};
 for(float o:obs){float x=150+o-distance_;if(x<-35||x>z.width+35)continue;
  Vec2 tri[3]={{x-18,GROUND},{x,GROUND+42},{x+18,GROUND}};
  world_->drawSolidPoly(tri,3,Color4F(.95f,.22f,.55f,1));
  if(p.intersectsRect(Rect(x-15,GROUND,30,39))){finish(false);return;}
 }
 int pct=std::min(100,(int)(distance_/2100*100));progress_->setString(std::to_string(pct)+"%");
 if(distance_>=2100)finish(true);
}
void GameplayScene::finish(bool won){
 ended_=true;message_->setString(won?"LEVEL COMPLETE!":"CRASHED!");
 auto z=Director::getInstance()->getVisibleSize();
 auto retry=button(won?"PLAY AGAIN":"RETRY",26,{z.width/2,z.height*.42f},[](Ref*){Director::getInstance()->replaceScene(TransitionFade::create(.2f,GameplayScene::createScene()));});
 auto levels=button("LEVELS",20,{z.width/2,z.height*.30f},[](Ref*){Director::getInstance()->replaceScene(LevelSelectScene::createScene());});
 auto m=Menu::create(retry,levels,nullptr);m->setPosition(Vec2::ZERO);addChild(m,10);
}