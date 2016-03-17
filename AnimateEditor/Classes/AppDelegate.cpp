#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "CocosQtPort/CCQGLView.h"
#include "qtedit.h"
USING_NS_CC;

//AppDelegate::AppDelegate() {
//
//}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
	auto director = Director::getInstance();
	GLViewImpl* glview = NULL;
	if (!glview)
	{
		glview = GLViewImpl::create("My Game");
		ShowWindow(glview->getWin32Window(), SW_HIDE);
		glview->setFrameSize(m_ParentRect.right - m_ParentRect.left, m_ParentRect.bottom - m_ParentRect.top);
		director->setOpenGLView(glview);
	}
	
	director->setProjection(Director::Projection::_2D);
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);


	ShowWindow(glview->getWin32Window(), SW_SHOW);
	auto frameSize = glview->getFrameSize();
	glview->setFrameSize(frameSize.width, frameSize.height);
	glview->setDesignResolutionSize(frameSize.width, frameSize.height, ResolutionPolicy::NO_BORDER);
	::SetParent(glview->getWin32Window(), m_ParentHwnd);
	SetWindowLong(glview->getWin32Window(), GWL_STYLE, GetWindowLong(glview->getWin32Window(), GWL_STYLE) & ~WS_CAPTION);
	::SetWindowPos(glview->getWin32Window(), HWND_TOP, 0, 0, frameSize.width, frameSize.height, SWP_NOCOPYBITS);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::setParent(HWND hwnd, RECT rect)
{
	m_ParentHwnd = hwnd;
	m_ParentRect.left = rect.left;
	m_ParentRect.top = rect.top;
	m_ParentRect.right = rect.right;
	m_ParentRect.bottom = rect.bottom;
}