#include "AppDelegate.h"
#include "GameScenes.h"
USING_NS_CC;
void AppDelegate::initGLContextAttrs(){ GLContextAttrs a={8,8,8,8,24,8,0}; GLView::setGLContextAttrs(a); }
bool AppDelegate::applicationDidFinishLaunching(){
 auto d=Director::getInstance(); auto v=d->getOpenGLView();
 if(!v){v=GLViewImpl::create("Dynamic Dash");d->setOpenGLView(v);}
 v->setDesignResolutionSize(960,540,ResolutionPolicy::SHOW_ALL);
 d->setAnimationInterval(1.0/60.0); d->setDisplayStats(false);
 d->runWithScene(LoadingScene::createScene()); return true;
}
void AppDelegate::applicationDidEnterBackground(){Director::getInstance()->stopAnimation();}
void AppDelegate::applicationWillEnterForeground(){Director::getInstance()->startAnimation();}