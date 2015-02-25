#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MenuScene.h"
#include "MenuSceneLoader.h"
#include "GameMacro.h"

USING_NS_CC;
USING_NS_CC_BUILDER;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("sprites.plist");
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();
    

    director->setOpenGLView(eglView);
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

   // Size screenSize = eglView->getFrameSize();

    auto pFileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    
    auto screenSize = eglView->getFrameSize();
    
    if (screenSize.width > 320)
    {
        searchPaths.push_back("images/hd");
        
        director->setContentScaleFactor(2.0);
    }
    else
    {
        searchPaths.push_back("images/sd");
        
    }
    searchPaths.push_back("Maps");
    
    pFileUtils->setSearchPaths(searchPaths);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");

    eglView->setDesignResolutionSize(480.0, 320.0, ResolutionPolicy::SHOW_ALL);
    
    if(UserDefault::getInstance()->getIntegerForKey("level"))
    {
        _level = UserDefault::getInstance()->getIntegerForKey("level");
    }
    else
    {
        this->setLevel(1);
    }
    
    MenuScene *menuScene = NULL;
    
    NODE_CREATE_BY_CCB_START("MenuScene", MenuSceneLoader::loader(), "MenuScene.ccbi", MenuScene *, menuScene);

    // create a scene. it's an autorelease object
    auto scene = Scene::create();
    scene->addChild(menuScene);

    // run
    director->runWithScene(scene);
    NODE_CREATE_BY_CCB_END

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::setLevel(unsigned int level)
{
    _level = level;
    
    UserDefault::getInstance()->setIntegerForKey("level", _level);
    UserDefault::getInstance()->flush();
}

unsigned int AppDelegate::getLevel()
{
    return _level;
}